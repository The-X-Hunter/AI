#include<stdio.h>
char playerNames[2][10], playerSign[2];
int matricsValues[9][3] = {
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1},
	{-1, -1, -1}
}, pos;
int winnerCheck() {
	int i, j, row, column, rowCount, columnCount, diagonalCount;
	char sign, direction = 'L';
	for(i = 0; i < 9; i++) {
		rowCount = columnCount = diagonalCount = 1;
		row = matricsValues[i][0];
		column = matricsValues[i][1];
		sign = matricsValues[i][2];
		for(j = 0; j < 9; j++)
			if(sign == matricsValues[j][2]) {
				if(row == matricsValues[j][0] && column != matricsValues[j][1]) {
					rowCount++;
				} else if(row != matricsValues[j][0] && column == matricsValues[j][1]) {
					columnCount++;
				} else {
					if((row == 0 && column == 0) && ((matricsValues[j][0] == row + 2 && matricsValues[j][1] == column + 2) || (matricsValues[j][0] == row + 4 && matricsValues[j][1] == column + 4))) {
						diagonalCount++;
					} else if(row == 2 && column == 2) {
						if((matricsValues[j][0] == row - 2 && matricsValues[j][1] == column - 2) || (matricsValues[j][0] == row + 2 && matricsValues[j][1] == column + 2)) {
							if(direction == 'L')
								diagonalCount++;
							else
								diagonalCount = 1;
							direction = 'L';
						} else if((matricsValues[j][0] == row - 2 && matricsValues[j][1] == column + 2) || (matricsValues[j][0] == row + 2 && matricsValues[j][1] == column - 2)) {
							if(direction == 'R')
								diagonalCount++;
							else
								diagonalCount = 1;
							direction = 'R';
						}
					} else if((row == 4 && column == 4) && ((matricsValues[j][0] == row - 2 && matricsValues[j][1] == column - 2) || (matricsValues[j][0] == row - 4 && matricsValues[j][1] == column - 4))) {
						diagonalCount++;
					} else if((row == 0 && column == 4) && ((matricsValues[j][0] == row + 2 && matricsValues[j][1] == column - 2) || (matricsValues[j][0] == row + 4 && matricsValues[j][1] == column - 4))) {
						diagonalCount++;
					} else if((row == 4 && column == 0) && ((matricsValues[j][0] == row - 2 && matricsValues[j][1] == column + 2) || (matricsValues[j][0] == row - 4 && matricsValues[j][1] == column + 4))) {
						diagonalCount++;
					}
				}
			}
		if(rowCount == 3 || columnCount == 3 || diagonalCount == 3) {
			if((char)sign == playerSign[0])
				printf("\n%s is winner\n", playerNames[0]);
			else
				printf("\n%s is winner\n", playerNames[1]);
			return 1;
		}
	}
	return 0;
}
int gameStop() {
	if(winnerCheck())
		return 1;
	else if(matricsValues[8][2] != -1) {
		printf("\nMatch draw\n");
		return 1;
	}
	return 0;
}
int valueCheck(int row, int column) {
	int i;
	for(i = 0; i < 9; i++)
		if(row == matricsValues[i][0] && column == matricsValues[i][1])
			return 0;
	return 1;
}
int printMatrics(int row, int column, char sign) {
	int i, j, k;
	if((row <= 0 || row >= 4) || (column <= 0 || column >= 4))
		printf("\nEnter valid row and column\n");
	else {
		if(row == 1)
			row -= 1;
		else if(row == 3)
			row += 1;
		if(column == 1)
			column -= 1;
		else if(column == 3)
			column += 1;
		if(valueCheck(row, column)) {
			printf("\n");
			for(i = 0; i < 5; i++) {
				for(j = 0; j < 5; j++) {
					if(i % 2 == 0 && j % 2 == 0) {
						if(i == row && j == column) {
							matricsValues[pos][0] = row;
							matricsValues[pos][1] = column;
							matricsValues[pos][2] = sign;
							pos++;
							printf(" %c ", sign);
						} else {
							for(k = 0; k < 9; k++)
								if(i == matricsValues[k][0] && j == matricsValues[k][1]) {
									printf(" %c ", (char)matricsValues[k][2]);
									break;
								}
							if(k == 9)
								printf("   ");
						}
					} else if(i % 2 == 0 && j % 2 != 0)
						printf("|");
					else if(i % 2 != 0 && j % 2 == 0)
						printf("---");
					else
						printf(" ");
				}
				printf("\n");
			}
			return 1;
		} else
			printf("\nPosition is already used\n");
	}
	return 0;
}
void toggleUser(int id) {
	int row, column;
	do {
		printf("\n%s, enter row: ", playerNames[id]);
		scanf("%d", &row);
		printf("\n%s, enter column: ", playerNames[id]);
		scanf("%d", &column);
	} while(!printMatrics(row, column, playerSign[id]));
}
void main() {
	char temp;
	int id = 0;
	printf("\nEnter player1 name: ");
	gets(playerNames[0]);
	printf("\nEnter player2 name: ");
	gets(playerNames[1]);
	do {
		printf("\n%s, choose any one character from 'X' and 'O': ", playerNames[0]);
		scanf("%c", &playerSign[0]);
		scanf("%c", &temp);
	} while(playerSign[0] != 'X' && playerSign[0] != 'O');
	if(playerSign[0] == 'X')
		playerSign[1] = 'O';
	else
		playerSign[1] = 'X';
	printf("\n   |   |   ");
	printf("\n--- --- ---");
	printf("\n   |   |   ");
	printf("\n--- --- ---");
	printf("\n   |   |   \n");
	do {
		toggleUser(id);
		if(id == 0)
			id = 1;
		else
			id = 0;
	} while(!gameStop());
}