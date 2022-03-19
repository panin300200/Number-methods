#include <string>
#include <unordered_map>
#include <algorithm>

using COMMAND = std::string;

using CLI = std::unordered_map<COMMAND, std::function<void(COMMAND)>>;

CLI menu{
    {"-h", [](COMMAND const &command = "") {}},
    {"-help", [](COMMAND const &command = "") {}},
    {"-h", [](COMMAND const &command = "") {}},
    {"-help", [](COMMAND const &command = "") {}},
	{"-h", [](COMMAND const &command = ""){}},
	{"-help", [](COMMAND const &command = ""){}},
	{"-h", [](COMMAND const &command = ""){}},
	{"-help", [](COMMAND const &command = ""){}},
};
