#pragma once

#include <array>
#include <vector>
#include <stdexcept>
#include <utility>

namespace af
{
template <typename T = double> using Point = std::array<T, 3>;
template <typename T = double> using SplainValue = Point<T>;

template <typename T = double> class Splain
{
  public:
    Splain()
    {
      if (!std::is_floating_point<T>::value)
        throw std::logic_error("For normal work use floating types : float, double, long double\n");
    }
    /**
     * first is anchor points
     * second is values of tables function
     */
    virtual void update(std::vector<Point<T>> const &, std::vector<T> const &) = 0;
    /**
     * first is point
     * second is tabel function values
     */
    virtual SplainValue<T> getValue(Point<T> const &) const = 0;
};
} // namespace af
