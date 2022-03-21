#pragma once

#include "Splain.hpp"
#include "constants.hpp"

namespace af
{
template <typename T = double>
class SmoothingInterpolationSplain : public af::Splain<T>
{

    private:
        // Smoothing parameter
        T paramSmooth;
        // grid points of Smoothing spline
        std::vector<Point<T>> grid;
        // alpha coefficcients of spline
        std::vector<T> coefficcient;
        // transfer to reference section [-1, 1]
        T transferToMasterElement(size_t numSegment, T x) const;
        // calculation of basis function
        T basisFunction(size_t numSegment, T ksi) const;
        // first derivate of basis function
        T derivBasisFunction(size_t numSegment) const;

    public:
        // constructor
        SmoothingInterpolationSplain(T parameter) : paramSmooth(parameter){}
        // update the splain
        void update(std::vector<Point<T>> const &, std::vector<T> const &) override;
        // get value of splain
        SplainValue<T> getValue(const Point <T> &point) const override;
};
} // namespace af

#include "SmoothingInterpolationSplain.inl"
