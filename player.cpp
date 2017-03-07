#include "player.hpp"

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
	//Creates a timer, but not needed yet.
	time_t now;
	time(&now);
	//Gets the opposite color
	Side other = (this->color == BLACK) ? WHITE : BLACK;
	//Does opponents move, i.e. syncs up internal and external boards
	this->game_board.doMove(opponentsMove, other);
	
	//If no move available or game over, return nullptr.
	if(!this->game_board.hasMoves(this->color) || this->game_board.isDone())
	{
		return nullptr;
	}
	
	/**
	 * Commented out the first 5 points, since unnecessary.
	 */
	
	/*int x = 0, y = 0;
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
	*/
	vector<Move *> possibleMoves = getMoves(game_board);
	Move * bestMove = getBestMove(possibleMoves, &this->game_board);
	//Makes move on internal board instance.
	this->game_board.doMove(bestMove, this->color);
	return bestMove;
}

Move *Player::doMinimax()
{
	vector<Move *> possibleMoves = getMoves(game_board);
	MinimaxElement * now = new MinimaxElement();
	now->updateBoard(&game_board);
	vector<MinimaxElement *> one_step = vector<MinimaxElement *>();
	
}

/**
 * @brief Gets a list of all available moves for the given player.
 * 
 * @param Board board: current board instance.
 * @returns vector<Move *>: vector of all the possible moves.
 */
vector<Move *> Player::getMoves(Board board, Side side)
{
	vector<Move *> moves = vector<Move *>();
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			Move * m = new Move(i, j);
			if(board.checkMove(m, side))
			{
				moves.push_back(m);
			}
		}
	}
	return moves;
}

void Player::moveScore(Move *m)
{
	int x = m->getX();
	int y = m->getY();
	if((x == 0 && y == 0) || (x == 7 && y == 0) || (x == 0 && y == 7)
			|| (x == 7 && y == 7))
		{
			// Corner spaces
			m->setScore(CORNER);
		}
		else if((x == 1 && y == 1) || (x == 1 && y == 6) || (x == 6 && 
				y == 1) || (x == 6 && y == 6))
		{
			//diagonal to corner spaces
			m->setScore(ADJ);
		}
		else if(x == 0 || x == 7 || y == 0 || y == 7)
		{
			//edge spaces
			m->setScore(EDGE);
		}
		else if(((x == 1 || x == 6) && y == 0) || ((x == 1 || x == 6) &&
				y == 6) || ((y == 1 || y == 6) && x == 0) || ((y == 1
				|| y == 6) && x == 6))
		{
			//edge spaces adjacent to corners
			m->setScore(ADJCORNER);
		}
		else
		{
			//regular spaces
			m->setScore(0);
		}
}

/**
 * @brief Given a list of available moves and a board instance, find the
 * best move according to the heuristic function and number of tiles 
 * flipped.
 * 
 * @param vector<Move *> moves:  list of possible move pointers
 * @param Board * board: pointer to the current board instance.
 * 
 * @returns Move *: a move pointer for the best move.
 */
Move *Player::getBestMove(vector<Move *> moves, Board * board)
{
	Move * bestMove = new Move(-1, -1);
	Move * currentMove = bestMove;
	int maxScore = -100;
	int maxTaken = 0;
	Side other = (this->color == BLACK) ? WHITE : BLACK;
	
	vector<Move *>::iterator i;
	for(i = moves.begin(); i != moves.end(); i++)
	{
		Board * board1 = board->copy(); // board to simulate move
		int taken = 0;
		currentMove = *i;
		
		Player::moveScore(currentMove);
		// make the move
		board1->doMove(currentMove, this->color);
		taken = board->count(other) - board1->count(other);
		if(currentMove->getScore() > maxScore)
		{
			// if good move, update info
			maxScore = currentMove->getScore();
			maxTaken = taken;
			bestMove = currentMove;
		}
		else if (taken > maxTaken && currentMove->getScore() >= maxScore)
		{
			// if same score but takes more, update info
			maxTaken = taken;
			maxScore = currentMove->getScore();
			bestMove = currentMove;
		}
	}
	return bestMove;
}
