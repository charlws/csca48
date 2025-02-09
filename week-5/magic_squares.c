////////////////////////////////////////////////
// CSC A48 - Exercise 5 - Solving Magic Squares
//
// (c) F. Estrada
////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

int validateMagicSquare(int square[6][6], int sum) {
    int ok = 1;
    for (int i = 0; i < 6; i++) {
        int local_sum = 0;
        for (int j = 0; j < 6; j++) local_sum = local_sum + square[i][j];
        if (local_sum > sum) return 2;
        if (local_sum != sum) ok = 0;
    }
    for (int j = 0; j < 6; j++) {
        int local_sum = 0;
        for (int i = 0; i < 6; i++) local_sum = local_sum + square[i][j];
        if (local_sum > sum) return 2;
        if (local_sum != sum) ok = 0;
    }
    return ok;
}

int dfs(int square[6][6], int numbers_to_try[36], int try_size, int sum) {
    // do not question why I can write a dfs at this stage
    // dfs is my favoriate when I was doing OI (Olympics in Informatics) in middle school
    // bcz I usually cannot figure out some fancy math-ish solutions (unless it's a graph)

    // (C) CharlesWithC

    int validation_result = validateMagicSquare(square, sum);
    if (validation_result == 1) return 1;
    if (validation_result == 2) return 0;  // already bigger than sum / return early
    // the second optimization does make things much faster

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (square[i][j] == -1) {
                for (int k = 0; k < try_size; k++) {
                    int to_try = numbers_to_try[k];
                    if (to_try == -1) continue;  // skip used numbers
                    square[i][j] = to_try;
                    numbers_to_try[k] = -1;                                    // mark as used
                    if (dfs(square, numbers_to_try, try_size, sum)) return 1;  // return early if successful
                    // revert changes
                    square[i][j] = -1;
                    numbers_to_try[k] = to_try;
                }
            }
        }
    }
    return 0;
}

void solveMagicSquare(int square[6][6]) {
    // This function receives an array of size 6x6
    // that corresponds to a magic square.
    // It then finds any entries with value -1
    // (which means they are not known),
    // and figures out what their value should
    // be to solve the magic square.
    //
    // Conditions:
    // You can not hard-code the value of the rows
    // and columns in the magic square - because
    // we will test this with a *different* magic
    // square than the one in this starter code
    //
    // Your function has to (somehow) figure out
    // what the sum of the rows and columns should be,
    // and then figure out for each entry whose
    // value is -1, what its value is to correctly
    // complete the magic square.
    //
    // This is about problem solving - you don't
    // need any fancy pointer management or anything
    // like that. Just plain old C with a 2D array
    // and a bit of thinking.
    //
    // As a reminder. 2D arrays in C are indexed as
    // array[i][j] - gives you the element at row i,
    // column j

    //////////////////////////////////////
    // TO DO: Complete this function
    //////////////////////////////////////

    // PART-I: we first try to find a constant row/column
    int sum = -1;

    // look horizontally
    for (int i = 0; i < 6 && sum == -1; i++) {
        int ok = 1, row_sum = 0;
        for (int j = 0; j < 6; j++) {
            row_sum += square[i][j];
            if (square[i][j] == -1) {
                ok = 0;
                break;
            }
        }
        if (ok == 1) sum = row_sum;
    }

    // look vertically
    for (int j = 0; j < 6 && sum == -1; j++) {
        int ok = 1, col_sum = 0;
        for (int i = 0; i < 6; i++) {
            col_sum += square[i][j];
            if (square[i][j] == -1) {
                ok = 0;
                break;
            }
        }
        if (ok == 1) sum = col_sum;
    }

    if (sum == -1) sum = 111;  // f*** it

    // PART-II: we iterate through the matrix for 100 times, trying to solve single unknowns
    // for each iteration, we find the row/column with single unknown and solve it
    // if there's multiple unknowns, we don't solve it
    int num_unknowns = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            num_unknowns += (square[i][j] == -1);
        }
    }
    for (int k = 0; k < 1000 && num_unknowns > 0 && sum != -1; k++) {
        // look horizontally
        for (int i = 0; i < 6; i++) {
            int ok = 2, col_idx = -1, rest_sum = 0;
            for (int j = 0; j < 6; j++) {
                if (square[i][j] == -1 && ok == 2) {  // first unknown
                    ok = 1;
                    col_idx = j;
                } else if (square[i][j] == -1 && ok == 1) {  // second unknown
                    ok = 0;
                    break;
                } else {
                    rest_sum += square[i][j];
                }
            }
            if (ok == 1) {
                // only one unknown
                square[i][col_idx] = sum - rest_sum;
                num_unknowns -= 1;
            }
        }

        // look vertically
        for (int j = 0; j < 6; j++) {
            int ok = 2, row_idx = -1, rest_sum = 0;
            for (int i = 0; i < 6; i++) {
                if (square[i][j] == -1 && ok == 2) {  // first unknown
                    ok = 1;
                    row_idx = i;
                } else if (square[i][j] == -1 && ok == 1) {  // second unknown
                    ok = 0;
                    break;
                } else {
                    rest_sum += square[i][j];
                }
            }
            if (ok == 1) {
                // only one unknown
                square[row_idx][j] = sum - rest_sum;
                num_unknowns -= 1;
            }
        }
    }

    // PART-III: if there's still unknowns
    // I'm not writing a guassian elimination in an a48 "exercise"
    // (I can consider about it if it's an "assignment")
    // since the number must be 1-36
    // we try a dfs
    if (num_unknowns > 0) {
        int unused_numbers[37];  // bool 0/1
        for (int i = 0; i <= 36; i++) unused_numbers[i] = 1;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (square[i][j] != -1) unused_numbers[square[i][j]] = 0;
            }
        }

        int numbers_to_try[36], try_size = 0;
        for (int i = 1; i <= 36; i++)
            if (unused_numbers[i]) numbers_to_try[try_size++] = i;

        dfs(square, numbers_to_try, try_size, sum);
    }
}

// DO NOT MODIFY ANYTHING BELOW THIS LINE!
// (we mean it! the auto-checker won't be happy)
void printMagicSquare(int square[6][6]) {
    // Prints out the contents of a magic square 6x6

    int i, j, sum;

    for (i = 0; i < 6; i++) {
        sum = 0;
        for (j = 0; j < 6; j++) {
            printf("%03d, ", square[i][j]);
            sum = sum + square[i][j];
        }
        printf(" : %03d\n", sum);
    }

    printf("---------------------------\n");

    for (j = 0; j < 6; j++) {
        sum = 0;
        for (i = 0; i < 6; i++) {
            sum = sum + square[i][j];
        }
        printf("%03d, ", sum);
    }
    printf("\n");
}

#ifndef __testing  // This is a compiler directive - used by the auto-checker to enable/disable this part of the code
int main() {
    int magic[6][6] = {{32, 29, 4, 1, 24, 21},   {30, -1, 2, 3, -1, 23}, {12, 9, 17, 20, 28, 25},
                       {10, 11, 18, -1, 26, 27}, {13, -1, 36, 33, 5, 8}, {14, 15, 34, 35, 6, -1}};
    // int solution[6][6] = {{32, 29, 4, 1, 24, 21},   {30, 31, 2, 3, 22, 23}, {12, 9, 17, 20, 28, 25},
    //                     {10, 11, 18, 19, 26, 27}, {13, 16, 36, 33, 5, 8}, {14, 15, 34, 35, 6, 7}};
    // int magic[6][6] = {{32, -1, 4, 1, -1, -1},   {30, -1, 2, 3, -1, 23}, {12, 9, 17, -1, 28, 25},
    //                    {10, -1, 18, 19, -1, 27}, {13, 16, -1, 33, 5, 8}, {14, 15, 34, -1, 6, -1}};

    printMagicSquare(magic);
    printf("Solving Magic Square!\n");
    solveMagicSquare(magic);
    printMagicSquare(magic);

    return 0;
}
#endif
