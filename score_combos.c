// EECS 348 • Lab 8 • Task 1
// score_combos.c — enumerate NFL scoring-play combinations for a given score
// Author: Gabe Liston
// Build:  gcc -Wall -Wextra -O2 -o score_combos score_combos.c
// Run:    ./score_combos
#include <stdio.h>

int main(void) {
    int score;

    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        if (scanf("%d", &score) != 1) {
            printf("Invalid input. Exiting.\n");
            return 0;
        }

        if (score == 1) break;
        if (score < 0) {
            printf("Score must be non-negative.\n");
            continue;
        }

        printf("Possible combinations of scoring plays if a team’s score is %d:\n", score);

        int found = 0;
        // Order: TD+2=8, TD+FG=7, TD=6, FG=3, Safety=2  (print in this order)
        for (int td2 = 0; td2 <= score / 8; ++td2) {
            int rem_after_td2 = score - 8 * td2;

            for (int tdfg = 0; tdfg <= rem_after_td2 / 7; ++tdfg) {
                int rem_after_tdfg = rem_after_td2 - 7 * tdfg;

                for (int td = 0; td <= rem_after_tdfg / 6; ++td) {
                    int rem_after_td = rem_after_tdfg - 6 * td;

                    for (int fg = 0; fg <= rem_after_td / 3; ++fg) {
                        int rem_after_fg = rem_after_td - 3 * fg;

                        if (rem_after_fg >= 0 && rem_after_fg % 2 == 0) {
                            int saf = rem_after_fg / 2;
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                                   td2, tdfg, td, fg, saf);
                            found = 1;
                        }
                    }
                }
            }
        }

        if (!found) {
            printf("No combinations possible.\n");
        }
    }

    return 0;
}
