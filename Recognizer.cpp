#include "Recognizer.h"
#include "Recognizer_sm.h"


bool Recognizer::checkString(const char* c) {
    _fsm.enterStartState();
    while (*c != '\0')
    {
        if (*c >= '0' && *c <= '9') {
            _fsm.Digit(*c);
        }
        else if (*c >= 'A' && *c <= 'Z' || *c >= 'a' && *c <= 'z' || *c == '_' || *c == '.') {
            _fsm.Letter(*c);
        }
        else if (*c == ' ') {
            _fsm.Space();
        }
        else if (*c == ':') {
            _fsm.Colon();
        }
        else {
            _fsm.Unknown();
        }
        ++c;
    }
    _fsm.EOS();
    return isAcceptable;
}

void Recognizer::createGoal() {
    if(readName)
        goals.push_back(std::shared_ptr<std::string>(new std::string("")));
}
void Recognizer::writeSymbol(char L) {
    if (readName && !goals.empty())
        *(goals.at(goals.size() - 1)) += L;
    else
        mainGoal += L;
}

bool Recognizer::checkEqual() {
    if (!goals.empty()) {
        auto last_goal = --goals.cend();
        if (**last_goal == mainGoal)
            return true;
        for (auto i = goals.cbegin(); i < last_goal;i++) {
            if (**last_goal == **i) 
                return true;
        }
    }
    return false;
}
void Recognizer::reset() {
    _fsm.setState(Map1::Start);
    isAcceptable = true;
    readName = false;
    mainGoal = "";
    goals.clear();
}
