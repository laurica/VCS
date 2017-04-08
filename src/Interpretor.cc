#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>

#include "Interpretor.h"

using namespace std;

Interpretor::Interpretor(OperationAccumulator& accumulator) :
  accumulator(accumulator) {}

static bool reachedTerminatingCommand(const string& command) {
  return command == "q" || command == "quit";
}

static void parseCommand(const string& command) {
  istringstream input(command);
  string firstToken = "";

  input >> firstToken;

  if (firstToken != "") {
    if (firstToken == "init") {
      cout << "KIL project already exists within directory!" << endl;
    } else if (firstToken == "add") {
      cout << "ADDING" << endl;
    } else {
      cout << "Command not recognized! Please try again." << endl;
    }
  }
}

bool kilDirExists() {
  struct stat info;

  string kilDirectoryName = "./.kil";
  
  if(stat(kilDirectoryName.c_str(), &info) != 0) {
    return false;
  }

  return info.st_mode & S_IFDIR;
}

bool Interpretor::parseInit(istringstream& input) {
  string projectName;

  if (!(input >> projectName)) {
    cout << "Not enough arguments! Please try again." << endl;
    return true;
  }

  string remainingArgs;
  if (input >> remainingArgs) {
    cout << "Too many arguments! Please try again." << endl;
    return true;
  }

  accumulator.projectInitialized(projectName);
  return false;
}

static bool isValidOperation(const string& command) {
  if (command == "init") {
    return true;
  }

  if (command == "add") {
    return true;
  }
}

bool Interpretor::parseFirstCommand(const string& command) {
  if (kilDirExists()) {
    parseCommand(command);
    return false;
  }

  istringstream input(command);
  string firstToken;
  input >> firstToken;
    
  if (firstToken != "init") {
    if (!isValidOperation(firstToken)) {
      cout << "Command not recognized! Please try again." << endl;
      return true;
    }
    cout << "Must initialize a KIL project in order to perform an operation."
	 << endl;
    return true;
  }

  return parseInit(input);
}

void Interpretor::interpret() {
  string command;

  cout << "> ";

  bool firstCommand = true;
  
  while (getline(cin, command) && !reachedTerminatingCommand(command)) {
    if (firstCommand) {
      firstCommand = parseFirstCommand(command);
    } else {
      parseCommand(command);
    }

    cout << "> " << flush;
  }
}
