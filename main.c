#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ROW 9
#define COL 9
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

int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, &read_sudoku_grid, NULL);
    pthread_join(tid, NULL);
//    for (int r=0; r < ROW; r++){
//        for (int c=0; c < COL; c++) {
//            printf("%d ", grid[r][c]);
//        }
//        printf("\n");
//    }
    return 0;
}