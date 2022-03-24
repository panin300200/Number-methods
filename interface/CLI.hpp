#include "../constants.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

template <typename T = double>
struct NoArg
{
	bool 	help{},
			printFuntions{};

	void print() const
	{
		if (help)
            std::cout << "\n-h|-help :\n\tprint all documentation.\n-f :\n\tprint all function which are using.\n\n-path [path-to-directory]:\n\tset path to directory where will save tabels.\n-a :\n\t set value of a. It is start of range.\n-b :\n\tset value of b. It is end of range.\n-s :\n\tset amount segments value.";
        if (printFuntions)
			for (auto& function : functions<T>)
				std::cout << function.first << '\n';
	}
};

template <typename T = double>
struct OneArg
{
	T aValue{0}, bValue{1};
    std::string path{};
	size_t segmentsAmount{10};
};

template <typename T = double>
const std::unordered_map<std::string, std::function<void(NoArg<T>&)>> menuPrint
{
    {
		"-h",
		[](NoArg<T> &s)
			{
				s.help = true;
				s.print();
				throw std::runtime_error("");
			}
	},
    {
		"-help",
		[](NoArg<T> &s)
			{
				s.help = true;
				s.print();
				throw std::runtime_error("");
			}
	},
    {
		"-f",
		[](NoArg<T> &s) { s.printFuntions = true; }
	}
};

template <typename T = double>
const std::unordered_map<std::string, std::function<void(OneArg<T>&, std::string const&)>> menuSet
{
	{
		"-a",
		[](OneArg<T> &s, std::string const &a)
			{
				try
				{
                    if constexpr (std::is_same<T, float>::value)
                        s.aValue = std::stof(a);
                    else if constexpr (std::is_same<T, double>::value)
                        s.aValue = std::stod(a);
                    else if constexpr (std::is_same<T, long double>::value)
                        s.avalue = std::stold(a);
                }
				catch(...)
				{
					std::cerr << "Invalid value for a" << '\n';
				}
			}
	},
    {
		"-b",
		[](OneArg<T> &s, std::string const &b)
			{
				try
				{
                    if constexpr (std::is_same<T, float>::value)
                        s.bValue = std::stof(b);
                    else if constexpr (std::is_same<T, double>::value)
                        s.bValue = std::stod(b);
                    else if constexpr (std::is_same<T, long double>::value)
                        s.bValue = std::stold(b);
                }
				catch(const std::exception& e)
				{
					std::cerr << "Invalid value for b" << '\n';
				}
			}
	},
    {
		"-s",
		[](OneArg<T> &s, std::string const &amount)
			{
				try
				{
                    s.segmentsAmount = std::stoul(amount);
                }
				catch(const std::exception& e)
				{
					std::cerr << "Invalid value for amount segments" << '\n';
				}
			}
	},
	{
		"-p",
		[](OneArg<T> &s, std::string const& p) { s.path = p; }
	},
    {
		"-path",
		[](OneArg<T> &s, std::string const& p) { s.path = p; }
	},
};
