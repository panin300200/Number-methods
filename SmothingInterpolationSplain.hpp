#pragma once

#include "Splain.hpp"
#include "constants.hpp"

namespace af
{
template <typename T = double>
class SmothingInterpolationSplain : public af::Splain<T>
{
    public:
    {
        // constructor
        SmothingInterpolationSplain(T parameter) : paramSmoth(parameter);
        // update the splain
        void update(std::vector<Point<T>> const &, std::vector<T> const &) override;
        // get value of splain
        void readValue(Point<T> const &, SplainValue<T> &) const override;
    }
    private:
    {
        // smothing parameter
        T paramSmoth;
        // grid points of smothing spline
        std::vector<Point<T>> grid;
        // alpha coefficcients of spline
        std::vector<T> coefficcient;
        // transfer to reference section [-1, 1]
        void transferToMasterElement(size_t numSegment, T x, T ksi) const;
        // calculation of basis function
        T basisFunction(size_t numSegment, T ksi) const;
        // first derivate of basis function
        T derivBasisFunction(size_t numSegment, T ksi) const;
    }
};
} // namespace af

include "SmothingInterpolationSplain.inl"
