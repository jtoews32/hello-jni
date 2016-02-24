#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include "JNISample.h"
#include "hash.h"

void *allocList[MAX_BUFFER];
int indx = 0;

void *allocmem(int sizeOf) {
	void *pointer = malloc(sizeOf);

	allocList[indx++] = pointer;
//	printf("allocating %u \n", (unsigned int) pointer);
	return pointer;
}

void freemem() {
	int i;

	for(i =0; i < indx; i++) {
//		printf("freeing %u \n", (unsigned int) allocList[i]);
		free(allocList[i]);
	}
}

int hash(char key, int size) {
	int retval;
	unsigned int hashval = 0;

	hashval = (hashval << 5) + key;
//	for (;key[0];key++) {
//		hashval = (hashval << 5) + key[0];
//	}
	retval = hashval % size;

	return retval;
}

int length(char S[]) {
	int i = 0;

	while(S[i] != '\0') {
		++i;
	}

	return i;
}

inline int minimum(int x, int y) {
	if(x<y) return x;
	else return y;
}

void hash_insert(HashTable h, char key, int data) {
	int hashval = hash(key, h->size);

	h->table[hashval] = hash_create_element(data, key, h->table[hashval]);
}

int hash_find(HashTable h, char key) {
	int hashval = hash(key,h->size);
	TableElement tmp = h->table[hashval];

	while(tmp != NULL) {
		if(key == tmp->key)
			return tmp->data;
		tmp = tmp->next;
	}

	return -1;
}

void hash_delete(HashTable h, char key) {
	int index;
	TableElement tmp;

	index = hash(key,h->size);
/*
	if (h->table[index] != NULL) {
		if (strcmp(h->table[index]->key,key) == 0) {
			h->table[index] = h->table[index]->next;   // * Memory Leak
		} else {
			for(tmp = h->table[index]; tmp->next != NULL &&
			strcmp(tmp->next->key,key) != 0; tmp = tmp -> next);
			if (tmp->next)
				tmp->next = tmp->next->next;
		}
	}*/
}

HashTable hash_create_table(int size) {
	int i;
	HashTable retval  = (HashTable) allocmem(sizeof(*retval));

	retval->size = size;
	retval->table = (TableElement *) allocmem(size * sizeof(TableElement *));

	for (i=0; i<size; i++)
		retval->table[i] = NULL;

	return retval;
}

TableElement hash_create_element(int data, char key, TableElement next) {
	TableElement retval = (TableElement) allocmem(sizeof(*retval));

	retval->data = data;
	retval->key = key;
	retval->next = next;

	return retval;
}

int hash_calculate_length(char P[]) {
	int i = 0,
		j = 0,
		count = 0,
		found = FALSE;

	while(P[i] != '\0') {
		found = FALSE;
		j = i+1;
		while(P[j] != '\0') {
			if(P[i] == P[j]) {
				found = TRUE;
				break;
			}
			++j;
		}
		if(found==FALSE)
			++count;

		++i;
	}

	return count;
}

HashTable hash_create_last_lookup_table(char P[]) {
	int i = 0,
		size = hash_calculate_length(P);
	HashTable hashTable = hash_create_table(size);

	while(P[i] != '\0') {
		char key = P[i];
		hash_insert( hashTable, key, i);
		++i;
	}

	return hashTable;
}

int search(char T[], char P[], HashTable table) {
	int n = length(T),
	    m = length(P),
	    i = m -1,
	    j = m -1;

	while(i <= n -1) {
		if( P[j] == T[i] ) {
			if(j==0) {
				return i;
			} else {
				i = i - 1;
				j = j - 1;
			}
		} else {
			i = i + m - minimum(j, 1 + hash_find(table, T[i]) );
			j = m - 1;
		}
	}

	return -1;
}

void read_file(const char* file_name, char P[], HashTable lastTable) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;

    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	int index = search(line, P, lastTable);
    	if(index != -1) {
    	//	printf("%i ", index);
    		++count;
    	}
    }

    fclose(fp);
    if (line)
        free(line);

    printf("Finished %i\n", count);
}

void read_dirs(const char* dir_name, char P[], HashTable lastTable) {
	DIR *d = opendir(dir_name);
	struct dirent *dir;

	if (d) {
		while ((dir = readdir(d)) != NULL) {
			int len = length(dir->d_name);
			if(len > 0) {
				char str[180];
				sprintf(str, "%s/%s", dir_name, dir->d_name);
				if(dir->d_name[0] != '.' && dir->d_type == DT_DIR) {
//					printf ("%s\n", str);
					read_dirs(str, P,lastTable);
				} else {
				 	printf("other %s\n", str);
				 	read_file(str, P, lastTable);
				}
			}
		}
		closedir(d);
	}
}

const char* jni_extract_string(JNIEnv* env, jstring string) {
	if(string == NULL)
		return NULL;

	return (*env)->GetStringUTFChars(env, string , NULL);
}

JNIEXPORT void JNICALL Java_JNISample_displayHelloWorld(JNIEnv *jnienv, jobject jobject) {
	printf("Hello world!\n");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_searchFileSystem(JNIEnv *jnienv, jobject jobject) {
	printf("Search FileSystem!\n");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_findFileSystemType(JNIEnv *jnienv, jobject jobject) {
	printf("find FileSystem Type!\n");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_stringManipulation (JNIEnv *jnienv, jobject jobject, jstring jstring) {
	// puts("!!!Searching for files for phrase!!!");
	char *phrase = jni_extract_string(jnienv, jstring);

	printf("%s \n", phrase);

	HashTable lastTable = hash_create_last_lookup_table(phrase);
	read_dirs("/home/jtoews/testfiles", phrase, lastTable);

	freemem();

	// printf("stringManipulation");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_characterManipulation(JNIEnv *jnienv, jobject jobject, jcharArray jcharArray) {
	printf("characterManipulation\n");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_objectManipulation(JNIEnv *jnienv, jobject j1, jobject j2) {
	printf("objectManipulation");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_integerManipulation(JNIEnv *jnienv, jobject jobject, jint j1, jint j2) {
	printf("integerManipulation");
	return;
}

JNIEXPORT void JNICALL Java_JNISample_search(JNIEnv *env, jobject obj, jstring str1, jstring str2) {
	printf("\n\nString String\n\n");
	return;
}
