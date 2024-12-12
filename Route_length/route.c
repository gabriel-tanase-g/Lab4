/*******************************************************
* Lab Assignments 16.1
* Date: 16.12.2024
* Name: Route length (1-D arrays)
* Authors: Gabriel Tanase, Khoon Sint Thar
* *******************************************************
* Determine the overall distance (in Km) of a round trip around HAW Hamburg.
* The route leads along Lohmuhlen park in the direction of lake Alster, around St. Georg hospital, and back toHAW Hamburg.
* *******************************************************
* The program handles the following:
- Store different locations in 2 different 1D arrays (1 for latitudes, 1 for longitudes)
- Convert coordinates from degrees to Radians in order to be processed by trigonometrical functions from math.h, and store them in separate array
- Calculate the overall distance from the round trip around this coordinates\
- Display the result to the user in the console
********************************************************/

#include<stdio.h>
#define _USE_MATH_DEFINES // allow the usage of value of pi from math.h
#include <math.h> // use for trigonometric functions, and the value of pi
#define SIZE 9 

double distanceKm(double latitude1, double latitude2, double longitude1, double longitude2); // parameters: latitude and longitude of 2 locations in Radians, return: distance in Km considering the curvature Earth
double getRouteLengthKm(double* latitudes, double* longitudes, int size);
void convertToRadians(const double* inputArray, double* outputArray, int size); // parameters: pointers to an input array, output array and its size, return: none: convert coordinates from input array into radians and store them in output array
double distanceKm(double latitude1, double latitude2, double longitude1, double longitude2); // parameters: coordinates of 2 locations on Earth (In radians), returns an accurate distance between 2 locations

int main(void)
{
	double routeLength = 0.0;
	double latitudes[SIZE] = { // Latitudes of the route around HAW in degrees
		53.557029,
		53.557166,
		53.557274,
		53.560288,
		53.561306,
		53.562015,
		53.558241,
		53.557900,
		53.557203
	};
	double longitudes[SIZE] = { // Longitudes of the route around HAW in degrees
		10.022918,
		10.021343,
		10.020297,
		10.014906,
		10.015426,
		10.016568,
		10.023244,
		10.022142,
		10.022632,
	};
	double latitudesInRadians[SIZE] = { 0 };
	double longitudesInRadians[SIZE] = { 0 };

	convertToRadians(latitudes, latitudesInRadians, SIZE);
	convertToRadians(longitudes, longitudesInRadians, SIZE);
	routeLength = getRouteLengthKm(latitudesInRadians, longitudesInRadians, SIZE);
	printf("+-------------------------------------------------------------------+\n"
		"This program calculates a round trip about HAW Hamburg.\n"
		"The route leads along Lohmuhlen park in the direction of lake Alster,\n"
		"around St. Georg hospital, and back to HAW Hamburg.\n");
	printf("+-------------------------------------------------------------------+\n"
		"The overall distance of this round trip is: %.2f Km\n", routeLength);

	getchar();
	return 0;
}

double distanceKm(double latitude1, double latitude2, double longitude1, double longitude2)
// Calculate the distance between two locations using coordinates in Radians, considering the curvature of the Earth
// Parameters:
// - latitude1: Latitude of location One in radians
// - latitude2: Latitude of location Two in radians
// - longitude1: Longitude of location One in radians
// - longitude2: Longitude of location Two in radians
// Return: Distance in Km, using an accurate formula that takes into the account the curvature of the Earth
{
	const double EARTH_RADIUS = 6378.388; // the Earth’s radius
	double acosArgument = sin(latitude1) * sin(latitude2)
		+ cos(latitude1) * cos(latitude2) * cos(longitude2 - longitude1);
	return EARTH_RADIUS * acos(acosArgument); //acos = 1/cos
}

void convertToRadians(const double* inputArray, double* outputArray, int size)
// Convert an array of coordinates from degrees to radians
// Parameters:
// - inputArray: Pointer to the array containing coordinates in degrees (not modified by the function)
// - outputArray: Pointer to the array where converted coordinates in radians will be stored
// - size: The number of elements in the arrays
// Return: None. The result is stored in the outputArray
{
	for (int i = 0; i < size; i++)
		outputArray[i] = inputArray[i] * M_PI / 180; // conversion formula from degrees to radians
}

double getRouteLengthKm(double* latitudes, double* longitudes, int size)
// Calculate the route length  
{
	double totalDistance = 0.0;

	for (int i = 0; i < SIZE - 1; i++)
		totalDistance += distanceKm(latitudes[i], latitudes[i + 1], longitudes[i], longitudes[i + 1]);

	return totalDistance;
}