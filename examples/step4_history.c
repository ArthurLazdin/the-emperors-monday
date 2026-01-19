#include <stdio.h>

/**
 * STEP 4: Accounting for History (The Calendar Reform of 1582).
 * Improvement: Universal formula handling both Julian and Gregorian calendars.
 * This stage demonstrates that mathematical logic must be reconciled 
 * with historical context and records.
 */
int calculate_zeller_universal(int d, int m, int y) {
    if (m < 3) { 
        m += 12; 
        y--; 
    }
    
    // Transition point to the Gregorian calendar (October 15, 1582)
    if (y > 1582 || (y == 1582 && m > 10) || (y == 1582 && m == 10 && d >= 15)) {
        return (d + (13 * (m + 1)) / 5 + y + (y / 4) - (y / 100) + (y / 400)) % 7;
    } else {
        // Julian formula for dates before 1582
        int J = y / 100;
        int K = y % 100;
        return (d + (13 * (m + 1)) / 5 + K + K / 4 + 5 - J) % 7;
    }
}

int main(void) {
    // Example: Coronation of Charlemagne (December 25, 800 AD)
    int d = 25, m = 12, y = 800; 
    
      /**
     * HISTORICAL CONTEXT:
     * 1. Gregorian formula would return 2 (Monday).
     * 2. Textbooks often claim Sunday (traditional association).
     * 3. Julian algorithm correctly calculates Friday (Code 6).
     */
    int res = calculate_zeller_universal(d, m, y);
    
    printf("Date: %02d.%02d.%04d | Zeller Code: %d (6 = Friday)\n", d, m, y, res);

    return 0;
}