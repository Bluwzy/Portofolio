#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int i = 1;


struct Employee
{
	int Id;
	char first[50];
	char last[50];
	int DOB;
	int number;
	int salary;
	struct Employee* next;
}*head;


void insert();
void antiduplication(char *first, char *last);
void Display();
void DisplayMenu();
void DisplayList();
void count();
void Delete();
void Search();
void Descending();
void Ascending();

void main() {
	char opt, sort;
	printf("\t\t\t\t\t\t\t\tEmployee Management System\n\n\n\n");
	do {
		DisplayMenu();
		scanf_s("  %c", &opt);
		switch (opt) {
		case '1':
			insert();
			break;
		case '2':
			Delete();
			break;
		case '3':
			Search();
			break;
		case '4':
			printf("1 - Ascending Sorting\n2 - Descending Sorting\n");
			scanf_s("  %c", &sort);
			switch (sort) {
			case '1':
				Ascending();
				break;
			case '2':
				Descending();
				break;
			}
			break;
		case '5':
			DisplayList();
			Display();
			count();
			break;
		default:
			printf("Invalid option\n");
			break;
		}
	} while (opt != '6');
}

void insert() {
	struct Employee* newEmployee = (struct Employee*) malloc(sizeof(struct Employee));

	printf("Enter new employee first name:");
	scanf_s("%s", &newEmployee->first, sizeof(newEmployee->first));

	printf("Enter new employee last name:");
	scanf_s("%s", &newEmployee->last, sizeof(newEmployee->last));

	antiduplication(newEmployee->first, newEmployee->last);

	printf("Enter new employee year of birth: ");
	scanf_s("%d", &newEmployee->DOB);

	printf("Enter new employee phone number: ");
	scanf_s("%d", &newEmployee->number);

	printf("Enter new employee salary: ");
	scanf_s("%d", &newEmployee->salary);

	newEmployee->Id = i;

	newEmployee->next = NULL;

	if (head == NULL) {
		head = newEmployee;
	}
	else {

		struct Employee* end;
		end = head;

		while (end->next != NULL) {
			end = end->next;
		}
		end->next = newEmployee;

	}
	i++;
	printf("New Employee Record Added Succesfully");

}

void Delete() {

	struct Employee* delet, *prev;
	delet = head;
	prev = NULL;

	char first[50];
	char last[50];

	if (head == NULL) {
		printf("list is empty\n");
	}
	else {
		printf("Enter Employee's First name to delete :");
		scanf_s("%s", first, _countof(first));
		printf("Enter Employee's Last name to delete :");
		scanf_s("%s", last, _countof(last));
		if (strcmp(delet->first, first) == 0 && strcmp(delet->last, last) == 0) {
			delet = head;
			head = head->next;
			free(delet);
			printf("%s %s was deleted successfully\n", first, last);
		}
		else {
			while (delet != NULL) {
				if (strcmp(delet->first, first) == 0 && strcmp(delet->last, last) == 0) {
					break;
				}
				else {
					prev = delet;
					delet = delet->next;

				}
			}

			if (delet != NULL) {
				prev->next = delet->next;
				free(delet);
				printf("%s %s was deleted successfully\n", first, last);
			}
			else {
				printf("%s %s was not found\n", first, last);
			}


		}

	}

}

void Search() {
	struct Employee* temp;
	temp = head;

	char first[50];
	char last[50];

	if (head == NULL) {
		printf("list is empty\n");
	}
	else {
		printf("Enter Employee's First name :");
		scanf_s("%s", first, sizeof(first));
		printf("Enter Employee's Last name  :");
		scanf_s("%s", last, sizeof(last));
		while (temp != NULL) {
			if (strcmp(temp->first, first) == 0 && strcmp(temp->last, last) == 0) {
				DisplayList();
				printf("\n%d\t%s\t\t%s\t\t%d\t\t0%d\t\t%d\n", temp->Id, temp->first, temp->last, temp->DOB, temp->number, temp->salary);
				break;
			}
			else {

				temp = temp->next;
			}
		}
		if (temp == NULL) {
			printf("%s %s was not found\n", first, last);
		}
	}
}

void swap(struct Employee*a, struct Employee*b) {

	char first[50], last[50];
	int id = a->Id, dob = a->DOB, number = a->number, salary = a->salary;
	strcpy_s(first, sizeof(first), a->first);
	strcpy_s(last, sizeof(last), a->last);
	strcpy_s(a->first, sizeof(a->first), b->first); strcpy_s(a->last, sizeof(a->last), b->last); a->Id = b->Id; a->DOB = b->DOB; a->number = b->number; a->salary = b->salary;
	strcpy_s(b->first, sizeof(b->first), first); strcpy_s(b->last, sizeof(b->last), last); b->Id = id; b->DOB = dob; b->number = number; b->salary = salary;

}


void Ascending() {

	struct Employee* prev, *current, *temp;
	temp = head;
	prev = NULL;
	current = head;

	DisplayList();

	if (head == NULL) {
		printf("list is empty\n");
	}
	else {

		for (; current->next != NULL; current = current->next) {
			for (prev = current->next; prev != NULL; prev = prev->next) {
				if (current->Id > prev->Id) {
					swap(current, prev);
				}
			}
		}


		Display();
	}
}

void Descending() {

	struct Employee* prev, *current, *temp;
	temp = head;
	prev = NULL;
	current = head;
	DisplayList();

	if (head == NULL) {
		printf("list is empty\n");
	}
	else {

		for (; current->next != NULL; current = current->next) {
			for (prev = current->next; prev != NULL; prev = prev->next) {
				if (current->Id < prev->Id) {
					swap(current, prev);
				}
			}
		}

		Display();
	}
}

void Display() {
	struct Employee* temp;
	temp = head;

	if (head != NULL) {
		while (temp != NULL) {
			printf("\n%d\t%s\t\t%s\t\t%d\t\t0%d\t\t%d\n", temp->Id, temp->first, temp->last, temp->DOB, temp->number, temp->salary);
			temp = temp->next;
		}
	}
}

void DisplayMenu() {
	printf("\n ******************************************\n");
	printf("\n *  System operations:                    *\n");
	printf("\n *    1. Add New Record                   *\n");
	printf("\n *    2. Delete Record                    *\n");
	printf("\n *    3. Search Record                    *\n");
	printf("\n *    4. Sort Records                     *\n");
	printf("\n *    5. Display All Records              *\n");
	printf("\n *    6. Exit                             *\n");
	printf("\n ******************************************\n");
	printf("\n Choose an option [1-6] : ");
}

void DisplayList() {
	printf("ID\tFirst Name\tLast Name\tYear Of Birth\tPhone Number\tSalary\n\n");
}

void count() {
	struct Employee *temp;
	temp = head;
	int c = 0;

	while (temp != NULL) {
		temp = temp->next;
		c++;
	}
	printf("\n\nThere are %d records in the System", c);
}

void antiduplication(char *first, char *last) {
	struct Employee* temp;
	temp = head;

	while (temp != NULL) {
		if (strcmp(temp->first, first) != 0 || strcmp(temp->last, last) != 0) {
			temp = temp->next;

		}
		else {
			printf("The name already exists\n\n");
			main();

		}
	}
}