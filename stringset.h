//
// Created by Hasan Yusuf Ahmed on 11/19/17.
//

#ifndef STRINGSET_STRINGSET_H
#define STRINGSET_STRINGSET_H

#include "strll.h"


#define STRSET_DEFAULT 0

struct string_set{
    unsigned int num_buckets; //the number of linked lists allocated
    unsigned int num_elements; //the actual number of elements allocated
    strll **strll_array; //array of nodes
    float load_factor;
};
typedef struct string_set stringset;
stringset* stringset_new(unsigned int initial_size, float load_factor);
void stringset_free(stringset **str_set);
void stringset_add(stringset **str_set, char *str);
int stringset_remove(stringset **str_set, char* string);
int stringset_contains(stringset **str_set, char *str);
void stringset_rehash(stringset **str_set);
float stringset_load_value(stringset **str_set);
//int stringset_copy(stringset *dest, stringset *src);
//int stringset_deepcopy(stringset *dest, stringset *src);
void stringset_free_lite(stringset **str_set);



unsigned long hash_code(stringset **str_set, const char *str);

#endif //STRINGSET_STRINGSET_H
