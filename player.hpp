#ifndef __PLAYER_H__
#define __PLAYER_H__

int EDGE = 1;
int ADJ = -10;
int CORNER = 5;
int ADJCORNER = -2;

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include "MinimaxElement.hpp"
#include <vector>
using namespace std;


class Player {

private:
	Board game_board;
	Side color;
	vector<Move *> getMoves(Board board, Side side);
	Move *getBestMove(vector<Move *> moves, Board * board);
public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *doMinimax();
    void moveScore(Move *m);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
