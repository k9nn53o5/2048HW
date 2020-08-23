/**********************set _2048AI = 0 to play   2048   *************************/
/**********************set _2048AI = 1 to launch 2048 AI*************************/

/*I use conio.h handle console IO. You may need to change the library and the code according to your OS*/
/*If you don's want to play the game, simply remove this line and the corresponding _getch()*/
int _2048AI = 0;

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h> 

double PROB4 = 0.1;


int FastLog2(int a) {
	if (a == 0) {
		return 0;
	}

	int count = 0;
	while (a != 1) {
		a = a >> 1;
		count++;
	}
	return count;
}

// if you want to map a borad to a scord, call this function to map the board to an unsigned long long,
// and then map this unsigned long long to a score
unsigned long long BoardToULL(int board[4][4]) {
	unsigned long long h;
	int logBoard[4][4];
	int exp;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				logBoard[i][j] = 0;
			}
			else {
				logBoard[i][j] = FastLog2(board[i][j]);
			}
		}
	}


	h = 0;
	unsigned long long pow2 = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int temp = logBoard[i][j];
			for (int k = 8; k > 0; k = k >> 1) {
				if (temp >= k) {
					h = h | pow2;
					temp -= k;
				}

				pow2 = pow2 << 1;
			}
		}
	}

	return h;
}

//Copy the content of src to dst
void CopyBoard(int dst[4][4], int src[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dst[i][j] = src[i][j];
		}
	}
}

//return 1 if the contents of b1 and b2 are the same
//return 0 otherwise
int AreEqual(int b1[4][4], int b2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b1[i][j] != b2[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void PrintBoard(int board[4][4]) {
	for (int y = 0; y < 17; y++) {
		if (y % 4 == 0) {
			printf("*****************************\n");
		}
		else if (y % 4 == 1 || y % 4 == 3) {
			printf("*      *      *      *      *\n");
		}
		else {
			int i = y / 4;
			for (int j = 0; j < 4; j++) {
				printf("*");

				if (board[i][j] == 0) {
					printf("      ");
				}
				else if (board[i][j] < 10) {
					printf("   %d  ", board[i][j]);
				}
				else if (board[i][j] < 100) {
					printf("  %d  ", board[i][j]);
				}
				else if (board[i][j] < 1000) {
					printf("  %d ", board[i][j]);
				}
				else {
					printf(" %d ", board[i][j]);
				}
			}
			printf("*\n");
		}
	}

	return;
}

//print the old board, the action, and the new board
void PrintGame(int oldBoard[4][4], int newBoard[4][4], char a) {
	PrintBoard(oldBoard);
	if (a == 'w') {
		printf("\n\nUp\n\n");
	}
	else if (a == 's') {
		printf("\n\nDown\n\n");
	}
	else if (a == 'd') {
		printf("\n\nRight\n\n");
	}
	else if (a == 'a') {
		printf("\n\nLeft\n\n");
	}
	PrintBoard(newBoard);
}

//return the number of 0s in the board
int GetNEmptyPos(int b[4][4]) {
	int count = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b[i][j] == 0) {
				count++;
			}
		}
	}

	return count;
}

int GenNewNumber() {
	if ((double)rand() / (double)RAND_MAX < PROB4) {
		return 4;
	}
	return 2;
}

void InitBoard(int board[4][4]) {
	int initCol1, initRow1, initCol2, initRow2;
	initCol1 = rand() % 4;
	initRow1 = rand() % 4;

	initCol2 = rand() % 4;
	initRow2 = rand() % 4;

	while (initCol1 == initCol2 && initRow1 == initRow2) {
		initCol2 = rand() % 4;
		initRow2 = rand() % 4;
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	board[initCol1][initRow1] = GenNewNumber();
	board[initCol2][initRow2] = GenNewNumber();

	return;
}


void Shift(int board[4][4], int oldX, int oldY, int newX, int newY) {
	if (oldX == newX && oldY == newY) {
		return;
	}
	else {
		board[newX][newY] = board[oldX][oldY];
		board[oldX][oldY] = 0;
		return;
	}
}

void UpdateIthColumn(int board[4][4], int i, char a) {
	int dir = 1;
	int first = 0;
	if (a == 's') {
		dir = -1;
		first = 3;
	}

	int hasNumber = 0;
	int nextPos = 0;

	for (int j = first; j >= 0 && j < 4; j += dir) {
		if (board[j][i] > 0) {
			hasNumber = 1;
			Shift(board, j, i, first, i);
			nextPos = j + dir;
			break;
		}
	}

	if (!hasNumber) {
		return;
	}

	int mergePos = first;
	int emptyPos = first + dir;
	int hasMerged = 0;

	for (int j = nextPos; j >= 0 && j < 4; j += dir) {
		if (board[j][i] > 0) {
			if (!hasMerged && board[mergePos][i] == board[j][i]) {
				board[mergePos][i] = board[mergePos][i] << 1;
				board[j][i] = 0;
				hasMerged = 1;
			}
			else {
				Shift(board, j, i, emptyPos, i);
				mergePos = emptyPos;
				emptyPos += dir;
				hasMerged = 0;
			}
		}
	}
}

void UpdateIthRow(int board[4][4], int i, char a) {
	int dir = 1;
	int first = 0;
	if (a == 'd') {
		dir = -1;
		first = 3;
	}

	int hasNumber = 0;
	int nextPos = 0;

	for (int j = first; j >= 0 && j < 4; j += dir) {
		if (board[i][j] > 0) {
			hasNumber = 1;
			Shift(board, i, j, i, first);
			nextPos = j + dir;
			break;
		}
	}

	if (!hasNumber) {
		return;
	}

	int mergePos = first;
	int emptyPos = first + dir;
	int hasMerged = 0;

	for (int j = nextPos; j >= 0 && j < 4; j += dir) {
		if (board[i][j] > 0) {
			if (!hasMerged && board[i][mergePos] == board[i][j]) {
				board[i][mergePos] = board[i][mergePos] << 1;
				board[i][j] = 0;
				hasMerged = 1;
			}
			else {
				Shift(board, i, j, i, emptyPos);
				mergePos = emptyPos;
				emptyPos += dir;
				hasMerged = 0;
			}
		}
	}
}

int IsGameOver(int board[4][4]) {
	if (GetNEmptyPos(board) > 0) {
		return 0;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == board[i][j + 1]) {
				return 0;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == board[i + 1][j]) {
				return 0;
			}
		}
	}

	return 1;
}

void UpdateBoard(int board[4][4], char a) {
	if (a == 'w' || a == 's') {
		for (int i = 0; i < 4; i++) {
			UpdateIthColumn(board, i, a);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			UpdateIthRow(board, i, a);
		}
	}
	return;
}

void AddNewNumber(int board[4][4]) {
	int nEmptyPos = GetNEmptyPos(board);

	int r = 1 + rand() % nEmptyPos;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				r--;
				if (r == 0) {
					board[i][j] = GenNewNumber();
					break;
				}
			}
		}
	}
}

char AIGenNextMove(int b[4][4]) {
	char move = 'w'; //move = 'w', 's', 'a', or 'd'
					 /*Your code goes here*/
	return move;
}

int main() {
	int board[4][4];
	int oldBoard[4][4];
	srand(time(NULL));
	InitBoard(board);
	PrintBoard(board);

	for (;;) {
		char c;
		CopyBoard(oldBoard, board);

		if (!_2048AI) {
			c = _getch();
			if (c != 'w' && c != 's' && c != 'a' && c != 'd') {
				printf("\n\n please press w, s, a, or d\n");
				continue;
			}
		}
		else {
			c = AIGenNextMove(oldBoard);
		}

		UpdateBoard(board, c);

		if (!AreEqual(board, oldBoard)) {
			AddNewNumber(board);

// I use system("cls") to clear screen. Change the code according to your OS.*/
			system("cls");
// I use system("cls") to clear screen. Change the code according to your OS.*/

			PrintGame(oldBoard, board, c);
		}

		if (IsGameOver(board)) {
			printf("\n\n Game Over!!\n\n");
			getchar();
		}
	}

	return 0;
}
