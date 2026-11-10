#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    COL_INT,
    COL_DOUBLE,
    COL_STRING
} DataType;

union data
{
    double *ndouble;
    char *nstring;
};

typedef union data data;

struct Column
{
    char *name;
    DataType type;
    data *data;
};

typedef struct Column Column;

struct DataFrame
{
    size_t COL_SIZE;
    size_t ROW_SIZE;
    Column *columns;
};

typedef struct DataFrame DataFrame;

void printCSV(const char *data, size_t size)
{
    printf("| ");
    for (size_t i = 0; i < size; i++)
    {
        if (data[i] == ',')
        {
            printf(" | ");
        }
        else if (data[i] == '\n')
        {
            printf(" |\n| ");
        }
        else
        {
            printf("%c", data[i]);
        }
    }
    printf(" |\n");
}

DataFrame *loadCSV(char *data, size_t size)
{
    DataFrame *df = (DataFrame *)malloc(sizeof(DataFrame));
    int field_l = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (data[i] == ',')
        {
            field_l = 0;

            continue;
        }
        if (data[i] == '\n')
        {
            df->ROW_SIZE++;
            field_l = 0;
            continue;
        }
        field_l++;
    }
    return df;
}

int main()
{
    char data[] = "name,age,city\nJohn Doe,30,New York\nJane Doe,25,San Francisco, CA";
    printCSV(data, strlen(data));
    return 0;
}