/****************************************************************************************************************
*		Programmer: Sofia Lizotte
*		Class : CptS 122
*		PA #1
*		23 January 2022
*		Description : This assignment parses data that was generated from a Fitbit and writes an interpretation of the raw data to a file.
*		Note : This file contains function declarations and descriptions.
****/
#pragma once
#ifndef _PA1HEADER_H
#define _PA1HEADER_H 


#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // for atof(), atoi() 



/************************************
*		Enumerated Type:  Sleep
*		Created by: Andrew O'Fallon  (starter code)
*		Description:  Four categories of wakefulness are given to determine sleep quality.
*       Note:  3 pts for correctly defining enum Sleep
**************************************/

typedef enum sleep {
    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

/************************************
*		Struct:  FitbitData
*		Created by: Andrew O'Fallon  (starter code)
*		Description:  provides a category for each component in a line of .csv data
*       Note:    5 pts for correctly defining struct FitbitData
**************************************/

typedef struct fitbit {
    char patient[10];
    char minute[9];
    double calories;
    double distance;
    unsigned int floors;
    unsigned int heartRate;
    unsigned int steps;
    Sleep sleepLevel;
} FitbitData;

/************************************
*		Struct:  badSleep
*		Created by: Sofia Lizotte
*		Description:  allows function find_sleep() to return both values of a givens sleep range
*       Note:    
**************************************/

typedef struct badSleep {
   char wake[9];
   char fallAsleep[9];
}badSleep;



/************************************
*		Function:  read_entry()
*		Date Created: 01 / 23 / 2022
*       Created by: Sofia Lizotte
*		Description:  Reads one line of .csv data- if a section is missing, it is filled with an indicator value of '0'
*		Input Parameter: pointer to a string (delimiter from last line)
*		Returns: one (valid) line of .csv data without the preceding token
*		Preconditions:  .csv file must be open for reading and begin with a comma (handled by reading and discarding first line)
*		Postconditions: return '0' if there was no entry (back-to-back delimiters)
**************************************/
double read_entry(char* line);


/*******************************************************************************
* Function: init_array()															
* Date Created: 01 / 23 / 2022													    
* Description: initializes each index of fitbitArray to '0'				    
* Input parameters: pointer to a FitbitData array (modified from example in class)							
* Returns: an array with elements set to 0									    
* Preconditions: fitbitArray must be declared									    
* Postconditions: Each struct element and array element set to 0	
********************************************************************************/
void init_array(FitbitData* pArr);



// come back and describe...

double find_heartrate(FitbitData * fitbitArray);  


double find_steps(FitbitData* fitbitArray);

char find_sleep(FitbitData *fitbitArray, badSleep * badSleepArray);  










/*******************************************************************************
* Function: write_to_results()
* Date Created: 01 / 23 / 2022
* Description: fills "results.csv" with interpreted data
* Input parameters: filestream and pointer to fitbitArray
* Returns: nothing
* Preconditions: fitbitArray must be declared, results.csv must be open with a pointer to the stream
* Postconditions:   Sleep quality, average heart rate, steps taken in a day will be written to the file       // FIXME
********************************************************************************/
void write_to_results(FitbitData fitbitArray, FILE* outfile, double totalkcal, double totalDistance, int totalFloors, int totalSteps, double aveHR, int maxSteps, char StartSleep, char EndSleep);



#endif