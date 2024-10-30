#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void redir(const char *inp, const char *cmd, const char *out) {
    // Create a command string to execute
    char command[256]; // Buffer for the command
    char input_redirection[128];
    char output_redirection[128];

    // Set up input redirection if needed
    if (strcmp(inp, "-") != 0) {
        snprintf(input_redirection, sizeof(input_redirection), "< %s ", inp);
    } else {
        input_redirection[0] = '\0'; // No input redirection
    }

    // Set up output redirection if needed
    if (strcmp(out, "-") != 0) {
        snprintf(output_redirection, sizeof(output_redirection), "> %s", out);
    } else {
        output_redirection[0] = '\0'; // No output redirection
    }

    // Construct the final command
    snprintf(command, sizeof(command), "%s %s %s", input_redirection, cmd, output_redirection);

    // Execute the command using system()
    int status = system(command);
    if (status == -1) {
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input> <command> <output>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *command = argv[2];
    const char *output_file = argv[3];

    redir(input_file, command, output_file);

    return EXIT_SUCCESS;
}

