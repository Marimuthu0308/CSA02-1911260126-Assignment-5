#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NAME_LEN 16

/* Validate blood group */
int is_valid_blood_group(const char *bg)
{
    const char *valid[] = {
        "O+", "O-", "A+", "A-",
        "B+", "B-", "AB+", "AB-"
    };

    int i;

    for (i = 0; i < 8; i++)
    {
        if (strcmp(bg, valid[i]) == 0)
            return 1;
    }

    return 0;
}

/* Remove newline */
void strip_newline(char *s)
{
    size_t len = strlen(s);

    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

/* Dynamic line reading */
char *read_line_dynamic(FILE *fp)
{
    size_t capacity = 32;
    size_t length = 0;
    int ch;

    char *buffer = malloc(capacity);

    if (buffer == NULL)
    {
        perror("malloc");
        return NULL;
    }

    while ((ch = fgetc(fp)) != EOF && ch != '\n')
    {
        if (length + 1 >= capacity)
        {
            capacity *= 2;

            char *temp = realloc(buffer, capacity);

            if (temp == NULL)
            {
                perror("realloc");
                free(buffer);
                return NULL;
            }

            buffer = temp;
        }

        buffer[length++] = (char)ch;
    }

    if (length == 0 && ch == EOF)
    {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';

    return buffer;
}

int main()
{
    char command[10];
    char blood_group[5];
    char safe_name[NAME_LEN];
    int units;

    printf("===== BLOOD BANK MANAGEMENT =====\n");

    /* Get command */
    printf("\nEnter command (find/issue): ");
    scanf("%9s", command);

    /* Get blood group */
    printf("Enter blood group: ");
    scanf("%4s", blood_group);

    /* Validate blood group */
    if (!is_valid_blood_group(blood_group))
    {
        printf("Error: Invalid blood group!\n");
        return 1;
    }

    /* Process command */
    if (strcmp(command, "find") == 0)
    {
        printf("\nSearching eligible donors for blood group %s...\n",
               blood_group);
    }
    else if (strcmp(command, "issue") == 0)
    {
        printf("Enter number of units: ");

        if (scanf("%d", &units) != 1 || units <= 0)
        {
            printf("Error: Units must be a positive integer.\n");
            return 1;
        }

        printf("Issuing %d unit(s) of %s...\n",
               units, blood_group);
    }
    else
    {
        printf("Error: Unknown command!\n");
        return 1;
    }

    /* File error handling */
    FILE *fp = fopen("missing_donors.txt", "r");

    if (fp == NULL)
        perror("fopen missing_donors.txt");
    else
        fclose(fp);

    fp = fopen("readonly_test.txt", "r+");

    if (fp == NULL)
        perror("fopen readonly_test.txt");
    else
        fclose(fp);

    /* Clear input buffer */
    while (getchar() != '\n' && !feof(stdin));

    /* Safe input using fgets */
    printf("\nEnter donor name (maximum 15 characters): ");

    if (fgets(safe_name, sizeof(safe_name), stdin) != NULL)
    {
        strip_newline(safe_name);

        printf("Stored safely with fgets: '%s'\n", safe_name);
    }

    /* Dynamic memory allocation */
    printf("\nEnter another line: ");

    char *dynamic_line = read_line_dynamic(stdin);

    if (dynamic_line != NULL)
    {
        printf("Read dynamically: '%s'\n", dynamic_line);
        free(dynamic_line);
    }

    printf("\nProgram executed successfully!\n");

    return 0;
}

