#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;

void ltrim(string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
		return !isspace(c);
		}));
}

void rtrim(string& s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char c) {
		return !isspace(c);
		}).base(), s.end());
}

void trim(string& s) {
	rtrim(s);
	ltrim(s);
}

bool isStringInArray(const string& inStr, const vector<string>& inArr) {
	return find(inArr.begin(), inArr.end(), inStr) != inArr.end();
}

string toLowercase(string str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
	return str;
}

void printDate() {
	const chrono::time_point now{ chrono::system_clock::now() };
	const chrono::year_month_day ymd{ chrono::floor<chrono::days>(now) };

	string month;

	switch (static_cast<unsigned>(ymd.month())) {
	case 1: month = "January"; break;
	case 2: month = "February"; break;
	case 3: month = "March"; break;
	case 4: month = "April"; break;
	case 5: month = "May"; break;
	case 6: month = "June"; break;
	case 7: month = "July"; break;
	case 8: month = "August"; break;
	case 9: month = "September"; break;
	case 10: month = "October"; break;
	case 11: month = "November"; break;
	case 12: month = "December"; break;
	}

	cout << "\n" << month << " " << static_cast<unsigned>(ymd.day()) << " " << static_cast<int>(ymd.year()) << "\n";
}

string getDateStr() {
	const chrono::time_point now{ chrono::system_clock::now() };
	const chrono::year_month_day ymd{ chrono::floor<chrono::days>(now) };

	string month;

	switch (static_cast<unsigned>(ymd.month())) {
	case 1: month = "January"; break;
	case 2: month = "February"; break;
	case 3: month = "March"; break;
	case 4: month = "April"; break;
	case 5: month = "May"; break;
	case 6: month = "June"; break;
	case 7: month = "July"; break;
	case 8: month = "August"; break;
	case 9: month = "September"; break;
	case 10: month = "October"; break;
	case 11: month = "November"; break;
	case 12: month = "December"; break;
	}

	return to_string(static_cast<unsigned>(ymd.day())) + month + to_string(static_cast<int>(ymd.year()));
}