#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip> //std::setw

using json = nlohmann::json;

int main()
{
	json j1;
	// add a number that is stored as double (note the implicit conversion of j to an object)
	j1["pi"] = 3.141;

	// add a Boolean that is stored as bool
	j1["happy"] = true;

	// add a string that is stored as std::string
	j1["name"] = "Niels";

	// add another null object by passing nullptr
	j1["nothing"] = nullptr;

	// add an object inside the object
	j1["answer"]["everything"] = 42;

	// add an array that is stored as std::vector (using an initializer list)
	j1["list"] = { 1, 0, 2 };

	// add another object (using an initializer list of pairs)
	j1["object"] = { {"currency", "USD"}, {"value", 42.99} };

	std::string s = j1.dump(4);
	std::cout << s << std::endl;

	auto j2 = json::parse(s);

	// read a JSON file
	std::ifstream i("file.json");
	json j3;
	i >> j3;

	// write prettified JSON to another file
	std::ofstream o("pretty.json");
	json j4;
	o << std::setw(4) << j4 << std::endl;

	return 0;
}