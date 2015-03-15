#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*Struct for a cache line*/
typedef struct {
	int valid;
	int dirty;
	int lru_index;
	char *tag;
} cache_line;

/*Struct for a set; stores a line*/
typedef struct {
	cache_line **lines;
} cache_set;

/*Struct for a cache; pointer to array of sets and stores all relevant variables*/
typedef struct {
        int hits;
        int misses;
        int reads;
        int writes;
        int cache_size;
        int block_size;
	int set_size;
        char *associativity;
        int asso_value;
        char *write_policy;
        int num_sets;
	cache_set **sets;
} cache;

/*Struct that stores relevant values of a line in the trace file including address-related values*/
typedef struct {
	int num_tag_bits;
	int num_set_index_bits;
	int num_block_offset_bits;
	int decimal_sindex;
	char *set_index;
	char *tag;
	char *readwrite;
} address_info;


/*Determines if n is a power of 2*/
int powerOfTwo(int n);

/*Returns the decimal form of a binary string*/
int binaryToDecimal(char *binary);

/*Returns the binary form of a hexadecimal address*/
char *binaryFromHex(char *address);

/*Gets number of lines in the trace file*/
int getNumLines(FILE *trace_file);

/*Appends a character to a string*/
void append(char *s, char c);

/*Initializes the cache*/
void initializeCache();

/*Creates and initializes a cache line*/
cache_line* makeLine();

/*Creates and mallocs a set*/
void createSet(cache_set *set);

/*Creates a cold cache*/
void coldHardCache();

/*Initializes memory address information*/
void initializeAddressInfo(address_info *memory);

/*Prints out address information*/
void printAddressInfo(address_info *memory, int mem_length);

/*Prints out the cache*/
void printCache();

/*Prints out cache information*/
void printInfo();

/*Calculates number of sets in cache*/
int calcNumSets();

/*Calculates number of tag bits*/
int calcNumTagBits();

/*Calculates number of block offset bits*/
int calcNumBlockOffsetBits();

/*Calculates number of set index bits*/
int calcNumSetIndexBits();

/*Updates the address values/parameters*/
void updateAddressValues();

/*Gets high index for LRU*/
int getHighestIndex(address_info *memory); 

/*Updates indices used for LRU algorithm*/
void updateRecents(address_info *memory);

/*LRU algorithm for updating a write-through cache*/
void lruWT(address_info *memory);

/*Update operations for a write-through cache*/
void writeThrough(address_info *memory);

/*LRU algorithm for updating a write-back cache*/
void lruWB(address_info *memory);

/*Update operations for a write-back cache*/
void writeBack(address_info *memory);

/*Updates the cache given a trace file*/
void updateCache(FILE *trace_file, int num_lines);

/*Main method*/
int main(int argc, char *argv[]);
