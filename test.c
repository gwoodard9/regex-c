#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* strings[] = {"how", "are", "you"};
    int n = 3;

    // Calculate total length needed
    size_t total_len = 0;
    for (int i = 0; i < n; i++) {
        total_len += strlen(strings[i]);
        // i=0: total_len = 3   ("how")
        // i=1: total_len = 6   ("how"+"are")
        // i=2: total_len = 9   ("how"+"are"+"you")
    }
    total_len += (n - 1); // total_len = 9 + 2 = 11 (spaces)
    total_len += 1;       // total_len = 12 (null terminator)

    // Allocate the merged string
    char* result = malloc(total_len);
    if (!result)
        return 1;

    result[0] = '\0'; // result = ""

    for (int i = 0; i < n; i++) {
        strcat(result, strings[i]);
        // i=0: result = "how"
        // i=1: result = "how are"
        // i=2: result = "how are you"

        if (i != n - 1)
            strcat(result, " ");
        // i=0: result = "how "
        // i=1: result = "how are "
        // i=2: (skipped, last iteration)
    }

    char* merged[1] = {result}; // merged[0] = "how are you"

    printf("%s\n", merged[0]); // prints "how are you"

    free(result);
    return 0;
}