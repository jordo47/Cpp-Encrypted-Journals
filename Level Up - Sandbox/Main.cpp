#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>
#include <chrono>
#include <fstream>
#include <limits>


using namespace std;

const map<int, string> functions{
	{1, "Show today's date."},
	{2, "Create journal entry."},
	{3, "View journal."},
	{4, "Delete journal."}
};

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

bool isStringInArray(const string &inStr, const vector<string> &inArr) {
	return find(inArr.begin(), inArr.end(), inStr) != inArr.end();
}

string toLowercase(string str) {
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
	return str;
}

void printFunctions() {
	for (const auto& [key, value] : functions)
		cout << key << " : " << value << "\n";
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

void createJournal() {
	string title;
	string entry;
	string mood;
	string sleep;
	string date;
	string filename;

	cout << "\nWhat would you like to name this journal entry?\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	cin.clear();
	cout << "\nWhat's on your mind?\n";
	getline(cin, entry);
	cin.clear();
	cout << "\nHow has your mood been?\n";
	getline(cin, mood);
	cin.clear();
	cout << "\nHow well have you slept, and how much?\n";
	getline(cin, sleep);
	cin.clear();

	date = getDateStr();
	trim(title);
	trim(date);
	filename = toLowercase(date) + "-" + toLowercase(title) + ".txt";

	ofstream journal(filename);
	journal << title << "\n\n" << date << "\n\nEntry:\n\t" << entry << "\n\nMood:\n\t" << mood << "\n\nSleep:\n\t" << sleep << endl;
	journal.close();

}

void selectFunction(int selection) {
	switch (selection) {
		case 1:
			printDate();
			break;
		case 2:
			createJournal();
			break;
		default:
			cout << "Invalid function designator.";
			break;
	}
}

int main()
{
	vector<string> acceptableGreetings = { "hi", "hello", "hey" };
	string greeting;
	int pickedFunction;

	cout << "Hello,\n\nWelcome to Project Level Up - Sandbox.\n";
	cin >> greeting;
	greeting = toLowercase(greeting);

	if (isStringInArray(greeting, acceptableGreetings))
		cout << "\nWelcome Entity <3\n";
	else
		return 0;

	cout << "\nWhich function would you like to perform?\n\n";
	printFunctions();
	cin >> pickedFunction;

	if (pickedFunction == 0) {
		cout << "Please provide a valid value. (Integer greater than 0)";
		return 0;
	}

	selectFunction(pickedFunction);
	
}