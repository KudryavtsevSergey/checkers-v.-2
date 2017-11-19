#include "Chess.h"



Chess::Chess() {
	this->isChess = FALSE;
	this->isQueen = FALSE;
	this->isSelected = FALSE;
	this->isShine = FALSE;
	this->strikeOnThis = FALSE;
	this->color = NONE;
}

Chess::Chess(POINT point) {
	this->point = point;
	this->isChess = FALSE;
	this->isQueen = FALSE;
	this->isSelected = FALSE;
	this->isShine = FALSE;
	this->strikeOnThis = FALSE;
	this->color = NONE;
}


Chess::~Chess() {

}

BOOL Chess::isMoveLeftBottom() {
	if ((this->point.x < 7) && (this->point.y > 0)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isMoveRightBottom() {
	if ((this->point.x < 7) && (this->point.y < 7)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isMoveLeftTop() {
	if ((this->point.x > 0) && (this->point.y > 0)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isMoveRightTop() {
	if ((this->point.x > 0) && (this->point.y < 7)) {
		return TRUE;
	}
	return FALSE;
}
/*
BOOL Chess::isMove() {
	if (this->isChess && this->isQueen) {
		if (this->isMoveLeftBottom() || this->isMoveLeftTop() || this->isMoveRightBottom() || this->isMoveRightTop()) {
			return TRUE;
		}
	}
	else if (this->isChess) {
		if (this->checkColor(WH)) {
			if (this->isMoveLeftTop() || this->isMoveRightTop()) {
				return TRUE;
			}
		}
		else if (this->checkColor(BL)) {
			if (this->isMoveLeftBottom() || this->isMoveRightBottom()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}
*/
BOOL Chess::isStrikeLeftBottom() {
	if ((this->point.x < 6) && (this->point.y > 1)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeRightBottom() {
	if ((this->point.x < 6) && (this->point.y < 6)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeLeftTop() {
	if ((this->point.x > 1) && (this->point.y > 1)) {
		return TRUE;
	}
	return FALSE;
}

BOOL Chess::isStrikeRightTop() {
	if ((this->point.x > 1) && (this->point.y < 6)) {
		return TRUE;
	}
	return FALSE;
}
/*
BOOL Chess::isStrike() {
	if (this->isChess && this->isQueen) {
		if (this->isStrikeLeftBottom() || this->isStrikeLeftTop() || this->isStrikeRightBottom() || this->isStrikeRightTop()){
			return TRUE;
		}
	}
	else if (this->isChess) {
		if (this->isStrikeLeftBottom() || this->isStrikeLeftTop() || this->isStrikeRightBottom() || this->isStrikeRightTop()){
				return TRUE;
		}
	}
	return FALSE;
}
*/
POINT Chess::getPoint() {
	return this->point;
}

void Chess::setColor(int color) {
	this->color = color;
}
int Chess::getColor() {
	return this->color;
}
BOOL Chess::checkColor(int color) {
	if (this->color == color) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Chess::setIsChess(BOOL isChess) {
	this->isChess = isChess;
}
BOOL Chess::getIsChess() {
	return this->isChess;
}

void Chess::setIsQueen(BOOL isQueen) {
	this->isQueen = isQueen;
}

BOOL Chess::getIsQueen() {
	return this->isQueen;
}

void Chess::setIsSelected(BOOL isSelected) {
	this->isSelected = isSelected;
}

BOOL Chess::getIsSelected() {
	return this->isSelected;
}
/*
void Chess::setNecessaryStrike(BOOL necessaryStrike) {
	this->necessaryStrike = necessaryStrike;
}

BOOL Chess::getNecessaryStrike() {
	return this->necessaryStrike;
}*/

void Chess::setIsShine(BOOL isShine) {
	this->isShine = isShine;
}

BOOL Chess::getIsShine() {
	return this->isShine;
}

void Chess::setStrikeOnThis(BOOL strikeOnThis) {
	this->strikeOnThis = strikeOnThis;
}

BOOL Chess::getStrikeOnThis() {
	return this->strikeOnThis;
}

void Chess::setChess(BOOL chess, int color) {
	this->setIsChess(chess);
	this->setColor(color);
	this->setIsQueen(FALSE);
	this->setIsSelected(FALSE);
	this->setIsShine(FALSE);
	this->setStrikeOnThis(FALSE);
}

void Chess::copyChessTo(Chess* chess) {
	chess->point = this->point;
	chess->isChess = this->isChess;
	chess->isQueen = this->isQueen;
	chess->isSelected = this->isSelected;
	chess->isShine = this->isShine;
	chess->strikeOnThis = this->strikeOnThis;
	chess->color = this->color;
}

void Chess::saveChess(HANDLE hFile) {
	DWORD NumberOfBytesRead;
	WriteFile(hFile, &this->point, sizeof(POINT), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->isChess, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->isQueen, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->isSelected, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->isShine, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->strikeOnThis, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->color, sizeof(int), &NumberOfBytesRead, NULL);
}

void Chess::loadChess(HANDLE hFile) {
	DWORD NumberOfBytesRead;
	ReadFile(hFile, &this->point, sizeof(POINT), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->isChess, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->isQueen, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->isSelected, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->isShine, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->strikeOnThis, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->color, sizeof(int), &NumberOfBytesRead, NULL);
}