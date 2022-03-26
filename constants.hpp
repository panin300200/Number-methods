#pragma once

#include <array>
#include <string>
#include <functional>
#include <initializer_list>
#include <cmath>

template <typename T = double>
constexpr T eps{T(1e-15)};

//? 1'048'576 - max amount strings for csv
//* (1'048'576 - 4) / 3 = 349'524
constexpr auto maxAmountStrings{349'524ul};

template <typename T = double>
const std::initializer_list<std::pair<std::string,
									  std::array<std::function<T(T)>,3>>> functions
{
    {
		std::string("Table of f(x) = x"),
		std::array<std::function<T(T)>,3>
		{
			[](T x) { return x; },
			[](T) { return 1; },
			[](T) { return 0; }
		}
	},
    {
        std::string("Table of f(x) = x^2"),
		std::array<std::function<T(T)>,3>
        {
			[](T x) { return x * x; },
			[](T x) { return 2 * x; },
			[](T)   { return 2; }
		}
    },
	{
        std::string("Table of f(x) = x^3"),
		std::array<std::function<T(T)>,3>
        {
			[](T x) { return x * x * x; },
			[](T x) { return 3 * x * x; },
			[](T x) { return 6 * x; }
		}
    },
	{
		std::string("Table of f(x) = x^4"),
		std::array<std::function<T(T)>,3>
		{
		   [](T x) { return x * x * x * x; },
		   [](T x) { return 4 * x * x * x; },
		   [](T x) { return 12 * x * x; }
		}
	},
    {
		std::string("Table of f(x) = sin(x)"),
		std::array<std::function<T(T)>,3>
		{
			[](T x) { return std::sin(x); },
			[](T x) { return std::cos(x); },
			[](T x) { return -std::sin(x);}
		}
	}
};
