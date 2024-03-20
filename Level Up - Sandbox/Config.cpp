#include "HelperFunctions.h"
#include <fstream>
#include <map>
#include <filesystem>
#include <iostream>

//DEFAULT CONFIGS:
const filesystem::path DEFAULT_JOURNAL_PATH = filesystem::current_path();

void writeDefaultConfigs() {
	ofstream configFile("config.jfig");
	configFile << "journal-path" << " : " << DEFAULT_JOURNAL_PATH.string() << endl;
	configFile.close();
}

map<string, string> config() {
	int checkflag = 0;

	for (const auto& entry : filesystem::directory_iterator(filesystem::current_path())) {
		if (entry.path().filename() == "config.jfig") {
			checkflag = 1;
		}
	}

	if (!checkflag) {
		ofstream configFile("config.jfig");
		configFile.close();
	}

	string line = "";
	string key = "";
	string value = "";
	map<string, string> configMap = map<string, string>();

	ifstream configFile("config.jfig");
	
	while (configFile.good()) {
		getline(configFile, line);

		if (line.empty()) {
			continue;
		}

		pair<string, string> configPair = splitString(line, ":");
		key = configPair.first;
		value = configPair.second;
		trim(key);
		trim(value);
		configMap[key] = value;
	}

	configFile.close();

	if (configMap.empty()) {
		writeDefaultConfigs();
	}

	return configMap;
}