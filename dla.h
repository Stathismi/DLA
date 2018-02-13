#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neillncurses.h"


#define SIZE 50
#define SEED  SIZE/2
#define DIRECTIONS 4
#define TOP_ROW 0
#define BOTTOM_ROW SIZE -1
#define FIRST_COLUMN 0
#define LAST_COLUMN SIZE -1
#define LAST_NUM SIZE -1
#define HASHES 250

typedef enum direction {up, down, left, right} direction;


void set_grid(char grid[SIZE][SIZE]);
void rand_edge_particle(char grid[SIZE][SIZE],int *row, int *column);
int edge_check(char grid[SIZE][SIZE], int *row, int *column);
int find_direction();
void create_dla(char grid[SIZE][SIZE], int row, int column, direction d, int hash_counter);
void move_particle(int *row, int *column, direction d);
int hash_check(char grid[SIZE][SIZE], int *row, int *column);
int negative_check(int *number);
int top_hash_check(char grid[SIZE][SIZE], int *row, int *column);
int bottom_hash_check(char grid[SIZE][SIZE], int *row, int *column);
int left_hash_check(char grid[SIZE][SIZE], int *row, int *column);
int right_hash_check(char grid[SIZE][SIZE], int *row, int *column);
