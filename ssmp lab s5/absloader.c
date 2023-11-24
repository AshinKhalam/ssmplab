#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//define the size for buffer
#define BUFFER 100

void AbsoluteLoader()
{
	//declare file pointer
	FILE *machinecode;
	
	int StartingAddress;
	int Index,CopyLoadMemory;
	char Line[BUFFER];
	
	//open file
	machinecode = fopen("machinecode.txt","r");
	
	
	while(fgets(Line, sizeof(Line), machinecode) != NULL)
	{	
		//if its a header record get the starting address
		if(Line[0] == 'H')
		{
			char ProgramName[7];	//Used to store Program name
			int HeadEndAddress;	//Used to store Header Address
			int HeadStartAddress;	//Used to Store Length of the program
			
			/*
			  ProgramName 	   - returns string of maximum 6 letters
			  HeadStartAddress - returns Hex of maximum 6 digits
			  HeadEndAddress   - returns Hex of maximum 2 digits
			*/
			
			sscanf(Line,"H^%6s^%6X^%6X",ProgramName,&HeadStartAddress,&HeadEndAddress);
			
			StartingAddress = HeadStartAddress;
			printf("Starting Address of the Program : %X\n",StartingAddress);
			
			//format for output
			printf("START\tMACHINE CODE\n");
					
		}
		//if its end record exit from loop
		else if(Line[0] == 'E')
		{
			break;
		}
		//if its text record fetch the start address and load the corresponding machine code with it
		else
		{
			char TextRecord[20]; 		//used to store the machine code
			int TextLength; 		//used to store the Length of text record
			int TextStartAddress;		//used to store the start address of each text record
			
			/*
			  TextStartAddress - returns maximum of 6 digit Hex
			  TextLength	   - returns maximum of 2 digit Hex
			  TextRecord       - returns maximum of 20 digit string
			*/
			
			sscanf(Line,"T^%6X^%2X^%20s",&TextStartAddress,&TextLength,TextRecord);
			
			
			/*
		         The file machinecode.txt contains seperator '^' .This is not needed in
		   	 the Loader since it just indicate the end of a machine code of a statement 		         
			*/
			
			//Declaring and initializing ArrayParts as an empty array for Preprocessing The TextTecord array
			char ArrayParts[100] = "";
			
			for(int i=0;i<strlen(TextRecord);i++)
			{
				//when the TextRecord gives value '^' eliminate it else copy the value to ArrayParts
				if(TextRecord[i] != '^')
				{
				
					//Create a temp array to store the current TextRecord value and null character
					char temp[2] = {TextRecord[i],'\0'};
					
					//Concatenate one element at a time using strncat
					strncat(ArrayParts,temp,1);
				
				}
			}
			
			//Print the Loaded address and corresponding two elements
			for(int i=0;i<strlen(ArrayParts);i=i+2)
			{
				
				printf("%X\t%c%c\n",TextStartAddress,ArrayParts[i],ArrayParts[i+1]);
				TextStartAddress = TextStartAddress + 1;
			}
			printf("\n**************\n");
			
		}
	}
	
	//close the file
	fclose(machinecode);
	
}

int main()
{	
	//Call the fucntion
	AbsoluteLoader();
	return 0;
}
