/** @file spf_analyzer.c
 *  @brief A program that analyzes student performance records from a CSV file.
 *
 *  This program processes student records based on specific filtering criteria
 *  and sorting requirements defined by three different tasks:
 *    - Task 1: Filter students with 100% attendance and "Yes" in extracurricular 
 *              activities, sorted by Record_ID (ascending)
 *    - Task 2: Filter students who studied more than 40 hours, 
 *              sorted by Exam_Score (descending)
 *    - Task 3: Filter students with Exam_Score >= 85, 
 *              sorted by Exam_Score (ascending) and Record_ID (ascending)
 *
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Tanuj D.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "emalloc.h"

/* Constants */
#define MAX_LINE_LEN 1024
#define MAX_FIELD_LEN 100
#define INPUT_FILE "data/a3-data.csv"
#define OUTPUT_FILE "output.csv"

/**
 * @brief Structure to represent a student record with relevant performance attributes.
 */
typedef struct {
    int record_id;
    float attendance;
    char extracurricular_activities[MAX_FIELD_LEN];
    int hours_studied;
    float exam_score;
} Student;

/**
 * @brief Removes leading and trailing whitespace from a string.
 * 
 * @param str The string to be trimmed
 * @return char* Pointer to the trimmed string
 */
char *trim(char *str) {
    char *end;
    
    // Remove leading whitespace
    while(isspace((unsigned char)*str)) str++;
    
    // Handle empty string
    if(*str == 0) return str;
    
    // Remove trailing whitespace
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    
    return str;
}

/**
 * @brief Creates a duplicate of a string (safer replacement for strdup).
 * 
 * @param str The string to duplicate
 * @return char* Pointer to the newly allocated duplicate string
 */
char *my_strdup(const char *str) {
    size_t len = strlen(str) + 1; // +1 for the null terminator
    char *new_str = (char *)emalloc(len);
    strcpy(new_str, str);
    return new_str;
}

/**
 * @brief Parses a CSV line into a Student record structure.
 * 
 * Maps columns from the CSV file to the appropriate Student structure fields:
 * - Column 0: Record_ID
 * - Column 1: Hours_Studied
 * - Column 2: Attendance
 * - Column 3: Extracurricular_Activities
 * - Column 7: Exam_Score
 * (Columns 4-6 are not used in the analysis tasks)
 * 
 * @param line The CSV line to parse
 * @return Student The parsed student record
 */
Student parse_csv_line(char *line) {
    Student student = {0};
    char *line_copy = my_strdup(line);
    char *token;
    int field = 0;

    token = strtok(line_copy, ",");
    while (token != NULL) {
        token = trim(token);
        switch (field) {
            case 0: // Record_ID
                student.record_id = atoi(token);
                break;
            case 1: // Hours_Studied
                student.hours_studied = atoi(token);
                break;
            case 2: // Attendance
                student.attendance = atof(token);
                break;
            case 3: // Extracurricular_Activities
                strncpy(student.extracurricular_activities, token, MAX_FIELD_LEN - 1);
                student.extracurricular_activities[MAX_FIELD_LEN - 1] = '\0';
                break;
            case 4: // Sleep_Hours (not used in tasks)
                break;
            case 5: // Tutoring_Sessions (not used in tasks)
                break;
            case 6: // Physical_Activity (not used in tasks)
                break;
            case 7: // Exam_Score
                student.exam_score = atof(token);
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }

    free(line_copy);
    return student;
}

/**
 * @brief Creates a string representation of a Student record.
 * 
 * The student record fields are separated by pipe (|) characters
 * in the following order: record_id, attendance, extracurricular_activities,
 * hours_studied, exam_score.
 * 
 * @param student Pointer to the Student record
 * @return char* String representation of the student record
 */
char *student_to_string(Student *student) {
    char *str = (char *)emalloc(MAX_LINE_LEN);
    sprintf(str, "%d|%.2f|%s|%d|%.2f", 
            student->record_id, 
            student->attendance, 
            student->extracurricular_activities, 
            student->hours_studied, 
            student->exam_score);
    return str;
}

/**
 * @brief Adds a student record to the list sorted by Record_ID (ascending).
 * 
 * Used for Task 1: Students with 100% attendance and "Yes" for extracurricular activities.
 * 
 * @param list The current list of student records
 * @param student Pointer to the student record to add
 * @return node_t* The updated list with the new student record
 */
node_t *add_task1_order(node_t *list, Student *student) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    char *student_str = student_to_string(student);
    node_t *new_node_ptr = new_node(student_str);
    free(student_str); // Free temporary string since it's copied in new_node

    // If list is empty, return the new node
    if (list == NULL) {
        return new_node_ptr;
    }

    // Find the appropriate position in the list based on Record_ID
    for (curr = list; curr != NULL; curr = curr->next) {
        Student curr_student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        
        // Extract Record_ID from the stored string
        token = strtok(curr_copy, "|");
        curr_student.record_id = atoi(token);
        free(curr_copy);
        
        // Insert at this position if the new record_id is less than or equal to current
        if (student->record_id <= curr_student.record_id) {
            break;
        }
        prev = curr;
    }

    // Insert the new node in the correct position
    new_node_ptr->next = curr;

    if (prev == NULL) {
        // Insert at the beginning
        return new_node_ptr;
    } else {
        // Insert after prev
        prev->next = new_node_ptr;
        return list;
    }
}

/**
 * @brief Adds a student record to the list sorted by Exam_Score (descending).
 * 
 * Used for Task 2: Students who studied more than 40 hours.
 * 
 * @param list The current list of student records
 * @param student Pointer to the student record to add
 * @return node_t* The updated list with the new student record
 */
node_t *add_task2_order(node_t *list, Student *student) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    char *student_str = student_to_string(student);
    node_t *new_node_ptr = new_node(student_str);
    free(student_str);

    // If list is empty, return the new node
    if (list == NULL) {
        return new_node_ptr;
    }

    // Find the appropriate position in the list based on Exam_Score (descending)
    for (curr = list; curr != NULL; curr = curr->next) {
        Student curr_student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        int field = 0;
        
        // Navigate to the exam_score field (5th field)
        token = strtok(curr_copy, "|");
        while (token != NULL && field < 4) {
            token = strtok(NULL, "|");
            field++;
        }
        if (token != NULL) {
            curr_student.exam_score = atof(token);
        }
        free(curr_copy);
        
        // For descending order, insert if new score is higher than or equal to current
        if (student->exam_score >= curr_student.exam_score) {
            break;
        }
        prev = curr;
    }

    // Insert the new node in the correct position
    new_node_ptr->next = curr;

    if (prev == NULL) {
        // Insert at the beginning
        return new_node_ptr;
    } else {
        // Insert after prev
        prev->next = new_node_ptr;
        return list;
    }
}

/**
 * @brief Adds a student record to the list sorted by Exam_Score (ascending) and Record_ID (ascending).
 * 
 * Used for Task 3: Students with Exam_Score >= 85.
 * Primary sort is by Exam_Score (ascending), secondary sort is by Record_ID (ascending).
 * 
 * @param list The current list of student records
 * @param student Pointer to the student record to add
 * @return node_t* The updated list with the new student record
 */
node_t *add_task3_order(node_t *list, Student *student) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    char *student_str = student_to_string(student);
    node_t *new_node_ptr = new_node(student_str);
    free(student_str);

    // If list is empty, return the new node
    if (list == NULL) {
        return new_node_ptr;
    }

    // Find the appropriate position based on Exam_Score (ascending) and Record_ID (ascending)
    for (curr = list; curr != NULL; curr = curr->next) {
        Student curr_student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        int field = 0;
        
        // Extract Record_ID (first field)
        token = strtok(curr_copy, "|");
        curr_student.record_id = atoi(token);
        
        // Navigate to the exam_score field (5th field)
        while (token != NULL && field < 4) {
            token = strtok(NULL, "|");
            field++;
        }
        if (token != NULL) {
            curr_student.exam_score = atof(token);
        }
        free(curr_copy);
        
        // Insert based on primary (exam_score) and secondary (record_id) sorting criteria
        if (student->exam_score < curr_student.exam_score ||
            (student->exam_score == curr_student.exam_score && 
             student->record_id <= curr_student.record_id)) {
            break;
        }
        prev = curr;
    }

    // Insert the new node in the correct position
    new_node_ptr->next = curr;

    if (prev == NULL) {
        // Insert at the beginning
        return new_node_ptr;
    } else {
        // Insert after prev
        prev->next = new_node_ptr;
        return list;
    }
}

/**
 * @brief Processes student records according to the specified task.
 * 
 * Reads the input CSV file, applies filtering criteria based on the task,
 * and adds qualifying records to a list in the specified order.
 * 
 * @param task The task number (1, 2, or 3)
 * @return node_t* List of filtered and sorted student records
 */
node_t *process_task(int task) {
    FILE *file = fopen(INPUT_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", INPUT_FILE);
        exit(1);
    }

    char line[MAX_LINE_LEN];
    node_t *list = NULL;

    // Read and discard the header line
    if (fgets(line, MAX_LINE_LEN, file) == NULL) {
        fprintf(stderr, "Error reading header line\n");
        fclose(file);
        exit(1);
    }

    // Read and process data lines
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        Student student = parse_csv_line(line);

        // Apply filters based on the task
        int pass_filter = 0;
        switch (task) {
            case 1:
                // Task 1: Students with 100% attendance and "Yes" for extracurricular activities
                pass_filter = (student.attendance == 100.0 && 
                              strcmp(student.extracurricular_activities, "Yes") == 0);
                break;
            case 2:
                // Task 2: Students who studied more than 40 hours
                pass_filter = (student.hours_studied > 40);
                break;
            case 3:
                // Task 3: Students with Exam_Score >= 85
                pass_filter = (student.exam_score >= 85);
                break;
        }

        // Add qualifying records to the list in the specified order
        if (pass_filter) {
            switch (task) {
                case 1:
                    list = add_task1_order(list, &student);
                    break;
                case 2:
                    list = add_task2_order(list, &student);
                    break;
                case 3:
                    list = add_task3_order(list, &student);
                    break;
            }
        }
    }

    fclose(file);
    return list;
}

/**
 * @brief Writes the filtered and sorted student records to a CSV file.
 * 
 * Formats the output based on the task and limits the number of records written.
 * 
 * @param filename The output file name
 * @param list The list of student records to write
 * @param task The task number (1, 2, or 3)
 * @param limit The maximum number of records to write
 */
void write_csv_file(const char *filename, node_t *list, int task, int limit) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        exit(1);
    }

    // Write header line based on the task
    switch (task) {
        case 1:
            fprintf(file, "Record_ID,Exam_Score\n");
            break;
        case 2:
        case 3:
            fprintf(file, "Record_ID,Hours_Studied,Exam_Score\n");
            break;
    }

    // Write data lines (limited by the specified count)
    node_t *curr;
    int count = 0;
    for (curr = list; curr != NULL && count < limit; curr = curr->next, count++) {
        Student student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        
        // Extract Record_ID (first field)
        token = strtok(curr_copy, "|");
        student.record_id = atoi(token);
        
        // Skip attendance and extracurricular activities fields
        token = strtok(NULL, "|"); // attendance
        token = strtok(NULL, "|"); // extracurricular
        
        // Extract Hours_Studied (fourth field)
        token = strtok(NULL, "|");
        student.hours_studied = atoi(token);
        
        // Extract Exam_Score (fifth field)
        token = strtok(NULL, "|");
        student.exam_score = atof(token);
        
        free(curr_copy);

        // Format and write the record based on the task
        switch (task) {
            case 1:
                fprintf(file, "%d,%.0f\n", student.record_id, student.exam_score);
                break;
            case 2:
            case 3:
                fprintf(file, "%d,%d,%.0f\n", student.record_id, student.hours_studied, student.exam_score);
                break;
        }
    }

    fclose(file);
}

/**
 * @brief Main function that parses command line arguments and executes the requested task.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return int Exit status (0 for success)
 */
int main(int argc, char *argv[]) {
    int task = 0;
    int limit = 0;

    // Parse command line arguments to determine the task
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--TASK=", 7) == 0) {
            task = atoi(argv[i] + 7);
        }
    }

    // Set the record limit based on the task
    switch (task) {
        case 1:
            limit = 20; // Task 1: Output up to 20 records
            break;
        case 2:
        case 3:
            limit = 10; // Tasks 2 & 3: Output up to 10 records
            break;
        default:
            fprintf(stderr, "Invalid task: %d\n", task);
            exit(1);
    }

    // Process the data based on the task
    node_t *result_list = process_task(task);

    // Write the results to the output CSV file
    write_csv_file(OUTPUT_FILE, result_list, task, limit);

    // Free memory allocated for the list
    node_t *temp_n = NULL;
    for (; result_list != NULL; result_list = temp_n) {
        temp_n = result_list->next;
        free(result_list->word);
        free(result_list);
    }

    return 0;
}
