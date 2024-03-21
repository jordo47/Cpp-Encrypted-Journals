#pragma once
#include "HelperFunctions.h"
#include <map>

map<string, string> config();
void setConfig(pair<string, string> figPair);
string getConfigValue(const string& key);