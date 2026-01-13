#include <stdio.h>

/*
 * STEP 1: Simplest implementation.
 * Problem: Values are hard-coded. 
 * To check a different date, you must modify the code and recompile.
 */
int main(void) {
    int day = 11, month = 11, year = 2025;
    int h;

    // Zeller's congruence (simplified)
    h = (day + (13 * (month + 1)) / 5 + year + (year / 4)
          - (year / 100) + (year / 400)) % 7;

    printf("Numerical value of the day of the week (10.11.2025): %d\n", h);
    return 0;
}
