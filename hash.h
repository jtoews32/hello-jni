#define MAX_BUFFER 50
#define FALSE 0
#define TRUE 1

typedef struct HashTable_ *HashTable;
typedef struct TableElement_ *TableElement;


struct HashTable_ {
	TableElement *table;
	int size;
	int last;
};
struct TableElement_ {
	int data;
	char key;
	TableElement next;
};

int hash(char key, int size);

HashTable hash_create_last_lookup_table(char[]);
HashTable hash_create_table(int);
TableElement hash_create_element(int, char, TableElement);

void hash_insert(HashTable h, char key, int data);
int hash_find(HashTable h, char key);
void hash_delete(HashTable h, char key);

int hash_calculate_length(char[]);

