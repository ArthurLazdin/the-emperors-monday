#include <stdio.h>
#include <time.h>

/**
 * STEP 3a: Limits of Algorithms and Context.
 * Problem: Both Zeller's Gregorian formula and <time.h> are designed for 
 * the Gregorian calendar. They fail when applied to historical dates 
 * (like 800 AD) when the Julian calendar was in use.
 */

int calculate_zeller_gregorian(int d, int m, int y) {
    if (m < 3) { 
        m += 12; 
        y--; 
    }
    // Standard Gregorian Zeller formula
    return (d + (13 * (m + 1)) / 5 + y + (y / 4) - (y / 100) + (y / 400)) % 7;
}

int main(void) {
    // Example: December 25, 800 (Coronation of Charlemagne)
    int d = 25, m = 12, y = 800;

    // 1. Our algorithm (Proleptic Gregorian)
    int res = (calculate_zeller_gregorian(d, m, y) + 6) % 7;
    
    // 2. Standard library (Oracle)
    struct tm t = {0};
    t.tm_mday = d;
    t.tm_mon = m - 1;
    t.tm_year = y - 1900; // Result will be -1100
    t.tm_isdst = -1;
    
    time_t t_of_day = mktime(&t);

    printf("Zeller result (index): %d\n", res);
   
    /**
     * Testing the Oracle's limits:
     * mktime often fails for dates before the Unix Epoch (1970) 
     * or the start of the Gregorian calendar.
     */
    if (t_of_day == (time_t)-1) {
        printf("time.h library: Error (date out of range!)\n");
    } else {
        printf("time.h library (tm_wday): %d\n", t.tm_wday);
    }

    return 0;
}