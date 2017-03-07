
#include "board.hpp"
#include <vector>


class MinimaxElement 
{
	private:
		Board * b;
		int score;
		std::vector<MinimaxElement *> next;
	public:
		MinimaxElement();
		~MinimaxElement();
		
		void updateBoard(Board * b);
		void updateScore(int score);
		void addNext(MinimaxElement * me);
		
		Board * getBoard();
		int returnScore();
		std::vector<MinimaxElement *> getNext();
};
