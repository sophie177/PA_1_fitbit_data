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


double read_entry(char* line) {  // FIXME
	double result = 0; // why 1000 ?
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
	strcpy(pArr->minute, "hh");  // This is all from Wed 1/19 class example. 
	pArr->distance = 0.0;
	pArr->calories = 0.0;
	pArr->floors = 0;
	pArr->heartRate = 0;
	pArr->steps = 0;
	pArr->sleepLevel = 0;
}




double find_heartrate(FitbitData *fitbitArray) {
	// call fn to compute total heartrate  (needed to get average hr)
	unsigned int numHR = 0, totalHR = 0;
	double aveHR = 0.0;
	for (int i = 0; i < 1440; i++) {

		if (fitbitArray[i].heartRate > 0) {  // was != 0
			totalHR += fitbitArray[i].heartRate;
			numHR++;
		}
	}
	//   4 pts for correctly computing the average heartrate over the 24 hour period  
	aveHR = (double)totalHR / numHR;	
	return aveHR;
}

double find_steps(FitbitData* fitbitArray) {
	unsigned int maxSteps = 0;
	for (int i = 0; i < 1440; i++) {
		// call fn to compute max steps taken in one minute (loop)
		if (fitbitArray[i].steps > maxSteps) { //&& fitbitArray[i].steps != 0)  - redundant?
			maxSteps = fitbitArray[i].steps;
			char timeMaxSteps[5] = "";
			strcpy(timeMaxSteps, fitbitArray[i].minute);
			// is it really supposed to be stored in minute?
		}
	}
	return maxSteps;
}

char find_sleep(FitbitData* fitbitArray, badSleep *badSleepArray) {                   //FIXME
	// print both results to file, then change write_to_results to display file contents. ! //TODO
	 char StartSleep[] = "", EndSleep[] = "";
	 int currTimeStart = 0, currTimeEnd= 0, PoorSleep = 0, j = 0;
	 int currSumPoorSleep = 0;
	 for (int i = 0; i < 1440; i++) {
		 if (fitbitArray[i].sleepLevel > 1 && fitbitArray[i].sleepLevel != 0) {
			 strcpy(currTimeStart, fitbitArray[i].minute);
			 while (fitbitArray[i].sleepLevel > 1 && fitbitArray[i].sleepLevel != 0) {
				 currSumPoorSleep += fitbitArray[i].sleepLevel;
				 i++;
			 }
			 strcpy(currTimeEnd, fitbitArray[i - 1].minute);
			 // compare if this range has higher sum than the max sum
			 if (currSumPoorSleep > PoorSleep) {
				 PoorSleep = currSumPoorSleep;
				 strcpy(StartSleep, currTimeStart);
				 strcpy(EndSleep, currTimeEnd);
			 }
		 }
	 }
	 *badSleepArray[0].fallAsleep = currTimeStart; //AGHH!!!??
	 *badSleepArray[0].wake = currTimeEnd;                         // Am I pointing or changing the value held in array badSleep? 
	 return badSleepArray;  
}


void write_to_results(FitbitData fitbitArray, FILE* outfile, double totalkcal, double totalDistance, int totalFloors, int totalSteps, double aveHR, int maxSteps, char maxTimeStartPoorSleep, char maxTimeEndPoorSleep) {//AGHH
	fputs("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n", outfile);
	fprintf(outfile, "%.3f, %.3f, %d, %d, %.3f, %d, %s:%s", totalkcal, totalDistance,
		totalFloors, totalSteps, aveHR, maxSteps, maxTimeStartPoorSleep, maxTimeEndPoorSleep);
}





