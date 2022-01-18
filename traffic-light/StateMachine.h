class StateMachine
{
  public:
    StateMachine(int initState);
    void addTransition(int stateId, int nextStateId);
    void setState(int newState);
    int getState();
    void transition();
  private:
    int states[10];
    int currentState;
};
