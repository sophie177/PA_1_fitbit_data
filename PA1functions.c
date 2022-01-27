/****************************************************************************************************************
*		Programmer: Sofia Lizotte
*		Class : CptS 122
*		PA #1
*		23 January 2022
*		Description : This assignment parses data that was generated from a Fitbit and writes an interpretation of the raw data to a file.
*		Note : This
 file contains function definitions. Descriptions can be found in the header file.
****/

#include "PA1header.h"


double read_entry(char* line) { 
	double result = 999; 
	if (*line != ',') // if there is an entry, get the token (from class)
	{
		result = atof(strtok(line, ",")); // From class example
		strcpy(line, strtok(NULL, ""));
	}
	else { // if no entry (double commas), replace with '0' to avoid mis-entering the next entry
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


double find_heartrate(FitbitData *fitbitArray) {
	// fitbitData.csv contains each heart rate per minute over a 24h period, so finding the average 
	// of all the heart rates in the file will work. 
	unsigned int numHR = 0, totalHR = 0;
	for (int i = 0; i < 1440; i++) {
		if (fitbitArray[i].heartRate < 999) {  // was != 0
			totalHR += fitbitArray[i].heartRate;
			numHR++;
		}
	}
	double aveHR = (double)totalHR / numHR;	// was 
	printf("Average Heart Rate: %.2lf \n\n", aveHR);
	return aveHR;
}

double find_steps(FitbitData* fitbitArray) {
	unsigned int maxSteps = 0, totalSteps = 0;
	for (int i = 0; i < 1440; i++) {
		// call fn to compute max steps taken in one minute (loop)
		if (fitbitArray[i].steps > maxSteps) { //&& fitbitArray[i].steps != 0)  - redundant?
			maxSteps = fitbitArray[i].steps;
		}
		totalSteps = i; 
	}
	printf("Most steps taken in a minute: %.2lf \n\n", (float)maxSteps / (float)totalSteps);
	return maxSteps;
}

char find_sleep(FitbitData* fitbitArray, badSleep *badSleepArray) {                  
	 char StartSleep[] = "", EndSleep[] = "", currTimeWake[] = "";
	 int currTimeStart = 0,  PoorSleep = 0, j = 0;//currTimeWake = 0,
	 int currSleepTotal = 0;
	 for (int i = 0; i < 1440; i++) {
		 if (fitbitArray[i].sleepLevel > 1 && fitbitArray[i].sleepLevel != 0) {
			 strcpy(currTimeWake, fitbitArray[i].minute);
			 while (fitbitArray[i].sleepLevel > 1 && fitbitArray[i].sleepLevel != 0) {
				 currSleepTotal += fitbitArray[i].sleepLevel;
				 i++;
			 }
			 strcpy(currTimeWake, fitbitArray[i - 1].minute);
			 // compare if this range has higher sum than the max sum
			 if (currSleepTotal > PoorSleep) {
				 PoorSleep = currSleepTotal;
				 strcpy(StartSleep, currTimeStart);  // why did Andy say these have to be strings? 
				 strcpy(EndSleep, currTimeWake);  
			 }
		 }
	 }
	 *badSleepArray[0].fallAsleep = currTimeStart; // Using badSleep Array to return two strings for main(). 
	 *badSleepArray[0].wake = currTimeWake;                         // Am I pointing or changing the value held in array badSleep? 
	 printf(" Longest consecutive range of poor sleep: %s to %s \n\n", StartSleep, currTimeWake);      
	 return badSleepArray;  
}


void write_to_results(FitbitData fitbitArray, FILE* outfile, double totalkcal, double totalDistance, int totalFloors, int totalSteps, double aveHR, int maxSteps, char StartSleep[], char EndSleep[]) {
	fputs("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n", outfile);
	fprintf(outfile, "%.3f, %.3f, %d, %d, %.3f, %d, %s:%s", totalkcal, totalDistance,
		totalFloors, totalSteps, aveHR, maxSteps, StartSleep, EndSleep);
}





