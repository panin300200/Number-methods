#include <iostream>
#include "CubicInterpolationSplain.hpp"
#include "spliting.hpp"

int main()
{
    auto grid{af::spliting(0., 2., 3)};
	std::vector<double> fValues(grid.size());
	for (size_t i = 0; i < grid.size(); ++i)
		fValues[i] = grid[i][0];

    af::CubicINterpolationSplain splain;
	splain.update(grid, fValues);

	return 0;
}
