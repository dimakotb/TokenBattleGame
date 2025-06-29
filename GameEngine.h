#pragma once
#include <iostream>
#include <stack>
const char EMPTY = '.';
const char PLAYER_X = 'X';
const char PLAYER_Y = 'Y';
struct State {
    char board[5][5];
};
class GameEngine {
public:
    std::stack<State> history;

    State game;
    char currentPlayer;

    GameEngine();
    void reset();

    bool isInside(int i, int j);
    bool isWinningState(char player);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    void applyMove(int fromRow, int fromCol, int toRow, int toCol);
    void generateNextStates(const State& current, char player, State nextStates[], int& count);
    bool isGoodState(const State& state, char player);
    bool computerMove();
    char getCell(int row, int col);
    bool hasValidMoves(char player);
};

