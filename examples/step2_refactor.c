#include <stdio.h>

/**
 * STEP 2: Moving logic into a function.
 * Improvement: Code reuse and handling of edge cases (Jan/Feb).
 * Now we can test different dates within a single execution cycle.
 */
int calculate_zeller(int day, int month, int year) {
    // In Zeller's algorithm, January and February are treated 
    // as months 13 and 14 of the PREVIOUS year.
    if (month < 3) {
        month += 12;
        year--;
    }
    // Note: The formula result depends on integer division behavior.
    return (day + (13 * (month + 1)) / 5 + year + (year / 4) - (year / 100) + (year / 400)) % 7;
}
int main(void) {
    // Manual testing (Positive Testing)
    printf("10.11.2025: %d (Expected 2 - Monday)\n", calculate_zeller(10, 11, 2025));
    printf("01.01.2026: %d (Expected 5 - Thursday)\n", calculate_zeller(1, 1, 2026));
    
    return 0;
}


