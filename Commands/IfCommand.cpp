//
// Created by Eyal on 20/12/18.
//

#include "IfCommand.h"

int IfCommand::doCommand(vector<string> vec, map<string, double> *map1) {

    int size = vec.size();

    int i = 1;
    string first = "";
    string second = "";
    while ((vec[i] != "<") && (vec[i] != ">") && (vec[i] != "=") && (vec[i] != "!")) {
        first = first + vec[i] + " ";
        i++;
    }
    string sign = vec[i];
    i++;
    if (vec[i] == "=") {
        sign = sign + vec[i];
        i++;

    }
    while (vec[i] != "{") {
        second = second + vec[i] + " ";
        i++;
    }
//    //double firstParm= this->dijkstra1->operator()(first);
//    //double secondParm= this->dijkstra1->operator()(second);
//    vector<vector<string>> newVactor=vector1;
//    newVactor.erase(newVactor.begin()+0);
//    for(int o = 0;o<newVactor[newVactor.size()-1].size();o++){
//        if(newVactor[newVactor.size()-1][o]=="}"){
//            newVactor[newVactor.size()-1].erase(newVactor[newVactor.size()-1].begin()+o);
//            break;
//        }
//    }
//    if(newVactor[newVactor.size()-1].size()==0){
//        newVactor.erase(newVactor.begin()+newVactor.size());
//    }
    if (returnBoolSign(first, second, sign, map1)) {

        auto it = commands.begin();
        for (it; it != commands.end(); ++it) {
            (*it)->doCommand(vec, map1);
        }
    }
    return 0;
}

bool IfCommand::returnBoolSign(string first, string second, string sign, map<string, double> *map1) {
    double firstParm = this->dijkstra1->toVl(first);
    double secondParm = this->dijkstra1->toVl(second);

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
        __throw_bad_exception();
    }
}

IfCommand::IfCommand(DataReaderServer *server, Client *client,
                     Dijkstra *dij, pthread_mutex_t *mut) : ConditionCommand(server, client, dij, mut) {

}

