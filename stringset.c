//
// Created by Hasan Yusuf Ahmed on 11/19/17.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stringset.h"
#include "strll.h"

#define STRSET_DEFAULT_INIT_SIZE 100
#define STRSET_DEFAULT_LOAD_FACTOR 0.75f

stringset* stringset_new(unsigned int initial_size, float load_factor){
    stringset *str_set = (stringset*) malloc(sizeof(stringset)); //allocate the pointer for the whole string set
    str_set->num_buckets = initial_size ? initial_size : STRSET_DEFAULT_INIT_SIZE; //if the initial size is 0, then make it 100

    str_set->strll_array = (strll**)malloc((sizeof(strll*) * str_set->num_buckets)); // allocate the pointer for the node_array
    str_set->load_factor = (load_factor <= 0) ? STRSET_DEFAULT_LOAD_FACTOR : load_factor;
    str_set->num_elements = 0;
    unsigned int i = 0;
    for (i = 0; i < str_set->num_buckets; i++) {
        str_set->strll_array[i] = strll_new(); //intilize all the linked lists
    }

    return str_set;
}

void stringset_free(stringset **str_set){
    int i = 0;
    for (i = 0; i < (*str_set)->num_buckets; i++){
        strll_free((*str_set)->strll_array[i]);
    }
    free((*str_set)->strll_array);
    free(*str_set);
}

// int stringset_check(stringset *str_set, const char *str) {
//     unsigned long hashcode = hash_code(str_set, str);
//     node *tmp = str_set->node_array[hashcode];
//     while (tmp) {
//         if (strcmp(tmp->string, str) == 0)
//             return 1;
//         tmp = tmp->next;
//     }
//     return 0;
// }
// float stringset_load_value(stringset *str_set){
//     return str_set->load_factor * (float)str_set->node_array_length;
// }

void stringset_add(stringset **str_set, char *str) {

    unsigned long hashcode = hash_code(str_set, str);
    strll *ll = (*str_set)->strll_array[hashcode];
    strll_insert(ll, str);

}

int stringset_contains(stringset **str_set, char *str) {
    unsigned long hashcode = hash_code(str_set, str);
    strll *ll = (*str_set)->strll_array[hashcode];
    return strll_has_entry(ll, str);
}



// int stringset_remove(stringset *str_set, const char *str) {
//     unsigned long hashcode = hash_code(str_set, str) % str_set->node_array_length;
//     node *tmp = str_set->node_array[hashcode];
//     node *prev = NULL;
//     while (tmp) {
//         if(strcmp(tmp->string, str) == 0) {
//             if (prev){
//                 str_set->node_array[hashcode] = tmp->next;
//                 node_free(tmp);
//                 str_set->num_elements--;
//                 return 1;
//             }

//             list_remove_node(prev, tmp, str);
//             str_set->num_elements--;
//             return 1;
//         }
//         prev = tmp;
//         tmp = tmp->next;
//     }
//     return 0; // no such element existed, and hence was not removed
// }
// //int stringset_deepcopy(stringset *dest, stringset *src) {
// //    if (dest->node_array_length <= src->node_array_length)
// //        return 0;
// //
// //    return 0; //delete this
// //}

// /**
//  * Utility that copies one stringset's pointers into another one
//  * *NOTE* This does not actually copy the string set's elements, just pointers to them,
//  * use stringset_deepcopy if you want to actually copy the elements
//  * @param dest pointer to the string set that we are going to copy into
//  * @param src pointer to string set we are copying
//  * @return 0 if the dest string set's size is smaller than the src's, 1 otherwise
//  */
// //int stringset_copy(stringset *dest, stringset *src) {
// //    if (dest->node_array_length < src->node_array_length)
// //        return 0;
// //    int i;
// //    for (i = 0; i < src->node_array_length; i++){
// //        dest->node_array[i] = node_new_ptr();
// //        dest->node_array[i] = src->node_array[i];
// //    }
// //    dest->num_elements = src->num_elements;
// //    return 1;
// //}

// /**
//  * Doubles the size of the stringset and rehashes all of the elements inside it to fit the new size
//  * @param str_set The string set to rehash
//  */
// void stringset_rehash(stringset *str_set) {
//     puts("rehashing");
//     unsigned int num_elements = str_set->num_elements;
//     stringset *new_str_set = stringset_new(str_set->node_array_length * 2,
//                                            str_set->load_factor); //stringset double the size of original
//     int i;
//     for (i = 0; i < str_set->node_array_length; i++){
//         node *tmp = str_set->node_array[i];
//         while (tmp) { //loop as long as tmp->next isn't NULL
//             unsigned long new_hash = hash_code(new_str_set, tmp->string); // get the new hash according to new size
//             //check to see if the new stringset's node_array entry new_hash is NULL
//             node *next = tmp->next; //save tmp's next because we are going to reassign the pointer
//             if (new_str_set->node_array[new_hash]) { //case that it is NOT NULL
//                 node_list_insert_before(tmp, new_str_set->node_array[new_hash]); //we want it to go before the node thats already there
//             } else { // case that that node_array entry IS NULL
//                 new_str_set->node_array[new_hash] = tmp;
//                 tmp->next = NULL; //null because we know that this is the first in the list
//             }
//             tmp = next;
//         }
//     }
//     str_set->num_elements = num_elements;
//     str_set->node_array_length = new_str_set->node_array_length;
//     free(str_set->node_array);
//     str_set->node_array = new_str_set->node_array;
//     free(new_str_set);
// }

unsigned long hash_code(stringset **str_set, const char *str) { /* copied djb2 hashing algorithm */
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % (*str_set)->num_buckets;
}