#include "HelperFunctions.h";
#include "Config.h";
#include <iostream>;
#include <filesystem>;
#include <fstream>;

const string VIEW_JOURNAL_PROMPT = "Which journal would you like to view? (Enter the integer value)";
const string DELETE_JOURNAL_PROMPT = "Which journal would you like to delete? (Enter the integer value)";
const string CONVERT_TYPE_PROMPT = "Which text file would you like to convert to a journal? (Enter the integer value)";

void createJournal() {
	string journalPath = getConfigValue("journal-path");
	string title;
	string entry;
	string mood;
	string sleep;
	string date;
	string filename;

	trim(journalPath);

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
	filename = toLowercase(date) + "-" + toLowercase(title) + ".journal";

	ofstream journal(journalPath + "\\" + filename);
	journal << title << "\n\n" << date << "\n\nEntry:\n\t" << entry << "\n\nMood:\n\t" << mood << 
		"\n\nSleep:\n\t" << sleep << endl;
	journal.close();

}

filesystem::path selectJournal(const string& prompt) {
	string pathStr = getConfigValue("journal-path");
	trim(pathStr);
	filesystem::path journal_dir = pathStr;

	cout << endl;

	int i = 1;
	for (const auto& entry : filesystem::directory_iterator(journal_dir)) {
		if (entry.path().extension() == ".journal") {
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
	for (const auto& entry : filesystem::directory_iterator(journal_dir)) {
		if (entry.path().extension() == ".journal") {
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

void convertTxtToJournal() {
	filesystem::path filePath = selectJournal(CONVERT_TYPE_PROMPT);

	if (filePath.empty()) {
		return;
	}

	string journalPath = getConfigValue("journal-path");
	trim(journalPath);

	rename(filePath, journalPath + "\\" + filePath.stem().string() + ".journal");
}

void moveJournals(const string& fromStr, const string& toStr) {

	if (!filesystem::exists(fromStr)) {
		cout << "Couldn't find previous journal entries.. Setting journal directory to " << toStr << endl;
	}

	error_code err = error_code();
	if (!createDirRecursive(toStr, err)) {
		cout << "Failed to create new directory for journals. Error: " << err.message() << endl;
	}
	
	for (const auto& entry : filesystem::directory_iterator(fromStr)) {
		if (entry.path().extension() == ".journal") {
			rename(entry.path(), toStr + "\\" + entry.path().filename().string());
		}
	}
}