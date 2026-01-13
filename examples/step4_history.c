#include <stdio.h>

/*
 * STEP 4: Accounting for history (the year 1582).
 * Why Charlemagne could not have been crowned on a Thursday.
 */
int calculate_zeller_universal(int d, int m, int y) {
    if (m < 3) { m += 12; y--; }
    
    // Transition point to the Gregorian calendar
    if (y > 1582 || (y == 1582 && m > 10) || (y == 1582 && m == 10 && d >= 15)) {
        return (d + (13 * (m + 1)) / 5 + y + (y / 4) - (y / 100) + (y / 400)) % 7;
    } else {
        // Julian formula for dates before 1582
        return (d + (13 * (m + 1)) / 5 + y + (y / 4) + 5) % 7;
    }
}

int main(void) {
    // Coronation of Charlemagne: 25.12.800 (Sunday)
    int res = calculate_zeller_universal(25, 12, 800);
    printf("Coronation of Charlemagne (25.12.800): Code %d (1 = Sunday)\n", res);
    return 0;
}
