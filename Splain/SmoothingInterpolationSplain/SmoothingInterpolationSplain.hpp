#pragma once

#include "../Splain.hpp"
#include "../../constants.hpp"

namespace af
{
template <typename T = double> class SmoothingInterpolationSplain : public af::Splain<T>
{
    // transfer to reference section [-1, 1]
    inline constexpr T transferToMasterElement(size_t, T) const noexcept;
    // calculation of basis function
    static inline constexpr T basisFunction(size_t, T);
    // TODO: comment
    static inline constexpr T derivBasisFunction(size_t);

  public:
    // constructor
    SmoothingInterpolationSplain(T p = 0.) : smooth(p) {}
    // update the splain
    void update(std::vector<Point<T>> const &, std::vector<T> const &) override;
    // get value of splain
    SplainValue<T> getValue(const Point<T> &) const override;

  private:
    // Smoothing parameter
    T smooth;
    // grid points of Smoothing spline
    std::vector<Point<T>> grid;
    // alpha coefficcients of spline
    std::vector<T> a;
};
} // namespace af

#include "SmoothingInterpolationSplain.inl"
