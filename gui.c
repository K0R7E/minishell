#include "minishell.h"

void ft_print_minishell_gui(void)
{
    printf("\033[2J\033[1;1H");
    printf("\033[1;32m"); 

    printf("\n");
    printf("  /$$      /$$ /$$$$$$ /$$   /$$ /$$$$$$            \n");
    printf(" | $$$    /$$$|_  $$_/| $$$ | $$|_  $$_/            \n");
    printf(" | $$$$  /$$$$  | $$  | $$$$| $$  | $$              \n");
    printf(" | $$ $$/$$ $$  | $$  | $$ $$ $$  | $$              \n");
    printf(" | $$  $$$| $$  | $$  | $$  $$$$  | $$              \n");
    printf(" | $$\\  $ | $$  | $$  | $$\\  $$$  | $$              \n");
    printf(" | $$ \\/  | $$ /$$$$$$| $$ \\  $$ /$$$$$$            \n");
    printf(" |__/     |__/|______/|__/  \\__/|______/            \n");
    printf("   /$$$$$$  /$$   /$$ /$$$$$$$$ /$$       /$$       \n");
    printf("  /$$__  $$| $$  | $$| $$_____/| $$      | $$       \n");
    printf(" | $$  \\__/| $$  | $$| $$      | $$      | $$       \n");
    printf(" |  $$$$$$ | $$$$$$$$| $$$$$   | $$      | $$       \n");
    printf("  \\____  $$| $$__  $$| $$__/   | $$      | $$       \n");
    printf("  /$$  \\ $$| $$  | $$| $$      | $$      | $$       \n");
    printf(" |  $$$$$$/| $$  | $$| $$$$$$$$| $$$$$$$$| $$$$$$$$ \n");
    printf("  \\______/ |__/  |__/|________/|________/|________/ \n");

    printf("\n");

    printf("\033[0m"); // Reset text color to default
}