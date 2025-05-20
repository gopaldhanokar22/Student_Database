#include "student_db.h"

int main()
{
	Node* head=NULL;
	char choice;

	// Load existing database
	load_database(&head);

	do
	{
		display_menu();
		printf("Enter your choice: ");
		scanf(" %c", &choice);

		switch(tolower(choice))
		{
			case 'a':
				add_record(&head);
				break;
			case 'p':
				print_records(head);
				break;
			case 's':
				save_database(head);
				break;
			case 'd':
				delete_record(&head);
				break;
			case 'e':
				edit_record(head);
				break;
			case 'f':
				find_student(head);
				break;
			case 'r':
				reverse_display(head);
				break;
			case 'q':
				printf("Exiting program...\n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");
		}
	}while(tolower(choice)!='q');

	// Free memory before exiting
	free_list(head);

	return 0;
}
