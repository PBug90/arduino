#include "StateMachine.h";

StateMachine::StateMachine(int initState) {
  currentState = initState;
}

void StateMachine::addState(int id, int nextStateId) {
  states[id] = nextStateId;
}

void StateMachine::transition() {
  currentState = states[currentState];
}

void StateMachine::setState(int newState) {
  currentState = newState;
}

int StateMachine::getState() {
  return currentState;
}
