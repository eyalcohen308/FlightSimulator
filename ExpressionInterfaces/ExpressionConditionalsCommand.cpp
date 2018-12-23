//
// Created by eyal on 12/21/18.
//

#include "ExpressionConditionalsCommand.h"


/**
 * do the command, Object Adapter.
 * @return 0 if succeeded
 */
double ExpressionConditionalsCommand::calculate() {
    command->setListOfCommands(command_lists);
    command->doCommand(vec, index, reader,client, varDataBase);
    return 0;
}

ExpressionConditionalsCommand::ExpressionConditionalsCommand(ConditionCommand *command, vector<string> vec,
                                                             int index, DataReaderServer *reader,
                                                             Client *client,
                                                             vector<Expression *> command_lists
                                                             ,VarDataBase *vdb) : command(
        command), vec(vec), index(index), reader(reader),
        client(client),
        command_lists(command_lists),varDataBase(vdb) {}
