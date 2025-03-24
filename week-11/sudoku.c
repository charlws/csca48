/*
 * CSC A48 - Exercise 11 - Sudoku Solver
 *
 * Your goal in this exercise is to practice recursion and
 * to see how a properly written recursive solution can
 * take care of fairly complicated tasks with a few lines
 * of (well thought out) code.
 *
 * We will be solving Sudoku puzzles. In case you have never
 * solved or seen a Sudoku, you can learn more about them
 * here:
 *
 * https://en.wikipedia.org/wiki/Sudoku
 *
 * Your task if to write a function that takes an input
 * Sudoku in the form of a 9x9 array of integers. the
 * array will have a few entries filled with numbers in
 * [1, 9], and the remaining entries set to zero.
 *
 * For the example in the wiki, the input array will
 * be
 *
 * 5 3 0 0 7 0 0 0 0
 * 6 0 0 1 9 5 0 0 0
 * 0 9 8 0 0 0 0 6 0
 * 8 0 0 0 6 0 0 0 3
 * 4 0 0 8 0 3 0 0 1
 * 7 0 0 0 2 0 0 0 6
 * 0 6 0 0 0 0 2 8 0
 * 0 0 0 4 1 9 0 0 5
 * 0 0 0 0 8 0 0 7 9
 *
 * Your code should find the values that correctly
 * complete the Sudoku.
 *
 * As a brief reminder, a correctly solved Sudoku is
 * one in which there are no repeated digits in any
 * row, any column, or any of the 3x3 sub-arrays that
 * make up the large 9x9 grid. Another way to think
 * about it is, every row, column, and 3x3 subgrid
 * uses all of the different digits.
 *
 * How to solve this?
 *
 * * RECURSIVELY!
 *
 * (hint) - Solving a Sudoku with N unknown values
 * may involve trying something, then solving an
 * easier Sudoku problem.
 *
 * * How to approach this?
 *
 * - As noted in class:
 * 	a) Determine the base case(s)
 * 	b) Figure out the recursive case
 * 	c) Determine what needs to happen to
 * 	   the solution for the entire problem
 * 	   is returned once the recursion hits
 * 	   the base case(s)
 *
 * - Conditions on the input Sudoku
 * 	- It will have AT LEAST ONE DIGIT in each
 * 	  3x3 subgrid. Likely there will be several
 * 	  3x3 subgrids with several digits already
 * 	  set to some value.
 *
 * - Conditions on your solution
 * 	- It should return a solution if there
 * 	  exists one.
 * 	- If no solution can be found, return the
 * 	  original input array
 * 	- If multiple solutions exist, any one of
 *        them is valid
 *
 * - Can I use helper functions?
 * 	- Yes, by all means!
 *
 * - Can I add extra libraries?
 * 	- No, they won't be needed.
 *
 * - Can I change the 'print_sudoku()' function?
 * 	- Please don't, we may need it for testing!
 *
 * (c) F. Estrada, March 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>

void print_sudoku(int sudoku[9][9]) {
    printf("The Sudoku contains:\n");
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            printf("%d  ", sudoku[j][i]);
        }
        printf("\n");
    }
}

// returns 1 if num is used in bitnum
int check_number(int *bitnum, int num) { return (*bitnum & (1 << num)) != 0; }

// set num position in bitnum to 1, to represent that num is used
void set_number(int *bitnum, int num) { *bitnum |= 1 << num; }

// undo the set operation
void unset_number(int *bitnum, int num) { *bitnum &= ~(1 << num); }

void print_bitnum(int *bitnum) {
    for (int i = 1; i <= 9; i++) printf("%d", check_number(bitnum, i));
    printf("\n");
}

int check_sudoku(int sudoku[9][9]) {
    /*
     *  This function checks whether a Sudoku is properly
     * solved. That means that each row, column, and
     * 3x3 subgrid uses each digit only once.
     *
     *  It *ignores* zeros, so you can use it to check
     * that a partial solution is valid
     */

    /*****
     * TO DO:
     * Complete this function
     *   -- BUT ONLY IF YOU WANT TO!
     * Our testing script only checks your Sudoku
     * solution, if you want to solve it without
     * using this function, or if you want to write
     * your own helper functions, that's ok!
     * *****/

    // check rows
    for (int i = 0; i < 9; i++) {
        int chk = 0;
        for (int j = 0; j < 9; j++) {
            if (check_number(&chk, sudoku[i][j])) return 0;
            set_number(&chk, sudoku[i][j]);
        }
    }

    // check cols
    for (int j = 0; j < 9; j++) {
        int chk = 0;
        for (int i = 0; i < 9; i++) {
            if (check_number(&chk, sudoku[i][j])) return 0;
            set_number(&chk, sudoku[i][j]);
        }
    }

    // check grids
    const int base[9][2] = {{0, 0}, {0, 3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {6, 0}, {6, 3}, {6, 6}};
    for (int k = 0; k < 9; k++) {
        int chk = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (check_number(&chk, sudoku[base[k][0] + i][base[k][1] + j])) return 0;
                set_number(&chk, sudoku[base[k][0] + i][base[k][1] + j]);
            }
        }
    }

    return 1;
}

int solved(int sudoku[9][9]) {
    /*
     * This function checks whether a given Sudoku is
     * completely solved (it has no zeros, all digits
     * are used once per row, column, and sub-grid.
     * It returns 1 if the Sudoku is solved, zero
     * otherwise
     */

    /*****
     * TO DO
     * Complete this function
     * BUT ONLY IF YOU WANT TO!
     *   You can solve the Sudoku without using this function,
     * or you can write a different helper function, whatever
     * makes more sense to yoU! our checker won't look at this
     * function,
     * ****/

    // check zero
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) return 0;
        }
    }

    // regular check
    return check_sudoku(sudoku);
}

int better_solved(int rows[9], int cols[9], int grids[9]) {
    // 1022 = 1111111110(bin) / last digit represents 0
    for (int i = 0; i < 9; i++)
        if (rows[i] != 1022 || cols[i] != 1022 || grids[i] != 1022) return 0;
    return 1;
}

int better_solve_sudoku(int sudoku[9][9], int rows[9], int cols[9], int grids[9], int todo[81][2], int idx,
                        int idxlimit) {
    // we create this helper function in order to not modify the original API
    // this may look "competetive programming" because I've been doing competitve programming in middle school
    // this is a typical *dfs* algorithm but optimized with bit-wise operations

    // reminder: rows, cols, grids have 1 on the position if number is USED
    // allowed_nums have 1 if number is ALLOWED (i.e. NOT USED)
    // this can be a bad design b/c it messed up my first test but I'm not going to change it since I fixed it

    if (idx == idxlimit) {
        // this should always be true b/c if any slot cannot be filled, then it returns early
        // this just serves as a security check but it still feels kind of useless
        // probably this is just to check if my `better_solved` is correctly written
        int ok = better_solved(rows, cols, grids);
        // printf("Final check: %s\n", ok ? "PASS" : "FAIL");
        // print_sudoku(sudoku);
        // getchar();
        return ok;
    }

    int x = todo[idx][0], y = todo[idx][1];
    int z = x / 3 * 3 + y / 3;                           // x / 3 => 0,1,2 | *3 => 0,3,6
    int allowed_nums = ~rows[x] & ~cols[y] & ~grids[z];  // 1 on position if number is ALLOWED

    // printf("Pos(x,y): %d, %d | Allowed nums (%d): ", x, y, allowed_nums);
    // print_bitnum(&allowed_nums);
    // print_sudoku(sudoku);
    // getchar();

    // we try numbers from 1-9
    for (int t = 1; t <= 9; t++) {
        if (!check_number(&allowed_nums, t)) continue;  // this is reversed from what we normally have
        // printf("Try number %d at %d, %d\n", t, x, y);
        sudoku[x][y] = t;
        set_number(&rows[x], t);
        set_number(&cols[y], t);
        set_number(&grids[z], t);
        if (better_solve_sudoku(sudoku, rows, cols, grids, todo, idx + 1, idxlimit)) return 1;
        sudoku[x][y] = 0;
        unset_number(&rows[x], t);
        unset_number(&cols[y], t);
        unset_number(&grids[z], t);
    }

    return 0;
}

void solve_sudoku(int sudoku[9][9], int depth) {
    /*
     * This function solves an input Sudoku, the
     * input has a value of 0 for any entries that
     * are not yet decided. If no solution exists
     * the function returns the input array *exactly
     * as it was* when the function was called.
     *
     * The 'depth' parameter is provided in case you
     * want to use it to help debug and trace your
     * code. You do not need to use it if you don't
     * want to, and the problem can be solved without
     * using the depth value at all.
     *
     * The automated checker won't look at the depth
     * either.
     */

    /*****
     * TO DO:
     * Complete this function
     *****/
    int rows[9], cols[9], grids[9];
    for (int i = 0; i < 9; i++) rows[i] = cols[i] = grids[i] = 0;

    int todo[81][2], idx = 0;  // position of numbers to be filled and idx of next number to be filled
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0)
                todo[idx][0] = i, todo[idx][1] = j, idx++;
            else {
                set_number(&rows[i], sudoku[i][j]);
                set_number(&cols[j], sudoku[i][j]);
                set_number(&grids[i / 3 * 3 + j / 3], sudoku[i][j]);
            }
        }
    }

    better_solve_sudoku(sudoku, rows, cols, grids, todo, 0, idx);
    // printf("Result code: %d\n", res); // don't uncomment this, you need to set "int res =" in the above line
}

#ifndef __testing

int main() {
    // We'll provide you with the same test case
    // from the Wiki, so you can check your output.
    // But as always, be aware we will test your
    // solution on different Sudoku puzzles.

    int Sudoku[9][9] = {{5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0}, {0, 9, 8, 0, 0, 0, 0, 6, 0},
                        {8, 0, 0, 0, 6, 0, 0, 0, 3}, {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
                        {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5}, {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    // AI Escargot
    // solved in 0.000794s (env: linux 2vCPU)
    // int Sudoku[9][9] = {
    //     {1, 0, 0, 0, 0, 7, 0, 9, 0},
    //     {0, 3, 0, 0, 2, 0, 0, 0, 8},
    //     {0, 0, 9, 6, 0, 0, 5, 0, 0},
    //     {0, 0, 5, 3, 0, 0, 9, 0, 0},
    //     {0, 1, 0, 0, 8, 0, 0, 0, 2},
    //     {6, 0, 0, 0, 0, 4, 0, 0, 0},
    //     {3, 0, 0, 0, 0, 0, 0, 1, 0},
    //     {0, 4, 0, 0, 0, 0, 0, 0, 7},
    //     {0, 0, 7, 0, 0, 0, 3, 0, 0}
    // };

    // multi-solution
    // int Sudoku[9][9] = {{0, 0, 0, 0, 0, 0, 0, 1, 2}, {0, 0, 0, 0, 3, 5, 0, 0, 0}, {0, 0, 0, 6, 0, 0, 0, 7, 0},
    //                     {0, 5, 0, 0, 0, 0, 0, 0, 0}, {4, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 3, 0},
    //                     {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 2, 0, 0}, {2, 4, 0, 0, 0, 0, 0, 0, 0}};

    // empty
    // int Sudoku[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
    //                     {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
    //                     {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    // actually multi-solution is easiest
    // b/c my algo won't be hit with a slot that cannot be filled with a number
    // which literally gives it a green light to fill in everything with one pass

    printf("Input puzzle is:\n");
    print_sudoku(Sudoku);

    // clock_t start = clock();
    solve_sudoku(Sudoku, 0);
    // clock_t end = clock();
    // double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Solution is:\n");
    print_sudoku(Sudoku);
    // printf("Time taken: %f seconds\n", cpu_time_used);
}

#endif