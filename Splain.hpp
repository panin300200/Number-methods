#pragma once

#include <array>
#include <vector>

namespace af
{
template <typename T = double> using Point = std::array<T, 3>;
template <typename T = double> using SplainValue = Point<T>;

template <typename T = double> 
class Splain
{
  public:
    /**
     * first is anchor points
     * second is values of tables function
     */
    virtual void update(std::vector<Point<T>> const &, std::vector<T> const &) = 0;
    /**
     * first is point
     * second is tabel function values
     */
    virtual void readValue(Point<T> const &, SplainValue<T> &) const = 0;

};
} // namespace af
