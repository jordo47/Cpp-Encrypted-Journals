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

void setConfig(pair<string, string> figPair) {
	string line = "";
	string comparisonKey = "";
	string configKey = figPair.first;
	string configValue = figPair.second;

	trim(configValue);

	ifstream configFile("config.jfig");
	ofstream tempFile("temp.txt");

	while (getline(configFile, line)) {
		pair<string, string> comparisonPair = splitString(line, ":");
		comparisonKey = comparisonPair.first;
		trim(comparisonKey);
		
		if (comparisonKey != configKey)
			tempFile << line << endl;
	}

	tempFile.close();
	configFile.close();
	remove("config.jfig");
	rename("temp.txt", "config.jfig");

	ofstream outFile("config.jfig", ios::app);
	outFile << configKey << " : " << configValue << endl;

}

string getConfigValue(const string& key) {
	ifstream configFile("config.jfig");
	string line = "";
	string configValue = "";
	string configKey = "";
	pair<string, string> returnPair;


	while (getline(configFile, line)) {
		pair<string, string> configPair = splitString(line, ":");
		configKey = configPair.first;
		trim(configKey);

		if (configKey == key)
			configValue = configPair.second;
	}

	trim(configValue);

	return configValue;
}