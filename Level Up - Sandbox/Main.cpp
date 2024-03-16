#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>
#include <chrono>
#include <fstream>
#include <limits>
#include <filesystem>

/* TODO/Ideas:
	*Refactor Journal and Helper Functions to live somewhere else.
	*Qt front-end?
	*Add Encryption Functions
	
	
*/


using namespace std;

const string VIEW_JOURNAL_PROMPT = "Which journal would you like to view? (Enter the integer value)";
const string DELETE_JOURNAL_PROMPT = "Which journal would you like to delete? (Enter the integer value)";

const map<int, string> functions {
	{0, "Exit"},
	{1, "Show today's date."},
	{2, "Create journal entry."},
	{3, "View journal."},
	{4, "Delete journal."},
	//Other functions to consider: Set path for journals, encrypt journals, ...
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

filesystem::path selectJournal(const string& prompt) {
	filesystem::path cw_dir = filesystem::current_path();

	cout << endl;

	int i = 1;
	for (const auto& entry : filesystem::directory_iterator(cw_dir)) {
		if (entry.path().extension() == ".txt") {
			cout << i << " - " << entry.path().filename() << endl;
			i++;
		}
	}

	if (i == 1) {
		cout << "No files found." << endl;
		return filesystem::path();
	}

	int selection;
	cout << endl << prompt << endl << endl;
	cin >> selection;

	i = 1;
	filesystem::path filePath = filesystem::path();
	for (const auto& entry : filesystem::directory_iterator(cw_dir)) {
		if (entry.path().extension() == ".txt") {
			if (i == selection) {
				filePath = entry.path();
				break;
			}
			i++;
		}
	}

	if (filePath.empty()) {
		cout << endl << "File not found. (Please enter a valid integer value)" << endl;
		return filePath;
	}

	return filePath;
}

void viewJournal() {
	filesystem::path filePath = selectJournal(VIEW_JOURNAL_PROMPT);

	if (filePath.empty()) {
		return;
	}

	string cmd = "notepad " + filePath.string();

	system(cmd.c_str());
}

void deleteJournal() {
	filesystem::path filePath = selectJournal(DELETE_JOURNAL_PROMPT);

	if (filePath.empty()) {
		return;
	}

	string cmd = "del \"" + filePath.string() + "\"";
	cout << cmd << endl;

	system(cmd.c_str());
}

int selectFunction(int selection) {
	switch (selection) {
		case 0:
			return 0;
		case 1:
			printDate();
			return -1;
		case 2:
			createJournal();
			return -1;
		case 3:
			viewJournal();
			return -1;
		case 4:
			deleteJournal();
			return -1;
		default:
			cout << endl << "Invalid function designator or not yet implemented." << endl;
			return -1;
	}
}

int main()
{
	vector<string> acceptableGreetings = { "hi", "hello", "hey" };
	string greeting;
	int pickedFunction = -1;

	cout << "Hello,\n\nWelcome to Project Level Up - Sandbox." << endl;
	cin >> greeting;
	greeting = toLowercase(greeting);

	if (isStringInArray(greeting, acceptableGreetings))
		cout << "\nWelcome Entity <3" << endl;
	else
		return 0;

	while (pickedFunction != 0) {
		cout << endl << "Which function would you like to perform? (Enter the corresponding integer value)" << endl << endl;
		printFunctions();
		cin >> pickedFunction;

		if (pickedFunction < 0 || pickedFunction > 4) {
			cout << "Please provide a valid integer value.";
			pickedFunction = -1;
			continue;
		}

		pickedFunction = selectFunction(pickedFunction);
	}

}