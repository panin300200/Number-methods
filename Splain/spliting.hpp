#include "Splain.hpp"
#include "../constants.hpp"

namespace af
{
template <typename T = double>
std::vector<T> createGrid(T left, T right, size_t amount, T r = 1)
{
    std::vector<T> grid;
    grid.reserve(amount + 1);

    auto step{(right - left) / amount};
    for (auto current = left; right - current > eps<T>; current += step * r)
    	grid.emplace_back(current);
    grid.emplace_back(right);

    return grid;
}

namespace
{
template <typename T = double>
bool compare(T left, T right, T current)
{
    return left < right
            ? right - current > eps<T>
            : current - right > eps<T>;
}

template <typename T = double>
T position(T current, T step, T left, T right)
{
    return left < right
            ? current + step
            : current - step;
}
}

template <typename T = double>
std::vector<T> spliting(T left, T right, size_t amount, T r = 1)
{
    std::vector<T> grid;
    grid.reserve(amount + 1);

    auto step{fabs(left - right) / amount};
    for (auto current{left}; compare(left, right, current); current = position(current, step *= r, left, right))
            grid.emplace_back(current);
    grid.emplace_back(right);

    if (left > right) std::reverse(grid.begin(), grid.end());
    return grid;
}
} // namespace af
