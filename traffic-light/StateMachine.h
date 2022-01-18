class StateMachine
{
  public:
    StateMachine(int initState);
    void addState(int stateId, int nextStateId);
    void setState(int newState);
    int getState();
    void transition();
  private:
    int states[10];
    int currentState;
};
