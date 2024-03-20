#pragma once
#include <string>
#include <vector>

using namespace std;

void ltrim(string& s);
void rtrim(string& s);
void trim(string& s);
bool isStringInArray(const string& inStr, const vector<string>& inArr);
pair<string, string> splitString(const string& inStr, const string& delimiter);
string toLowercase(string str);
string getDateStr();
void printDate();