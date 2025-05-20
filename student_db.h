#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_NAME 50
#define MAX_EMAIL 50
#define MAX_ID 20
#define MAX_CONTACT 15
#define MAX_DOB 11
#define DB_FILE "student_database.dat"

typedef struct
{
    char student_id[MAX_ID];
    char name[MAX_NAME];
    char dob[MAX_DOB];
    float matric_percent;
    float inter_percent;
    float grad_percent;
    char contact[MAX_CONTACT];
    char email[MAX_EMAIL];
}Student;

typedef struct Node
{
    Student data;
    struct Node* next;
}Node;

// Function prototypes
void add_record(Node** head);
void print_records(Node* head);
void save_database(Node* head);
void delete_record(Node** head);
void edit_record(Node* head);
void find_student(Node* head);
void reverse_display(Node* head);
void load_database(Node** head);
int is_id_unique(Node* head, const char* id);
void free_list(Node* head);
void display_menu();
char* generate_student_id(const char* name, int seq);
void to_uppercase(char* str);

#endif
