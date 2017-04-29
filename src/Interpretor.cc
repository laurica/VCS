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
  errorMessages[INVALID_COMMIT_MESSAGE] =
    "Please provide a valid commit message.";
  errorMessages[NOTHING_TO_COMMIT] = "No changes staged for commit!";
  errorMessages[UNRECOGNIZED_OPTION] = "Unrecognized option! Please try again.";
}

static bool reachedTerminatingCommand(const string& command) {
  return command == "q" || command == "quit";
}

bool Interpretor::parseOneArgument(istringstream& input, string& arg) const {
  if (!(input >> arg)) {
    cout << errorMessages.at(NOT_ENOUGH_ARGS) << endl;
    return false;
  }

  string extraArg;

  if (input >> extraArg) {
    cout << errorMessages.at(TOO_MANY_ARGS) << endl;
    return false;
  }

  return true;
}

void Interpretor::parseAdd(istringstream& input) const {
  string fileArg;
  if (!parseOneArgument(input, fileArg)) {
    return;
  }

  // Otherwise, we're fine
  if (FileSystemInterface::fileExists(fileArg.c_str())) {
    bool actuallyAdded = accumulator.addFile(fileArg);
    if (actuallyAdded) {
      cout << "File " << fileArg << " is now staged for commit." << endl;
    } else {
      cout << "File " << fileArg << " was already tracked." << endl;
    }
  } else {
    cout << errorMessages.at(FILE_NOT_FOUND) << endl;
  }
}

void Interpretor::parseCommit(string command, istringstream& input) const {
  string nextToken;
  
  if (!(input >> nextToken)) {
    cout << errorMessages.at(NOT_ENOUGH_ARGS) << endl;
    return;
  }

  bool addFlag = false;
  
  if (nextToken == "-a") {
    addFlag = true;
    if (!(input >> nextToken)) {
      cout << errorMessages.at(NOT_ENOUGH_ARGS) << endl;
      return;
    }
  }

  if (nextToken.at(0) == '-') {
    cout << errorMessages.at(UNRECOGNIZED_OPTION) << endl;
    return;
  }
  
  // ensure that the following tokens are a part of the commit message
  if (nextToken.at(0) != '"') {
    cout << errorMessages.at(INVALID_COMMIT_MESSAGE) << endl;
    return;
  }

  // ensure that the last non-whitespace character is a double-quote
  bool once = false;
  while ((input >> nextToken)) {
    once = true;
  }

  if (once) {
    if (nextToken.at(nextToken.length() - 1) != '"') {
      cout << errorMessages.at(INVALID_COMMIT_MESSAGE) << endl;
      return;
    }
  } else {
    if (nextToken.length() == 1) {
      cout << errorMessages.at(INVALID_COMMIT_MESSAGE) << endl;
      return;
    }

    if (nextToken.at(nextToken.length() - 1) != '"') {
      cout << errorMessages.at(INVALID_COMMIT_MESSAGE) << endl;
      return;
    }
  }

  // Now we know we have a valid commit message, we just need to parse it
  command = command.substr(command.find("\"") + 1);
  command = command.substr(0, command.find("\""));

  bool changesToCommit = accumulator.commit(command, addFlag);
  
  if (!changesToCommit) {
    cout << errorMessages.at(NOTHING_TO_COMMIT) << endl;
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
    } else if (firstToken == "commit") {
      parseCommit(command, input);
    } else {
      cout << errorMessages.at(UNRECOGNIZED_COMMAND) << endl;
    }
  }
}

bool Interpretor::parseInit(istringstream& input) const {
  string projectName;

  if (!parseOneArgument(input, projectName)) {
    return false;
  }

  accumulator.initializeProject(projectName);
  cout << "Project " << projectName << " successfully initialized." << endl;
  return true;
}

static bool isValidOperation(const string& command) {
  if (command == "init") {
    return true;
  }

  if (command == "add") {
    return true;
  }

  if (command == "commit") {
    return true;
  }

  return false;
}

bool Interpretor::parseFirstCommand(const string& command) const {
  istringstream input(command);
  string firstToken;
  input >> firstToken;
    
  if (firstToken != "init") {
    if (!isValidOperation(firstToken)) {
      cout << errorMessages.at(UNRECOGNIZED_COMMAND) << endl;
      return false;
    }
    cout << errorMessages.at(PROJECT_UNINITIALIZED) << endl;
    return false;
  }

  return parseInit(input);
}

void Interpretor::interpret() const {
  string command;

  bool initialized = accumulator.isInitialized();

  if (initialized) {
    cout << "(" << accumulator.getCurBranchName() << ") ";
  }
  
  cout << "> ";

  while (getline(cin, command) && !reachedTerminatingCommand(command)) {
    if (!initialized) {
      initialized = parseFirstCommand(command);
      if (initialized) {
	cout << "(" << accumulator.getCurBranchName() << ")" << " > " << flush;
      } else {
	cout << "> " << flush;
      }
    } else {
      parseCommand(command);
      cout << "(" << accumulator.getCurBranchName() << ")" << " > " << flush;
    }
  }
}
