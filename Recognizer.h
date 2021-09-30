#pragma once
#include <string>
#include <vector>
#include "Recognizer_sm.h"
typedef std::vector<std::shared_ptr<std::string>> goal_vector;
class Recognizer {
private:
	RecognizerContext _fsm;
	std::string mainGoal;
	goal_vector goals;
	bool readName;
	bool isAcceptable;
public:
	std::string getMainGoal() { return mainGoal; }
	bool hasGoals() { return goals.size(); }
	goal_vector getGoals(){ return goals; }
	Recognizer() :_fsm(*this), isAcceptable(true), readName(false),mainGoal(""){}
	bool isNameRead() { return readName; }
	void createGoal();
	void writeSymbol(char);
	void nameRead() { readName = true; }
	bool checkEqual();
	bool checkString(const char*);
	void Acceptable(){ isAcceptable = true;};
	void Unacceptable(){ isAcceptable = false;};
	void reset();
};