#include "GameEngine.h"
#include <iostream>
#include <stack>
GameEngine::GameEngine() {
	reset();
}
//This function is used to intialize the constructor and for the reset
void GameEngine::reset() {
	//Intializes 5x5 board
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			game.board[i][j] = EMPTY;

	game.board[0][1] = PLAYER_Y;
	game.board[0][2] = PLAYER_Y;
	game.board[0][3] = PLAYER_Y;

	game.board[1][0] = PLAYER_X;
	game.board[2][0] = PLAYER_X;
	game.board[3][0] = PLAYER_X;

	currentPlayer = PLAYER_X;
}
//return the cell chosen by the user
char GameEngine::getCell(int row, int col) {
	return game.board[row][col];
}
//checks if the player has any valid moves return true if it is
bool GameEngine::hasValidMoves(char player) {
	State nextStates[100];
	int moveCount;
	generateNextStates(game, player, nextStates, moveCount);
	return moveCount > 0;
}
//Check if the selected cell is within the 5x5 board
bool GameEngine::isInside(int i, int j) {
	if (i >= 0 && i < 5 && j >= 0 && j < 5) {
		return true;
	}
	else {
		return false;
	}
}
//Check if the current state is a winning state for either the user or the computer
bool GameEngine::isWinningState(char player) {
	if (player == PLAYER_X) {
		for (int i = 1; i <= 3; ++i)
			if (game.board[i][4] != PLAYER_X)
				return false;
		return true;
	}
	else {
		for (int j = 1; j <= 3; ++j)
			if (game.board[4][j] != PLAYER_Y)
				return false;
		return true;
	}
}

bool GameEngine::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
	if (!isInside(fromRow, fromCol) || !isInside(toRow, toCol)) return false; //check if the cell selected is for the current player and checks if the move is within the 5x5 board
	if (game.board[fromRow][fromCol] != currentPlayer || game.board[toRow][toCol] != EMPTY) return false; //ensure that the destination cell is empty

	if (currentPlayer == PLAYER_X) { //ensures that the user can only move right or can only jump if opponent player is in the next cell
		if (toRow == fromRow && toCol == fromCol + 1) //right move
			return true;
		if (toRow == fromRow && toCol == fromCol + 2) {
			int midCol = fromCol + 1;
			if (game.board[fromRow][midCol] != PLAYER_X && game.board[fromRow][midCol] != EMPTY) //jump move
				return true;
		}
	}
	else { //ensures that the computer can only move downwards or can only jump if opponent player is in the next cell
		if (toRow == fromRow + 1 && toCol == fromCol) //move downwards
			return true;
		if (toRow == fromRow + 2 && toCol == fromCol) {
			int midRow = fromRow + 1;
			if (game.board[midRow][fromCol] != PLAYER_Y && game.board[midRow][fromCol] != EMPTY) //jump move
				return true;
		}
	}

	return false;
}
//move the token from the current cell to the destination cell and change the current player to the other player
void GameEngine::applyMove(int fromRow, int fromCol, int toRow, int toCol) {
	game.board[toRow][toCol] = game.board[fromRow][fromCol]; //moving the token
	game.board[fromRow][fromCol] = EMPTY; //making the current cell empty
	currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_Y : PLAYER_X; //switching the players
}
//Generate all the next valid states for the current player and stores it in nextState array
void GameEngine::generateNextStates(const State& current, char player, State nextStates[], int& count) {
	count = 0; //return the number of generated states
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (current.board[i][j] == player) {
				if (player == PLAYER_X) {
					if (isValidMove(i, j, i, j + 1)) {//checks if it's valid to move to the right
						State next = current;
						next.board[i][j + 1] = player;
						next.board[i][j] = EMPTY;
						nextStates[count++] = next;
					}
					if (isValidMove(i, j, i, j + 2)) {//check if it's valid to jump
						State next = current;
						next.board[i][j + 2] = player;
						next.board[i][j] = EMPTY;
						nextStates[count++] = next;
					}
				}
				else {
					if (isValidMove(i, j, i + 1, j)) {//checks if it's valid to move downwards
						State next = current;
						next.board[i + 1][j] = player;
						next.board[i][j] = EMPTY;
						nextStates[count++] = next;
					}
					if (isValidMove(i, j, i + 2, j)) {//check if it's valid to jump
						State next = current;
						next.board[i + 2][j] = player;
						next.board[i][j] = EMPTY;
						nextStates[count++] = next;
					}
				}
			}
		}
	}
}
//This recursive function checks whether the given game state is "good" for the current player, no matter what the opponent does, they can still eventually win.
bool GameEngine::isGoodState(const State& state, char player) {
	//push the current state in the stack history
	history.push(state); 
	
	//if the current state is a winning state for the player, the state is popped from the stack,if not generate the next possible state
	if (isWinningState(player)) {
		history.pop(); 
		return true;
	}
	//Determine the opponent of the current player
	char opponent = (player == PLAYER_X) ? PLAYER_Y : PLAYER_X;
	//if the opponent is winning in this state then this state is bad for the current player
	if (isWinningState(opponent)) {
		history.pop();
		return false;
	}
	//calling the function generateNextState to determine all the possible states for the player from the current state
	State nextStates[100];
	int moveCount;//how many states is made
	generateNextStates(state, player, nextStates, moveCount);
	//for each state in the next state we determine the next move from the opponent
	for (int i = 0; i < moveCount; ++i) {
		if (!isGoodState(nextStates[i], opponent)) {
			history.pop(); 
			return true;// a good state is found,backtrack to check other better states
		}
	}
	// All possible moves(children) for the current player lead to good outcomes for the opponent, so this is a bad state. Backtracks.
	history.pop(); 
	return false;
}

bool GameEngine::computerMove() {
	if (currentPlayer == PLAYER_Y) {//ensuring that this function can only be used by Player Y(Computer)
		State nextStates[100];
		int moveCount;
		generateNextStates(game, currentPlayer, nextStates, moveCount);//generate all the possible next moves for the computer
		//if no possible moves the computer's turn is skipped and the user plays instead
		if (moveCount == 0) {
			currentPlayer = PLAYER_X;
			return false;
		}
		//it calls the isGoodState function to check whether the resulting state is favorable for the computer.
		for (int i = 0; i < moveCount; ++i) {
			if (!isGoodState(nextStates[i], PLAYER_X)) {//will check if the user can still win or not
				game = nextStates[i];
				currentPlayer = PLAYER_X;
				return true;//a move was made
			}
		}

		game = nextStates[0];//if no good state is found the computer chooses the first available move
		currentPlayer = PLAYER_X;
		return true;
	}
	return false;
}
