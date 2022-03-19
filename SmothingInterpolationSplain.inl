#include "SmoothingInterpolationSplain.hpp"

template <typename T>
void af::SmoothingInterpolationSplain<T>::transferToMasterElement(size_t numSegment, T x, T &ksi) const {
    ksi = 2. * (x - grid[numSegment][0]) / (grid[numSegment + 1][0] - grid[numSegment][0]) - 1.
}

template <typename T>
T af::SmoothingInterpolationSplain<T>::basisFunction(size_t numSegment, T ksi) const {
    switch (numSegment) {
        case 1:
            return 0.5 * (1 - ksi);

        case 2:
            return 0.5 * (1 + ksi);

        default:
            throw std::exception("There is a problem with the base function number!");

    }
}

template <typename T>
T af::SmoothingInterpolationSplain<T>::derivBasisFunction(size_t numSegment, T ksi) const {
    switch (numSegment) {
        case 1:
            return -0.5;

        case 2:
            return 0.5;

        default:
            throw std::exception("There is a problem with the base function derivative number!");
    }
}