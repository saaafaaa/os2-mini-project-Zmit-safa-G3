#include <stdio.h>

// Declare functions
void run_ex1();
void run_ex2();

int main() {
    int choice;

    printf("1 - Exercise 1\n");
    printf("2 - Exercise 2\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        run_ex1();
    } else if (choice == 2) {
        run_ex2();
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}