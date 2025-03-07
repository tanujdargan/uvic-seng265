/** @file spf_analyzer.c
 *  @brief A program to analyze student performance factors data.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "emalloc.h"

#define MAX_LINE_LEN 1024
#define MAX_FIELD_LEN 100
#define INPUT_FILE "data/a3-data.csv"
#define OUTPUT_FILE "output.csv"

// Structure to represent a student record
typedef struct {
    int record_id;
    float attendance;
    char extracurricular_activities[MAX_FIELD_LEN];
    int hours_studied;
    float exam_score;
} Student;

// Function to duplicate a string (replacement for strdup)
char *my_strdup(const char *str) {
    size_t len = strlen(str) + 1; // +1 for the null terminator
    char *new_str = (char *)emalloc(len);
    strcpy(new_str, str);
    return new_str;
}

// Function to trim whitespace
char *trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

// Function to parse a CSV line into a Student record
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
            case 1: // Attendance
                student.attendance = atof(token);
                break;
            case 2: // Extracurricular_Activities
                strncpy(student.extracurricular_activities, token, MAX_FIELD_LEN - 1);
                student.extracurricular_activities[MAX_FIELD_LEN - 1] = '\0';
                break;
            case 3: // Hours_Studied
                student.hours_studied = atoi(token);
                break;
            case 4: // Exam_Score
                student.exam_score = atof(token);
                break;
        }
        token = strtok(NULL, ",");
        field++;
    }

    free(line_copy);
    return student;
}

// Create a string representation of a Student record
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

// Task 1: Add student record sorted by Record_ID (ascending)
node_t *add_task1_order(node_t *list, Student *student) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    char *student_str = student_to_string(student);
    node_t *new_node_ptr = new_node(student_str);
    free(student_str); // Free temporary string since it's copied in new_node

    if (list == NULL) {
        return new_node_ptr;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        Student curr_student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        
        token = strtok(curr_copy, "|");
        curr_student.record_id = atoi(token);
        free(curr_copy);
        
        if (student->record_id <= curr_student.record_id) {
            break;
        }
        prev = curr;
    }

    new_node_ptr->next = curr;

    if (prev == NULL) {
        return new_node_ptr;
    } else {
        prev->next = new_node_ptr;
        return list;
    }
}

// Task 2: Add student record sorted by Exam_Score (descending)
node_t *add_task2_order(node_t *list, Student *student) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    char *student_str = student_to_string(student);
    node_t *new_node_ptr = new_node(student_str);
    free(student_str);

    if (list == NULL) {
        return new_node_ptr;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        Student curr_student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        int field = 0;
        
        token = strtok(curr_copy, "|");
        while (token != NULL && field < 4) {
            token = strtok(NULL, "|");
            field++;
        }
        if (token != NULL) {
            curr_student.exam_score = atof(token);
        }
        free(curr_copy);
        
        if (student->exam_score >= curr_student.exam_score) {
            break;
        }
        prev = curr;
    }

    new_node_ptr->next = curr;

    if (prev == NULL) {
        return new_node_ptr;
    } else {
        prev->next = new_node_ptr;
        return list;
    }
}

// Task 3: Add student record sorted by Exam_Score (ascending) and Record_ID (ascending)
node_t *add_task3_order(node_t *list, Student *student) {
    node_t *prev = NULL;
    node_t *curr = NULL;
    char *student_str = student_to_string(student);
    node_t *new_node_ptr = new_node(student_str);
    free(student_str);

    if (list == NULL) {
        return new_node_ptr;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        Student curr_student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        int field = 0;
        
        token = strtok(curr_copy, "|");
        curr_student.record_id = atoi(token);
        
        while (token != NULL && field < 4) {
            token = strtok(NULL, "|");
            field++;
        }
        if (token != NULL) {
            curr_student.exam_score = atof(token);
        }
        free(curr_copy);
        
        if (student->exam_score < curr_student.exam_score ||
            (student->exam_score == curr_student.exam_score && 
             student->record_id <= curr_student.record_id)) {
            break;
        }
        prev = curr;
    }

    new_node_ptr->next = curr;

    if (prev == NULL) {
        return new_node_ptr;
    } else {
        prev->next = new_node_ptr;
        return list;
    }
}

// Process data for a specific task
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
                pass_filter = (student.attendance == 100.0 && 
                              strcmp(student.extracurricular_activities, "Yes") == 0);
                break;
            case 2:
                pass_filter = (student.hours_studied > 40);
                break;
            case 3:
                pass_filter = (student.exam_score >= 85);
                break;
        }

        if (pass_filter) {
            // Add the student to the list in the specified order
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

// Write the results to the output CSV file
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

    // Write data lines
    node_t *curr;
    int count = 0;
    for (curr = list; curr != NULL && count < limit; curr = curr->next, count++) {
        Student student;
        char *curr_copy = my_strdup(curr->word);
        char *token;
        
        token = strtok(curr_copy, "|");
        student.record_id = atoi(token);
        
        token = strtok(NULL, "|"); // attendance
        token = strtok(NULL, "|"); // extracurricular
        token = strtok(NULL, "|");
        student.hours_studied = atoi(token);
        
        token = strtok(NULL, "|");
        student.exam_score = atof(token);
        
        free(curr_copy);

        switch (task) {
            case 1:
                fprintf(file, "%d,%.2f\n", student.record_id, student.exam_score);
                break;
            case 2:
            case 3:
                fprintf(file, "%d,%d,%.2f\n", student.record_id, student.hours_studied, student.exam_score);
                break;
        }
    }

    fclose(file);
}

// Main function
int main(int argc, char *argv[]) {
    int task = 0;
    int limit = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--TASK=", 7) == 0) {
            task = atoi(argv[i] + 7);
        }
    }

    // Set the limit based on the task
    switch (task) {
        case 1:
            limit = 20;
            break;
        case 2:
        case 3:
            limit = 10;
            break;
        default:
            fprintf(stderr, "Invalid task: %d\n", task);
            exit(1);
    }

    // Process the data based on the task
    node_t *result_list = process_task(task);

    // Write the results to the output CSV file
    write_csv_file(OUTPUT_FILE, result_list, task, limit);

    // Free memory
    node_t *temp_n = NULL;
    for (; result_list != NULL; result_list = temp_n) {
        temp_n = result_list->next;
        free(result_list->word);
        free(result_list);
    }

    return 0;
}
