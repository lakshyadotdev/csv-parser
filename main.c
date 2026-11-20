#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    COL_INT,
    COL_DOUBLE,
    COL_STRING
} DataType;

typedef union
{
    int i;
    double d;
    char *s;
} CellValue;

typedef struct Data
{
    CellValue *values;
} Data;

typedef struct Column
{
    char *name;
    DataType type;
    Data data;
} Column;

typedef struct DataFrame
{
    size_t ROWSIZE;
    size_t COLSIZE;
    Column **columns;
} DataFrame;

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

void parse_header(DataFrame *df, char *data, size_t len)
{
    int i = 0;
    // Counting number of cols
    while (data[i] != '\n' && i < len)
    {
        if (data[i] == ',')
        {
            df->COLSIZE++;
        }
        i++;
    }
    df->COLSIZE++;
    i = 0;

    // trimming the cols name and adding into columns array which is a array of pointers of columns
    Column **columns = (Column **)calloc(sizeof(Column *), df->COLSIZE);
    df->columns = columns;
    size_t col_index = 0;
    size_t start = 0;
    for (i = 0; i < len; i++)
    {
        if (data[i] == ',')
        {
            Column *col = (Column *)calloc(sizeof(Column), 1); // new col
            strncpy(col->name, &data[start], i - start - 1);
            start = i + 1;
            columns[col_index] = col;
            col_index++;
        }
    }
}

DataFrame *initDF(char *data, size_t len)
{
    DataFrame *df = (DataFrame *)malloc(sizeof(DataFrame));
    parse_header(df, data, len);
    return df;
}

void printDF(DataFrame *df)
{
    return;
}

void freeDF(DataFrame *df)
{
    return;
}

int main()
{
    char data[] = "name,age,city\nJohn Doe,30,New York\nJane Doe,25,San Francisco, CA";
    printCSV(data, strlen(data));
    DataFrame *df = initDF(data, strlen(data));
    printf("COLSIZE: %zu\n", df->COLSIZE);
    printf("COLName: %s\n", df->columns[0]->name);
    return 0;
}