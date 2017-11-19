#define _CRT_SECURE_NO_WARNINGS
#include "Ai.h"
#include <stdio.h>

Ai::Ai() {
	this->color = BL;
	this->depthOfTreeConstruction = 5;
}

Ai::Ai(int color, int depthOfTreeConstruction) {
	this->color = color;
	this->depthOfTreeConstruction = depthOfTreeConstruction;
}

Ai::~Ai() {
}

void Ai::Delete(listOfMoves *listSost) {
	listOfMoves::oneMove *additionalMove;
	if (listSost != NULL) {
		additionalMove = (*listSost).first;
		while (additionalMove != NULL) {
			this->Delete((*additionalMove).nextTree);
			additionalMove = (*additionalMove).nextList;
		}
		delete additionalMove;
	}
}

void Ai::Addlist(listOfMoves** listTree, Board * board) {
	listOfMoves::oneMove* additionalMove;
	if (*listTree == NULL) {
		*listTree = new listOfMoves;
		(*listTree)->first = NULL;
	}
	additionalMove = new listOfMoves::oneMove;
	additionalMove->board = new Board;
	board->copyBoardTo(additionalMove->board);
	additionalMove->nextList = NULL;
	additionalMove->nextTree = NULL;
	additionalMove->mark = 0;
	if ((*listTree)->first == NULL) {
		(*listTree)->first = additionalMove;
	}
	else {
		(*listTree)->last->nextList = additionalMove;
	}
	(*listTree)->last = additionalMove;
}

Ai::listOfMoves* Ai::buildTreeOfMoves(listOfMoves** listTree,Board* board, Player* currentPlayer, int depthOfTreeConstruction) {
	/*if (depthOfTreeConstruction) {
		FILE *file;
		if ((file = fopen("OUT.txt", "w+")) == NULL) {
			printf("Невозможно открыть файл\n");
			exit(1);
		};
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				int key = board->boardChess[i][j]->getColor();
				if (key == 2)
					fprintf(file, "  ");
				else
					fprintf(file, "%d ", key);
			}
			putc('\n', file);
		}
		fprintf(file, "%d\n%d\n%s\n", currentPlayer->getColor(), currentPlayer->getIsPressedChess(), currentPlayer->getName());
		fclose(file);
		if (board->isCheckStrike(currentPlayer->getColor())) {
	
		}
		else {
			for (int X = 0; X < 8; X++) {
				for (int Y = 0; Y < 8; Y++) {
					if ((X < 8 && Y < 8 && ((X % 2) ^ (Y % 2))) && (board->getIsChess(X, Y)) && (board->checkColor(currentPlayer->getColor(), X, Y) && (board->isMove(X, Y) || (board->isStrike(X, Y))))) {
						if (board->isCheckStrike(currentPlayer->getColor())) {
							if (board->getNecessaryStrike(X, Y)) {
								currentPlayer->setXY(X, Y);
								currentPlayer->setIsPressedChess(TRUE);
								for (int i = 2; i < 8; i++) {
									if ((board->isStrikeFromTo(currentPlayer->getX(), currentPlayer->getY(), X - i, Y - i))) {
										currentPlayer->setXY(X - i, Y - i);
										if (!board->isStrike(currentPlayer->getX(), currentPlayer->getY())) {
											currentPlayer->setIsPressedChess(FALSE);
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
										}
										else {
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer, depthOfTreeConstruction - 1);
										}
									}
								}
								for (int i = 2; i < 8; i++) {
									if ((board->isStrikeFromTo(currentPlayer->getX(), currentPlayer->getY(), X - i, Y + i))) {
										currentPlayer->setXY(X - i, Y + i);
										if (!board->isStrike(currentPlayer->getX(), currentPlayer->getY())) {
											currentPlayer->setIsPressedChess(FALSE);
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
										}
										else {
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer, depthOfTreeConstruction - 1);
										}
									}
								}
								for (int i = 2; i < 8; i++) {
									if ((board->isStrikeFromTo(currentPlayer->getX(), currentPlayer->getY(), X + i, Y + i))) {
										currentPlayer->setXY(X + i, Y + i);
										if (!board->isStrike(currentPlayer->getX(), currentPlayer->getY())) {
											currentPlayer->setIsPressedChess(FALSE);
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
										}
										else {
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer, depthOfTreeConstruction - 1);
										}
									}
								}
								for (int i = 2; i < 8; i++) {
									if ((board->isStrikeFromTo(currentPlayer->getX(), currentPlayer->getY(), X + i, Y - i))) {
										currentPlayer->setXY(X + i, Y - i);
										if (!board->isStrike(currentPlayer->getX(), currentPlayer->getY())) {
											currentPlayer->setIsPressedChess(FALSE);
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
										}
										else {
											this->Addlist(listTree, board);
											*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer, depthOfTreeConstruction - 1);
										}
									}
								}
							}
						}
						else {
							board->setIsShine(FALSE, currentPlayer->getX(), currentPlayer->getY());
							currentPlayer->setXY(X, Y);
							currentPlayer->setIsPressedChess(TRUE);

							if (currentPlayer->getIsPressedChess()) {
								for (int i = 1; i < 8; i++) {
									if (board->isMoveFromTo(currentPlayer->getX(), currentPlayer->getY(), X - i, Y - i)) {
										currentPlayer->setXY(X - i, Y - i);
										currentPlayer->setIsPressedChess(FALSE);
										this->Addlist(listTree, board);
										*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
									}
								}
								for (int i = 1; i < 8; i++) {
									if (board->isMoveFromTo(currentPlayer->getX(), currentPlayer->getY(), X - i, Y + i)) {
										currentPlayer->setXY(X - i, Y + i);
										currentPlayer->setIsPressedChess(FALSE);
										this->Addlist(listTree, board);
										*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
									}
								}
								for (int i = 1; i < 8; i++) {
									if (board->isMoveFromTo(currentPlayer->getX(), currentPlayer->getY(), X + i, Y + i)) {
										currentPlayer->setXY(X + i, Y + i);
										currentPlayer->setIsPressedChess(FALSE);
										this->Addlist(listTree, board);
										*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
									}
								}
								for (int i = 1; i < 8; i++) {
									if (board->isMoveFromTo(currentPlayer->getX(), currentPlayer->getY(), X + i, Y - i)) {
										currentPlayer->setXY(X + i, Y - i);
										currentPlayer->setIsPressedChess(FALSE);
										this->Addlist(listTree, board);
										*listTree = buildTreeOfMoves(&(*listTree)->last->nextTree, board, currentPlayer == playerOne ? playerTwo : playerOne, depthOfTreeConstruction - 1);
									}
								}
							}
						}
					}
				}
			}
		}
	}*/
	return NULL;
}

Board* Ai::searchMove(listOfMoves* listTree, int count, BOOL extraMove) {
	listOfMoves::oneMove *additionalMove;
	Board *board = NULL;
	Board *boardReturn = NULL;
	if (listTree != NULL) {
		additionalMove = listTree->first;
		while (additionalMove != NULL) {
			if (extraMove) {
				additionalMove->board->copyBoardTo(additionalMove->board);
			}
			board = this->searchMove(additionalMove->nextTree, count + additionalMove->mark, extraMove ? (additionalMove->extraMove ? TRUE : FALSE) : FALSE);
			if ((boardReturn == NULL) || (this->maxSum < count)) {
				if (board != NULL) {
					board->copyBoardTo(boardReturn);
				}
			}
			additionalMove = additionalMove->nextList;
		}
	}
	return boardReturn;
}

void Ai::initial(Player* playerOne, Player* playerTwo) {
	this->playerOne = new Player;
	playerOne->copyPlayerTo(this->playerOne);
	this->playerTwo = new Player;
	playerTwo->copyPlayerTo(this->playerTwo);

}

Board* Ai::getMove(Board* board, Player* currentPlayer) {
	listOfMoves *listTree = NULL;
	Board* boardIn = new Board;
	board->copyBoardTo(boardIn);
	this->Addlist(&listTree, board);
	buildTreeOfMoves(&listTree, boardIn, this->playerTwo, this->depthOfTreeConstruction);
	Board* boardReturn = this->searchMove(listTree);
	this->Delete(listTree);
	return boardReturn;
}
