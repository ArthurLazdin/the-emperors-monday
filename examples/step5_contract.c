#include <stdio.h>
#include <assert.h>

/*
 * STEP 5: The Final Level.
 * Function Contract: We require valid data via assert.
 * The responsibility for validation lies with the caller.
 */

// Helper validation function (System boundary check)
int is_valid_date(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12 || d < 1 || d > 31) return 0;
    // (Additional strict logic for days per month could be added here)
    return 1;
}

int calculate_zeller_final(int d, int m, int y) {
    // CONTRACT: If data is invalid, the program will terminate here (in Debug mode)
    assert(is_valid_date(d, m, y) && "CRITICAL: Calling function with invalid date!");

    if (m < 3) { m += 12; y--; }
    return (d + (13 * (m + 1)) / 5 + y + (y / 4) + 5) % 7; // Simplified for this example
}

int main(void) {
    int d = 32, m = 13, y = 2025;

    printf("Checking user input...\n");
    if (is_valid_date(d, m, y)) {
        calculate_zeller_final(d, m, y);
    } else {
        printf("Error: User entered garbage data. The function will not be called.\n");
    }

    // Uncomment the line below to see assert in action:
    // calculate_zeller_final(32, 1, 2025); 

    return 0;
}
