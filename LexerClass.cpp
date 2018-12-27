//
// Created by Eyal on 13/12/18.
//
#include "LexerClass.h"
#include <fstream>
#include <string.h>
#include <map>
#include <list>
#include <regex>

using namespace std;


/**
 * sets the spaces to be ok.
 * @param line to convert.
 * @return the line after fine spaces.
 */
string addSpaces(string line) {
    string output;
    bool in_quotation_marks = false;
    if (line == "") return line;
    for (char ch : line) {
        switch (ch) {
            case ' ': {
                if (output.back() != ' ' && !output.empty()) output += ' ';
                break;
            }
            case '\"': {
                output += ch;
                in_quotation_marks = !in_quotation_marks;
                break;
            }
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
            case '>':
            case '<':
            case '!':
            case ',':
            case '{':
            case '}':
            case ')':
            case '(': {
                if (!in_quotation_marks) {
                    //first letter of the line, no space.
                    if (output.empty() || output.back() == ' ') {
                        output += ch;
                        output += ' ';
                    } else {
                        output += ' ';
                        output += ch;
                        output += ' ';
                    }
                    break;
                }
            }
            default: {
                output += ch;
            }
        }
    }
    //if the last char is space, delete it.
    if (output.back() == ' ') output.pop_back();
    return output;
}

/**
 * split line to vector by separate sign
 * e.x - splitLine("hey-you-o", v, '-')
 *          --> v = {"hey", "you", "o"}
 * @param line to split
 * @param sign to separte
 */
vector<string> splitLine(const string &line, char sign) {
    stringstream stream(line);
    string split;
    vector<string> spaces_split;
    while (getline(stream, split, sign)) {
        spaces_split.push_back(split);
    }
    return spaces_split;
}

vector<string> LexerClass::lexer(string line) {
    return splitLine(addSpaces(line), ' ');
}

//vector<string> LexerClass:: lexer(string line){
//
//    vector<string> vecAfterLex;
//    string enterTolist = "";
//    regex number("[0-9,.]*");
//    regex var_name("[a-zA-Z_][a-zA-Z_0-9]*");
//    regex stringEx("[^]*");
//    regex whiteSpaces("[\t,\n, ]");
//    //regex operators("[+,-,/,*,=]");
//    regex operators("[^]");
//    smatch m;
//
//    while(line.size()>0) {
//        if (line[0] == '"') {
//            regex_search(line, m, stringEx);
//            for (unsigned i = 0; i < m.size(); ++i) {
//                enterTolist += enterTolist + m.str(i);
//            }
//            vecAfterLex.push_back(enterTolist);
//            line = line.substr(enterTolist.size(), line.size());
//            enterTolist = "";
//        } else if (line[0] == '\t' || line[0] == '\n' || line[0] == ' ') {
//            regex_search(line, m, whiteSpaces);
//            for (unsigned i = 0; i < m.size(); ++i) {
//                enterTolist += enterTolist + m.str(i);
//            }
//            line = line.substr(enterTolist.size(), line.size());
//            enterTolist = "";
//        } else if (line[0] > 48 && line[0] < 58) {
//            regex_search(line, m, number);
//            for (unsigned i = 0; i < m.size(); ++i) {
//                enterTolist += enterTolist + m.str(i);
//            }
//            vecAfterLex.push_back(enterTolist);
//            line = line.substr(enterTolist.size(), line.size());
//            enterTolist = "";
//        } else if ((line[0] >= 65 && line[0] <= 90) || (line[0] >= 97 && line[0] <= 122)) {
//            regex_search(line, m, var_name);
//            for (unsigned i = 0; i < m.size(); ++i) {
//                enterTolist += enterTolist + m.str(i);
//            }
//            vecAfterLex.push_back(enterTolist);
//            line = line.substr(enterTolist.size(), line.size());
//            enterTolist = "";
//        } else {
//            regex_search(line, m, operators);
//            for (unsigned i = 0; i < m.size(); ++i) {
//                enterTolist += enterTolist + m.str(i);
//            }
//            vecAfterLex.push_back(enterTolist);
//            line = line.substr(enterTolist.size(), line.size());
//            enterTolist = "";
//        }
//
//    }
//    return vecAfterLex;
//}

vector<vector<string>> LexerClass::readFromFile(string fileName) {
    string command;
    string line;
    string buffer;
    size_t found;
    size_t begining = 0;
    vector<vector<string>> vector1;
    ifstream myfile(fileName);
    if (myfile.good()) {
        while (getline(myfile, line)) {
            vector<string> afterSplit = lexer(line);
            if (afterSplit.size() > 0) {
                vector1.push_back(lexer(line));
            }

        }
    }
    return vector1;
}


