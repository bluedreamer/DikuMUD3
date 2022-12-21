/*
 $Author: tperry $
 $RCSfile: trie.h,v $
 $Date: 2001/04/29 03:46:07 $
 $Revision: 2.1 $
 */
#pragma once

#include "essential.h"

class trie_type;
struct trie_entry
{
    char c;
    trie_type *t;
};

struct trie_type
{
    void *data;
    uint8_t size;
    trie_entry *nexts;
};

void *search_trie(const char *s, trie_type *t);
void set_triedata(const char *s, trie_type *t, void *p, bool verbose);
trie_type *add_trienode(const char *s, trie_type *t);
void free_trie(trie_type *t, void (*free_data)(void *));
bool del_trie(char *s, trie_type **t, void (*)(void *));
void qsort_triedata(trie_type *t);
