#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

#ifndef STRINGS_H
#define STRINGS_H

extern const char *textBefore[];
extern const int textBeforeLen;

extern const char *textAfter[];
extern const int textAfterLen;

int loopBefore(const char *textBefore[]);
int loopAfter(const char *textAfter[]);
int shift_arr(char *tre_arr[], int *current_size);

#endif

int main()
{
    loopBefore(textBefore);
    loopAfter(textAfter);
    return 0;
}

#include <regex.h>
#include <stdio.h>

int matches_email(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_phone(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^\\(?[0-9]{3}\\)?[-. ]?[0-9]{3}[-. ]?[0-9]{4}$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_counter(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^[a-zA-Z_]+[-_]?[0-9]+$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_date_one(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_date_two(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/[0-9]{4}$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_timestamp_stand(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int matches_timestamp_ISO(const char *word)
{
    regex_t regex;
    int result;

    regcomp(&regex, "^[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}$", REG_EXTENDED);
    result = regexec(&regex, word, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int loopBefore(const char *textBefore[])
{
    regex_t regex;

    char *tre_arr[3] = {};
    int current_size = 3;

    for (int i = 0; i < 75; i++)
    {
        char temp[256];
        strncpy(temp, textBefore[i], sizeof(temp) - 1);
        char *word = strtok(temp, " ");

        word = strtok(NULL, " ");

        while (word != NULL)
        {
            printf("\n");

            if (current_size == 3)
            {
                shift_arr(tre_arr, &current_size);
            }

            if (current_size < 3)
            {
                tre_arr[current_size] = strdup(word);
                current_size++;
            }

            for (int j = 0; j < current_size; j++)
            {
                printf("%s ", tre_arr[j]);
            }
            word = strtok(NULL, " ");
        }

        // {
        //     if (matches_email(word))
        //     {
        //         printf("%s,%s\n", "Email Address", word);
        //     }
        //     else if (matches_phone(word))
        //     {
        //         printf("%s,%s\n", "Phone Number", word);
        //     }
        //     else if (matches_counter(word))
        //     {
        //         printf("%s,%s\n", "Counter", word);
        //     }
        //     else if (matches_date_one(word))
        //     {
        //         printf("%s,%s\n", "Datetime", word);
        //     }
        //     else if (matches_date_two(word))
        //     {
        //         printf("%s,%s\n", "Datetime", word);
        //     }
        //     else if (matches_timestamp_stand(word))
        //     {
        //         printf("%s,%s\n", "Timestamp", word);
        //     }
        //     else if (matches_timestamp_ISO(word))
        //     {
        //         printf("%s,%s\n", "Timestamp", word);
        //     }
        //     else
        //     {
        //         printf("%s,%s\n", "None", word);
        //     }
        //     word = strtok(NULL, " ");
        // }
    }

    return 0;
}

int loopAfter(const char *textAfter[])
{
    for (int i = 0; i < textAfterLen; i++)
    {
    }

    return 0;
}

int shift_arr(char *tre_arr[], int *current_size)
{
    memmove(&tre_arr[0], &tre_arr[1], (*current_size - 1) * sizeof(char *));

    tre_arr[*current_size - 1] = NULL;
    (*current_size)--;

    return 0;
}