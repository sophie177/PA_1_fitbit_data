/****************************************************************************************************************
*		Programmer: Sofia Lizotte
*		Class : CptS 122
*		PA #1
*		23 January 2022
*		Description : This assignment parses data that was generated from a Fitbit and writes an interpretation of the raw data to a file.
*		Note : This file contains function definitions. Descriptions can be found in the header file.
****/

#include "fitbit.h"


double read_entry(char* line) {
	double result = 999;
	if (*line != ',') // if there is an entry, get the token (from class)
	{
		result = atof(strtok(line, ",")); // From class example
		strcpy(line, strtok(NULL, ""));
	}
	else { // if no entry (double commas), replace with '999' to avoid mis-entering the next entry
		*line = '0';
		return result;
	}	// handling back-to-back delimiters with strtok() ! (empty entry handling)
}

void init_array(FitbitData* pArr) {
	strcpy(pArr->minute, "\0");  // This is from Wed 1/19 class example. -"hh"
	pArr->distance = 0.0;
	pArr->calories = 0.0;
	pArr->floors = 0;
	pArr->heartRate = 0;         // we use -> for pass-by-reference and . for pass-by-value
	pArr->steps = 0;
	pArr->sleepLevel = 0;
}


double find_heartrate(FitbitData* fitbitArray) {
	// fitbitData.csv contains each heart rate per minute over a 24h period, so finding the average 
	// of all the heart rates in the file will work. 
	unsigned int numHR = 0, totalHR = 0;
	for (int i = 0; i < 1440; i++) {
		if (fitbitArray[i].heartRate < 999) {  // 999 is marker of previously empty cell
			totalHR += fitbitArray[i].heartRate;
			numHR++;
		}
	}
	double aveHR = (double)totalHR / numHR;
	printf("Average Heart Rate: %.2lf \n\n", aveHR);
	return aveHR;
}

double find_steps(FitbitData* fitbitArray) {
	unsigned int maxSteps = 0, totalSteps = 0;
	for (int i = 0; i < 1440; i++) {
		if (fitbitArray[i].steps > maxSteps) {
			maxSteps = fitbitArray[i].steps;
		}
		totalSteps = i;
	}
	printf("Most steps taken in a minute: %d \n\n", (int)maxSteps / (int)totalSteps);
	return maxSteps;
}

char find_sleep(FitbitData* fitbitArray, badSleep* badSleepArray) {
	char StartSleep[10] = "", EndSleep[10] = "", currTimeWake[10] = "";
	int currSleepTotal = 0, TotalPoorSleep = 0, currTimeStart = 0;        // currSleepTotal stores minutes of bad sleep
	for (int i = 0; i < 1440; i++) {
		if (fitbitArray[i].sleepLevel == 2) {                   // while we have poor sleep
			char StartSleep[] = { fitbitArray[i].minute };          // store the minute of first instance of poor sleep
			while (fitbitArray[i].sleepLevel == 2) {            // for each following instance of poor sleep
				currSleepTotal += fitbitArray[i].sleepLevel;    // add the instance to total
				i++;                                            // update next line to read
			}

			if (currSleepTotal > TotalPoorSleep) {			      // compare if this range has higher sum than the max sum
				TotalPoorSleep = currSleepTotal;
				strcpy(StartSleep, currTimeStart);
				strcpy(EndSleep, currTimeWake);
			}

		}
		else {
			currTimeWake[10] = fitbitArray[i].minute;				  // size should be 7, but just in case  - would this be [i-1] ?
		}
	}
	*badSleepArray[0].fallAsleep = currTimeStart;					 // Using badSleep Array to return two strings for main(). 
	*badSleepArray[0].wake = currTimeWake;							 // Am I pointing or changing the value held in array badSleep? 
	badSleepArray[0].totalBadSleep = TotalPoorSleep;
	printf(" Longest consecutive range of poor sleep: %s to %s. Total Duration: %f\n\n", currTimeStart, currTimeWake, TotalPoorSleep);
	return badSleepArray;
}


void write_to_results(FitbitData fitbitArray, FILE* outfile, double totalkcal, double totalDistance, int totalFloors, int totalSteps, double aveHR, int maxSteps, char StartSleep[], char EndSleep[], double totalPoorSleep) {
	fputs("Total Calories,Total Distance,Total Floors,Total Steps,Average Heartrate,Max Steps in a Minute,Longest stretch of bad Sleep: \n", outfile);
	fprintf(outfile, "%.3f, %.3f, %d, %d, %.3f, %d, %f", totalkcal, totalDistance,
		totalFloors, totalSteps, aveHR, maxSteps, totalPoorSleep);
}