#pragma once

#include "CubicInterpolationSplain/CubicInterpolationSplain.hpp"
#include "SmoothingInterpolationSplain/SmoothingInterpolationSplain.hpp"
#include "spliting.hpp"
#include <fstream>

namespace
{
template <typename T = double>
std::array<T, 3> getDerivatives(T x, std::array<std::function<T(T)>,3> const &F)
{
    return af::Point<T>{F[0](x), F[1](x), F[2](x)};
}
}

template <typename T = double>
void createTableCSV(T a, T b, size_t amount, std::vector<T> const &steps, T r, std::string const& path = "")
{
    for (auto &function : functions<T>)
    {
        std::ofstream file(path + function.first + ".csv", std::ios::out);
        // uniform step
        for (auto step : steps)
        {
            auto grid{af::createGrid(a, b, amount, step)};

            af::CubicInterpolationSplain splainCubic;
            af::SmoothingInterpolationSplain splainSmooth;
            {
                std::vector<af::Point<T>> points(grid.size());
                std::vector<T> fTable(grid.size());
                for (size_t i{}; i < grid.size(); ++i)
                {
                    points[i] = {grid[i]};
                    fTable[i] = function.second[0](grid[i]);
                }
                splainCubic.update(points, fTable);
                splainSmooth.update(points, fTable);
            }

            {
                auto stepP{(b - a) / amount * step};
                file << function.first << ",,S1 - cubic splain,, S2 - smooth splain\nstep = " << stepP
                     << ",step^2 = " << stepP * stepP
                     << "\nx,F(x),S1(x),S2(x),,,x,F`(x),S1`x),S2`(x),,,x,F``(x),S1``(x),S2``(x)\n";
            }
            auto skew1{std::array<T, 3>{}}, skew2{skew1};
            for (size_t j{}; j < grid.size() - 1; ++j)
            {
                auto x{af::spliting(grid[j], grid[j + 1], amount)};
                for (size_t i{}; i < x.size() - 1; ++i)
                {
                    auto s1{splainCubic.getValue({x[i]})};
                    auto s2{splainSmooth.getValue({x[i]})};
                    auto f{getDerivatives(x[i], function.second)};
                    file <<
                        x[i] << ',' << f[0] << ',' << s1[0] << ',' << s2[0] << ",,," <<
                        x[i] << ',' << f[1] << ',' << s1[1] << ',' << s2[1] << ",,," <<
                        x[i] << ',' << f[2] << ',' << s1[2] << ',' << s2[2] << '\n';
                    skew1 =
                    {
                        std::max(skew1[0], fabs(f[0] - s1[0])),
                        std::max(skew1[1], fabs(f[1] - s1[1])),
                        std::max(skew1[2], fabs(f[2] - s1[2]))
                    };
                    skew2 =
                    {
                        std::max(skew2[0], fabs(f[0] - s2[0])),
                        std::max(skew2[1], fabs(f[1] - s2[1])),
                        std::max(skew2[2], fabs(f[2] - s2[2]))
                    };
                }
            }
            auto s1{splainCubic.getValue({grid.back()})};
            auto s2{splainSmooth.getValue({grid.back()})};
            auto f{getDerivatives(grid.back(), function.second)};
            file <<
                    grid.back() << ',' << f[0] << ',' << s1[0] << ',' << s2[0] << ",,," <<
                    grid.back() << ',' << f[1] << ',' << s1[1] << ',' << s2[1] << ",,," <<
                    grid.back() << ',' << f[2] << ',' << s1[2] << ',' << s2[2] << '\n' <<
                    "max|F(x) - S1(x)|= " << std::max(skew1[0], fabs(f[0] - s1[0])) << ',' <<
                    ",,max|F(x) - S2(x)|= " << std::max(skew2[0], fabs(f[0] - s2[0])) << ",,," <<
                    "max|F`(x) - S1`(x)|= " << std::max(skew1[1], fabs(f[1] - s1[1])) << ',' <<
                    ",,max|F`(x) - S2`(x)|= " << std::max(skew2[1], fabs(f[1] - s2[1])) << ",,," <<
                    "max|F``(x) - S1``(x)|= " << std::max(skew1[2], fabs(f[2] - s1[2])) << ',' << ",,max|F``(x) - S2``(x)|= " << std::max(skew2[2], fabs(f[2] - s2[2])) << "\n\n\n";
        }

        // // ununiform step
        // auto grid{af::spliting<T>(b, a, amount, function.second, r)};
        // af::CubicInterpolationSplain splain;
        // {
        //     std::vector<T> fValues;
        //     fValues.reserve(grid.size());
        //     for (const auto& point : grid)
        //         fValues.emplace_back(point[0]);

        //     splain.update(grid, fValues);
        // }

        // file << function.first <<
        //     "\nr = " << r <<
        //     "\nx,F(x),S(x),,,x,F(x)`,S(x)`,,,x,F(x)``,S(x)``\n";
        // auto maxUncertainty = std::vector<T>(3, 0);
        // for (size_t j{}; j < grid.size() - 1; ++j)
        // {
        //     auto newGrid{af::spliting(function.second, grid[j][0], grid[j + 1][0], amount)};
        //     for (size_t i{}; i < newGrid.size() - 1; ++i)
        //     {
        //         auto result = splain.getValue({newGrid[i][0]});
        //         file <<
        //             newGrid[i][0] << ',' << function.second[0](newGrid[i][0]) << ',' << result[0] << ",,," <<
        //             newGrid[i][0] << ',' << newGrid[i][1] << ',' << result[1] << ",,," <<
        //             newGrid[i][0] << ',' << newGrid[i][2] << ',' << result[2] << '\n';
        //         maxUncertainty =
        //         {
        //             std::max(maxUncertainty[0], fabs(result[0] - function.second[0](newGrid[i][0]))),
        //             std::max(maxUncertainty[1], fabs(result[1] - newGrid[i][1])),
        //             std::max(maxUncertainty[2], fabs(result[2] - newGrid[i][2]))
        //         };
        //     }
        // }
        // auto result = splain.getValue({grid.back()[0]});
        // file << grid.back()[0] << ',' << function.second[0](grid.back()[0]) << ',' << result[0] << ",,,"
        //      << grid.back()[0] << ',' << grid.back()[1] << ',' << result[1] << ",,,"
        //      << grid.back()[0] << ',' << grid.back()[2] << ',' << result[2] << '\n';
        // maxUncertainty = {std::max(maxUncertainty[0], fabs(result[0] - function.second[0](grid.back()[0]))),
        //                   std::max(maxUncertainty[1], fabs(result[1] - grid.back()[1])),
        //                   std::max(maxUncertainty[2], fabs(result[2] - grid.back()[2]))};
        // file << "max|F(x) - S(x)|= " << maxUncertainty[0] << ",,,,,"
        //      << "max|F`(x) - S`(x)|= " << maxUncertainty[1] << ",,,,,"
        //      << "max|F``(x) - S``(x)|= " << maxUncertainty[2] << "\n\n\n";
        file.close();
    }
}
