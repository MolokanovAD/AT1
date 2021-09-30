#include <iostream>
#include "statemap.h"
#include "Recognizer.h"
#include <fstream>
using namespace statemap;
int main(int argc, char* argv[]) {
    Recognizer thisContext;
    goal_vector correctness_report;
    int index = 0;
    goal_vector result;
    int retcode = 0;
    std::string str;
    if (argc < 2)
    {
        std::cerr << "No file to check." << std::endl;
        retcode = 2;
    }
    else if (argc > 2)
    {
        std::cerr << "Only one argument is accepted." << std::endl;
        retcode = 3;
    }
    else
    {
        std::ifstream file(argv[1]);
        //std::ifstream file("data.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                std::getline(file, str);
                correctness_report.push_back(std::shared_ptr<std::string>(new std::string("String \"" + str + "\" is ")));
                try {
                    if (thisContext.checkString(str.c_str())) {
                        *correctness_report.at(correctness_report.size() - 1) += "correct";
                        auto new_goals = thisContext.getGoals();
                        for (auto i = result.cbegin(); i < result.cend(); i++) {
                            //≈сли цель со списком требований есть в 
                            //результирующем массиве, ее надо удалить
                            if (*(*i) == thisContext.getMainGoal() && thisContext.hasGoals()) {
                                result.erase(i);
                                break;
                            }
                        }
                        for (auto i : new_goals) {
                            //≈сли цель из нового списка требований уже есть
                            //в результирующем массиве, то ее вставл€ть не надо
                            auto j = result.cbegin();
                            for (; j < result.cend(); j++) {
                                if (*(*j) == *i)
                                    break;
                            }
                            if (j == result.cend())
                                result.push_back(i);
                        }
                    }
                    else
                        *correctness_report.at(correctness_report.size() - 1) += " not correct";
                }
                catch (std::runtime_error&) {
                    retcode = 1;
                }
                thisContext.reset();
            }
            std::string of(argv[1]);
            int sz = of.length();
            of += ".result";
            std::ofstream outFile(of);
            of.erase(sz) += ".check";
            std::ofstream outFile1(of);
            for (auto i : correctness_report) {
                outFile1 << *i << std::endl;
            }
            for (auto i : result) {
                outFile << *i << std::endl;
            }
        }
        else
            std::cerr << "Error: can't open the file" << std::endl;
    }
    return retcode;
}