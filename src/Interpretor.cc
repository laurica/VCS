#include <iostream>

#include "FileSystemInterface.h"
#include "Interpretor.h"

using namespace std;

Interpretor::Interpretor(OperationAccumulator& accumulator) :
  accumulator(accumulator) {}

static bool reachedTerminatingCommand(const string& command) {
  return command == "q" || command == "quit";
}

void Interpretor::parseAdd(istringstream& input) const {
  string fileArg;

  if (!(input >> fileArg)) {
    cout << "Not enough arguments! Please try again." << endl;
    return;
  }

  string extraArg;

  if (input >> extraArg) {
    cout << "Too many arguments! Please try again." << endl;
    return;
  }

  // Otherwise, we're fine
  if (FileSystemInterface::fileExists(fileArg.c_str())) {
    cout << "File " << fileArg << " is now tracked." << endl;
    accumulator.addFile(fileArg);
  } else {
    cout << "Specified file not found!" << endl;
  }
}

void Interpretor::parseCommand(const string& command) const {
  istringstream input(command);
  string firstToken = "";

  input >> firstToken;

  if (firstToken != "") {
    if (firstToken == "init") {
      cout << "KIL project already exists within directory!" << endl;
    } else if (firstToken == "add") {
      parseAdd(input);
    } else {
      cout << "Command not recognized! Please try again." << endl;
    }
  }
}

bool Interpretor::parseInit(istringstream& input) const {
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

  accumulator.initializeProject(projectName);
  cout << "Project " << projectName << " successfully initialized." << endl;
  return false;
}

static bool isValidOperation(const string& command) {
  if (command == "init") {
    return true;
  }

  if (command == "add") {
    return true;
  }

  return false;
}

bool Interpretor::parseFirstCommand(const string& command) const {
  if (FileSystemInterface::fileExists("./.kil")) {
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

void Interpretor::interpret() const {
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
