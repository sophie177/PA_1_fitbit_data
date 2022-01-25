/****************************************************************************************************************
*		Programmer: Sofia Lizotte
*		Class : CptS 122
*		PA #1
*		23 January 2022
*		Description : This assignment parses data that was generated from a Fitbit and writes an interpretation of the raw data to a file.
*		Note : Two functions and main() contain starter code from class. (TODO: elaborate which pieces)
****/

#include "PA1header.h"


int main(void) {

/*    3 pts for correctly opening “FitbitData.csv” for mode read,
      3 pts for correctly opening “Results.csv” for mode write     */

	//FILE* infile = '\0', * outfile = '\0';
	FILE* infile = fopen("sample.csv", "r"), * outfile = fopen("results.csv", "w");

	/*   2 pts for correctly checking the success of the file opening operation  */
	if (infile == NULL) {
		puts(" Error: Cannot open FitbitData.csv \n");
	}


	char line[100] = "";
	FitbitData fitbitArray[1440]; // declared an array of type FitbitData 
	unsigned int i = 0;  // this is the index of array fitbitArray
	init_array(fitbitArray); // must initialize the array because otherwise the index variable arrayIndex will be undefined. 


			double totalkcal = 0.0, totalDistance = 0.0;
			unsigned int totalFloors = 0, totalSteps = 0;

	/*   10 pts for correctly reading each record in the file as a string,
	*    one line at a time, and filtering and deduping any lines that do not belong to the target patient or are duplicates  */

	fgets(line, 100, infile); // 1440?  - This reads + discards the first line. 
	
	while(fitbitArray[i].patient == "12cx7"){   
		fgets(line, 100, infile); // from class: read one line
		strcpy(fitbitArray[i].minute, strtok(line, ",")); // minute is first listed

		fitbitArray[i].calories, read_entry(line);
		fitbitArray[i].distance, read_entry(line);
		fitbitArray[i].floors = (unsigned int)read_entry(line);
		fitbitArray[i].heartRate = (unsigned int)read_entry(line);
		fitbitArray[i].steps = (unsigned int)read_entry(line);
		if (*line != ',') {  // taken from class example : only gets tok if there is a sleep entry
			fitbitArray[i].sleepLevel = (Sleep)atof(line);
		}
		else {
			fitbitArray[i].sleepLevel = 0;
		}
		 i ++;
	} //Assuming the csv data ends with "23:59:00,0.968900025,0,0,68,0,1" - no "\n" *  ----> FIXME !!


	/*   15 pts for correctly cleaning the data and parsing each record into the corresponding fields   */
	/*   5 pts for correctly converting the strings to the field types  */
	/*   5 pts for correctly storing the fields into the FitbitData array  */


	for (i = 0; i < 1440; i++) { // '0' is also the marker where back-to-back delimiters were
		if (fitbitArray[i].calories >= 0) { 
			totalkcal += fitbitArray[i].calories;      //  3 pts for correctly computing the total calories burned
		}if (fitbitArray[i].distance >= 0) {
			totalDistance += fitbitArray[i].distance;  // 3 pts for correctly computing the total distance walked in miles
		}if (fitbitArray[i].floors >= 0) {        
			totalFloors += fitbitArray[i].floors;      // 3 pts for correctly computing the total floors walked
		}if (fitbitArray[i].steps >= 0) {
			totalSteps += fitbitArray[i].steps;        //  3 pts for correctly computing the total steps taken 
		} 
	}

	/* 	 4 pts for correctly computing the average heartrate over the 24 hour period  */
	 double aveHR = find_heartrate(fitbitArray); 

	 /*   8 pts for correctly determining the max steps taken in one minute over the 24 hour period   */
	 double maxSteps = find_steps(fitbitArray);  


	/*   8 pts for correctly determining the longest consecutive range of poor sleep    */
	 badSleep badSleepArray[1] = { find_sleep(fitbitArray, badSleepArray) };
	 char startSleep = badSleepArray[0].fallAsleep;
	 char EndSleep = badSleepArray[0].wake;

	/*   8 pts for correctly formatting and outputting the data, without any duplicate entries, to “Results.csv” and to the screen   */
	write_to_results(*fitbitArray, outfile, totalkcal, totalDistance, totalFloors, totalSteps, aveHR, maxSteps, startSleep, EndSleep);


   /*   2 pts for correctly closing the “FitbitData.csv,
	*   2 pts for correctly closing the “Results.csv”    */
	fclose(infile);
	fclose(outfile);

	return 0;
}