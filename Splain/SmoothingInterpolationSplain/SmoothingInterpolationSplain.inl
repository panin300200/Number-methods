#include "SmoothingInterpolationSplain.hpp"

template <typename T>
constexpr T af::SmoothingInterpolationSplain<T>::transferToMasterElement(size_t numSegment, T x) const noexcept
{
    return T(2.) * (x - grid[numSegment][0]) / (grid[numSegment + 1][0] - grid[numSegment][0]) - T(1.);
}

template <typename T>
constexpr T af::SmoothingInterpolationSplain<T>::basisFunction(size_t numSegment, T ksi)
{
    switch (numSegment)
    {
        case 1: return T(0.5) * (1 - ksi);
        case 2: return T(0.5) * (1 + ksi);
        default: throw std::invalid_argument("There is a problem with the base function number!");
    }
}

template <typename T>
constexpr T af::SmoothingInterpolationSplain<T>::derivBasisFunction(size_t numSegment)
{
    switch (numSegment)
    {
    case 1:
        return -0.5;
    case 2:
        return 0.5;
    default:
        throw std::invalid_argument("There is a problem with the base function derivative number!");
    }
}

template<typename T>
void af::SmoothingInterpolationSplain<T>::update(std::vector<af::Point<T>> const & points, std::vector<T> const & fValues)
{
    size_t amountSegment = points.size();

    if (amountSegment-- <= 1)
        throw std::invalid_argument("A few amount of point!");

    grid = points;
    a.resize(amountSegment + 1);

    // a = diagonal[0] - lower diagonal, b = diagonal[1] - main diagonal of matrix, c = diagonal[2] - upper diagonal
    std::vector diagonal(amountSegment + 1, std::array<T, 3>{});

    // lambda-function of assembling
    auto assembling = [&](size_t i, Point<T> const &point, T fVal, T weight)
    {
        T ksi = transferToMasterElement(i, point[0]);

        // date of basis functions
        T fi1 = basisFunction(1, ksi);
        T fi2 = basisFunction(2, ksi);

        // calculate diagonals
        auto coef = (1. - smooth) * weight;
        // b[i]
        diagonal[1][i]     += coef * fi1 * fi1;
        // b[i+1]
        diagonal[1][i + 1] += coef * fi2 * fi2;
        // a[i+1]
        diagonal[0][i + 1] += coef * fi1 * fi2;
        // c[i]
        diagonal[2][i]     += coef * fi2 * fi1;

        // calculate alpha coefficcients
        a[i]     += coef * fi1 * fVal;
        a[i + 1] += coef * fi2 * fVal;
    };

    for (size_t i{}; i < amountSegment; i++)
    {
        // coefficcient of weight
        assembling(i, grid[i], fValues[i], 1.);
        assembling(i, grid[i + 1], fValues[i + 1], 1.);

        // usefull coefficcient
        auto beta = T(1.) / (grid[i + 1][0] - grid[i][0]) * smooth;
        // b[i]
        diagonal[1][i]     += beta;
        // b[i+1]
        diagonal[1][i + 1] += beta;
        //a[i+1]
        diagonal[0][i + 1] -= beta;
        //c[i]
        diagonal[2][i]     -= beta;
    }

    // go to forward
    for (size_t i{1}; i < amountSegment + 1; i++)
    {
        auto buf = diagonal[0][i] / diagonal[1][i - 1];
        // b[i]
        diagonal[1][i]  -= buf * diagonal[2][i - 1];
        // alpha[i]
        a[i] -= buf * a[i - 1];
    }

    //alpha[amountSegment] /= b[amountSegment]
    a[amountSegment] /= diagonal[1][amountSegment];
    //go to back
    for (size_t i{amountSegment - 1}; i < amountSegment ; --i)
        // alpha[i] = (alpha[i] - alpha[i+1] * c[i]) / b[i]
        a[i] = (a[i] - a[i + 1] * diagonal[2][i]) / diagonal[1][i];
}

template <typename T>
af::SplainValue<T> af::SmoothingInterpolationSplain<T>::getValue(const af::Point<T> & point) const
{
    size_t amountSegment = grid.size();
    if (amountSegment-- <= 1)
        throw std::invalid_argument("Grid is so small");

    for(size_t i{}; i < amountSegment; i++)
    {
        if(point[0] > grid[i][0] && point[0] < grid[i + 1][0] ||
            fabs(point[0] - grid[i][0]) < eps<T> ||
            fabs(point[0] - grid[i + 1][0]) < eps<T>)
        {
            T ksi = transferToMasterElement(i, point[0]);

            return
            {
                a[i] * basisFunction(1, ksi) + a[i + 1] * basisFunction(2, ksi),

                (a[i] * derivBasisFunction(1) + a[i + 1] * derivBasisFunction(2)) * 2. / (grid[i + 1][0] - grid[i][0]),

                T(0.)
            };
        }
    }
    throw std::domain_error("Point not found on segments");
}
