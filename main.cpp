#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// Class to handle the item tracking logic
class ItemTracker {
private:
    map<string, int> itemFrequencies;

    // Reads the input file and populates the map
    void loadData(string filename) {
        ifstream inputFile(filename);
        string item;
        if (inputFile.is_open()) {
            while (inputFile >> item) {
                itemFrequencies[item]++;
            }
            inputFile.close();
        }
        else {
            cout << "Error: Could not open " << filename << endl;
        }
    }

    // Creates the frequency.dat backup file
    void backupData(string filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (auto const& [item, count] : itemFrequencies) {
                outFile << item << " " << count << endl;
            }
            outFile.close();
        }
    }

public:
    ItemTracker(string inputFileName) {
        loadData(inputFileName);
        backupData("frequency.dat");
    }

    void searchItem() {
        string searchWord;
        cout << "Enter the item to look for: ";
        cin >> searchWord;
        if (itemFrequencies.count(searchWord)) {
            cout << searchWord << " count: " << itemFrequencies[searchWord] << endl;
        }
        else {
            cout << "Item not found." << endl;
        }
    }

    void printAllFrequencies() {
        for (auto const& [item, count] : itemFrequencies) {
            cout << item << " " << count << endl;
        }
    }

    void printHistogram() {
        for (auto const& [item, count] : itemFrequencies) {
            cout << setw(12) << left << item << " ";
            for (int i = 0; i < count; ++i) cout << "*";
            cout << endl;
        }
    }
};

int main() {
    
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");
    int choice = 0;

    while (choice != 4) {
        cout << "\n1. Search Item\n2. List All\n3. Histogram\n4. Exit\nChoice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) tracker.searchItem();
        else if (choice == 2) tracker.printAllFrequencies();
        else if (choice == 3) tracker.printHistogram();
    }

    return 0;
}