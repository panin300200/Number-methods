#pragma once

#include "Splain.hpp"
#include "constants.hpp"
#include <algorithm>
#include <stdexcept>

namespace af
{
template <typename T = double> class CubicINterpolationSplain : public af::Splain<T>
{
  public:
    void update(std::vector<Point<T>> const &, std::vector<T> const &) override;
    void readValue(Point<T> const &, SplainValue<T> &) const override;

  private:
    /**
     * @brief grid of splain points
     */
    std::vector<Point<T>> grid;
    /**
     * @brief coefficient [a, b, c, d] of cubic interpolation splain
     */
    std::vector<std::array<T, 4>> coefficient;
};
} // namespace af

#include "CubicINterpolationSplain.inl"
