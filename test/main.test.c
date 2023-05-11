#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_HASH    0xFFFF
#define takentime(t) (((double)(clock() - t)) / CLOCKS_PER_SEC)

typedef unsigned long Uint32;
typedef unsigned int  Uint16;

typedef struct HashEntry_t HashEntry;
struct HashEntry_t
{
    Uint32              hashkey;
    char                *rawkey;
    void                *value;
    HashEntry           *next;
};

typedef struct
{
    HashEntry   *entries;
    Uint16      count;
} HashTable;


Uint32 ht_hash(char *);
void ht_insert(char *, void *, HashTable**);
void *ht_get(char *, HashTable *);

typedef struct 
{
    int     a;
    char    *b;
} MyData;

void fill(HashTable**);

int main(int argc, char *argv[])
{
    HashTable *ht = NULL;    
    fill(&ht);
    
    MyData *result = (MyData *)ht_get("b", ht);    
    MyData *failed = (MyData *)ht_get("c", ht);

    if (result != NULL)
    {
        printf("Key: b was found in hash table!\n");
    }
    else
    {
        fprintf(stderr, "Key: b was not found in hash table!\n");
    }

    if (failed == NULL)
    {
        printf("Key: c was not found in hash table :D\n");
    }
    else
    {
        fprintf(stderr, "Key: c was found in hash table D:\n");
    }

    free(ht);

    return 0;
}

Uint32 ht_hash(char *key)
{
    Uint16 byte, crc, mask;
    int i = 0, j;

    crc = 0xFFFFFFFF;
    
    while(key[i] != 0)
    {
        byte = key[i];
        crc ^= byte;
        for (j = 7; j >= 0; j--)
        {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i++;
    }
    return ~crc;
}

void ht_insert(char *key, void *data, HashTable **ht)
{
    clock_t t = clock();

    if (*ht == NULL)
    {
        *ht = (HashTable*)malloc(sizeof(HashTable));
        (*ht)->entries = NULL;
        (*ht)->count = 0;
    }
    
    HashEntry *entry;
    if ((*ht)->count == 0)
    {        
        (*ht)->entries = (HashEntry *)malloc(sizeof(HashEntry));
        entry = (*ht)->entries;
        entry->next = NULL;
    }
    else
    {   
        HashEntry *iter = (*ht)->entries;
        while(iter->next != NULL)
            iter = iter->next;
        entry = (HashEntry *)malloc(sizeof(HashEntry));
        iter->next = entry;        
    }
    
    entry->rawkey = key;
    entry->value = data;
    entry->hashkey = ht_hash(key);    
    (*ht)->count++;    
    
    printf("HT insert taken time: %f\n", takentime(t));
}

void *ht_get(char *rawkey, HashTable *ht) 
{
    clock_t t = clock();

    if (ht == NULL || ht->count == 0)
    {
        printf("HT get taken time: %f\n", takentime(t));
        return NULL;
    }

    Uint32 key = ht_hash(rawkey);
        
    HashEntry *entry = ht->entries;
    do 
    {        
        if (key == entry->hashkey)
        {
            if (strncmp(rawkey, entry->rawkey, strlen(rawkey)) == 0)
            {
                printf("HT get taken time: %f\n", takentime(t));
                return entry->value;
            }
        }

    } while((entry = entry->next) != NULL);

    printf("HT get taken time: %f\n", takentime(t));
    return NULL;
}

void fill(HashTable **ht)
{
    MyData d = {
        .a = 32,
        .b = "example1"
    };
    MyData d2 = {
        .a = 452,
        .b = "example2"
    };

    ht_insert("a", (void*)&d, ht);
    ht_insert("b", (void*)&d2, ht);
}