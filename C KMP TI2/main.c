#pragma warning(disable : 4996) //suppress scanf unsafe warning

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

void KMP_Search(char search_pattern[], int length_Pattern, char search_String[], int length_String, int pi_Table[])
{

}

int main(void)
{
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

	KMP_Setup(search_Pattern, length_Pattern, pi_Table);
	KMP_Search(search_Pattern, length_Pattern, search_String, length_String, pi_Table);

	free(pi_Table);

	return 0;
}