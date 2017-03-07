#include "MinimaxElement.hpp"

MinimaxElement::MinimaxElement()
{
	b = new Board();
	score = 0;
	next = std::vector<MinimaxElement *>();
}

MinimaxElement::~MinimaxElement()
{
	delete b;
}

void MinimaxElement::updateBoard(Board * b)
{
	this->b = b;
}

void MinimaxElement::updateScore(int score)
{
	this->score = score;
}

void MinimaxElement::addNext(MinimaxElement * me)
{
	this->next.push_back(me);
}
		
Board *MinimaxElement::getBoard()
{
	return this->b;
}

int MinimaxElement::returnScore()
{
	return this->score;
}

std::vector<MinimaxElement *> MinimaxElement::getNext()
{
	return this->next;
}
