#include "CubicInterpolationSplain.hpp"
#include "spliting.hpp"
#include <iostream>

int main()
{
    try
    {
        std::vector grid{
            af::Point<double>{},
            af::Point<double>{1.},
            af::Point<double>{3.},
            af::Point<double>{7.}
        };
        std::vector<double> fValues{0., 1., 3., 7.};

        af::CubicInterpolationSplain splain;
        splain.update(grid, fValues);

        af::SplainValue<double> result;
        splain.readValue(af::Point<double>{3}, result);
        std::cout << "f(5) = " << result[0] << '\n';
        std::cin.get();
    }
    catch (std::domain_error ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
