#include "HelperFunctions.h";
#include <iostream>;
#include <filesystem>;
#include <fstream>;

const string VIEW_JOURNAL_PROMPT = "Which journal would you like to view? (Enter the integer value)";
const string DELETE_JOURNAL_PROMPT = "Which journal would you like to delete? (Enter the integer value)";

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
	journal << title << "\n\n" << date << "\n\nEntry:\n\t" << entry << "\n\nMood:\n\t" << mood << 
		"\n\nSleep:\n\t" << sleep << endl;
	journal.close();

}

filesystem::path selectJournal(const string& prompt) {
	filesystem::path cw_dir = filesystem::current_path();

	cout << endl;

	int i = 1;
	for (const auto& entry : filesystem::directory_iterator(cw_dir)) {
		if (entry.path().filename() == "config.txt") {
			continue;
		}

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

	system(cmd.c_str());
}