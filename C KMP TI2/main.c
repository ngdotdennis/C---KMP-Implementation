#pragma warning(disable : 4996) //suppress scanf unsafe warning

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define getName(var) #var		//Variable name
#define defaultSize 30			//Default string size for KMP string
#define newline printf("\n")	//New line :)

void KMP_Setup(char search_Pattern[], int length_Pattern, int pi_Table[])
{
	int pi_Counter = 0;
	pi_Table[1] = 0;			//String with a length of 1 has no real suffix

	for (int i = 1; i < length_Pattern; i++)
	{
		bool match = search_Pattern[i] == search_Pattern[pi_Counter];

		switch (match)
		{
		case true:				//Match
			pi_Counter += 1;
			break;
		case false:				//Missmatch
			//Check PI-Table whether we find a match from earlier entries or not
			//If so, then match will be set to true. Otherwise it's a utter missmatch => 0
			while (pi_Counter > 0 && match == false)	
			{
				pi_Counter = pi_Table[pi_Counter];
				match = search_Pattern[i] == search_Pattern[pi_Counter];
			}
			if (match == true)
				pi_Counter += 1;
			break;
		}
		pi_Table[i + 1] = pi_Counter;	//Enter entry number into the corresponding table slot
	}

	printf("\n%s:\t%2s\n", getName(search_Pattern), search_Pattern);
	printf("PI-Table:	");
	for (int i = 1; i <= length_Pattern; i++) //Ignore token
	{
		printf("%d", pi_Table[i]);
	}
	newline;
}

void KMP_Search(char search_Pattern[], int length_Pattern, char search_String[], int length_String, int pi_Table[])
{
	int j = 0;					//PI-Table(pattern) counter

	for (int i = 0; i < length_String; ++i)
	{
		bool match = search_String[i] == search_Pattern[j];

		switch (match)
		{
		case true:				//Match
			if (match == true)				
						j += 1;
			break;
		case false:				//Missmatch
			while (j > 0 && match == false)	//Missmatch
			{
				j = pi_Table[j];
				match = search_String[i] == search_Pattern[j];
			}
			if (match)
				j += 1;
			break;
		}
		//Reached the end?
		if (j == length_Pattern)
		{
			printf("%s\n", search_String);
			printf("%*s%s\n", i - (j - 1), "", search_Pattern);
			j = pi_Table[j];
		}
	}
}

void Naive(char search_Pattern[], char search_String[])
{
	int i, j;
	for (i = 0; search_String[i] != 0; i++)
	{
		for (j = 0; search_String[i + j] == search_Pattern[j]; j++)
		{
			if (search_Pattern[j + 1] == 0)
			{
				printf("Match found at position: %i", i), newline;
			}
		}
	}
}

int main(void)
{
	Naive("acact", "acacgacgacacact");
	double time_spent[2];
	clock_t begin, end;

	char search_Pattern[defaultSize];
	int length_Pattern;					//Pattern string length
	char search_String[defaultSize];	
	int length_String;					//Search string length

	//Text string
	printf("Enter a string with less than 15 characters and without whitespaces!"), newline;
	scanf("%s", &search_String), newline;
	length_String = strlen(search_String);
	//Search pattern
	printf("Enter a search pattern for KMP!"), newline;
	scanf("%s", &search_Pattern);
	length_Pattern = strlen(search_Pattern);
	//Pi table for prefix and suffix determination
	int *pi_Table = malloc((length_Pattern + 1) * sizeof(int));
	system("cls");

	printf("%s:\t%s", getName(search_String), search_String), newline;
	printf("%s:\t%s", getName(search_Pattern), search_Pattern), newline;

	begin = clock();
	KMP_Setup(search_Pattern, length_Pattern, pi_Table), newline;
	_sleep(3);
	end = clock();
	time_spent[0] = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	KMP_Search(search_Pattern, length_Pattern, search_String, length_String, pi_Table), newline;
	_sleep(3);
	end = clock();
	time_spent[1] = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("Time elapsed during %s is %.*f ms.", getName(KMP_Setup), 2, time_spent[0]*1000), newline;
	printf("Time elapsed during %s is %.*f ms.", getName(KMP_Search), 2, time_spent[1]*1000), newline;

	free(pi_Table);

	return 0;
}