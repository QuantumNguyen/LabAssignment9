#include <stdio.h>
#include <stdlib.h>

#define SIZE 31
// RecordType
struct RecordType
{
	int id;
	char name;
	int order;
};

// Fill out this structure
struct HashType
{
	struct RecordType *records;
	int count;
};

// Compute the hash function
int hash(int x)
{
	return x % SIZE;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
	FILE *inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i = 0; i < hashSz; ++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].count > 0)
		{
			// Print records stored in the hash slot
			printf("Index %d -> ", i);
			int j;
			for (j = 0; j < pHashArray[i].count; ++j)
			{
				struct RecordType record = pHashArray[i].records[j];
				printf("%d, %c, %d -> ", record.id, record.name, record.order);
			}
			printf("\n");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
struct HashType hashTable[SIZE];
    int i;
    for (i = 0; i < SIZE; ++i)
    {
        hashTable[i].records = NULL; // Initialize records to NULL
        hashTable[i].count = 0; // Initialize count to 0
    }

    // Insert records into the hash table
    for (i = 0; i < recordSz; ++i)
    {
        struct RecordType record = pRecords[i];
        int hashIndex = hash(record.id); // Get the hash index for the record
        struct HashType *hashSlot = &hashTable[hashIndex]; // Get the hash slot

        // Allocate memory for the record in the hash slot
        hashSlot->records = (struct RecordType*)realloc(hashSlot->records, (hashSlot->count + 1) * sizeof(struct RecordType));
        if (hashSlot->records == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        // Insert the record into the hash slot
        hashSlot->records[hashSlot->count] = record;
        hashSlot->count++;
    }

    // Display the records in the hash table
    displayRecordsInHash(hashTable, SIZE);

    // Free memory allocated for the hash table
    for (i = 0; i < SIZE; ++i)
    {
        free(hashTable[i].records);
    }

	return 0;
}