#include "student_db.h"

void add_record(Node** head)
{
	Node* new_node=(Node*)malloc(sizeof(Node));
	if(!new_node)
	{
		printf("Memory allocation failed.\n");
		return;
	}

	printf("\n--- Add New Student Record ---\n");

	// Generate student ID
	char name[MAX_NAME];
	int seq;
	printf("Enter student first name: ");
	scanf("%s", name);
	printf("Enter sequence number: ");
	scanf("%d", &seq);

	char* generated_id=generate_student_id(name, seq);
	strcpy(new_node->data.student_id, generated_id);
	free(generated_id);

	printf("Generated Student ID: %s\n", new_node->data.student_id);

	// Check if ID already exists
	if(!is_id_unique(*head, new_node->data.student_id))
	{
		printf("Error: Student ID already exists.\n");
		free(new_node);
		return;
	}

	printf("Enter full name: ");
	scanf(" %[^\n]s", new_node->data.name);
	printf("Enter date of birth (DD-MM-YYYY): ");
	scanf("%s", new_node->data.dob);
	printf("Enter matriculation percentage: ");
	scanf("%f", &new_node->data.matric_percent);
	printf("Enter intermediate/diploma percentage: ");
	scanf("%f", &new_node->data.inter_percent);
	printf("Enter graduation percentage: ");
	scanf("%f", &new_node->data.grad_percent);
	printf("Enter contact number: ");
	scanf("%s", new_node->data.contact);
	printf("Enter email id: ");
	scanf("%s", new_node->data.email);

	// Add to linked list
	new_node->next=*head;
	*head=new_node;

	printf("Record added successfully.\n");
}

void print_records(Node* head)
{
	printf("\n--- Student Records ---\n");
	if(!head)
	{
		printf("Database is empty.\n");
		return;
	}

	Node* current=head;
	int count=1;
	while(current)
	{
		printf("\nRecord #%d\n", count++);
		printf("Student ID: %s\n", current->data.student_id);
		printf("Name: %s\n", current->data.name);
		printf("Date of Birth: %s\n", current->data.dob);
		printf("Matriculation Percentage: %.2f\n", current->data.matric_percent);
		printf("Intermediate Percentage: %.2f\n", current->data.inter_percent);
		printf("Graduation Percentage: %.2f\n", current->data.grad_percent);
		printf("Contact: %s\n", current->data.contact);
		printf("Email: %s\n", current->data.email);
		current=current->next;
	}
}

void save_database(Node* head)
{
	FILE* file=fopen(DB_FILE, "wb");
	if(!file)
	{
		printf("Error opening file for writing.\n");
		return;
	}

	Node* current=head;
	while(current)
	{
		fwrite(&current->data, sizeof(Student), 1, file);
		current=current->next;
	}

	fclose(file);
	printf("Database saved successfully to %s\n", DB_FILE);
}

void delete_record(Node** head)
{
	if(!*head)
	{
		printf("Database is empty.\n");
		return;
	}

	char id[MAX_ID];
	printf("Enter Student ID to delete: ");
	scanf("%s", id);

	Node *current=*head, *prev=NULL;

	while(current)
	{
		if(strcmp(current->data.student_id, id)==0)
		{
			if(prev)
			{
				prev->next=current->next;
			} 
			else 
			{
				*head=current->next;
			}
			free(current);
			printf("Record deleted successfully.\n");
			return;
		}
		prev=current;
		current=current->next;
	}

	printf("Student ID not found.\n");
}

void edit_record(Node* head)
{
	if(!head)
       	{
		printf("Database is empty.\n");
		return;
	}

	char id[MAX_ID];
	printf("Enter Student ID to edit: ");
	scanf("%s", id);

	Node* current=head;
	while(current)
	{
		if(strcmp(current->data.student_id, id)==0)
	       	{
			int choice;
			printf("\n--- Edit Menu ---\n");
			printf("1. Edit name\n");
			printf("2. Edit date of birth\n");
			printf("3. Edit percentages\n");
			printf("4. Edit contact\n");
			printf("5. Edit email id\n");
			printf("Enter your choice: ");
			scanf("%d", &choice);

			switch(choice) {
				case 1:
					printf("Enter new name: ");
					scanf(" %[^\n]s", current->data.name);
					break;
				case 2:
					printf("Enter new date of birth (DD-MM-YYYY): ");
					scanf("%s", current->data.dob);
					break;
				case 3:
					printf("Enter new matriculation percentage: ");
					scanf("%f", &current->data.matric_percent);
					printf("Enter new intermediate percentage: ");
					scanf("%f", &current->data.inter_percent);
					printf("Enter new graduation percentage: ");
					scanf("%f", &current->data.grad_percent);
					break;
				case 4:
					printf("Enter new contact number: ");
					scanf("%s", current->data.contact);
					break;
				case 5:
					printf("Enter new email id: ");
					scanf("%s", current->data.email);
					break;
				default:
					printf("Invalid choice.\n");
			}
			printf("Record updated successfully.\n");
			return;
		}
		current=current->next;
	}

	printf("Student ID not found.\n");
}

void find_student(Node* head)
{
	if(!head)
       	{
		printf("Database is empty.\n");
		return;
	}

	char search_term[MAX_NAME];
	printf("Enter student name or ID to search: ");
	scanf(" %[^\n]s", search_term);

	Node* current=head;
	int found=0;

	while(current)
	{
		if(strstr(current->data.name, search_term) || strstr(current->data.student_id, search_term))
	       	{
			printf("\nFound Record:\n");
			printf("Student ID: %s\n", current->data.student_id);
			printf("Name: %s\n", current->data.name);
			printf("Date of Birth: %s\n", current->data.dob);
			printf("Matriculation Percentage: %.2f\n", current->data.matric_percent);
			printf("Intermediate Percentage: %.2f\n", current->data.inter_percent);
			printf("Graduation Percentage: %.2f\n", current->data.grad_percent);
			printf("Contact: %s\n", current->data.contact);
			printf("Email: %s\n", current->data.email);
			found=1;
		}
		current=current->next;
	}

	if(!found)
	{
		printf("No matching records found.\n");
	}
}

void reverse_display(Node* head)
{
	if(!head)
	{
		printf("Database is empty.\n");
		return;
	}

	// Count number of nodes
	int count=0;
	Node* current=head;
	while(current)
	{
		count++;
		current=current->next;
	}

	// Create array of pointers
	Student** arr=(Student**)malloc(count*sizeof(Student*));
	if(!arr)
	{
		printf("Memory allocation failed.\n");
		return;
	}

	// Fill array
	current=head;
	for(int i=0; i<count; i++)
	{
		arr[i]=&current->data;
		current=current->next;
	}

	// Print in reverse
	printf("\n--- Records in Reverse Order ---\n");
	for(int i=count-1; i>=0; i--)
       	{
		printf("\nRecord #%d\n", count-i);
		printf("Student ID: %s\n", arr[i]->student_id);
		printf("Name: %s\n", arr[i]->name);
		printf("Date of Birth: %s\n", arr[i]->dob);
		printf("Matriculation Percentage: %.2f\n", arr[i]->matric_percent);
		printf("Intermediate Percentage: %.2f\n", arr[i]->inter_percent);
		printf("Graduation Percentage: %.2f\n", arr[i]->grad_percent);
		printf("Contact: %s\n", arr[i]->contact);
		printf("Email: %s\n", arr[i]->email);
	}

	free(arr);
}

void load_database(Node** head)
{
	FILE* file=fopen(DB_FILE, "rb");
	if(!file)
	{
		return; // File doesn't exist yet
	}

	Student temp;
	while(fread(&temp, sizeof(Student), 1, file)==1)
	{
		Node* new_node=(Node*)malloc(sizeof(Node));
		if(!new_node)
		{
			printf("Memory allocation failed while loading database.\n");
			fclose(file);
			return;
		}

		new_node->data=temp;
		new_node->next=*head;
		*head=new_node;
	}

	fclose(file);
}

int is_id_unique(Node* head, const char* id)
{
	Node* current=head;
	while(current)
	{
		if(strcmp(current->data.student_id, id)==0)
		{
			return 0;
		}
		current=current->next;
	}
	return 1;
}

void free_list(Node* head)
{
	Node* current=head;
	while(current)
	{
		Node* next=current->next;
		free(current);
		current=next;
	}
}

void display_menu()
{
	printf("\n------------------MENU--------------------------\n");
	printf("a/A  : Add a new student record\n");
	printf("p/P  : Print the records from database\n");
	printf("s/S  : Save the database in a file\n");
	printf("d/D  : Delete a record\n");
	printf("e/E  : Edit a record\n");
	printf("f/F  : Find a student\n");
	printf("r/R  : Reverse the records of current display\n");
	printf("q/Q  : Quit from app\n");
}

char* generate_student_id(const char* name, int seq)
{
	char* id=(char*)malloc(MAX_ID * sizeof(char));
	if (!id) return NULL;

	// Format: V24HE2A1 (Vector2024HyderabadEmbedded Seq7Akash1)
	snprintf(id, MAX_ID, "V24HE%d%c%d", seq, toupper(name[0]), 1);
	return id;
}

void to_uppercase(char* str)
{
	for(int i=0; str[i]; i++) 
	{
		str[i]=toupper(str[i]);
	}
}
