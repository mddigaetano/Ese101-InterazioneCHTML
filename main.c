#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRLEN 25
#define FNAME_TXT "NamesRoles.txt"
#define FNAME_HTML "Compito.html"

typedef struct s_element{                                                       //definizione di lista per salvare nomi-ruoli
    char name[MAX_STRLEN];
    char role[MAX_STRLEN];
    struct s_element *next;
}element;

void addAtPosition(element **pfirst, char name[], char role[], int position);
void printList(element *first);

int main(int argc, char** argv) {
    FILE *txt, *html;
    element *first = NULL;
    char tempName[MAX_STRLEN];                                                  //verrà utilizzata per memorizzare i dati dal file insieme a tempRole
    char tempRole[MAX_STRLEN];                                                  //verrà utilizzata per memorizzare il ruolo attuale
    
    if(!(txt=fopen(FNAME_TXT,"r")))                                             //controllo validità apertura file || ERROR N°1
        exit(1);
    
    do{
        fscanf(txt,"%[^_]_%[^\n]\n",tempName,tempRole);                         //preleva riga da file
        addAtPosition(&first, tempName, tempRole, 0);                           //aggiunge elemento in testa (posizione 0)
    }while(feof(txt) == 0);
    
    printList(first);
    
    
    
    return (EXIT_SUCCESS);
}

void addAtPosition(element **pfirst, char name[], char role[], int position){
    element **browse=NULL;
    element *temp=NULL;
    
    temp=(element*)malloc(sizeof(element));
    strcpy(temp->name, name);
    strcpy(temp->role, role);
    temp->next=NULL;
    
    browse=pfirst;
    while(position > 0 && (*browse) != NULL){
        browse = &((*browse)->next);
        position--;
    }
    
    temp->next=*browse;
    *browse=temp;
    
    return;
}

void printList(element *first){
    
    while(first != NULL){
        printf("Nome: %s\n",first->name);
        printf("Ruolo: %s\n",first->role);
        first=first->next;
    }
}