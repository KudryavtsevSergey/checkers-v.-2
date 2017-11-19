#include "Player.h"



Player::Player()
{
	this->point.x = 0;
	this->point.y = 0;
	this->color = NONE;
	this->name = NULL;
	this->ii = FALSE;
	this->isPressedChess = FALSE;
}

Player::Player(int color, char* name, BOOL ii) : name(new char[strlen(name) + 1]) {
	this->point.x = 0;
	this->point.y = 0;
	this->color = color;
	this->ii = ii;
	strcpy_s(this->name, strlen(name) + 1, name);
	this->isPressedChess = FALSE;
}

Player::~Player()
{
	delete[] name;
}

POINT Player::getPoint() {
	return this->point;
}
void Player::setPoint(POINT point) {
	this->point = point;
}

BOOL Player::getIi() {
	return this->ii;
}

int Player::getColor() {
	return this->color;
}

char* Player::getName() {
	return this->name;
}

BOOL Player::checkColor(int color) {
	if (this->color == color) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL Player::getIsPressedChess() {
	return this->isPressedChess;
}
void Player::setIsPressedChess(BOOL isPressedChess) {
	this->isPressedChess = isPressedChess;
}

void Player::copyPlayerTo(Player* player) {
	player->point = this->point;
	player->color = this->color;
	player->name = new char[strlen(this->name) + 1];
	strcpy_s(player->name, strlen(this->name) + 1, this->name);
	player->ii = this->ii;
	player->isPressedChess = this->isPressedChess;
}

void Player::savePlayer(HANDLE hFile) {
	DWORD NumberOfBytesRead;
	WriteFile(hFile, &this->point, sizeof(POINT), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->color, sizeof(int), &NumberOfBytesRead, NULL);
	int lenghtName = strlen(this->name) + 1;
	WriteFile(hFile, &lenghtName, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->name, lenghtName, &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->ii, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &this->isPressedChess, sizeof(BOOL), &NumberOfBytesRead, NULL);
}

void Player::loadPlayer(HANDLE hFile) {
	DWORD NumberOfBytesRead;
	int lenghtName;
	ReadFile(hFile, &this->point, sizeof(POINT), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->color, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &lenghtName, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->name, lenghtName, &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->ii, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &this->isPressedChess, sizeof(BOOL), &NumberOfBytesRead, NULL);
}
