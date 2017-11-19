#pragma once
#include "Config.h"
#include "Board.h"
#include "Player.h"
#include "StdAfx.h"

class Ai
{
public:
	Ai();
	Ai(int color, int depthOfTreeConstruction);
	~Ai();
	void initial(Player* playerOne, Player* playerTwo);
	Board* getMove(Board* board, Player* currentPlayer);

private:
	struct listOfMoves {
		struct oneMove {
			Board* board;
			int mark;
			BOOL extraMove;
			oneMove *nextList;
			listOfMoves *nextTree;
		};
		oneMove *first, *last;
	};

	int color;
	int depthOfTreeConstruction;
	int maxSum = -1000;
	Player* playerOne;
	Player* playerTwo;

	void Delete(listOfMoves* listTree);
	void Addlist(listOfMoves** listTree, Board* board);
	Board* searchMove(listOfMoves* listTree, int count = 0, BOOL extraMove = TRUE);
	listOfMoves* buildTreeOfMoves(listOfMoves** listTree, Board* board, Player* currentPlayer, int depthOfTreeConstruction);
};
