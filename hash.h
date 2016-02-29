#define MAX_BUFFER 50
#define FALSE 0
#define TRUE 1

typedef struct HashTable_ *HashTable;
typedef struct HashTableElement_ *HashTableElement;

struct HashTable_ {
	HashTableElement *table;
	int size;
	int last;
};
struct HashTableElement_ {
	int data;
	char key;
	HashTableElement next;
};

int hash_function(char key, int size);

HashTable hash_create_last_lookup_table(char[]);
HashTable hash_create_table(int);
HashTableElement hash_create_element(int, char, HashTableElement);

void hash_insert(HashTable h, char key, int data);
int hash_find(HashTable h, char key);
void hash_delete(HashTable h, char key);

int hash_calculate_length(char[]);

