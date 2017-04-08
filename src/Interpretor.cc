#include <iostream>

#include "FileSystemInterface.h"
#include "Interpretor.h"

using namespace std;

Interpretor::Interpretor(OperationAccumulator& accumulator) :
  accumulator(accumulator) {
  errorMessages[NOT_ENOUGH_ARGS] = "Not enough arguments! Please try again.";
  errorMessages[TOO_MANY_ARGS] = "Too many arguments! Please try again.";
  errorMessages[FILE_NOT_FOUND] = "Specified file not found!";
  errorMessages[PROJECT_ALREADY_INITIALIZED] =
    "KIL project already exists within directory!";
  errorMessages[UNRECOGNIZED_COMMAND] =
    "Command not recognized! Please try again.";
  errorMessages[PROJECT_UNINITIALIZED] =
    "Must initialize a KIL project in order to perform an operation.";
}

static bool reachedTerminatingCommand(const string& command) {
  return command == "q" || command == "quit";
}

void Interpretor::parseAdd(istringstream& input) const {
  string fileArg;

  if (!(input >> fileArg)) {
    cout << errorMessages.at(NOT_ENOUGH_ARGS) << endl;
    return;
  }

  string extraArg;

  if (input >> extraArg) {
    cout << errorMessages.at(TOO_MANY_ARGS) << endl;
    return;
  }

  // Otherwise, we're fine
  if (FileSystemInterface::fileExists(fileArg.c_str())) {
    cout << "File " << fileArg << " is now tracked." << endl;
    accumulator.addFile(fileArg);
  } else {
    cout << errorMessages.at(FILE_NOT_FOUND) << endl;
  }
}

void Interpretor::parseCommand(const string& command) const {
  istringstream input(command);
  string firstToken = "";

  input >> firstToken;

  if (firstToken != "") {
    if (firstToken == "init") {
      cout << errorMessages.at(PROJECT_ALREADY_INITIALIZED) << endl;
    } else if (firstToken == "add") {
      parseAdd(input);
    } else {
      cout << errorMessages.at(UNRECOGNIZED_COMMAND) << endl;
    }
  }
}

bool Interpretor::parseInit(istringstream& input) const {
  string projectName;

  if (!(input >> projectName)) {
    cout << errorMessages.at(NOT_ENOUGH_ARGS) << endl;
    return true;
  }

  string remainingArgs;
  if (input >> remainingArgs) {
    cout << errorMessages.at(TOO_MANY_ARGS) << endl;
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
      cout << errorMessages.at(UNRECOGNIZED_COMMAND) << endl;
      return true;
    }
    cout << errorMessages.at(PROJECT_UNINITIALIZED) << endl;
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
