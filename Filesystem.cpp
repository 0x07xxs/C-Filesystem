#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

class FileSystem {
	
	private: std::map<std::string, std::string> files;
	
	public:
		//namespace fs = std:: filesystem;
		void createFile(string fileName, string fileContent) {
		
			ofstream file(fileName); // Creates a file
			
			file << fileContent; // writing to the file created

			if (!file) { // check if file exists
				cout << "File " << fileName << " failed to be created";
			}
			else {
				cout << "File " << fileName << " has been created";
			}
			file.close();
		 }
		
		void readFile(string fileName) {
			string output; // output string
			ifstream file; // ifstream instance
			file.open(fileName);
			
			if (file) { // Check if the file exists
				while (getline (file, output)) { //reads the file line by line in a loop 
					cout <<  output;
					file.close();
				}	
			}
			else{
				cout << "File doesn't exist";
			}
					}

		void updateFile(const string fileName, const string newContent) {
			
			ifstream inFile (fileName);
			string oldContent((istreambuf_iterator<char>(inFile)), // File opens and iterates through each char to read it
					istreambuf_iterator<char>()); // With istreambuf 
			inFile.close();
			
			ofstream outFile(fileName);
			outFile << oldContent << newContent; // printing the old and new content into the output file
			outFile.close();
		}

		void deleteFile(const char* fileName) {
			string userDelete;
			ifstream file;
			file.open(fileName);// checks if file is exists to open
			if (file.is_open()) {
				cout << "Are you sure you want to delete " << fileName << " (Y/N).";
				getline(cin, userDelete);
				if (userDelete == "Y" || userDelete == "y") {
					remove(fileName);
					file.close();
				}
				else {
					cout << "File " << fileName << " was not deleted." << endl;	
				
				}
			}
			else {
				cout << "File couldn't be deleted because it does not exist." << endl;
				
			}
			file.close();
			
		}

};	

int main(int argc, char* argv[]) {
	FileSystem fs;

	string fileName;
	string fileContent;
	string newContent;

	if (argc < 2) {
		cout << "Error: No command line arguments found" << endl;
	}

	for (int i = 1; i < argc; i++) {
		std::string argument = argv[i];	
	
		if (argument[0] == '-') {
			if (argument == "-c") {
				cout << "Enter a file name: ";
				getline(cin, fileName);
				cout << "Enter the contents of the file: ";
				getline(cin, fileContent);
				fs.createFile(fileName, fileContent);
			}
			
			if (argument == "-r") {
				cout << "Enter a file to read: ";
				getline(cin, fileName);
				fs.readFile(fileName);
			}

			if (argument == "-u") {
				cout << "Enter a file name to update: ";
				getline(cin, fileName);
				cout << "Enter the contents of the file you want to update: ";
				getline(cin, newContent);
				fs.updateFile(fileName, newContent);
			}

			if (argument == "-d") {
				cout << "Enter a file name to delete: " << endl;
				string fileName;
				cin >> fileName;
				cin.ignore();
				fs.deleteFile(fileName.c_str());
			}
		}
		else {
			cout << "Please enter an argument with a flag" << endl;
		}
	}
}

