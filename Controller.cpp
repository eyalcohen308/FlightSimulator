//
// Created by eyal on 12/21/18.
//

#include "Controller.h"


Controller::Controller(int argc, char **argv) {
    command_data_base = new CommandDataBase();
    var_data_base = new VarDataBase();
    data_reader_server = new DataReaderServer(var_data_base);
    /**
     *
     * decide if to split responsabilities between DataReaderServer And VarData Base.
     * for now var data base not in heap.(not pointer).
     */
    if (argc > 1) {
        inputManager = new InputManager(new FileReader(argv[1]));
    } else {
        inputManager = new InputManager(new StdinReader());
    }
}

/**
 * work on lines. make every line to command and return the command list.
 * use the member commandDataBase to get the commands from.
 * use the member DataReaderServer to read and write to server.
 * @param find_parenthesis check if need to find "{" before making commands.
 * @return commands list to execute. "syntax error, didn't find "{""
 */
vector<Expression *> Controller::conditionParser(bool find_parenthesis) {
    //list of commands to execute by reference(will saved after function done).
    vector<Expression *> commands_list;
    // read the next line.
    //string line = inputReader->readLine();
    vector<string> parsered_line = inputManager->readParseredLine();
//    lines_vector.push_back(parser(line));
    /**
     * i want the parsered vector and also the iterator still be alive after
     * function end, so i save them inside member.
     */
//    lines_iterators.push_back(lines_vector[lines_vector.size() - 1].begin());
    if (!find_parenthesis && parsered_line.back() != "{") {
        // check if didn't find "{" open to read command.
        throw runtime_error("syntax error, didn't find \"{\"");
    }
    // read and create commands until '}' or eof.
    while (!parsered_line.back().empty() && parsered_line.back() != "}") {
        //save the iterator reference to add to the commands.
        int current_index = inputManager->getStartVectorIndex();
        //parserd vector of string line input.
        Expression *ex = getCommandFromLine(parsered_line, current_index);
        commands_list.push_back(ex);
        parsered_line = inputManager->readParseredLine();
        if (parsered_line.back() == "}") {
            break;
        }
    }
    return commands_list;
}

void Controller::runProgram() {
    //reading line(stdin or file)
    vector<string> parsered_line = inputManager->readParseredLine();
    while (!parsered_line.back().empty()) {
        // save all the lines and the iterators on each line.
//        vector<string>::iterator it = inputManager->getParseredIterator();
        int index = inputManager->getStartVectorIndex();
        //parse vector in to expression.
        //send the last iterator made from the vector.
        Expression *expression = getCommandFromLine(parsered_line, index);
        expression->calculate();
        parsered_line = inputManager->readParseredLine();
    }
}

/**
 * make and return command by
 * @param line of the file/stdin.
 * @param data_reader to connet with the commands.
 * @return command interpeted in specific line.
 */
Expression *Controller::getCommandFromLine(vector<string> &parsered_line, int &index) {
    Expression *expression_command;
    //    vector<string>::iterator it = parsered_line.begin();
    int current_index = 0;
    //split to cases, if its condition command create and return condition
    if (parsered_line[current_index] == "while" || parsered_line[current_index] == "if") {
        //check if saw "{" in the same line as the command if or while.
        bool saw_parenthesis = CheckValidityOfConditionCommand(parsered_line);
        // add all commands to command list in the scope between {};
        vector<Expression *> command_lists = conditionParser(saw_parenthesis);
        // create conditional command.
        expression_command =
                (command_data_base->getConditionCommand(parsered_line, index, data_reader_server, command_lists,
                                                        var_data_base));

    } else {
        // expression command create.
        expression_command = (command_data_base->getCommand(parsered_line, index, data_reader_server, var_data_base));
    }
    to_delete.push_back(expression_command);
    return expression_command;
}

/**
 * get iterator to a line of condition and check if it has "{".
 * throw exception if not.
 * @param it to iterate the line and find "{".
 */
bool Controller::CheckValidityOfConditionCommand(vector<string> &vec) {
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
        if (*it == "{") {
            return true;
        }
    }
    return false;
}

Controller::~Controller() {
    delete (this->command_data_base);
    delete (this->var_data_base);
    delete (this->data_reader_server);
    delete (inputManager);
    for (vector<Expression *>::iterator it = to_delete.begin(); it != to_delete.end(); ++it) {
        delete *it;
        *it = nullptr;
    }
    to_delete.clear();
}
