#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct tnode{
	char nama[100];
	char nomor[100];
	struct tnode* next;
	struct tnode* prev;
} *head = NULL, *tail = NULL;

void inputData(char nama[], char nomor[]){
	struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));
	strcpy(newNode->nama, nama);
	strcpy(newNode->nomor, nomor);
	newNode->next = NULL;
	
	if(head == NULL){
		newNode->prev = NULL;
		head = newNode;
		tail = newNode;
	}else{
		struct tnode* curr = head;
		struct tnode* temp;
		
		while(curr != NULL && strcmp(nama, curr->nama) > 0){
			temp = curr;
			curr = curr->next;
		}
		
		if(temp == NULL){
			newNode->prev = NULL;
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}else{
			newNode->prev = temp;
			newNode->next = curr;
			if(curr != NULL){
				curr->prev = newNode;
			}else{
				tail = newNode;
			}
			temp->next = newNode;
		}
	}
}

void deleteInsert(char nama[]){
	if(head == NULL){
		printf("List is empty, name not found.\n");
		return;
	}
	
	struct tnode* curr = head;
	struct tnode* temp;
	
	while(curr != NULL && strcmp(nama, curr->nama) != 0){
		temp = curr;
		curr = curr->next;
	}
	
	if(curr == NULL){
		printf("Name not found.\n");
		return;
	}
	
	if(temp == NULL){
		head = curr->next;
		if(curr->next != NULL){
			curr->next->prev = NULL;
		}else{
			tail = NULL;
		}
	}else{
		temp->next = curr->next;
		if(curr->next != NULL){
			curr->next->prev = temp;
		}else{
			tail = temp;
		}
	}
	
	free(curr);
	printf("Name deleted successfully.\n");
}

void print(struct tnode* head){
	if(head == NULL){
		printf("List is empty.\n");
		return;
	}
	
	printf("Name\t\tPhone\n");
	puts("======================");
	
	while(head != NULL){
		printf("%s\t\t%s\n", head->nama, head->nomor);
		head = head->next;
	}
	printf("\n");
}

int checknama(const char* nama){
	return (strlen(nama) >= 3 && strlen(nama) <= 15);
}

int angka(const char* nomor){
	while(*nomor){
		if(!isdigit(*nomor)){
			return 0;
		}
		nomor++;
	}
	return 1;
}

void mainMenu(){
	int n;
	char nama[100];
	char nomor[100];
	
	do{
		puts("Student's Phone NUmber List:");
		puts("1. Insert");
		puts("2. Delete");
		puts("3. Display");
		puts("4. Exit");
		printf("Enter your Choice: ");
		scanf("%d", &n);
		
		switch(n){
			case 1:
				printf("Enter name[3-15 characters] : ");
				scanf("%s", nama);
				while(!checknama(nama)){
					printf("Enter name[3-15 characters] : ");
					scanf("%s", nama);
				}
				
				printf("Enter phone number: ");
				scanf("%s", nomor);
				while(!angka(nomor)){
					printf("Enter phone number: ");
					scanf("%s", nomor);
				}
				
				inputData(nama, nomor);
				print(head);
				break;
			case 2:
				printf("Enter name to delete: ");
				scanf("%s", nama);
				deleteInsert(nama);
				print(head);
				break;
				
			case 3:
				print(head);
				break;
				
			case 4:
				printf("Exiting program.\n");
				break;
				
			default:
				printf("Invalid choice, please anter again\n");
		}
	}while(n != 4);
}

int main(){
	mainMenu();
	return 0;
}






