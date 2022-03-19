#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define ROW 9
#define COL 9
#define NUM_CELLS 9
#define SUDOKU_GRID_FILE "Lab3_puzzle.txt"

int grid[ROW][COL];

void *read_sudoku_grid() {
    FILE *fd;
    fd = fopen(SUDOKU_GRID_FILE, "r");
    char c;
    int row = 0;
    int col = 0;
    while ((c = (char) fgetc(fd)) != EOF) {
        if (c == '\n') {
            row++;
            col = 0;
//            printf("\n");
        } else {
            if (c != ' ') {
                grid[row][col] = (int) strtol(&c, NULL, 10);
//                printf(" (%d, %d) = %d ", row, col, grid[row][col]);
                col++;
            }
        }
    }
    pthread_exit(NULL);
}

struct check_column_args {
    int column_index;
};


/* 
 *  Check the given column index in the sudoku grid if the row contains numbers from 1-9
 *  valid sudoku grid contains only numbers from 1 to 9 across column. One instance of number should only appears once.
 */
void *check_column(void *vptr) {
    int nums[NUM_CELLS];
    struct check_column_args *args = (struct check_column_args *) vptr;
    int col = args->column_index;
    if (col < 0 || col >= COL)
        pthread_exit((void *) -1);
    for (int i = 1; i <= 9; i++) {
        bool found = false;
        for (int r = 0; r < ROW && !found; r++) {
            if (grid[r][col] == i)
                found = true;
        }
        if (!found)
            pthread_exit((void *) false);
    }
    pthread_exit((void *) true);
}

struct check_row_args {
    int row_index;
};


/* 
 *  Check the given row index in the sudoku grid if the row contains numbers from 1-9
 *  valid sudoku grid contains only numbers from 1 to 9 across row. One instance of number should only appears once.
 */
void *check_row(void *vptr) {
    struct check_row_args *args = (struct check_row_args *) vptr;
    int row = args->row_index;
    if (row < 0 || row >= ROW)
        pthread_exit((void *) -1);
    for (int i = 1; i < 9; i++) {
        bool found = false;
        for (int c = 0; c < COL && !found; c++) {
            if (grid[row][c] == i)
                found = true;
        }
        if (!found)
            pthread_exit((void *) false);
    }
    pthread_exit((void *) true);
}

struct check_square_args {
    int row;
    int column;
};

void *check_square(void *vptr) {
    struct check_square_args *args = (struct check_square_args *) vptr;
    int row = args->row;
    int column = args->column;


}

int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, &read_sudoku_grid, NULL);
    pthread_join(tid, NULL);

    pthread_t threads[27];

    for (int r = 0; r < ROW; r++) {

    }

    for (int c = 0; c < COL; c++) {
        struct check_column_args *cs_args = (struct check_column_args *) malloc(sizeof(struct check_column_args));
    }

    int square_r[9] = { 0, 0, 0,   3, 3, 3,   6, 6, 6 };
    int square_c[9] = { 0, 3, 6,   0, 3, 6,   0, 3, 6 };
    for (int i = 0; i < 9; i++) {
        struct check_square_args *cs_args = (struct check_square_args *) malloc(sizeof(struct check_square_args));
        cs_args->row    = square_r[i];
        cs_args->column = square_c[i];
        pthread_create(&threads[i], NULL, &check_square, (void *) cs_args);
    }
//    for (int r=0; r < ROW; r++){
//        for (int c=0; c < COL; c++) {
//            printf("%d ", grid[r][c]);
//        }
//        printf("\n");
//    }
    return 0;
}