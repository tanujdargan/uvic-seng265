#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 6608

/* Define DEBUG to 1 to enable debug messages, or 0 to disable */
#define DEBUG 0

/* --------------------------------------------------------------------------
 *  Structs for csv and yaml files.
 * -------------------------------------------------------------------------- */
typedef struct {
    int record_id;
    int hours_studied;
    int attendance;
    int tutoring_sessions;
    int exam_score;
} CurricularData;

typedef struct {
    int  record_id;
    char extracurricular_activities[16];
    int  physical_activity;
    int  sleep_hours;
} ExtraData;

/* --------------------------------------------------------------------------
 *  Debug print helper - used to debug yaml parsing
 * -------------------------------------------------------------------------- */
void debug_print(const char* msg) {
#if DEBUG
    fprintf(stderr, "DEBUG: %s\n", msg);
#endif
}

/* --------------------------------------------------------------------------
 *  CSV reading
 * -------------------------------------------------------------------------- */
int read_csv_file(const char *filename, CurricularData data[]) {
    debug_print("Entering read_csv_file()...");

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return -1;
    }

    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), file)) {
        /* Skip header line—if that fails, no data. */
        fclose(file);
        return 0;
    }

    int index = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        /* If your CSV is tab-delimited or otherwise, adjust parsing below. */
        int fields = sscanf(buffer, "%d,%d,%d,%d,%d",
                            &data[index].record_id,
                            &data[index].hours_studied,
                            &data[index].attendance,
                            &data[index].tutoring_sessions,
                            &data[index].exam_score);
        if (fields == 5) {
            index++;
        }
        if (index >= MAX_RECORDS) {
            break;
        }
    }

    fclose(file);

    char dbg[100];
    snprintf(dbg, sizeof(dbg), "Exiting read_csv_file(): read %d rows.", index);
    debug_print(dbg);

    return index;
}

/* --------------------------------------------------------------------------
 *  YAML reading (line by line approach)
 * -------------------------------------------------------------------------- */
int read_yaml_file(const char* filename, ExtraData extra[]) {
    debug_print("Entering read_yaml_file()...");

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open YAML file %s\n", filename);
        return -1;
    }

    char line[256];
    // Skip lines until we reach 'records:'
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "records:")) {
            break;
        }
    }

    int idx = -1;  // Start at -1 since we'll increment at the start of a new record

    while (fgets(line, sizeof(line), file) && idx + 1 < MAX_RECORDS) {
        // Trim leading spaces
        char* lptr = line;
        while (*lptr == ' ' || *lptr == '\t') {
            lptr++;
        }

        if (*lptr == '-') {
            // Start of a new record
            idx++;
            // Initialize new record
            extra[idx].record_id = -1;
            extra[idx].extracurricular_activities[0] = '\0';
            extra[idx].physical_activity = 0;
            extra[idx].sleep_hours = 0;
            // Move lptr past '-'
            lptr++;
            // Skip spaces after '-'
            while (*lptr == ' ' || *lptr == '\t') {
                lptr++;
            }
            // Continue parsing the rest of the line for key-value pairs
        }

        // Skip empty lines
        if (*lptr == '\0' || *lptr == '\n') {
            continue;
        }

        // Parse key and value
        char key[64], value[64];
        if (sscanf(lptr, "%[^:]: %[^\n]", key, value) == 2) {
            // Trim value
            char *vptr = value;
            while (*vptr == ' ' || *vptr == '\t') {
                vptr++;
            }
            // Remove surrounding quotes if any
            if (*vptr == '\'' || *vptr == '"') {
                vptr++;
                char *end = vptr;
                while (*end && *end != '\'' && *end != '"' && *end != '\n' && *end != '\r') {
                    end++;
                }
                *end = '\0';
            } else {
                // Remove trailing spaces
                char *end = vptr + strlen(vptr) - 1;
                while (end > vptr && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
                    *end = '\0';
                    end--;
                }
            }

            // Now key and vptr contain the cleaned key and value
            if (strcmp(key, "Extracurricular_Activities") == 0) {
                strncpy(extra[idx].extracurricular_activities, vptr, sizeof(extra[idx].extracurricular_activities) - 1);
                extra[idx].extracurricular_activities[sizeof(extra[idx].extracurricular_activities) - 1] = '\0';
            } else if (strcmp(key, "Physical_Activity") == 0) {
                extra[idx].physical_activity = atoi(vptr);
            } else if (strcmp(key, "Record_ID") == 0) {
                extra[idx].record_id = atoi(vptr);
            } else if (strcmp(key, "Sleep_Hours") == 0) {
                extra[idx].sleep_hours = atoi(vptr);
            }
        }
    }

    fclose(file);

    char dbg[100];
    snprintf(dbg, sizeof(dbg), "Exiting read_yaml_file(): read %d records.", idx + 1);
    debug_print(dbg);

    return idx + 1;
}

/* --------------------------------------------------------------------------
 *  Merge on Record_ID
 * -------------------------------------------------------------------------- */
int merge_on_record_id(const CurricularData* curr, int curr_size,
                       const ExtraData* extra, int extra_size,
                       CurricularData *out_curr, ExtraData* out_extra) {
    debug_print("Entering merge_on_record_id()...");

    int count = 0;
    for (int i = 0; i < curr_size; i++) {
        int c_id = curr[i].record_id;
        for (int j = 0; j < extra_size; j++) {
            if (extra[j].record_id == c_id) {
                out_curr[count] = curr[i];
                out_extra[count] = extra[j];
                count++;
                break;
            }
        }
    }

    char dbg[100];
    snprintf(dbg, sizeof(dbg), "Exiting merge_on_record_id(): matched %d rows.", count);
    debug_print(dbg);

    return count;
}

/* --------------------------------------------------------------------------
 *  CSV writer
 * -------------------------------------------------------------------------- */
void write_header_and_rows(const char* header, const char** rows, int row_count) {
    debug_print("Entering write_header_and_rows()...");

    FILE *out = fopen("output.csv", "w");
    if (!out) {
        fprintf(stderr, "ERROR: Unable to open output.csv for writing.\n");
        return;
    }

    fprintf(out, "%s\n", header);
    for (int i = 0; i < row_count; i++) {
        fprintf(out, "%s\n", rows[i]);
    }
    fclose(out);

    debug_print("Wrote output.csv and exiting write_header_and_rows().");
}

/* --------------------------------------------------------------------------
 *  Print usage
 * -------------------------------------------------------------------------- */
void print_usage() {
    printf("Usage: spf_analyzer --TASK=\"N\"  (where N=1..6)\n");
}

/* --------------------------------------------------------------------------
 *  main
 * -------------------------------------------------------------------------- */
int main(int argc, char *argv[]) {
    debug_print("Entering main()...");

    /* 1) Check arguments */
    if (argc < 2) {
        printf("Insufficient arguments.\n");
        print_usage();
        return 1;
    }

    /* 2) Parse --TASK= */
    int task = 0;
    if (strncmp(argv[1], "--TASK=", 7) == 0) {
        task = atoi(&argv[1][7]);
        char dbg[100];
        snprintf(dbg, sizeof(dbg), "Parsed task number = %d", task);
        debug_print(dbg);
    } else {
        printf("Unrecognized argument: %s\n", argv[1]);
        print_usage();
        return 1;
    }

    /* 3) Read the CSV and YAML data */
    CurricularData cdata[MAX_RECORDS];
    ExtraData edata[MAX_RECORDS];
    const char *csv_filename = "data/a1-data-curricular.csv";
    const char *yaml_filename = "data/a1-data-extracurricular.yaml";

    int c_size = read_csv_file(csv_filename, cdata);
    if (c_size < 0) {
        fprintf(stderr, "Error: Could not read CSV file.\n");
        return 1;
    }
    int e_size = read_yaml_file(yaml_filename, edata);
    if (e_size < 0) {
        fprintf(stderr, "Error: Could not read YAML file.\n");
        return 1;
    }

    printf("Successfully read %d records from %s\n", c_size, csv_filename);
    printf("Successfully read %d records from %s\n", e_size, yaml_filename);

    /* 4) Prepare arrays for merging and for row output */
    static CurricularData merged_c[MAX_RECORDS];
    static ExtraData      merged_e[MAX_RECORDS];
    int merged_size = 0;

    static char row_buffer[MAX_RECORDS][256];
    const char* row_storage[MAX_RECORDS];
    int row_count = 0;

    /* 5) Task-based logic */
    switch (task) {
    case 1: {
        debug_print("Task 1 logic entered: Scores > 90");
        char header[] = "Record_ID,Exam_Score";
        for (int i = 0; i < c_size; i++) {
            if (cdata[i].exam_score > 90) {
                snprintf(row_buffer[row_count], sizeof(row_buffer[row_count]),
                         "%d,%d",
                         cdata[i].record_id,
                         cdata[i].exam_score);
                row_storage[row_count] = row_buffer[row_count];
                row_count++;
            }
        }
        write_header_and_rows(header, row_storage, row_count);
        break;
    }
    case 2: {
        debug_print("Task 2 logic entered: All extracurricular dataset");
        char header[] = "Extracurricular_Activities,Physical_Activity,Record_ID,Sleep_Hours";
        for (int i = 0; i < e_size; i++) {
            snprintf(row_buffer[row_count], sizeof(row_buffer[row_count]),
                     "%s,%d,%d,%d",
                     edata[i].extracurricular_activities,
                     edata[i].physical_activity,
                     edata[i].record_id,
                     edata[i].sleep_hours);
            row_storage[row_count] = row_buffer[row_count];
            row_count++;
        }
        write_header_and_rows(header, row_storage, row_count);
        break;
    }
    case 3: {
        debug_print("Task 3 logic entered: Merge + Exam_Score > 90");
        merged_size = merge_on_record_id(cdata, c_size, edata, e_size, merged_c, merged_e);
        char header[] = "Record_ID,Hours_Studied,Attendance,Tutoring_Sessions,Exam_Score,Extracurricular_Activities,Physical_Activity,Sleep_Hours";
        for (int i = 0; i < merged_size; i++) {
            if (merged_c[i].exam_score > 90) {
                snprintf(row_buffer[row_count], sizeof(row_buffer[row_count]),
                         "%d,%d,%d,%d,%d,%s,%d,%d",
                         merged_c[i].record_id,
                         merged_c[i].hours_studied,
                         merged_c[i].attendance,
                         merged_c[i].tutoring_sessions,
                         merged_c[i].exam_score,
                         merged_e[i].extracurricular_activities,
                         merged_e[i].physical_activity,
                         merged_e[i].sleep_hours);
                row_storage[row_count] = row_buffer[row_count];
                row_count++;
            }
        }
        write_header_and_rows(header, row_storage, row_count);
        break;
    }
    case 4: {
        debug_print("Task 4 logic entered: 100% attendance");
        char header[] = "Record_ID,Exam_Score";
        for (int i = 0; i < c_size; i++) {
            if (cdata[i].attendance == 100) {
                snprintf(row_buffer[row_count], sizeof(row_buffer[row_count]),
                         "%d,%d",
                         cdata[i].record_id,
                         cdata[i].exam_score);
                row_storage[row_count] = row_buffer[row_count];
                row_count++;
            }
        }
        write_header_and_rows(header, row_storage, row_count);
        break;
    }
    case 5: {
        debug_print("Task 5 logic entered: Sleep_Hours >= Hours_Studied");
        merged_size = merge_on_record_id(cdata, c_size, edata, e_size, merged_c, merged_e);
        char header[] = "Record_ID,Exam_Score";
        for (int i = 0; i < merged_size; i++) {
            if (merged_e[i].sleep_hours >= merged_c[i].hours_studied) {
                snprintf(row_buffer[row_count], sizeof(row_buffer[row_count]),
                         "%d,%d",
                         merged_c[i].record_id,
                         merged_c[i].exam_score);
                row_storage[row_count] = row_buffer[row_count];
                row_count++;
            }
        }
        write_header_and_rows(header, row_storage, row_count);
        break;
    }
    case 6: {
            debug_print("Task 6 logic entered: Scores < 60");
            merged_size = merge_on_record_id(cdata, c_size, edata, e_size, merged_c, merged_e);
            char header[] = "Record_ID,Exam_Score,Extracurricular_Activities";
            for (int i = 0; i < merged_size; i++) {
                if (merged_c[i].exam_score < 60) {
                    snprintf(row_buffer[row_count], sizeof(row_buffer[row_count]),
                            "%d,%d,%s",
                            merged_c[i].record_id,
                            merged_c[i].exam_score,
                            merged_e[i].extracurricular_activities);
                    row_storage[row_count] = row_buffer[row_count];
                    row_count++;
                }
            }
            write_header_and_rows(header, row_storage, row_count);
            break;
        }
    default:
        printf("Unrecognized task: %d\n", task);
        print_usage();
        return 1;
    }

    /* 6) Done */
    printf("\nTask %d complete. See output.csv.\n", task);
    debug_print("Exiting main()...");
    return 0;
}
