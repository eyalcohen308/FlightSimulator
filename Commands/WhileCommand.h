//
// Created by tomer on 12/21/18.
//

#ifndef FLIGHTSIMULATOR_WHILECOMMAND_H
#define FLIGHTSIMULATOR_WHILECOMMAND_H


#include "ConditionCommand.h"

class WhileCommand : public ConditionCommand{
    VarDataBase varDataBase;
public:
    virtual int doCommand(vector<string> line, int i, DataReaderServer *server);
};


#endif //FLIGHTSIMULATOR_WHILECOMMAND_H
