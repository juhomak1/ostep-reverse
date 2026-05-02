#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creates a node structure for the linked list.
struct Node {
    char *line;
    struct Node *next;
};


int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;

    // Gives an error if the number of given arguments is more than 3.
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if (argc == 3) {
        // Gives an error if the input and output are the same.
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }

        // Gives an error if the output file cannot be opened.
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }

    // Gives an error if the input file cannot be opened.
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    // Creates the head of the linked list.
    struct Node *head = NULL;

    // Creates a variable for the current line.
    char *lineptr = NULL;
    size_t n = 0;

    // Loops through the input until the end has been reached.
    while (getline(&lineptr, &n, input) != -1) {

        // Creates a new node and outputs an error if the memory allocation fails.
        struct Node *new_node = malloc(sizeof(struct Node));
        if (new_node == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        // Duplicates the text from lineptr as line for the new node.
        new_node->line = strdup(lineptr);
        if (new_node->line == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        // Links the new node to the list and puts it as the new head making the list form in a reversed order.
        new_node->next = head;
        head = new_node;
    }
    free(lineptr);

    // Loops through the list and prints it.
    struct Node *current = head;
    while (current != NULL) {
        fprintf(output, "%s", current->line);
        current = current->next;
    }

    // Cleaning up the used memory.
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->line);
        free(temp);
    }

    // Closing the used files.
    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);
    
    return 0;
}
