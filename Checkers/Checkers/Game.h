#pragma once
#include "Config.h"
#include "Player.h"
#include "Ai.h"
#include "Board.h"
#include "StdAfx.h"
class Game
{
public:
	Game();
	~Game();

	void gameChess(POINT point);

	void onePlayerGame();
	void twoPlayerGame();

	void drawBoard(HDC hDC);

	void saveGame(HANDLE hFile);
	void loadGame(HANDLE hFile);

private:
	Board* board;
	Player* playerOne;
	Player* playerTwo;
	Player* currentPlayer;
	Ai* ai;

	HBITMAP hBitmapNum1 = (HBITMAP)LoadImage(NULL, L"data//checkers1.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP hBitmapNum2 = (HBITMAP)LoadImage(NULL, L"data//checkers2.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP hBitmapNum3 = (HBITMAP)LoadImage(NULL, L"data//checkers3.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
};

