#include "Splain.hpp"
#include "../constants.hpp"
#include <functional>

namespace af
{
template <typename T = double>
std::vector<Point<T>> spliting(Point<std::function<T(T)>> F, T left, T right, size_t amount, T r = 1)
{
    std::vector<Point<T>> grid;
    grid.reserve(amount);
    auto step{(right - left) / amount};
    for (auto current = left; right - current > eps<T>; current += step * r)
    	grid.emplace_back(Point<T>{current, F[1](current), F[2](current)});
    grid.emplace_back(Point<T>{right, F[1](right), F[2](right)});
    return grid;
}
} // namespace af
