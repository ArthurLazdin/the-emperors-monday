#include <stdio.h>
#include <time.h>

/**
 * STEP 3: Using an Oracle (standard library).
 * Improvement: Automated verification against the <time.h> library.
 * We compare our result against the industry standard to ensure accuracy.
 */

int calculate_zeller(int day, int month, int year) {
    // January and February are treated as months 13 and 14 of the previous year
    if (month < 3) { 
        month += 12; 
        year--; 
    }
    
    int h = (day + (13 * (month + 1)) / 5 + year + (year / 4) 
             - (year / 100) + (year / 400)) % 7;
    
    return h; 
}

/**
 * Automated test runner.
 * Compares calculate_zeller results with the standard mktime function.
 */
int auto_test(int start_year, int end_year) {
    struct tm target = {0};
    int fail_count = 0;
    int d = 1; // Testing the 1st day of every month

    for (int y = start_year; y <= end_year; y++) {
        for (int m = 1; m <= 12; m++) {
            // Standard library (struct tm) requirements:
            target.tm_year = y - 1900; // Years since 1900
            target.tm_mon = m - 1;     // Months 0-11
            target.tm_mday = d;        
            
            // Setting tm_isdst to -1 lets mktime determine DST automatically,
            // preventing potential one-hour shifts that could affect dates.
            target.tm_isdst = -1;

            // mktime calculates the tm_wday (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
            if (mktime(&target) == -1) continue; 

            int zeller = calculate_zeller(d, m, y);
            
            /** * Alignment:
             * Zeller: 0=Sat, 1=Sun, 2=Mon, 3=Tue, 4=Wed, 5=Thu, 6=Fri
             * tm_wday: 0=Sun, 1=Mon, 2=Tue, 3=Wed, 4=Thu, 5=Fri, 6=Sat
             * To convert Zeller to tm_wday: (zeller + 6) % 7
             */
            int zeller_standardized = (zeller + 6) % 7; 

            if (zeller_standardized != target.tm_wday) {
                printf("Error! Date: 01.%02d.%d | Expected: %d, Got: %d\n", 
                        m, y, target.tm_wday, zeller_standardized);
                fail_count++;
            }
        }
    }
    return fail_count;
}

int main(void) {
    // Range includes a leap year (1964) to verify logic consistency
    int errors = auto_test(1961, 1968);
    
    if (errors == 0) {
        printf("All tests passed successfully!\n");
    } else {
        printf("Total errors found: %d\n", errors);
    }

    return 0;
}