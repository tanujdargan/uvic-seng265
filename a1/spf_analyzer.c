#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 6608

/**
 * Struct: CurricularData
 * ----------------------
 * @brief Represents a row from the a1-data-curricular.csv file.
 */
typedef struct {
    int record_id;           // Maps to the "Record_ID" column
    int hours_studied;       // Maps to the "Hours_Studied" column
    int attendance;          // Maps to the "Attendance" column
    int tutoring_sessions;   // Maps to the "Tutoring_Sessions" column
    int exam_score;          // Maps to the "Exam_Score" column
} CurricularData;

/**
 * Function: read_csv_file
 * -----------------------
 * @brief Reads data from the a1-data-curricular.csv file and populates an array of CurricularData structs.
 *
 * @param filename The name of the CSV file to read.
 * @param data Array of CurricularData where the CSV data will be stored.
 * @return int The number of records successfully read.
 */
int read_csv_file(const char *filename, CurricularData data[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }

    // Skip the header line
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    int index = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && index < MAX_RECORDS) {
        sscanf(buffer, "%d,%d,%d,%d,%d", 
               &data[index].record_id, 
               &data[index].hours_studied, 
               &data[index].attendance, 
               &data[index].tutoring_sessions, 
               &data[index].exam_score);
        index++;
    }

    fclose(file);
    return index;
}

/**
 * Function: print_data
 * --------------------
 * @brief Prints the contents of the array of CurricularData.
 *
 * @param data Array of CurricularData to print.
 * @param size The number of records in the array.
 */
void print_data(const CurricularData data[], int size) {
    printf("Record_ID | Hours_Studied | Attendance | Tutoring_Sessions | Exam_Score\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%10d | %13d | %10d | %17d | %10d\n", 
            data[i].record_id, 
            data[i].hours_studied, 
            data[i].attendance, 
            data[i].tutoring_sessions, 
            data[i].exam_score);
    }
}

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @return int 0: No errors; 1: Errors produced.
 */
int main() {
    CurricularData data[MAX_RECORDS];  // Array to hold all rows from the CSV
    const char *filename = "data/a1-data-curricular.csv";

    int num_records = read_csv_file(filename, data);
    if (num_records < 0) {
        return 1; // Error occurred while reading the file
    }

    printf("\nSuccessfully read %d records from %s\n\n", num_records, filename);
    // print_data(data, num_records);

    return 0;
}
