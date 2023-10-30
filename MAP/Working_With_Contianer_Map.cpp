#include<iostream>
#include<string>
#include<map>
#include <vector>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

//#define RANGE_BASED_FOR_ARRAY
//#define STL_MAP

/*
Implement a traffic police database on fine tickets using a 
binary tree. the key will be the car number, 
the value of the node will be a list of offenses. 
If a receipt is added for the first time, 
then a new node appears in the tree, 
and data on the offense appears in the list; 
if not, the data is added to the existing list. 
It is also necessary to implement the following operations
full printout of the database 
(by car numbers and list of offenses registered with them)
printout of data according to a given number
Save and load information from a file
*/


// Structure for presenting offenses
struct Violation {
    std::string description;
    int fineAmount;
};

// definition for the traffic database police(GAI)
using GaiDatabase = std::map<std::string, std::vector<Violation>>;

// Function for adding an offense to the database
void AddViolation(GaiDatabase& database, const std::string& carNumber, const Violation& violation) 
{
    database[carNumber].push_back(violation);
}

// Function for complete database listing
void PrintDatabase(const GaiDatabase& database) 
{
    for (const auto& entry : database) {
        std::cout << "Car Number: " << entry.first << std::endl;
        for (const auto& violation : entry.second) {
            std::cout << "  Violation: " << violation.description << ", Fine Amount: " << violation.fineAmount << std::endl;
        }
    }
}

// Function for printing data by given number
void PrintDataForCar(const GaiDatabase& database, const std::string& carNumber) 
{
    auto it = database.find(carNumber);
    if (it != database.end()) {
        std::cout << "Car Number: " << it->first << std::endl;
        for (const auto& violation : it->second) {
            std::cout << "  Violation: " << violation.description << ", Fine Amount: " << violation.fineAmount << std::endl;
        }
    }
    else {
        std::cout << "Car Number " << carNumber << " not found in the database." << std::endl;
    }
}

// Function for saving the database to a file
void SaveDatabaseToFile(const GaiDatabase& database, const std::string& filename)
{
    std::ofstream outFile(filename);
    for (const auto& entry : database) {
        outFile << entry.first << " " << entry.second.size() << " ";
        for (const auto& violation : entry.second) {
            outFile << violation.description << " " << violation.fineAmount << " ";
        }
        outFile << std::endl;
    }
    outFile.close();
}

// Function to load a database from a file
GaiDatabase LoadDatabaseFromFile(const std::string& filename) 
{
    GaiDatabase database;
    std::ifstream inFile(filename);
    std::string carNumber;
    while (inFile >> carNumber) {
        int numViolations;
        inFile >> numViolations;
        for (int i = 0; i < numViolations; ++i) {
            Violation violation;
            inFile >> violation.description >> violation.fineAmount;
            database[carNumber].push_back(violation);
        }
    }
    inFile.close();
    return database;
}


void main()
{
	setlocale(LC_ALL, "");
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		{0, "Sunday"},
		{1, "Monday"},
		{2, "Tuesday"},
		{3, "Wednesday"},
		{4, "Thursday"},
		{5, "Friday"},
		{6, "Saturday"},
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << " - " << it->second << endl;
	}
	cout << endl;
	cout << "\n-------------------------------\n";
	for (std::pair<int, std::string> i : week)
	{
		cout << i.first << " - " << i.second << endl;
	}
	cout << endl;
#endif // STL_MAP


    GaiDatabase database;
    // // Adding records to the database
    AddViolation(database, "M666KH", { "Speeding", 100 });
    AddViolation(database, "P538AB", { "Parking Violation", 50 });
    AddViolation(database, "H991EM", { "Running Red Light", 200 });

    // Display all entries
    std::cout << "Database Contents:" << std::endl;
    PrintDatabase(database);

    // Search and display records by car number
    std::cout << "\nSearch Results:" << std::endl;
    PrintDataForCar(database, "M666KH");
    PrintDataForCar(database, "DEF456");

    // Saving a database to a file
    SaveDatabaseToFile(database, "database.txt");

    // Loading a database from a file
    GaiDatabase loadedDatabase = LoadDatabaseFromFile("database.txt");

    // Data output after loading
    std::cout << "\nDatabase Contents After Loading:" << std::endl;
    PrintDatabase(loadedDatabase);


	
}




