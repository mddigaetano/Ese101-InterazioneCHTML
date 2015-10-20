#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRLEN 25                                                           //lunghezza massima stringhe;
#define FNAME_TXT "NamesRoles.txt"                                              //nome file txt;
#define FNAME_HTML "Compito.html"                                               //nome file html;
#define FNAME_JS "script.js"                                                    //nome file javascript;

typedef struct s_element{                                                       //definizione di lista per salvare nomi-ruoli;
    char name[MAX_STRLEN+1];
    char role[MAX_STRLEN+1];
    struct s_element *next;                                                     //puntatore al prossimo elemento della lista;
}element;

void addAtPosition(element **pfirst, char name[], char role[], int position);   //prototipo funzione di aggiunta, in qualsiasi posizione, di un elemento in una lista;
void emptyList(element *first);                                                 //prototipo deallocazione lista;

int main(int argc, char** argv) {
    FILE *txt, *html, *js;                                                           //puntatori per i file da aprire;
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
    
    if(fclose(txt))                                                             //controllo validità chiusura file || ERROR N°2;
        exit(2);
    
    if(!(html = fopen(FNAME_HTML,"w")))                                         //controllo validità apertura file || ERROR N°3;
        exit(3);
    
    fprintf(html,"<!DOCTYPE html>\n");                                          //inizio stampa html;
    fprintf(html,"<html>\n\t<head>\n\t\t<title>Compito Informatica</title>\n\t\t<script src=%s></script>\n\t</head>\n",FNAME_JS);
    fprintf(html,"\t<body>\n\t\t<select id=\"tendina\" autofocus onchange=\"printNames()\">\n");
 
    strcpy(tempRole, first->role);                                              //inizializzazione prima option;
    fprintf(html,"\t\t\t<option>%s</option>\n", tempRole);
    
    for(browse=first->next; browse!=NULL; browse = browse->next){
        if(strcmp(tempRole, browse->role)){
            strcpy(tempRole,browse->role);
            fprintf(html,"\t\t\t<option>%s</option>\n", tempRole);
        }
    }
    
    fprintf(html,"\t\t</select>\n");                                            //fine select;
    fprintf(html,"\t\t<div id=\"nameList\"></div>\n");                          //div dove verranno stampati i nomi;
    fprintf(html,"\t</body>\n</html>");                                         //fine pagina html;
    
    if(fclose(html))                                                            //controllo validità chiusura file || ERROR N°4;
        exit(4);
    
    if(!(js = fopen(FNAME_JS,"w")))                                           //controllo validità apertura file || ERROR N°5;
        exit(5);
    
    fprintf(js,"function printNames(){\n");
    
    strcpy(tempRole, first->role);                                              
    fprintf(js,"\tvar %s = '[\"%s\"", tempRole, first->name);
    for(browse=first->next; browse!=NULL; browse = browse->next){
        if(strcmp(tempRole, browse->role)){
            fprintf(js,"]';\n");
            strcpy(tempRole,browse->role);
            fprintf(js,"\tvar %s = '[\"%s\"", tempRole, browse->name);
        }
        else{
            fprintf(js ,", \"%s\"", browse->name);
        }
    }
    fprintf(js,"]';\n");
    
    fprintf(js,"    var e = document.getElementById(\"tendina\");\n"
            "    var array = JSON.parse(eval(e.options[e.selectedIndex].text));\n");
    fprintf(js,"    array = array.sort();\n");
    fprintf(js,"    i=0;\n"
            "   document.getElementById('nameList').innerHTML = \"\";\n"
            "   for(i=0;i<array.length;i++){\n"
            "       document.getElementById('nameList').innerHTML += array[i]+\"<br>\";\n"
            "   }\n"
            "}\n");
    
    if(fclose(js))                                                              //controllo validità chiusura file || ERROR N°6;
        exit(6);
    
    emptyList(first);                                                           //deallocazione lista;
    
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

void emptyList(element *first){
    element *temp=NULL;
    
    while(first != NULL){
        temp=first->next;
        free(first);
        first=temp;
    }
    
    return;
}