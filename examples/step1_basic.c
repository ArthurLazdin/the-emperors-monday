#include <stdio.h>

/**
 * STEP 1: Simplest implementation.
 * Problem: Values are hard-coded. 
 * To check a different date, you must modify the code and recompile.
 */
int main(void) {
    int day = 11, month = 11, year = 2025;
    int h;

    /** Zeller's congruence (simplified version).
     * Formula calculates the day of the week.
     * Result (h): 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday.
     */
    h = (day + (13 * (month + 1)) / 5 + year + (year / 4)
          - (year / 100) + (year / 400)) % 7;

    printf("Date: %02d.%02d.%d\n", day, month, year);
    printf("Day of the week (numeric index): %d\n", h);
    return 0;
}