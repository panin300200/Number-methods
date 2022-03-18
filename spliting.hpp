#include "CubicInterpolationSplain.hpp"
#include "constants.hpp"

namespace af
{
template <typename T = double> std::vector<Point<T>> spliting(T left, T right, size_t amount, T r = 1)
{
    std::vector<Point<T>> result;
    result.reserve(amount);
    auto step{(right - left) / amount};
    for (auto current = left; fabs(right - current) > eps<double>; ++current)
    {
        result.emplace_back(Point<T>{step, .0, .0});
        step *= r;
    }
    return result;
}
} // namespace af
