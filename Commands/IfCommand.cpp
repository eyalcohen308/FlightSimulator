//
// Created by Tomer & Eyal on 20/12/18.
//

#include "IfCommand.h"

int IfCommand::doCommand(vector<vector<string>> vector1, map<string, double> *symbol_table, int index) {

    int size = vector1[index].size();

    int i = 1;
    string first = "";
    string second = "";
    while ((vector1[index][i] != "<") && (vector1[index][i] != ">") && (vector1[index][i] != "=") &&
           (vector1[index][i] != "!")) {
        first = first + vector1[index][i] + " ";
        i++;
    }
    string sign = vector1[index][i];
    i++;
    if (vector1[index][i] == "=") {
        sign = sign + vector1[index][i];
        i++;

    }
    while (vector1[index][i] != "{") {
        second = second + vector1[index][i] + " ";
        i++;
    }
    //double firstParm= this->shunting_yard->operator()(first);
    //double secondParm= this->shunting_yard->operator()(second);
    vector<vector<string>> newVactor = vector1;
    newVactor.erase(newVactor.begin() + 0);
    for (int o = 0; o < newVactor[newVactor.size() - 1].size(); o++) {
        if (newVactor[newVactor.size() - 1][o] == "}") {
            newVactor[newVactor.size() - 1].erase(newVactor[newVactor.size() - 1].begin() + o);
            break;
        }
    }
    if (newVactor[newVactor.size() - 1].size() == 0) {
        newVactor.erase(newVactor.begin() + newVactor.size());
    }
    if (checkCondition(first, second, sign, symbol_table)) {

        this->interpreter->interpLine(newVactor);
    }

    return 0;
}

bool IfCommand::checkCondition(string first, string second, string sign, map<string, double> *symbol_table) {
    double firstParm = this->shunting_yard->dijkstratoi(first);
    double secondParm = this->shunting_yard->dijkstratoi(second);

    double firstVal = firstParm;
    double secondVal = secondParm;

    if (sign == ">") {
        if (firstVal > secondVal) {
            return true;
        } else {
            return false;
        }


    } else if (sign == "<") {
        if (firstVal < secondVal) {
            return true;
        } else {
            return false;
        }


    } else if (sign == ">=") {
        if (firstVal >= secondVal) {
            return true;
        } else {
            return false;
        }


    } else if (sign == "<=") {
        if (firstVal <= secondVal) {
            return true;
        } else {
            return false;
        }


    } else if (sign == "==") {
        if (firstVal == secondVal) {
            return true;
        } else {
            return false;
        }
    } else if (sign == "!=") {
        if (firstVal != secondVal) {
            return true;
        } else {
            return false;
        }

    } else {
        throw runtime_error("missing correct operator in condition");
    }
}

