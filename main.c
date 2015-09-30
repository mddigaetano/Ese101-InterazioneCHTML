#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRLEN 25                                                           //lunghezza massima stringhe;
#define FNAME_TXT "NamesRoles.txt"                                              //nome file txt;
#define FNAME_HTML "Compito.html"                                               //nome file html;

typedef struct s_element{                                                       //definizione di lista per salvare nomi-ruoli;
    char name[MAX_STRLEN+1];
    char role[MAX_STRLEN+1];
    struct s_element *next;                                                     //puntatore al prossimo elemento della lista;
}element;

void addAtPosition(element **pfirst, char name[], char role[], int position);   //prototipo funzione di aggiunta, in qualsiasi posizione, di un elemento in una lista;
void printList(element *first);                                                 //stampa lista || SOLO DEBUG!!!

int main(int argc, char** argv) {
    FILE *txt, *html;                                                           //puntatori per i file da aprire;
    element *first = NULL, *browse = NULL;
    int ctrl = 1, i;
    char tempName[MAX_STRLEN+1];                                                //verrà utilizzata per memorizzare i dati dal file insieme a tempRole;
    char tempRole[MAX_STRLEN+1];                                                //verrà utilizzata per memorizzare il ruolo attuale;
    
    if(!(txt=fopen(FNAME_TXT,"r")))                                             //controllo validità apertura file || ERROR N°1;
        exit(1);
    
    fscanf(txt,"%[^_]_%[^\n]\n",tempName,tempRole);                             //inizializzazione lista;
    addAtPosition(&first, tempName, tempRole, 0);                               //aggiunta in testa;
    while(feof(txt) == 0){
        fscanf(txt,"%[^_]_%[^\n]\n",tempName,tempRole);                         //prelevo di stringhe da file;
        
        browse = first;                                                         //inizializzazione parametri
        i=0;                                                                    //e flag per ciclo;
        ctrl=1;
        while(browse->next && ctrl){                                            //controllo se ultimo elemento o raggiunta posizione;
            if(strcmp(tempRole,browse->role)<=0)
                ctrl = 0;                                                       //flag di uscita ciclo;
            else{
                browse=browse->next;                                            //preparazione iterazione successiva;
                i++;
            }
        }
        
        addAtPosition(&first, tempName, tempRole, i);                           //aggiunta in lista in modo ordinato;
    }

    printList(first);                                                           //stampa lista || SOLO DEBUG!!!
    
    if(fclose(txt))                                                             //controllo validità chiusura file || ERROR N°2;
        exit(2);
    
    return (EXIT_SUCCESS);
}

void addAtPosition(element **pfirst, char name[], char role[], int position){   //funzione di aggiunta, in qualsiasi posizione, di un elemento in una lista;
    element **browse=NULL;                                                      //puntatore al puntatore al primo elemento della lista (utile per modificare la testa anche nei programmi superiori);
    element *temp=NULL;
    
    temp=(element*)malloc(sizeof(element));                                     //allocazione nuovo elemento;
    strcpy(temp->name, name);                                                   //inizializzazione campi;
    strcpy(temp->role, role);
    temp->next=NULL;
    
    browse=pfirst;
    while(position > 0 && (*browse) != NULL){                                   //iterazione per idividuare posizione di aggiunta;
        browse = &((*browse)->next);
        position--;
    }
    
    temp->next=*browse;
    *browse=temp;
    
    return;
}

void printList(element *first){                                                 //stampa lista || SOLO DEBUG!!!
    
    while(first != NULL){
        printf("Nome: %s\n",first->name);
        printf("Ruolo: %s\n",first->role);
        first=first->next;
    }
}