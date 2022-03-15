#include "CubicINterpolationSplain.hpp"

template <typename T>
void af::CubicINterpolationSplain<T>::update(std::vector<af::Point<T>> const & points, std::vector<T> const & fValues)
{
    size_t amountSegment = points.size() - 1;

    this->grid.resize(amountSegment + 1);
	std::copy(points.begin(), points.end(), grid.begin());

    coefficient.resize(amountSegment);
	if (!amountSegment) return;

	T current{}, next{}; // h (step)
    std::vector<T> fi(--amountSegment); // --amountSegment

	// get coefficient [a, b, d] and fi
    for (size_t i = 0; i < amountSegment; ++i)
	{
		current = grid[i + 1][0] - grid[i][0];
		next = grid[i + 2][0] - grid[i + 1][0];

        //  b[i] = 2 * (current + next)
        coefficient[i][1] = 2 * (current + next);

		// a[i + 1] = current
		coefficient[i + 1][0] = current;

		// d[i] = next
		coefficient[i][3] = next;

		fi[i] = 3. * ((fValues[i + 2] - fValues[i + 1]) / next - (fValues[i + 1] - fValues[i]) / current);
	}

	// to forward
	for (size_t i = 1; i < amountSegment; ++i)
	{
		// a[i] / b[i - 1]
		auto buf = coefficient[i][0] / coefficient[i - 1][1];

		// b[i] = a[i] / b[i - 1] * d[i - 1]
        coefficient[i][1] -= buf * coefficient[i - 1][3];

        fi[i] -= buf * fi[i - 1];
	}

	// to back
	// c[amountSegment - 1] = fi[amountSegment - 2] / b[amountSegment - 2]
	coefficient[amountSegment - 1][2] = fi[amountSegment - 2] / coefficient[amountSegment - 2][1];
	for (size_t  i = amountSegment - 3; i < amountSegment; --i)
	{
		// c[i + 1] = (fi[i] - c[i + 2] * d[i]) / b[i]
		coefficient[i + 1][2] = (fi[i] - coefficient[i + 2][2] * coefficient[i][3]) / coefficient[i][1];
	}
	// c[0] = 0.0
	coefficient[0][2] = 0.;

	// coefficient of splain
	for (size_t i = 0; i < amountSegment - 1; ++i)
	{
        current = grid[i + 1][0] - grid[i][0];
        coefficient[i][0] = fValues[i];
        coefficient[i][1] =
			(fValues[i + 1] - fValues[i]) / current - (coefficient[i + 1][2] + 2. * coefficient[i][2]) * current / 3.;
        coefficient[i][3] = (coefficient[i + 1][2] - coefficient[i][2]) / current / 3.;
    }

	// last coefficient
	current = grid[amountSegment][0] - grid[amountSegment - 1][0];
    coefficient[amountSegment - 1][0] = fValues[amountSegment - 1];
    coefficient[amountSegment - 1][1] =
		(fValues[amountSegment] - fValues[amountSegment - 1]) / current - 2. * coefficient[amountSegment - 1][2]  * current / 3.;
    coefficient[amountSegment - 1][3] = -coefficient[amountSegment - 1][2] / current / 3.;
}

template <typename T>
void af::CubicINterpolationSplain<T>::readValue(af::Point<T> const &point, af::SplainValue<T> &result) const
{
	for (size_t i = 0; i < grid.size() - 1; ++i)
	{
		if (point[0] > grid[i][0] && point[0] < grid[i + 1][0] ||
			fabs(point[0] - grid[i][0]) < eps ||
			fabs(point[0] - grid[i + 1][0]) < eps)
		{
			T distance = fabs(point[0] - grid[i][0]);
			result[0] =
				coefficient[i][0] + coefficient[i][1] * distance + coefficient[i][2] * distance * distance + coefficient[i][3] * distance * distance * distance;
            result[1] =
				coefficient[i][1] + 2. * coefficient[i][2] * distance + 3. coefficient[i][3] * distance * distance;
            result[2] =
				2. * coefficient[i][2] + 6. coefficient[i][3] * distance;
			return;
        }
	}
	throw std::domain_error("Point out of the domain");
}
