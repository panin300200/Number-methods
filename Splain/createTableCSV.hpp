#pragma once

#include "CubicInterpolationSplain/CubicInterpolationSplain.hpp"
#include "../constants.hpp"
#include "spliting.hpp"
#include <fstream>

template <typename T = double>
void createTableCSV(T a, T b, size_t amount, std::vector<T> const &steps, std::string const& path)
{
    for (auto &function : functions<T>)
    {
        std::ofstream file(path + function.first + ".csv", std::ios::out);
        for (auto &step : steps)
        {
            auto grid{af::spliting(function.second, a, b, amount, step)};

            af::CubicInterpolationSplain splain;
            {
                std::vector<T> fValues;
                fValues.reserve(grid.size());
                for (const auto &point : grid)
                    fValues.emplace_back(function.second[0](point[0]));

                splain.update(grid, fValues);
            }

            auto printStep{(b - a) / amount * step};
            file << function.first << "\nstep = " << printStep <<
                    ",step^2 = " << printStep * printStep <<
                    "\nx,F(x),S(x),,,x,F(x)`,S(x)`,,,x,F(x)``,S(x)``\n";
            auto maxUncertainty = std::vector<T>(3, 0);
            for (size_t j{}; j < amount; ++j)
            {
                auto newGrid{af::spliting(function.second,
                                            grid[j][0],
                                            grid[j + 1][0],
                                            amount,
                                            step)};
                for (size_t i{}; i < amount; ++i)
                {
                    auto result = splain.getValue({newGrid[i][0]});
                    file << newGrid[i][0] << ',' << function.second[0](newGrid[i][0]) << ',' << result[0] << ",,,"
                         << newGrid[i][0] << ',' << function.second[1](newGrid[i][0]) << ',' << result[1] << ",,,"
                         << newGrid[i][0] << ',' << function.second[2](newGrid[i][0]) << ',' << result[2] << '\n';
                    maxUncertainty = {std::max(maxUncertainty[0], fabs(result[0] - function.second[0](newGrid[i][0]))),
                                      std::max(maxUncertainty[1], fabs(result[1] - newGrid[i][1])),
                                      std::max(maxUncertainty[2], fabs(result[2] - newGrid[i][2]))};
                }
            }
            auto result = splain.getValue({grid.back()[0]});
            file << grid.back()[0] << ',' << function.second[0](grid.back()[0]) << ',' << result[0] << ",,,"
                 <<
                    grid.back()[0] << ',' << function.second[1](grid.back()[0]) << ',' << result[1] << ",,,"
                 << grid.back()[0] << ',' << function.second[2](grid.back()[0]) << ',' << result[2] << '\n';
            maxUncertainty =
                {
                    std::max(maxUncertainty[0],
                            fabs(result[0] - function.second[0](grid.back()[0]))),
                    std::max(maxUncertainty[1], fabs(result[1] - grid.back()[1])),
                    std::max(maxUncertainty[2], fabs(result[2] - grid.back()[2]))
                };
            file << "max|F(x) - S(x)|= " << maxUncertainty[0] << ",,,,,"
                 << "max|F`(x) - S`(x)|= " << maxUncertainty[1] << ",,,,,"
                 << "max|F``(x) - S``(x)|= " << maxUncertainty[2] << "\n\n\n";
        }
        file.close();
    }
}
