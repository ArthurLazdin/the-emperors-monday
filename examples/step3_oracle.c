#include <stdio.h>
#include <time.h>

/*
 * STEP 3: Using an Oracle (standard library).
 * We compare our result against the industry standard.
 */
int calculate_zeller(int d, int m, int y) {
    if (m < 3) { m += 12; y--; }
    return (d + (13 * (m + 1)) / 5 + y + (y / 4) - (y / 100) + (y / 400)) % 7;
}

int main(void) {
    struct tm t = {0};
    int d = 10, m = 11, y = 2025;

    // Setting up the Oracle
    t.tm_mday = d;
    t.tm_mon = m - 1;   // months since January [0-11]
    t.tm_year = y - 1900; // years since 1900
    mktime(&t);

    // Normalizing to the tm_wday standard (0 = Sunday, 1 = Monday, etc.)
    int my_res = (calculate_zeller(d, m, y) + 6) % 7; 
    
    printf("Our result: %d, Oracle: %d\n", my_res, t.tm_wday);
    if (my_res == t.tm_wday) printf("TEST PASSED!\n");
    
    return 0;
}
