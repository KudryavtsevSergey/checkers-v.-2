#include "Config.h"

#include "StdAfx.h"
#include "resource.h"
#include "Game.h"

TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// �������� ������� ��������� ��������� � ���������������� ���������:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInst, int nCmdShow);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// ����������� �������:
int WINAPI WinMain(HINSTANCE hInst, // ���������� ���������� ����������
	HINSTANCE hPrevInst, // �� ����������
	LPSTR lpCmdLine, // �� ����������
	int nCmdShow) // ����� ����������� ������
{
	LoadString(hInst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInst, IDC_MY50, szWindowClass, MAX_LOADSTRING);
	//	HWND hMainWnd; // ������ ���������� �������� ������
	MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������
	MyRegisterClass(hInst);
	if (!InitInstance(hInst, nCmdShow)) {
		return FALSE;
	}

	while (GetMessage(&msg, NULL, NULL, NULL)) { // ��������� ��������� �� �������, ���������� ��-�����, ��
		TranslateMessage(&msg); // �������������� ���������
		DispatchMessage(&msg); // ������� ��������� ������� ��
	}
	return msg.wParam; // ���������� ��� ������ �� ����������
}


ATOM MyRegisterClass(HINSTANCE hInst) {
	WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
	wc.cbSize = sizeof(wc); // ������ ��������� (� ������)
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ������ ������
	wc.lpfnWndProc = WndProc; // ��������� �� ���������������� �������
	wc.lpszMenuName = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
	wc.lpszClassName = szWindowClass; // ��������� �� ��� ������
	wc.cbWndExtra = NULL; // ����� ������������� ������ � ����� ���������
	wc.cbClsExtra = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // ��������� �����������
	wc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2)); // ���������� ��������� ����������� (� ����)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� �������
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(253, 253, 200)); // ���������� ����� ��� �������� ���� ����
	wc.hInstance = hInst; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������
	if (!RegisterClassEx(&wc)) {
		// � ������ ���������� ����������� ������:
		MessageBox(NULL, L"�� ���������� ���������������� �����!", L"������", MB_OK);
		return NULL; // ����������, �������������, ������� �� WinMain
	}
	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow) {
	HWND hMainWnd;
	// �������, ��������� ������:
	hMainWnd = CreateWindow(szWindowClass, // ��� ������
		szTitle,  // ��� ������ (�� ��� ������)
		WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, // ������ ����������� ������
		CW_USEDEFAULT, // ������� ������ �� ��� �
		NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
		visOkna - 42,//    (CW_USEDEFAULT ��� ���������) ������ ������
		visOkna,// ������ ������ (��� ������ � ������, �� ������ �� �����) - NULL
		(HWND)NULL, // ���������� ������������� ����
		NULL, // ���������� ����
		HINSTANCE(hInst), // ���������� ���������� ����������
		NULL); // ������ �� ������� �� WndProc
	if (!hMainWnd) {
		// � ������ ������������� �������� ������ (�������� ��������� � ��):
		MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
		return FALSE;
	}
	ShowWindow(hMainWnd, nCmdShow); // ���������� ������
	UpdateWindow(hMainWnd); // ��������� ������
	return TRUE;
}

Game *game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC; // ������ ���������� ���������� ������ �� ������
	static HANDLE hFile = NULL;
	static HINSTANCE hInst;
	PAINTSTRUCT ps; // ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
	RECT rect; // ���-��, ������������ ������ ���������� �������
	static POINT point;

	switch (uMsg) {
	case WM_CREATE: {
		HMENU hMenubar = CreateMenu();
		HMENU hFile = CreateMenu();
		HMENU hGame = CreateMenu();

		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hGame, L"����");
		AppendMenu(hMenubar, MF_POPUP, ID_prog, L"� ���������");

		AppendMenu(hGame, MF_POPUP, (UINT_PTR)hFile, L"�����");
		AppendMenu(hGame, MF_POPUP, ID_save, L"���������");
		AppendMenu(hGame, MF_STRING, ID_load, L"���������");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_cancel, L"��������");
		AppendMenu(hGame, MF_SEPARATOR, NULL, NULL);
		AppendMenu(hGame, MF_STRING, ID_lose, L"�������");
		AppendMenu(hGame, MF_STRING, ID_exit, L"�����");

		AppendMenu(hFile, MF_STRING, ID_new1, L"���� �����");
		AppendMenu(hFile, MF_STRING, ID_new2, L"��� ������");
		SetMenu(hWnd, hMenubar);
		game = new Game;

	}
					break;
	case WM_LBUTTONDOWN: {
		point.x = HIWORD(lParam) / 65;
		point.y = LOWORD(lParam) / 65;

		game->gameChess(point);
		InvalidateRect(hWnd, NULL, FALSE);
	}
						 break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_prog:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About);
			break;
		case ID_cancel: {
			hFile = CreateFile(FILE_FOR_CANCEL, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile) {
				game->loadGame(hFile);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			else
				MessageBox(hWnd, L"���������� ������� ����", L"������", MB_ICONWARNING | MB_OK);
		}
						break;
		case ID_lose: {
			/*if (movChess == BL) {
				MessageBox(hWnd, L"����� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
			}
			else if (movChess == WH) {
				MessageBox(hWnd, L"׸���� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
			}*/
		}
					  break;
		case ID_exit:
			DestroyWindow(hWnd);
			break;
		case ID_new1:
			game->onePlayerGame();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_new2:
			game->twoPlayerGame();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_save: {
			hFile = CreateFile(FILE_PATH, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile) {
				game->saveGame(hFile);
			}
			else
				MessageBox(hWnd, L"���������� ������� ����", L"������", MB_ICONWARNING | MB_OK);
		}
					  break;
		case ID_load: {
			hFile = CreateFile(FILE_PATH, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile) {
				game->loadGame(hFile);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			else
				MessageBox(hWnd, L"���������� ������� ����", L"������", MB_ICONWARNING | MB_OK);
		}
					  break;
		}
		break;
	case WM_PAINT: // ���� ����� ����������, ��:
		hDC = BeginPaint(hWnd, &ps); // �������������� �������� ����������
		GetWindowRect(hWnd, &rect);
		game->drawBoard(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//�������, ����������� ���� �� ����� ����
/*
BOOL myprover(HWND hWnd, clChess::myChessStruct raspChess[8][8]) {
	BOOL black = FALSE, white = FALSE;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if (raspChess[i][j].chess) {
				if (raspChess[i][j].color == BL) {
					black = TRUE;
				}
				else if (raspChess[i][j].color == WH) {
					white = TRUE;
				}
			}
		}
	}
	if ((!black) && (white)) {
		MessageBox(hWnd, L"����� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
		return FALSE;
	}
	else if ((black) && (!white)) {
		MessageBox(hWnd, L"׸���� ��������.", L"����� ����.", MB_ICONASTERISK | MB_OK);
		return FALSE;
	}
	return TRUE;
}
//�������, ���������� ���� � ����
void mySaveGame(HWND hWnd, HANDLE hFile) {
	DWORD NumberOfBytesRead;
	WriteFile(hFile, raspChess, sizeof(raspChess), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &cl.nShashka, sizeof(clChess::myChessStruct), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &cl.xG, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &cl.yG, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &movChess, sizeof(int), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &START, sizeof(BOOL), &NumberOfBytesRead, NULL);
	WriteFile(hFile, &gameWithComp, sizeof(BOOL), &NumberOfBytesRead, NULL);
	CloseHandle(hFile);
}

void myLoadGame(HWND hWnd, HANDLE hFile) {
	DWORD NumberOfBytesRead;
	ReadFile(hFile, raspChess, sizeof(raspChess), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &cl.nShashka, sizeof(clChess::myChessStruct), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &cl.xG, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &cl.yG, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &movChess, sizeof(int), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &START, sizeof(BOOL), &NumberOfBytesRead, NULL);
	ReadFile(hFile, &gameWithComp, sizeof(BOOL), &NumberOfBytesRead, NULL);
	CloseHandle(hFile);
}*/