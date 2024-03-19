#include "HelperFunctions.h"
#include <fstream>
#include <map>
#include <filesystem>
#include <iostream>

map<string, string> config() {
	int checkflag = 0;

	for (const auto& entry : filesystem::directory_iterator(filesystem::current_path())) {
		if (entry.path().filename() == "config.txt") {
			checkflag = 1;
		}
	}

	if (!checkflag) {
		ofstream config("config.txt");
		config.close();
	}

	string line = "";
	string key = "";
	string value = "";
	map<string, string> configMap = map<string, string>();

	ifstream config("config.txt");
	
	while (config.good()) {
		getline(config, line);

		if (line.empty()) {
			continue;
		}

		istringstream ss(line);
		ss >> key >> value;
		configMap[key] = value;
	}

	config.close();

	return configMap;
}