#ifndef _STRLL_H_
#define _STRLL_H_

struct _str_node{
    char *str; //the value that will be stored
    struct _str_node *next; //pointer to next quentry struct or tail
    struct _str_node *prev; //pointer to previouse quentry struct or head
};

typedef struct _str_node strll; //typical handle for head of strll
typedef struct _str_node strll_entry;
typedef struct _str_node strll_tail;

#define ishead(ll) ll->prev ? 0 : 1
//#define istail(ll) ll->next ? 0 : 1


strll* strll_new();
void strll_free_entry(strll_entry*);
void strll_free(strll*);
strll_entry* strll_new_entry(char*); //allocates a new strll_entry struct containing char
//strll_tail* strll_get_tail(strll*);
//strll* strll_get_head(strll*);
int strll_has_entry(strll*, char*);
int strll_isempty(strll_entry*);


void strll_insert(strll*, char*); //inserts at the front of the list
int strll_delete(strll*, char*); //delete element containing char* if it exists
int strll_isempty(strll*);

//queue interface
//int strll_enqueue(strll*, char*); //insert at the back of the list
//int strll_dequeue(strll_entry*); //remove from the front of the list

void strll_print(strll_entry *q);

#endif //_STRLL_H_
