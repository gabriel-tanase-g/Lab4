/*******************************************************
* Lab Assignments 16.2
* Date: 16.12.2024
* Name: Maximum distance (2-D arrays)
* Authors: Gabriel Tanase, Khoon Sint Thar
* *******************************************************
* Determine the locations which cover the largest distance between them from a list of multiple locations.
* Output which 2 locations cover the largest distance and show how large the distance is in Km.
* *******************************************************
* The program handles the following:
- Store different locations in a 2D array, each location takes 1 row with another array of coordinates (latitute x longitude)
- Convert coordinates from degrees to Radians in order to be processed by trigonometrical functions from math.h, and store them in separate array
- C
- Display the result to the user in the console
********************************************************/
#define _USE_MATH_DEFINES // allow the usage of value of pi from math.h
#include<stdio.h>
#include <math.h> // use for trigonometric functions, and the value of pi
#define SIZE 7 // number of locations
#define COORDINATES 2 // latitude x longitude

double getMaximumDistance(const double coordinatesInRad[SIZE][COORDINATES], int* index1, int* index2); // parameters: 2d array with coordinates of locations, pointer to index to store location inside the array for the locations with largest distance. return: largest distance among all locations in the array
void convertToRadians(const double inputArray[SIZE][COORDINATES], double outputArray[SIZE][COORDINATES], int rows, int columns); // parameters: pointers to an input 2d array and an output 2d array, size in rows and columns, return: none: convert coordinates from input array into radians and store them in output array
double distanceKm(const double location1[COORDINATES], const double location2[COORDINATES]); // parameters: arrays with location as latitude x longitude (in radians). return an accurate distance between 2 locations

int main(void)
{
    int locationA = -1, locationB = -1;
    double maxDistance = 0;
    char* names[SIZE] = {
        "HAW Hamburg",
        "Eiffel Tower",
        "Palma de Mallorca",
        "Las Vegas",
        "Copacabana",
        "Waikiki Beach",
        "Surfer's Paradise"
    };
    double coordinates[SIZE][COORDINATES] = {
        {53.557078, 10.023109},
        {48.858363, 2.294481},
        {39.562553, 2.661947},
        {36.156214, -115.148736},
        {-22.971177, -43.182543},
        {21.281004, -157.837456},
        {-28.002695, 153.431781}
    };
    double coordinatesInRad[SIZE][COORDINATES] = { 0 };

    convertToRadians(coordinates, coordinatesInRad, SIZE, COORDINATES); 
    maxDistance= getMaximumDistance(coordinatesInRad, &locationA, &locationB); // calculate the largest distance and get the 2 locations index
    printf("This program determines which locations from a list have the largest distance between them.\n");
    printf("Given the following locations:\n");
    printf("\n+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - -  --  -- - - - - - +\n");
    for (int i = 0; i < SIZE; i++) 
    { 
        printf("%s            ", names[i]);
        if((i + 1) % 4 == 0)  
            printf("\n");
    }
    printf("\n+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - -  --  -- - - - - - +\n");
    printf("\n%s and %s have the largest distance of %.0f Km.\n"
        "You'd better not walk. Take a flight instead.\n", names[locationA], names[locationB], maxDistance);

    getchar();
    return 0;
}

double getMaximumDistance(const double coordinatesInRad[SIZE][COORDINATES], int* indexA, int* indexB)
{
// parameters: 2d array with coordinates of locations 
// parameter: pointer to index to store first location inside the array, for the locations with largest distance
// parameter: pointer to index to store second location inside the array, for the locations with largest distance
// return: largest distance among all locations in the array
    double maxDistance = 0;
    double currentDistance = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i + 1; j < SIZE; j++) // Compare each pair of locations
        {
             currentDistance= distanceKm(coordinatesInRad[i], coordinatesInRad[j]);
            if (currentDistance > maxDistance) 
            {
                maxDistance = currentDistance;
                *indexA = i; // store the first location for largest distance
                *indexB = j; // store the second location for largest distance
            }
        }
    }

    return maxDistance;
}

void convertToRadians(const double inputArray[SIZE][COORDINATES], double outputArray[SIZE][COORDINATES], int rows, int columns)
{
// parameter: pointers to an input 2d array
// parameter: pointer to an output 2d array
// parameter: size of rows
// parameter: size of columns (coordinates)
// return: none: convert coordinates from input array into radians and store them in output array
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            outputArray[i][j] = inputArray[i][j] * M_PI / 180; // Conversion formula from degrees to radians
    }
}

double distanceKm(const double location1[COORDINATES], const double location2[COORDINATES])
{
// parameters: array for first location with coordinates as latitude x longitude (in radians)
// parameters: array for second location with coordinates as latitude x longitude (in radians)
// return an accurate distance between the 2 locations
    const double EARTH_RADIUS = 6378.388; // The Earth’s radius
    double acosArgument = sin(location1[0]) * sin(location2[0])
        + cos(location1[0]) * cos(location2[0]) * cos(location2[1] - location1[1]);
    return EARTH_RADIUS * acos(acosArgument);
}
