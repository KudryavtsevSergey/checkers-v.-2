#include "Game.h"



Game::Game() {
	this->board = new Board;
	this->playerOne = new Player;
	this->playerTwo = new Player;
	this->currentPlayer = playerOne;
}


Game::~Game() {
	delete board;
}

void Game::gameChess(POINT point) {
	BOOL strike = FALSE;
	if (currentPlayer != NULL) {
		if (point.x < 8 && point.y < 8 && ((point.x % 2) ^ (point.y % 2))) {
			if ((!board->getCanNotSelectAnother()) && (board->getIsChess(point)) && (board->checkColor(currentPlayer->getColor(), point))) {
				board->initializationMoves();
				if (board->isCheckStrike(currentPlayer->getColor())) {
					board->initializationMoves();
					if (board->isStrike(point)) {
						board->setIsShine(FALSE, currentPlayer->getPoint());
						currentPlayer->setPoint(point);
						currentPlayer->setIsPressedChess(TRUE);
						board->setIsShine(TRUE, point);
					}
				}
				else if (board->isMove(point)) {
					board->setIsShine(FALSE, currentPlayer->getPoint());
					currentPlayer->setPoint(point);
					currentPlayer->setIsPressedChess(TRUE);
					board->setIsShine(TRUE, point);
				}
			}
			else {
				if (currentPlayer->getIsPressedChess()) {
					if (board->isStrike(currentPlayer->getPoint())) {
						strike = TRUE;
					}
					if ((board->isMoveFromTo(currentPlayer->getPoint(), point))) {
						currentPlayer->setPoint(point);
						board->initializationMoves();
						if (strike && board->isStrike(currentPlayer->getPoint())) {
							board->setIsShine(TRUE, currentPlayer->getPoint());
							board->setCanNotSelectAnother(TRUE);
						}
						else {
							board->setCanNotSelectAnother(FALSE);
							currentPlayer->setIsPressedChess(FALSE);
							currentPlayer = currentPlayer == playerOne ? playerTwo : playerOne;
						}
					}
				}
			}
		}
		if ((currentPlayer == playerTwo) && (playerTwo->getIi())) {
			//board = 
			ai->getMove(board, currentPlayer);
			currentPlayer = currentPlayer == playerOne ? playerTwo : playerOne;
		}
	}
}

void Game::onePlayerGame() {
	board->initializationBoard();
	playerOne = new Player(0, "Player One!");
	playerTwo = new Player(1, "Player ii!", true);
	ai = new Ai(BL, 5);
	ai->initial(playerOne, playerTwo);
	currentPlayer = playerOne;
}

void Game::twoPlayerGame() {
	board->initializationBoard();
	playerOne = new Player(0, "Player One!");
	playerTwo = new Player(1, "Player Two!");
	currentPlayer = playerOne;
}

void Game::drawBoard(HDC hDC) {
	HPEN hPen;
	HBRUSH hBrush;
	HDC hDCmem = CreateCompatibleDC(hDC);
	HBITMAP Bitmap;
	HANDLE hOldBitmap;
	POINT point;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i % 2) ^ (j % 2)) {
				point.x = i;
				point.y = j;
				if (board->getStrikeOnThis(point)) {
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					hBrush = CreateSolidBrush(RGB(0, 0, 0));
					SelectObject(hDC, hPen);
					SelectObject(hDC, hBrush);
				}
				else {
					hPen = CreatePen(PS_SOLID, 0, RGB(129, 88, 47));
					hBrush = CreateSolidBrush(RGB(129, 88, 47));
					SelectObject(hDC, hPen);
					SelectObject(hDC, hBrush);
				}
				Rectangle(hDC, 65 * j, 65 * i, 65 * (j + 1), 65 * (i + 1));
				DeleteObject(hPen);
				DeleteObject(hBrush);
				if (board->getIsChess(point)) {
					GetObject(hBitmapNum1, sizeof(BITMAP) / 4, &Bitmap);
					if (board->getIsShine(point)) {
						hOldBitmap = SelectObject(hDCmem, hBitmapNum2);
					}
					else {
						hOldBitmap = SelectObject(hDCmem, hBitmapNum1);
					}

					if (board->checkColor(WH, point)) {
						if (board->getIsQueen(point) == TRUE) {
							StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 195, 0, 65, 65, SRCCOPY);
						}
						else {
							StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 130, 0, 65, 65, SRCCOPY);
						}
					}
					else if (board->checkColor(BL, point)) {
						if (board->getIsQueen(point) == TRUE) {
							StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 65, 0, 65, 65, SRCCOPY);
						}
						else {
							StretchBlt(hDC, 65 * j, 65 * i, 65, 65, hDCmem, 0, 0, 65, 65, SRCCOPY);
						}
					}
				}
			}
		}
	}
	DeleteDC(hDCmem);
}

void Game::saveGame(HANDLE hFile) {
	DWORD NumberOfBytesRead;
	this->board->saveBoard(hFile);
	this->playerOne->savePlayer(hFile);
	this->playerTwo->savePlayer(hFile);
	int player = 0;
	if (this->currentPlayer == this->playerOne) {
		player = 1;
	}
	else {
		player = 2;
	}
	WriteFile(hFile, &player, sizeof(int), &NumberOfBytesRead, NULL);
	CloseHandle(hFile);
}

void Game::loadGame(HANDLE hFile) {
	DWORD NumberOfBytesRead;
	this->board->loadBoard(hFile);
	this->playerOne->loadPlayer(hFile);
	this->playerTwo->loadPlayer(hFile);
	int player = 0;
	ReadFile(hFile, &player, sizeof(int), &NumberOfBytesRead, NULL);
	if (player == 1) {
		this->currentPlayer = playerOne;
	}
	else if(player == 2){
		this->currentPlayer = playerTwo;
	}
	CloseHandle(hFile);
}