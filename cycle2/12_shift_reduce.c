/*=============================================================================
 |   Problem:  An improved, simple implementation of a Shift-Reduce Parser.
 |
 |   Improvements from the original:
 |   1.  Correct Reduction: Only reduces a handle if it's at the TOP of the stack.
 |   2.  Clearer Logic: The main loop now explicitly decides whether to shift or
 |       reduce, which is more accurate to how real parsers work.
 |   3.  Robust Handle Matching: Uses string comparison from the end of the
 |       stack for more reliable handle detection.
 +-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Grammar and Parser Configuration ---
// Note: Productions are written in reverse to simplify handle searching.
// (e.g., "E+E" for E=E+E)
char productions[][10] = {"E+E", "E*E", "i", "(E)", "E-E", "E/E"};
char non_terminals[] = {'E', 'E', 'E', 'E', 'E', 'E'}; // LHS for each production
int num_productions = 6;

// --- Parser State ---
char stack[100];
int top = -1;

// --- Function Prototypes ---
void print_step(const char* action, const char* input, int ip);
void shift(char symbol);
int reduce();

int main() {
    char input[100];
    int ip = 0; // Input pointer

    printf("The grammar is:\n");
    for(int i=0; i<num_productions; ++i) {
        printf("  E -> %s\n", productions[i]);
    }
    printf("--------------------------------------------------\n");
    printf("Enter the input string: ");
    scanf("%s", input);

    // Initialize stack with '$' to represent the bottom
    stack[++top] = '$';

    printf("\n--- Parsing Steps ---\n");
    printf("Stack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");

    print_step("Initial", input, ip);

    // The main parser loop
    while (1) {
        // First, try to reduce.
        int reduction_rule_num = reduce();

        if (reduction_rule_num != -1) {
            // If a reduction happened, print the step and continue the loop
            // to check for more possible reductions.
            char action_str[50];
            sprintf(action_str, "Reduce E->%s", productions[reduction_rule_num]);
            print_step(action_str, input, ip);
            continue; // Go back and check for another reduction
        }

        // If no reduction was possible, try to shift.
        if (input[ip] != '\0') {
            shift(input[ip]);
            char action_str[50];
            sprintf(action_str, "Shift %c", input[ip]);
            ip++;
            print_step(action_str, input, ip); // Move input pointer forward
        } else {
            // If no reduction and no more input, break the loop.
            break;
        }
    }

    // --- Final Acceptance Check ---
    // The input is accepted if the input is fully read and the stack
    // contains only the start symbol '$E'.
    if (top == 1 && stack[top] == 'E') {
        printf("\n--------------------------------------------------\n");
        printf("SUCCESS: Input string is accepted.\n");
        printf("--------------------------------------------------\n");
    } else {
        printf("\n--------------------------------------------------\n");
        printf("ERROR: Input string is rejected.\n");
        printf("--------------------------------------------------\n");
    }

    return 0;
}

/**
 * @brief Prints a single step of the parsing process.
 */
void print_step(const char* action, const char* input, int ip) {
    // Print stack contents
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\t\t");

    // Print remaining input
    printf("%s", input + ip);
    printf("\t\t");

    // Print the action taken
    printf("%s\n", action);
}

/**
 * @brief Shifts a symbol onto the top of the stack.
 */
void shift(char symbol) {
    stack[++top] = symbol;
}

/**
 * @brief Tries to find a handle at the top of the stack and reduce it.
 * @return The rule number used for reduction, or -1 if no reduction was possible.
 */
int reduce() {
    for (int i = 0; i < num_productions; i++) {
        int handle_len = strlen(productions[i]);

        // Check if the stack is long enough for this handle
        if (top < handle_len) {
            continue;
        }

        // Pointer to the start of the potential handle on the stack
        char* handle_start_on_stack = &stack[top - handle_len + 1];

        // Compare the handle with the top of the stack
        if (strncmp(handle_start_on_stack, productions[i], handle_len) == 0) {
            // Match found! Perform the reduction.
            top -= handle_len; // Pop the handle
            stack[++top] = non_terminals[i]; // Push the non-terminal
            return i; // Return the rule number that was used
        }
    }
    return -1; // No handle found at the top of the stack
}
