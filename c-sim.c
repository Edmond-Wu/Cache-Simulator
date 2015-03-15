#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "c-sim.h"

cache *cash_money = NULL; /*Global variable representing the cache*/

/*Determines if n is a power of 2*/
int powerOfTwo(int n) {
    	while ((n % 2 == 0) && n > 1)
        	n /= 2;
    	return (n == 1);
}

/*Converts a binary string to a decimal-form integer*/
int binaryToDecimal(char *binary) {
    	int i;
    	int result = 0;
    	int power = 0;
    	for (i = strlen(binary) - 1; i >= 0; i--) {
    	    	int added = (binary[i] - '0') * (int)pow(2, power);
    	    	result += added;
    	    	power++;
    	}
    	return result;
}

/*Converts a hexadecimal address into binary form*/
char* binaryFromHex(char *address) {
	/*char* bin;
	int i;
	
	bin = malloc(sizeof(char)*33);
	
	for(i = 2; i < strlen(hex); i++) {
		switch(hex[i]) {
			case '0':
				bin[i*4+0] = '0';
				bin[i*4+1] = '0';
				bin[i*4+2] = '0';
				bin[i*4+3] = '0';
				break;
			case '1':
				bin[i*4+0] = '0';
				bin[i*4+1] = '0';
				bin[i*4+2] = '0';
				bin[i*4+3] = '1';
				break;
			case '2':
				bin[i*4+0] = '0';
				bin[i*4+1] = '0';
				bin[i*4+2] = '1';
				bin[i*4+3] = '0';
				break;
			case '3':
				bin[i*4+0] = '0';
				bin[i*4+1] = '0';
				bin[i*4+2] = '1';
				bin[i*4+3] = '1';
				break;
			case '4':
				bin[i*4+0] = '0';
				bin[i*4+1] = '1';
				bin[i*4+2] = '0';
				bin[i*4+3] = '0';
				break;
			case '5':
				bin[i*4+0] = '0';
				bin[i*4+1] = '1';
				bin[i*4+2] = '0';
				bin[i*4+3] = '1';
				break;
			case '6':
				bin[i*4+0] = '0';
				bin[i*4+1] = '1';
				bin[i*4+2] = '1';
				bin[i*4+3] = '0';
				break;
			case '7':
				bin[i*4+0] = '0';
				bin[i*4+1] = '1';
				bin[i*4+2] = '1';
				bin[i*4+3] = '1';
				break;
			case '8':
				bin[i*4+0] = '1';
				bin[i*4+1] = '0';
				bin[i*4+2] = '0';
				bin[i*4+3] = '0';
				break;
			case '9':
				bin[i*4+0] = '1';
				bin[i*4+1] = '0';
				bin[i*4+2] = '0';
				bin[i*4+3] = '1';
				break;
			case 'a':
				bin[i*4+0] = '1';
				bin[i*4+1] = '0';
				bin[i*4+2] = '1';
				bin[i*4+3] = '0';
				break;
			case 'b':
				bin[i*4+0] = '1';
				bin[i*4+1] = '0';
				bin[i*4+2] = '1';
				bin[i*4+3] = '1';
				break;
			case 'c':
				bin[i*4+0] = '1';
				bin[i*4+1] = '1';
				bin[i*4+2] = '0';
				bin[i*4+3] = '0';
				break;
			case 'd':
				bin[i*4+0] = '1';
				bin[i*4+1] = '1';
				bin[i*4+2] = '0';
				bin[i*4+3] = '1';
				break;
			case 'e':
				bin[i*4+0] = '1';
				bin[i*4+1] = '1';
				bin[i*4+2] = '1';
				bin[i*4+3] = '0';
				break;
			case 'f':
				bin[i*4+0] = '1';
				bin[i*4+1] = '1';
				bin[i*4+2] = '1';
				bin[i*4+3] = '1';
				break;	
		}
	}
	
	bin[32] = '\0';
	return bin;*/
    	int i;
    	char *bin_add = malloc(sizeof(char) * 33);
    	for(i = 2; i < strlen(address); i++) {
        	switch(address[i]) {
			case '0': strcat(bin_add,"0000"); break;
            		case '1': strcat(bin_add,"0001"); break;
            		case '2': strcat(bin_add,"0010"); break;
            		case '3': strcat(bin_add,"0011"); break;
            		case '4': strcat(bin_add,"0100"); break;
            		case '5': strcat(bin_add,"0101"); break;
            		case '6': strcat(bin_add,"0110"); break;
            		case '7': strcat(bin_add,"0111"); break;
            		case '8': strcat(bin_add,"1000"); break;
            		case '9': strcat(bin_add,"1001"); break;
            		case 'a': strcat(bin_add,"1010"); break;
            		case 'b': strcat(bin_add,"1011"); break;
            		case 'c': strcat(bin_add,"1100"); break;
            		case 'd': strcat(bin_add,"1101"); break;
            		case 'e': strcat(bin_add,"1110"); break;
            		case 'f': strcat(bin_add,"1111"); break;
        	}
    	}
	strcat(bin_add,"\0");
    	return bin_add;
}

/*Gets number of lines in the trace file*/
int getNumLines(FILE *trace_file) {
	int ch, num_lines = 0;
    	do {
		ch = fgetc(trace_file);
    	    	if (ch == '\n')
            		num_lines++;
    	} while (ch != EOF);
    	return num_lines;
}

/*Adds a character to the end of a string*/
void append(char* s, char c)
{
    	int len = strlen(s);
    	s[len] = c;
    	s[len + 1] = '\0';
}

/*Initialize default cache values*/
void initializeCache() {
    	cash_money = malloc(sizeof(cache));
    	cash_money -> hits = 0;
    	cash_money -> misses = 0;
    	cash_money -> reads = 0;
    	cash_money -> writes = 0;
    	cash_money -> cache_size = 0;
    	cash_money -> block_size = 0;
    	cash_money -> set_size = 0;
    	cash_money -> associativity = NULL;
    	cash_money -> asso_value = 0;
    	cash_money -> write_policy = NULL;
    	cash_money -> num_sets = 0;
    	cash_money -> sets = NULL;
}

/*Creates a line in the cache*/
cache_line* makeLine() {
    	cache_line *temp;
    	temp = malloc(sizeof(cache_line));
    	temp -> valid = 0;
	temp -> dirty = 0;
    	temp -> tag = (char *)malloc(sizeof(char) * 33);
    	temp -> lru_index = 0;
    	return temp;
}

/*Creates and mallocs a set*/
void createSet(cache_set *set) {
    	set -> lines = malloc(cash_money -> set_size * sizeof(cache_line));
}

/*Creates a cold cache*/
void coldHardCache() {
	int i, l;
	cash_money -> sets = malloc(cash_money -> num_sets * sizeof(cache_set*));
       	for (i = 0; i < cash_money -> num_sets; i++) {
		cash_money -> sets[i] = malloc(sizeof(cache_set));
		createSet(cash_money -> sets[i]);
            	for (l = 0; l < cash_money -> set_size; l++) {
			cash_money -> sets[i] -> lines[l] = makeLine();
            	}
        }
}

/*Initializes an address_info struct with appropriate values*/
void initializeAddressInfo(address_info *memory) {
    	memory -> num_tag_bits = 0;
    	memory -> num_set_index_bits = 0;
    	memory -> num_block_offset_bits = 0;
    	memory -> set_index = NULL;
    	memory -> decimal_sindex = 0;
    	memory -> tag = NULL;
    	memory -> readwrite = NULL;
}

/*Prints out information related to the memory address*/
void printAddressInfo(address_info *memory, int mem_length) {
    	printf("Memory address length: %d\n", mem_length);
    	printf("Number of tag bits: %d\n", memory -> num_tag_bits);
    	printf("Number of set index bits: %d\n", memory -> num_set_index_bits);
    	printf("Number of block offset bits: %d\n", memory -> num_block_offset_bits);
    	printf("Tag: %s\n", memory -> tag);
    	printf("Set Index: %s\n", memory -> set_index);
    	printf("Decimal Set Index: %d\n", memory -> decimal_sindex);
    	printf("Read/Write: %s\n\n", memory -> readwrite);
}

/*Prints out the cache*/
void printCache() {
    	int i, j;
    	for(i = 0; i < cash_money -> num_sets; i++) {
        	for (j = 0; j < cash_money -> set_size; j++) {
			printf("Set number: %d\n", i);
			printf("Set line number: %d\n", j);
			printf("Tag: %s\n", cash_money -> sets[i] -> lines[j] -> tag);
			printf("Tag length: %d\n", strlen(cash_money -> sets[i] -> lines[j] -> tag));
			printf("Valid bit: %d\n\n", cash_money -> sets[i] -> lines[j] -> valid);
        	}
    	}
}

/*Prints out relevant information*/
void printInfo() {
    	printf("Memory reads: %d\n", cash_money -> reads);
    	printf("Memory writes: %d\n", cash_money -> writes);
    	printf("Cache hits: %d\n", cash_money -> hits);
    	printf("Cache misses: %d\n", cash_money -> misses);
    	/*printf("Cache size: %d\n", cash_money -> cache_size);
    	printf("Cache block size: %d\n", cash_money -> block_size);
    	printf("Cache associativity: %s\n", cash_money -> associativity);
    	printf("Cache associativity value: %d\n", cash_money -> asso_value);
    	printf("Cache write policy: %s\n", cash_money -> write_policy);
    	printf("Number of sets: %d\n", cash_money -> num_sets);
    	printf("Set size: %d\n", cash_money -> set_size);*/
}

/*Calculates the number of sets*/
int calcNumSets() {
    	if (strcmp(cash_money -> associativity, "direct") == 0)
        	return (cash_money -> cache_size)/(cash_money -> block_size);
    	else if (cash_money -> asso_value != 0)
        	return (cash_money -> cache_size)/(cash_money -> block_size * cash_money -> asso_value);
    	else
		return 1;
}

/*Returns the number of bits needed for the tag*/
int calcNumTagBits(int mem_length, address_info *memory) {
    	return mem_length - memory -> num_set_index_bits - memory -> num_block_offset_bits;
}

/*Calculates number of block offset bits*/
int calcNumBlockOffsetBits() {
    	return (int)(log((double)cash_money -> block_size)/log(2.0));
}

/*Calculates number of set index bits*/
int calcNumSetIndexBits() {
    	return (int)(log((double)cash_money -> num_sets)/log(2.0));
}

/*Updates appropriate values for the memory address*/
void updateAddressValues(int mem_length, address_info *memory, char *address) {
    	int i;
    	memory -> num_block_offset_bits = calcNumBlockOffsetBits();
    	memory -> num_set_index_bits = calcNumSetIndexBits();
    	memory -> num_tag_bits = calcNumTagBits(mem_length, memory);
    	
	memory -> tag = malloc(memory -> num_tag_bits * sizeof(char) + 1);
    	memory -> set_index = malloc(memory -> num_set_index_bits * sizeof(char) + 1);
    	for (i = 0; i < memory -> num_tag_bits; i++) {
        	append(memory -> tag, address[i]);
    	}
    	
    	while (i < (memory -> num_set_index_bits + memory -> num_tag_bits)) {
        	append(memory -> set_index, address[i]);
        	i++;
    	}
    	memory -> decimal_sindex = binaryToDecimal(memory -> set_index); /*Stores decimal value of the set index*/
}

/*Gets the highest index for LRU*/
int getHighestIndex(address_info *memory) {
	int i, high_index = 0, lru_i = 0;
	for (i = 0; i < cash_money -> set_size; i++) {
		if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index > lru_i) {
                    	lru_i = cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index;
                    	high_index = i;
                }
	}
	return high_index;
}

/*Updates indices used for LRU algorithm*/
void updateRecents(address_info *memory) {
    	int i, high_index = getHighestIndex(memory);
    	for(i = 0; i < cash_money -> set_size; i++) {
        	cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index++;
    	}
    	cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> lru_index = 0; /*Resets the most recently used index*/
}

/*LRU algorithm for updating a write-through cache*/
void lruWT(address_info *memory) {
	int i, high_index = 0, lru_i = 0;
	for (i = 0; i < cash_money -> set_size; i++) {
                if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> valid == 0) {
                    	strcpy(cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> tag, memory -> tag);
                    	cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> valid = 1;
			updateRecents(memory);
                    	return;
                }
		if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index > lru_i) {
			lru_i = cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index;
			high_index = i;
		}
	}
	cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> tag = memory -> tag;
	updateRecents(memory);
}

/*Update operations for a write-through cache*/
void writeThrough(address_info *memory) {
	int i, j;
    	for (i = 0; i < cash_money -> set_size; i++) {
        	if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> valid == 1 && strcmp(memory -> tag, cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> tag) == 0) {
                	cash_money -> hits++;
			cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index = 0;
			if (strcmp(memory -> readwrite, "W") == 0) {
				cash_money -> writes++;
			}
			for (j = 0; j < cash_money -> set_size; j++) {
				if (j != i) { /*Ignore the index that got a hit*/
					cash_money -> sets[memory -> decimal_sindex] -> lines[j] -> lru_index++;
				}
			}
			return;
            	}
    	}
	cash_money -> misses++;
	cash_money -> reads++;
	if (strcmp(memory -> readwrite, "W") == 0) {
		cash_money -> writes++;
	}
	lruWT(memory);
}

/*LRU algorithm for updating a write-through cache*/
void lruWB(address_info *memory) {
	int i, high_index = 0, lru_i = 0;
	for (i = 0; i < cash_money -> set_size; i++) {
                if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> valid == 0) {
                    	strcpy(cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> tag, memory -> tag);
                    	cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> valid = 1;
			if (cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> dirty == 1) {
				cash_money -> writes++;
			}
			if (strcmp(memory -> readwrite, "R") == 0) {
				cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> dirty = 0;
			}
			else {
				cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> dirty = 1;
			}
			updateRecents(memory);
                    	return;
                }
		if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index > lru_i) {
			lru_i = cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index;
			high_index = i;
		}
	}
	if (cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> dirty == 1) {
		cash_money -> writes++;
	}
	if (strcmp(memory -> readwrite, "R") == 0) {
		cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> dirty = 0;
	}
	else {
		cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> dirty = 1;
	}
	cash_money -> sets[memory -> decimal_sindex] -> lines[high_index] -> tag = memory -> tag;
	updateRecents(memory);
}

/*Update operations for a write-back cache*/
void writeBack(address_info *memory) {
	int i, j;
    	for (i = 0; i < cash_money -> set_size; i++) {
        	if (cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> valid == 1 && strcmp(memory -> tag, cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> tag) == 0) {
                	cash_money -> hits++;
			cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> lru_index = 0;
			if (strcmp(memory -> readwrite, "W") == 0) {
				cash_money -> sets[memory -> decimal_sindex] -> lines[i] -> dirty = 1;
			}
			for (j = 0; j < cash_money -> set_size; j++) {
				if (j != i) { /*Ignore the index that got a hit*/
					cash_money -> sets[memory -> decimal_sindex] -> lines[j] -> lru_index++;
				}
			}
			return;
            	}
    	}
	cash_money -> misses++;
	cash_money -> reads++;
	lruWB(memory);
}

/*Updates the cache given a trace file*/
void updateCache(FILE *trace_file, int num_lines) {
    	int mem_length;
    	char ip[12], rw[2], address[11], *binary_add;
    	address_info *memory;
    	while (fscanf(trace_file, "%s %s %s", ip, rw, address) != EOF && strcmp(ip, "#eof") != 0) {
        	memory = malloc(sizeof(address_info));
        	initializeAddressInfo(memory);
        	if (strcmp(rw, "W") == 0) {
            		memory -> readwrite = "W";
        	}
        	else {
            		memory -> readwrite = "R";
        	}
        	binary_add = binaryFromHex(address);
        	mem_length = strlen(binary_add);
        	updateAddressValues(mem_length, memory, binary_add); /*Calls malloc for the memory's set index and tag in this function*/

		/*Performs operations for a write-through or write-back depending on the write policy*/
        	if (strcmp(cash_money -> write_policy, "wt") == 0) {
            		writeThrough(memory);
        	}
		else {
			writeBack(memory);
		}
		free(binary_add);
		free(memory);
    	}
}

/*Frees the cache*/
void freeCache() {
	int i, j;
	for (i = 0; i < cash_money -> num_sets; i++) {
		for (j = 0; j < cash_money -> set_size; j++) {
			free(cash_money -> sets[i] -> lines[j] -> tag);
			free(cash_money -> sets[i] -> lines[j]);
		}
		free(cash_money -> sets[i] -> lines);
		free(cash_money -> sets[i]);
	}
	free(cash_money);
}

/*Main method - parses input*/
int main(int argc, char *argv[]) {
    	char *argument, *assoc, *assoc_substring, *assoc_val, *writepolicy;
    	int cachesize, n, blocksize, num_lines; /*n here refers to associativity value for "assoc:n"*/
    	FILE *trace_pointer;
    	if (argc != 6 && argc != 7) {
        	fprintf(stderr, "ERROR: Invalid amount of arguments\n");
    	}
    	else { /*Parses input; any errors results in termination of program*/
        	if (argc == 7) {
            		argument = argv[1];
            		if (strcmp(argument, "-h") == 0) {
                		printf("Usage: \"./c-sim <cache size> <associativity> <block size> <write policy> <trace file>\"\n");
                		exit(0);
            		}
            		else {
                		fprintf(stderr, "ERROR: Invalid syntax for help\n");
                		exit(0);
            		}
        	}
        	initializeCache();
        	cachesize = atoi(argv[1]);
        	if (cachesize == 0) {
            		fprintf(stderr, "ERROR: Invalid cache size\n");
            		exit(0);
        	}
        	else {
            		if (powerOfTwo(cachesize) == 1) {
                		cash_money -> cache_size = cachesize;
            		}
            		else {
                		fprintf(stderr, "ERROR: Cache size not a power of 2\n");
                		exit(0);
            		}
        	}
        	assoc = argv[2];
        	if (strcmp(assoc, "direct") == 0) {
            		cash_money -> associativity = assoc;
        	}
        	else if (strcmp(assoc, "assoc") == 0) {
            		cash_money -> associativity = assoc;
        	}
        	else {
            		assoc_substring = malloc(6);
            		strncpy(assoc_substring, assoc, 6);
            		if (strcmp(assoc_substring, "assoc:") == 0) {
                		if (strlen(assoc) - 6 == 0) {
                    			fprintf(stderr, "ERROR: No associative value\n");
                    			free(assoc_substring);
                    			exit(0);
                		}
                		assoc_val = malloc(strlen(assoc) - 6);
                		strncpy(assoc_val, assoc + 6, strlen(assoc) - 6);
                		n = atoi(assoc_val);
                		if (n == 0) {
                    			fprintf(stderr, "ERROR: Invalid associativity value\n");
                    			free(assoc_val);
                    			free(assoc_substring);
                    			exit(0);
                		}
                		else {
                    			if (powerOfTwo(n) == 1) {
                        			cash_money -> associativity = assoc;
                        			cash_money -> asso_value = n;
                    			}
                    			else {
                        			fprintf(stderr, "ERROR: Associative value not a power of 2\n");
                        			free(assoc_val);
                        			free(assoc_substring);
                        			exit(0);
                    			}
                		}
            		}
            		else {
                		fprintf(stderr, "ERROR: Invalid associativity\n");
                		exit(0);
            		}
        	}
		blocksize = atoi(argv[3]);
        	if (blocksize == 0) {
            		fprintf(stderr, "ERROR: Invalid cache block size\n");
            		exit(0);
        	}
        	else {
            		if (powerOfTwo(blocksize) == 1) {
                		cash_money -> block_size = blocksize;
            		}
            		else {
                		fprintf(stderr, "ERROR: Block size not a power of 2\n");
                		exit(0);
            		}
        	}
        	writepolicy = argv[4];
        	if (strcmp(writepolicy, "wt") == 0) {
            		cash_money -> write_policy = writepolicy;
        	}
        	else if (strcmp(writepolicy, "wb") == 0) {
            		cash_money -> write_policy = writepolicy;
        	}
        	else {
            		fprintf(stderr, "ERROR: Invalid write policy\n");
            		free(writepolicy);
            		exit(0);
        	}
        	cash_money -> num_sets = calcNumSets();
        	if (cash_money -> asso_value > 0) {
            		cash_money -> set_size = cash_money -> asso_value;
        	}
        	else if (strcmp(cash_money -> associativity, "direct") == 0) {
            		cash_money -> set_size = 1;
        	}
        	else {
            		cash_money -> set_size = (cash_money -> cache_size)/(cash_money -> block_size);
        	}

        	coldHardCache(); /*Builds the cache with a bunch of empty arrays*/

        	trace_pointer = fopen(argv[5], "r");
        	if (trace_pointer == NULL) {
            		fprintf(stderr, "ERROR: Invalid trace text\n");
            		exit(0);
        	}
        	else {
			num_lines = getNumLines(trace_pointer);
        		fclose(trace_pointer);
        		trace_pointer = fopen(argv[5], "r");
            		updateCache(trace_pointer, num_lines);
        	}
		printInfo();
		freeCache();
    	}
    	return 0;
}
