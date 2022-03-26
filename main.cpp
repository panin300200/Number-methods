#include "Splain/createTableCSV.hpp"
#include "interface/CLI.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        NoArg<double> noArg; OneArg<double> oneArg;
        for (int i = 1; i < argc; ++i)
        {
            if (auto f{menuPrint<double>.find(argv[i])}; f != menuPrint<double>.end())
                f->second(noArg);
            else if (auto f{menuSet<double>.find(argv[i])};
                     f != menuSet<double>.end())
                if (++i < argc)
                    f->second(oneArg, argv[i]);
                else
                    throw std::runtime_error("Invalid option arguments.");
            else
                throw std::runtime_error("Invalid option use option -h|-help for more info");
        }
        noArg.print();

        double a{oneArg.aValue}, b{oneArg.bValue};
        size_t amount{oneArg.segmentsAmount};
        while (a >= b || amount < 2 || amount >= maxAmountStrings)
        {
            std::cout << "input [a, b] (must: a < b) and separate amount (>= 10 && < 349 524): ";
            std::cin >> a >> b >> amount;
        }

        createTableCSV<double>(a, b, amount, {1., .5, .25}, 1.5, functions<double>, oneArg.path);
    }
    catch (std::exception const &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
