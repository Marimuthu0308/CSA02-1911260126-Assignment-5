
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int id;
    char group[4];
    int days_since_donation;
    int eligible_next_week;
} Donor;

typedef struct
{
    Donor *data;
    int size;
    int capacity;
} DonorList;

/* Add donor using dynamic memory allocation */
int add_donor(DonorList *list, int id, const char *group)
{
    Donor *temp;
    int new_capacity;

    if (list == NULL)
        return 0;

    /* Increase capacity when required */
    if (list->size == list->capacity)
    {
        if (list->capacity == 0)
            new_capacity = 2;
        else
            new_capacity = list->capacity * 2;

        temp = (Donor *)realloc(
            list->data,
            (size_t)new_capacity * sizeof(Donor));

        if (temp == NULL)
            return 0;

        list->data = temp;
        list->capacity = new_capacity;
    }

    /* Store donor details */
    list->data[list->size].id = id;

    strncpy(list->data[list->size].group, group, 3);
    list->data[list->size].group[3] = '\0';

    list->data[list->size].days_since_donation = id % 120;

    if (list->data[list->size].days_since_donation >= 83)
        list->data[list->size].eligible_next_week = 1;
    else
        list->data[list->size].eligible_next_week = 0;

    list->size++;

    return 1;
}

/* Main function */
int main(void)
{
    DonorList list = {NULL, 0, 0};

    const char *groups[] = {
        "O+", "A+", "B-", "AB+", "O-"
    };

    int i;

    printf("===== BLOOD BANK DONOR MANAGEMENT =====\n");

    /* Add five sample donors */
    printf("\nAdding Donor Records:\n");

    for (i = 0; i < 5; i++)
    {
        if (!add_donor(&list, 7001 + i, groups[i]))
        {
            printf("Memory allocation failed!\n");
            free(list.data);
            return 1;
        }

        printf("Added %d (%s): Size = %d, Capacity = %d\n",
               list.data[i].id,
               list.data[i].group,
               list.size,
               list.capacity);
    }

    /* Release first donor list */
    free(list.data);

    list.data = NULL;
    list.size = 0;
    list.capacity = 0;

    /* Nightly report simulation */
    printf("\n===== NIGHTLY REPORT SIMULATION =====\n");

    int total_donors = 50000;

    DonorList report_list = {NULL, 0, 0};

    clock_t start = clock();

    /* Generate 50000 donor records */
    for (i = 0; i < total_donors; i++)
    {
        if (!add_donor(
                &report_list,
                100000 + i,
                groups[i % 5]))
        {
            printf("Memory allocation failed at %d donors!\n", i);

            free(report_list.data);
            return 1;
        }
    }

    /* Count eligible donors */
    int eligible_count = 0;

    for (i = 0; i < report_list.size; i++)
    {
        if (report_list.data[i].eligible_next_week == 1)
        {
            eligible_count++;
        }
    }

    clock_t end = clock();

    double elapsed =
        (double)(end - start) / CLOCKS_PER_SEC;

    size_t mem_bytes =
        (size_t)report_list.capacity * sizeof(Donor);

    /* Display report */
    printf("\nNightly Report Summary:\n");

    printf("Total donors loaded : %d\n",
           report_list.size);

    printf("Allocated capacity  : %d\n",
           report_list.capacity);

    printf("Eligible next week  : %d\n",
           eligible_count);

    printf("Allocated memory    : %lu bytes\n",
           (unsigned long)mem_bytes);

    printf("Memory in KB        : %.2f KB\n",
           (double)mem_bytes / 1024.0);

    printf("Execution time      : %.4f seconds\n",
           elapsed);

    /* Release allocated memory */
    free(report_list.data);

    report_list.data = NULL;
    report_list.size = 0;
    report_list.capacity = 0;

    printf("\nMemory released successfully.\n");
    printf("Program executed successfully!\n");

    return 0;
}

