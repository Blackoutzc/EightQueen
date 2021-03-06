// EightQueen.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <malloc.h>
#include <string.h>
#define NUM 7
struct EightQueen {
	int chessboard[NUM][NUM];
	int(*is_valid)(struct EightQueen *eight_queen, int row_num, int column_num);
	int(*put_chesspiece)(struct EightQueen *eight_queen, int column);
	int(*print_chessboard)(struct EightQueen *eight_queen);
};

int valid(struct EightQueen *eight_queen, int row_num, int column_num) {
	for (int i = 0; i < NUM; i++) {
		if (i != row_num) {
			if (eight_queen->chessboard[i][column_num])
				return 1;
		}
		if (i != column_num) {
			if (eight_queen->chessboard[row_num][i])
				return 1;
		}
	}
	int index = 1;
	int row = row_num + index;
	int column = column_num + index;
	int direction_index = 0;
	while (1) {
		if (row > NUM-1 || column > NUM -1 || row < 0 || column < 0) {
			direction_index++;
			index = 0;
			if (direction_index > 3)
				return 0;
		}
		else {
			if (eight_queen->chessboard[row][column])
				return 1;
		}
		index++;
		switch (direction_index)
		{
		case 0:
			row = row_num + index;
			column = column_num + index;
			break;
		case 1:
			row = row_num - index;
			column = column_num - index;
			break;
		case 2:
			row = row_num + index;
			column = column_num - index;
			break;
		case 3:
			row = row_num - index;
			column = column_num + index;
			break;
		default:
			break;
		}
	}
}

int put(struct EightQueen *eight_queen, int column_num) {
	static int result;
	if (column_num > NUM -1) {
		eight_queen->print_chessboard(eight_queen);
		return 1;
	}
	for (int i = 0; i < NUM; i++) {
		if (!eight_queen->is_valid(eight_queen, i, column_num)) {
			eight_queen->chessboard[i][column_num] = 1;
			result = put(eight_queen, column_num + 1);
			if (!result) {
				eight_queen->chessboard[i][column_num] = 0;
			}
		}
	}
	return 0;
}
int print(struct EightQueen *eight_queen) {
	printf("\n");
	int row_num = 0;
	int column_num = 0;
	for (; row_num < NUM;) {
		for (; column_num < NUM;) {
			printf("%d ", eight_queen->chessboard[row_num][column_num]);
			column_num++;
		}
		printf("\n");
		column_num = 0;
		row_num++;
	}
	return 1;
}

struct EightQueen* construct_eightqueen_instance() {
	struct EightQueen *eightqueen = (struct EightQueen*)malloc(sizeof(struct EightQueen));
	if (eightqueen == NULL)
		return NULL;
	memset(eightqueen->chessboard, 0, NUM*NUM*sizeof(int));
	eightqueen->is_valid = valid;
	eightqueen->print_chessboard = print;
	eightqueen->put_chesspiece = put;
	return eightqueen;
}

int main()
{
	 struct EightQueen *instance = construct_eightqueen_instance();
	if (instance!=NULL) {
		instance->put_chesspiece(instance, 0);
		free(instance);
		instance = NULL;
	}
	getchar();
    return 0;
}

