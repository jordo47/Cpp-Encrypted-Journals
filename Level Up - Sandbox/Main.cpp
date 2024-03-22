#include <iostream>h
#include <map>
#include "HelperFunctions.h"
#include "Journal.h"
#include "Config.h"

using namespace std;

/* TODO/Ideas:
	*Qt front-end?
	*Add Encryption Functions (classical/post-quantum methods)
	
*/

const map<int, string> functions {
	{0, "Exit"},
	{1, "Show today's date."},
	{2, "Create journal entry."},
	{3, "View journal."},
	{4, "Delete journal."},
	{5, "Set new default path for journals."}
	//Other functions to consider: encrypt journals, ...
};

void printFunctions() {
	for (const auto& [key, value] : functions)
		cout << key << " : " << value << "\n";
}

int selectFunction(int selection) {
	string workingString = "";
	pair<string, string> workingPair;
	string lastFigValue = "";
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
		case 5:
			cout << "Enter your desired path (Ex. C:\\my_journals): " << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> workingString;
			trim(workingString);
			workingPair = { "journal-path" , workingString };
			lastFigValue = getConfigValue("journal-path");
			setConfig(workingPair);
			moveJournals(lastFigValue, workingString);
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
	map<string, string> configMap = config();

	if (configMap.empty()) {
		configMap = config();
	}

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

		if (pickedFunction < 0 || pickedFunction > functions.size()) {
			cout << "Please provide a valid integer value.";
			pickedFunction = -1;
			continue;
		}

		pickedFunction = selectFunction(pickedFunction);
	}

}