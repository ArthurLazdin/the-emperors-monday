#include <stdio.h>
#include <assert.h>

/**
 * STEP 5: Defensive Programming and Function Contracts.
 * Final Stage: Separation of concerns between input validation 
 * and internal logic protection.
 */

/**
 * Helper validation function (System Boundary Check).
 * Checks if the basic date parameters are within reasonable bounds.
 */
int is_valid_date(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12 || d < 1 || d > 31) {
        return 0;
    }
    // Note: In a production environment, one should also check
    // for month-specific day counts (e.g., February 30th).
    return 1;
}

/**
 * Zeller's algorithm (Julian version for demonstration).
 * Function Contract: The caller MUST provide a valid date.
 */
int calculate_zeller_final(int d, int m, int y) {
    /** * CONTRACT: If data is invalid, the program will terminate (in Debug mode).
     * Assertions are for catching developer errors, not user input errors.
     */
    assert(is_valid_date(d, m, y) && "CRITICAL: Function called with invalid date!");

    if (m < 3) { 
        m += 12; 
        y--; 
    }
    
    // Using the Julian version for simplicity in this final step
    int J = y / 100;
    int K = y % 100;
    return (d + (13 * (m + 1)) / 5 + K + K / 4 + 5 - J) % 7;
}

int main(void) {
    // Scenario A: Garbage data from an external source (User, File, etc.)
    int d = 32, m = 13, y = 2025;

    printf("Checking user input...\n");
    if (is_valid_date(d, m, y)) {
        int res = calculate_zeller_final(d, m, y);
        printf("Result: %d\n", res);
    } else {
        /** * SOFT ERROR: We inform the user and keep the program running.
         */
        printf("Error: Input data is invalid. The logic function will not be called.\n");
    }

    /**
     * Scenario B: Developer's error (Hard Fail).
     * Uncommenting the line below triggers the assertion to catch a logic bug.
     */
    // calculate_zeller_final(99, 99, 99); 

    return 0;
}