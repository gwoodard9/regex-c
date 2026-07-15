#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRINGS_H
#define STRINGS_H

extern const char* textBefore[];
extern const int textBeforeLen;

extern const char* textAfter[];
extern const int textAfterLen;

int loopBefore(const char* textBefore[]);
int loopAfter(const char* textAfter[]);
int shift_arr(char* tre_arr[], int* tre_arr_len);
int merge_tre_str(char* tre_arr[], int tre_arr_len, char* str_arr[]);
int check_regex(char* word);
void strip_trailing_punct(char* word);

#endif

int main() {
    loopBefore(textBefore);
    loopAfter(textAfter);
    return 0;
}

#include <regex.h>
#include <stdio.h>

int matches_email(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$",
            REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_phone(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^\\(?[0-9]{3}\\)?[-. ]?[0-9]{3}[-. ]?[0-9]{4}$",
            REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_counter(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^[a-zA-Z_]+[-_]?[0-9]+$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_date_one(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$",
            REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_date_two(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/[0-9]{4}$",
            REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_timestamp_stand(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_timestamp_ISO(const char* word) {
    regex_t regex;
    int result;

    regcomp(&regex, "^[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}$",
            REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int loopBefore(const char* textBefore[]) {
    regex_t regex;

    char* tre_arr[3] = {"", "", ""};
    int tre_arr_len = 3;

    char* str_arr[1] = {""};

    for (int i = 0; i < textBeforeLen; i++) {
        char temp[256];
        strncpy(temp, textBefore[i], sizeof(temp) - 1);
        char* word = strtok(temp, " ");

        word = strtok(NULL, " ");

        while (word != NULL) {

            if (tre_arr_len == 3) {
                shift_arr(tre_arr, &tre_arr_len);
            }

            if (tre_arr_len < 3) {
                tre_arr[tre_arr_len] = strdup(word);
                tre_arr_len++;
            }
            merge_tre_str(tre_arr, tre_arr_len, str_arr);
            strip_trailing_punct(word);
            check_regex(word);

            word = strtok(NULL, " ");
        }
    }

    return 0;
}

int loopAfter(const char* textAfter[]) {
    for (int i = 0; i < textAfterLen; i++) {
    }

    return 0;
}

int shift_arr(char* tre_arr[], int* tre_arr_len) {
    memmove(&tre_arr[0], &tre_arr[1], (*tre_arr_len - 1) * sizeof(char*));

    tre_arr[*tre_arr_len - 1] = NULL;
    (*tre_arr_len)--;

    return 0;
}

int merge_tre_str(char* tre_arr[], int tre_arr_len, char* str_arr[]) {
    size_t total_len = 0;

    for (int i = 0; i < tre_arr_len; i++) {
        total_len += strlen(tre_arr[i]);
    }
    total_len += (tre_arr_len - 1);
    total_len += 1;

    char* result = malloc(total_len);
    if (!result) {
        return 1;
    }

    result[0] = '\0';

    for (int i = 0; i < tre_arr_len; i++) {
        strcat(result, tre_arr[i]);

        if (i != tre_arr_len - 1) {
            strcat(result, " ");
        }
    }

    //
    str_arr[0] = strdup(result);

    // printf("%s\n", str_arr[0]);

    free(result);
    return 0;
}

int check_regex(char* word) {
    if (matches_email(word)) {
        printf("%s\n", "Email Address");
    } else if (matches_phone(word)) {
        printf("%s\n", "Phone Number");
    } else if (matches_counter(word)) {
        printf("%s\n", "Counter");
    } else if (matches_date_one(word)) {
        printf("%s\n", "Datetime");
    } else if (matches_date_two(word)) {
        printf("%s\n", "Datetime");
    } else if (matches_timestamp_stand(word)) {
        printf("%s\n", "Timestamp");
    } else if (matches_timestamp_ISO(word)) {
        printf("%s\n", "Timestamp");
    }
    return 0;
}

void strip_trailing_punct(char* word) {
    int len = strlen(word);
    while (len > 0 && !isalnum((unsigned char)word[len - 1])) {
        word[len - 1] = '\0';
        len--;
    }
}