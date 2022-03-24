#include <gtest/gtest.h>
#include "CubicInterpolationSplain.hpp"

TEST(CubicInterpolationSplain, equalSplit)
{
    try
    {
        std::vector grid{
			af::Point<double>{},
			af::Point<double>{1.},
			af::Point<double>{2.}
		};
        std::vector<double> fValues{0., 1., 2.};

        af::CubicInterpolationSplain splain;
        splain.update(grid, fValues);

        EXPECT_EQ(1.5, splain.getValue(af::Point<double>{1.5})[0]);
        EXPECT_EQ(1., splain.getValue(af::Point<double>{1.})[0]);
        EXPECT_EQ(2., splain.getValue(af::Point<double>{1.5})[0]);
    }
    catch (std::exception const &ex)
    {
        EXPECT_TRUE(false) << ex.what();
    }
}

TEST(CubicInterpolationSplain, unequalSplit)
{
    try
    {
        std::vector grid{
			af::Point<double>{},
			af::Point<double>{1.},
			af::Point<double>{3.},
			af::Point<double>{7.}
		};
        std::vector fValues{0., 1., 3., 7.};

        af::CubicInterpolationSplain splain;
        splain.update(grid, fValues);

        EXPECT_EQ(.5, splain.getValue(af::Point<double>{.5})[0]);
        EXPECT_EQ(1., splain.getValue(af::Point<double>{1.})[0]);
        EXPECT_EQ(2., splain.getValue(af::Point<double>{2.})[0]);
        EXPECT_EQ(5., splain.getValue(af::Point<double>{2.})[0]);
    }
    catch (std::exception const &ex)
    {
        EXPECT_TRUE(false) << ex.what();
    }
}
