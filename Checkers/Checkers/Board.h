#pragma once
#include "Config.h"
#include "Chess.h"
#include "StdAfx.h"

class Board
{
public:

	Board();
	~Board();

	BOOL getCanNotSelectAnother();
	void setCanNotSelectAnother(BOOL canNotSelectAnother);

	BOOL getIsChess(POINT point);
	BOOL checkColor(int color, POINT point);
	void setIsShine(BOOL isShine, POINT point);
	BOOL getIsShine(POINT point);
	BOOL getIsQueen(POINT point);
	BOOL getStrikeOnThis(POINT point);

	BOOL isMove(POINT point);
	BOOL isStrike(POINT point);
	BOOL isCheckStrike(int color);
	BOOL isMoveFromTo(POINT pointFrom, POINT pointTo);
	void initializationBoard();
	void initializationMoves();
	void copyBoardTo(Board* board);

	void saveBoard(HANDLE hFile);
	void loadBoard(HANDLE hFile);

	Chess *boardChess[8][8];

private:
	
	BOOL canNotSelectAnother;

	void moveChess(POINT pointFrom, POINT pointTo);

	BOOL isMoveLeftBottom(Chess chess);
	BOOL isMoveRightBottom(Chess chess);
	BOOL isMoveLeftTop(Chess chess);
	BOOL isMoveRightTop(Chess chess);

	BOOL isStrikeLeftBottom(Chess chess);
	BOOL isStrikeRightBottom(Chess chess);
	BOOL isStrikeLeftTop(Chess chess);
	BOOL isStrikeRightTop(Chess chess);
};
