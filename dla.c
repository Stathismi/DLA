#include "dla.h"

int main(void)
{
	direction d;
	int row = 0, column = 0, hash_counter = 1;
	char grid[SIZE][SIZE];
	srand(time(NULL));

	set_grid(grid);
	rand_edge_particle(grid, &row, &column);
	d = find_direction();
	create_dla(grid, row, column, d, hash_counter);

	return 0;
}

void set_grid(char grid[SIZE][SIZE])
{
	int i, k;
	for (i = 0; i < SIZE; i++){
		for (k = 0; k < SIZE; k++){
			grid[i][k] = ' ';
		}
	}
	grid[SEED][SEED] = '#';
}

void rand_edge_particle(char grid[SIZE][SIZE], int *row, int *column)
{
	do{
		*row = rand() % SIZE;
		*column = rand() % SIZE;
	}while (edge_check(grid, row, column) == 0);
}

int edge_check(char grid[SIZE][SIZE], int *row, int *column)
{
	if (*row == TOP_ROW && grid[TOP_ROW][*column] != '#'){
		return 1;
	}
	if (*row == BOTTOM_ROW && grid[BOTTOM_ROW][*column] != '#'){
		return 1;
	}
	if (*column == FIRST_COLUMN && grid[*row][FIRST_COLUMN] != '#'){
		return 1;
	}
	if (*column == LAST_COLUMN && grid[*row][LAST_COLUMN] != '#'){
		return 1;
	}
	return 0;
}

int find_direction()
{
	int d;
	d = rand() % DIRECTIONS;
	return d;
}

void create_dla(char grid[SIZE][SIZE], int row, int column, direction d, int hash_counter)
{

	NCURS_Simplewin sw;
	Neill_NCURS_Init(&sw);
	Neill_NCURS_CharStyle(&sw, "#", COLOR_RED, COLOR_RED, A_NORMAL);
	Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);

	do{

		if (hash_check(grid, &row, &column) == 1){
			hash_counter++;
			grid[row][column] = '#';
			Neill_NCURS_Delay(10.0);
			Neill_NCURS_PrintArray(&grid[0][0], SIZE, SIZE, &sw);
			rand_edge_particle(grid, &row, &column);
			d = find_direction();
		}
		else {
			move_particle(&row, &column, d);
			d = find_direction();
		}

		Neill_NCURS_Events(&sw);
	}while (hash_counter <= HASHES && !sw.finished);

}

int hash_check(char grid[SIZE][SIZE], int *row, int *column)
{
	if (top_hash_check(grid, row, column) || bottom_hash_check(grid, row, column)
			|| left_hash_check(grid, row, column) || right_hash_check(grid, row, column)){
		return 1;
	}
	return 0;
}

int top_hash_check(char grid[SIZE][SIZE], int *row, int *column)
{
	if (grid[negative_check(row)][*column] == '#'){
		return 1;
	}
	return 0;
}

int bottom_hash_check(char grid[SIZE][SIZE], int *row, int *column)
{
	if (grid[(*row + 1) % SIZE][*column] == '#'){
		return 1;
	}
	return 0;
}

int left_hash_check(char grid[SIZE][SIZE], int *row, int *column)
{
	if (grid[*row][negative_check(column)] == '#'){
		return 1;
	}
	return 0;
}

int right_hash_check(char grid[SIZE][SIZE], int *row, int *column)
{
	if (grid[*row][(*column + 1) % SIZE] == '#'){
		return 1;
	}
	return 0;
}

/*TOP_ROW or FIRST_COLUMN, toroidal case, else normal case*/
int negative_check(int *number)
{
	if (*number == 0){
		return LAST_NUM;
	}
	return *number - 1;
}

void move_particle(int *row, int *column, direction d)
{
	if (d == up){
		*row = negative_check(row);
	}
	if (d == down){
		*row = (*row + 1) % SIZE;
	}
	if (d == left){
		*column = negative_check(column);
	}
	if (d == right){
		*column = (*column + 1) % SIZE;
	}
}
