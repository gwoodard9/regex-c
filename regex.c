#include <stdio.h>
#include <string.h>
#include <regex.h>

#ifndef STRINGS_H
#define STRINGS_H

extern const char *textBefore[];
extern const int textBeforeLen;

extern const char *textAfter[];
extern const int textAfterLen;

int loopBefore(const char *textBefore[]);
int loopAfter(const char *textAfter[]);

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

    return result == 0; // 0 means match found
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

    for (int i = 0; i < 20; i++)
    {
        int prev = (i > 0) ? textBefore[i - 1] : 0;
        int nex = (i < 20 - 1) ? atextBeforerr[i + 1] : 0;
        int cur = textBefore[i];

        char temp[256];
        strncpy(temp, textBefore[i], sizeof(temp) - 1);
        char *word = strtok(temp, " ");

        if (matches_email(word))
        {
            printf("%s,%s\n", "Email Address", word);
        }
        else if (matches_phone(word))
        {
            printf("%s,%s\n", "Phone Number", word);
        }
        else if (matches_counter(word))
        {
            printf("%s,%s\n", "Counter", word);
        }
        else if (matches_date_one(word))
        {
            printf("%s,%s\n", "Datetime", word);
        }
        else if (matches_date_two(word))
        {
            printf("%s,%s\n", "Datetime", word);
        }
        else if (matches_timestamp_stand(word))
        {
            printf("%s,%s\n", "Timestamp", word);
        }
        else if (matches_timestamp_ISO(word))
        {
            printf("%s,%s\n", "Timestamp", word);
        }
        else
        {
            printf("%s,%s\n", "None", word);
        }
        word = strtok(NULL, " ");

        printf("\n");
        // while (word != NULL)
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