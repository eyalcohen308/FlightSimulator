

#include "DefineVarCommand.h"
#include <string>
using namespace std;
int DefineVarCommand::doCommand(vector<vector<string>> vector1,map<string, double>* symbol_table,int index){

    // string temp = list1[index+3];
    string temp = vector1[index][3];
    //if var is bind

    if(temp.compare("bind")==0){
        //add to map
        pthread_mutex_lock(this->mut);
        symbol_table->insert(pair<string,double >(vector1[index][1],0));
        pthread_mutex_unlock(this->mut);
        //if the 4th elemt is in the map
        if(symbol_table->count(vector1[index][4])==1){
            string path25 = this->server->getPath(vector1[index][4]);
            this->server->addNewPath(vector1[index][1], path25);
        } else{
            string nameVar = vector1[index][1];
            string path = vector1[index][4];
            path = path.substr(1,path.size()-2);
            this->server->addNewPath(nameVar, path);
        }
        this->server->updateSymbolTable();

        return 5;

        //if var isn't bind
    }else{
        string var = vector1[index][1];
                                    //temp = list1[index+3];
        string valueExp="";
        for (int i=3;i<vector1[index].size();i++){
            valueExp=valueExp+vector1[index][i]+" ";
        }

        double val=this->shunting_yard->dijkstratoi(valueExp);
        pthread_mutex_lock(this->mut);
        symbol_table->insert(pair<string, double>(var,val));
        pthread_mutex_unlock(this->mut);

        return 4;

    }


}
