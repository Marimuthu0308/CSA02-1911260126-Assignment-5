
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int group_code;
    int units;
} Stock;

typedef struct
{
    int id;
    char name[32];
    char group[4];
    int age;
    char phone[16];
    char last_donation[12];
} DonorRecord;

/* Update a specific binary record */
int update_units(FILE *fp, int index, int units)
{
    Stock s;
    long offset;

    if (fp == NULL || index < 0)
        return 0;

    offset = (long)index * sizeof(Stock);

    if (fseek(fp, offset, SEEK_SET) != 0)
        return 0;

    if (fread(&s, sizeof(Stock), 1, fp) != 1)
        return 0;

    s.units = units;

    if (fseek(fp, offset, SEEK_SET) != 0)
        return 0;

    if (fwrite(&s, sizeof(Stock), 1, fp) != 1)
        return 0;

    if (fflush(fp) != 0)
        return 0;

    return 1;
}

/* Benchmark text and binary files */
void benchmark_donors(int count)
{
    DonorRecord *arr;
    DonorRecord *read_arr;
    DonorRecord tmp;

    FILE *ft;
    FILE *fb;

    int i, r_txt = 0;
    size_t r_bin;

    long sz_txt, sz_bin;

    clock_t t0, t1, t2;
    clock_t b0, b1, b2;

    arr = (DonorRecord *)malloc(
        (size_t)count * sizeof(DonorRecord));

    if (arr == NULL)
    {
        perror("malloc");
        return;
    }

    /* Generate donor records */
    for (i = 0; i < count; i++)
    {
        arr[i].id = 1000 + i;

        snprintf(arr[i].name, sizeof(arr[i].name),
                 "Donor_%d", i);

        strcpy(arr[i].group,
               (i % 2 == 0) ? "O+" : "A+");

        arr[i].age = 20 + (i % 35);

        snprintf(arr[i].phone, sizeof(arr[i].phone),
                 "98765%05d", i % 100000);

        strcpy(arr[i].last_donation, "2026-01-15");
    }

    /* Text file writing */
    t0 = clock();

    ft = fopen("donors_bench.txt", "w");

    if (ft == NULL)
    {
        perror("Text file opening failed");
        free(arr);
        return;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(ft, "%d|%s|%s|%d|%s|%s\n",
                arr[i].id,
                arr[i].name,
                arr[i].group,
                arr[i].age,
                arr[i].phone,
                arr[i].last_donation);
    }

    fclose(ft);

    t1 = clock();

    /* Text file reading */
    ft = fopen("donors_bench.txt", "r");

    if (ft == NULL)
    {
        perror("Text file reading failed");
        free(arr);
        return;
    }

    while (fscanf(ft,
                  "%d|%31[^|]|%3[^|]|%d|%15[^|]|%11s",
                  &tmp.id,
                  tmp.name,
                  tmp.group,
                  &tmp.age,
                  tmp.phone,
                  tmp.last_donation) == 6)
    {
        r_txt++;
    }

    fclose(ft);

    t2 = clock();

    /* Binary file writing */
    b0 = clock();

    fb = fopen("donors_bench.bin", "wb");

    if (fb == NULL)
    {
        perror("Binary file opening failed");
        free(arr);
        return;
    }

    if (fwrite(arr, sizeof(DonorRecord),
               (size_t)count, fb) != (size_t)count)
    {
        printf("Binary file writing failed.\n");
        fclose(fb);
        free(arr);
        return;
    }

    fclose(fb);

    b1 = clock();

    /* Binary file reading */
    fb = fopen("donors_bench.bin", "rb");

    if (fb == NULL)
    {
        perror("Binary file reading failed");
        free(arr);
        return;
    }

    read_arr = (DonorRecord *)malloc(
        (size_t)count * sizeof(DonorRecord));

    if (read_arr == NULL)
    {
        perror("malloc");
        fclose(fb);
        free(arr);
        return;
    }

    r_bin = fread(read_arr, sizeof(DonorRecord),
                  (size_t)count, fb);

    fclose(fb);

    b2 = clock();

    /* Text file size */
    ft = fopen("donors_bench.txt", "rb");

    if (ft == NULL)
    {
        perror("Text file size check failed");
        free(read_arr);
        free(arr);
        return;
    }

    fseek(ft, 0, SEEK_END);
    sz_txt = ftell(ft);
    fclose(ft);

    /* Binary file size */
    fb = fopen("donors_bench.bin", "rb");

    if (fb == NULL)
    {
        perror("Binary file size check failed");
        free(read_arr);
        free(arr);
        return;
    }

    fseek(fb, 0, SEEK_END);
    sz_bin = ftell(fb);
    fclose(fb);

    /* Display results */
    printf("\nDonor Records: %d\n", count);

    printf("Text Records Read: %d\n", r_txt);
    printf("Binary Records Read: %lu\n",
           (unsigned long)r_bin);

    printf("Text Write Time: %.4f seconds\n",
           (double)(t1 - t0) / CLOCKS_PER_SEC);

    printf("Text Read Time: %.4f seconds\n",
           (double)(t2 - t1) / CLOCKS_PER_SEC);

    printf("Text File Size: %ld bytes\n", sz_txt);

    printf("Binary Write Time: %.4f seconds\n",
           (double)(b1 - b0) / CLOCKS_PER_SEC);

    printf("Binary Read Time: %.4f seconds\n",
           (double)(b2 - b1) / CLOCKS_PER_SEC);

    printf("Binary File Size: %ld bytes\n", sz_bin);

    free(read_arr);
    free(arr);
}

/* Main function */
int main(void)
{
    FILE *fp;

    Stock initial[5] = {
        {1, 40},
        {2, 25},
        {3, 12},
        {4, 8},
        {5, 30}
    };

    Stock s;

    printf("===== BLOOD BANK FILE HANDLING =====\n");

    /* Create binary file */
    fp = fopen("stock.dat", "wb+");

    if (fp == NULL)
    {
        perror("File opening failed");
        return 1;
    }

    /* Write initial stock records */
    if (fwrite(initial, sizeof(Stock), 5, fp) != 5)
    {
        printf("File writing failed.\n");
        fclose(fp);
        return 1;
    }

    fflush(fp);

    /* Update records */
    printf("\nUpdating Binary Records:\n");

    printf("Update record 3: %s\n",
           update_units(fp, 3, 20) ? "SUCCESS" : "FAILED");

    printf("Update record 9: %s\n",
           update_units(fp, 9, 20) ? "SUCCESS" : "FAILED");

    /* Display updated records */
    printf("\nUpdated Stock Records:\n");

    rewind(fp);

    while (fread(&s, sizeof(Stock), 1, fp) == 1)
    {
        printf("Group Code: %d | Units: %d\n",
               s.group_code, s.units);
    }

    fclose(fp);

    /* Benchmark different record sizes */
    printf("\n===== TEXT AND BINARY FILE BENCHMARK =====\n");

    benchmark_donors(10);
    benchmark_donors(1000);
    benchmark_donors(10000);
    benchmark_donors(100000);

    printf("\nProgram executed successfully!\n");

    return 0;
}

