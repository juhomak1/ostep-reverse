#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

struct Node {
    char *line;
    struct Node *next;
};


int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;
    
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    
    if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }
    
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    
    struct Node *head = NULL;
    
    char *lineptr = NULL;
    size_t n = 0;
    
    while (getline(&lineptr, &n, input) != -1) {
        
        struct Node *new_node = malloc(sizeof(struct Node));
        if (new_node == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        
        new_node->line = strdup(lineptr);
        if (new_node->line == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        
        new_node->next = head;
        head = new_node;
    }
    free(lineptr);
    
    struct Node *current = head;
    while (current != NULL) {
        fprintf(output, "%s", current->line);
        current = current->next;
    }
    
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->line);
        free(temp);
    }
    
    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);
    
    return 0;
}