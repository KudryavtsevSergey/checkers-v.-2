#pragma once
#include "Config.h"

#include "StdAfx.h"

class Chess
{
public:

	Chess();
	Chess(POINT point);
	~Chess();

	POINT getPoint();

	void setColor(int color);
	int getColor();
	BOOL checkColor(int color);

	void setIsChess(BOOL isChess);
	BOOL getIsChess();

	void setIsQueen(BOOL isQueen);
	BOOL getIsQueen();

	void setIsSelected(BOOL isSelected);
	BOOL getIsSelected();

	void setIsShine(BOOL isShine);
	BOOL getIsShine();

	void setStrikeOnThis(BOOL strikeOnThis);
	BOOL getStrikeOnThis();

	void setChess(BOOL chess = FALSE, int color = NONE);

	void copyChessTo(Chess* chess);

	void saveChess(HANDLE hFile);
	void loadChess(HANDLE hFile);


	BOOL isMoveLeftBottom();
	BOOL isMoveRightBottom();
	BOOL isMoveLeftTop();
	BOOL isMoveRightTop();

	BOOL isStrikeLeftBottom();
	BOOL isStrikeRightBottom();
	BOOL isStrikeLeftTop();
	BOOL isStrikeRightTop();

private:
	POINT point;
	BOOL isChess;
	BOOL isQueen;
	BOOL isSelected;
	BOOL isShine;
	BOOL strikeOnThis;
	int color;
};
