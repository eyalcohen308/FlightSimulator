//
// Created by tomer on 12/20/18.
//

#include "PrintCommand.h"

/**
 * print can get string, number (or expression) or var
 * if start with ' " ' -> string, print it as is
 * if exists var with that name -> get it's value and print it
 * else -> expression, calculate and print
 * @param itor
 * @param server
 */
void PrintCommand::doCommand(vector<string>::iterator &itor, DataReaderServer *server) {
    string print_me = *itor; // take value to print
    if (print_me[0] == '"') { // string
        cout << print_me << endl;
    } else if (varDataBase.isVarExists(print_me)) { // var
        cout << varDataBase.getVarValue(print_me) << endl;
    } else { // expression
        try {
            cout << dijkstra(print_me) << endl; // get the number / var value to assign the new var
        } catch (const out_of_range &no_such_var) {
            // if there is no var in this name- dijkstra throw error
            __throw_runtime_error("Error in PrintCommend : invalid params to print");
        }
    }
    ++itor; // increase iterator
}
