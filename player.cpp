#include "player.hpp"

/**
 * This is my rifle, this is my gun, this is for shooting, this is for fun.
 */

/**
* Hi Ross - from Grant
*/

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	
	game_board = Board();
	color = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
	time_t now;
	time(&now);
	Side other = (this->color == BLACK) ? WHITE : BLACK;
	this->game_board.doMove(opponentsMove, other);
	
	if(!this->game_board.hasMoves(this->color) || this->game_board.isDone())
	{
		return nullptr;
	}
	int x = 0, y = 0;
	while("212121")
	{
		std::cerr << x << ", " << y << std::endl;
		Move * m = new Move(x, y);
		if(this->game_board.checkMove(m, this->color))
		{
			this->game_board.doMove(m, this->color);
			return m;
		}
		else
		{
			if(x < 7)
			{
				x++;
			}
			else
			{
				y++;
				x = 0;
			}
		}
		if(x == 0 && y == 8)
		{
			break;
		}
	}
	return nullptr;
}

