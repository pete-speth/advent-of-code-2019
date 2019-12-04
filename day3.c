#include <stdio.h>
#include <math.h>
#include "aoc-utils.h"

struct point {int x; int y;};

struct point* getPath(char* str, int* size);
struct point* findIntersection(struct point p1a, struct point p1b, struct point p2a, struct point p2b);
void printPoint(struct point p);
_Bool isVertical(struct point p1, struct point p2);
int min(int a, int b);
int max(int a, int b);
void sortLowToHigh(int* arr, int size);

int main(){
	// read each path from input into an array
	FILE* file_p = fopen("input/day3.txt","r");
	// these sizes will be modified in the getPath function to reflect the number of points
	int sizeA = 1500;
	int sizeB = 1500;
	char* lineA = readLine(file_p,sizeA);
	char* lineB = readLine(file_p,sizeB);

	// create an array of points to represent each wire's path
	struct point* pathA = getPath(lineA,&sizeA);
	struct point* pathB = getPath(lineB,&sizeB);

	// for each line on Wire A, check if it intersects any path of Wire B
	// find the minimum distance of all the intersections
	int minDistance = 0;
	int minSteps = 0;
	int isteps = 0;
	for (int i=1; i<sizeA; i++){
		isteps += abs(pathA[i].x-pathA[i-1].x) + abs(pathA[i].y-pathA[i-1].y);
		int jsteps = 0;
		for (int j=1; j<sizeB; j++){
			jsteps += abs(pathB[j].x-pathB[j-1].x) + abs(pathB[j].y-pathB[j-1].y);
			struct point* intersect = findIntersection(pathA[i-1],pathA[i],pathB[j-1],pathB[j]);
			if (intersect != NULL) {
				int distance = abs(intersect -> x) + abs(intersect -> y);
				if (minDistance == 0 || distance < minDistance){
					minDistance = distance;
				}

				if (!(i==1 && j==1) && minSteps == 0 || (isteps+jsteps) < minSteps){
					int distA = abs(pathA[i].x - intersect -> x) + abs(pathA[i].y - intersect -> y);
					int distB = abs(pathB[j].x - intersect -> x) + abs(pathB[j].y - intersect -> y);
					minSteps = isteps + jsteps - distA - distB;
				}
			}

		}
	}

	printf("The distance to the shortest intersection is: %d\n",minDistance);
	printf("The minimum number of steps to an intersection is: %d\n",minSteps);
}

struct point* getPath(char* str, int* size){
	struct point* path = malloc((*size)*sizeof(struct point));
	path[0].x = 0;
	path[0].y = 0;

	int count = 1;
	char* token = strtok(str,",");
	while(token) {
		if (token[0] == 'R') {
			path[count].x = path[count-1].x + atoi(token+1);
			path[count].y = path[count-1].y;
		} else if (token[0] == 'L') {
			path[count].x = path[count-1].x - atoi(token+1);
			path[count].y = path[count-1].y;
		} else if (token[0] == 'U') {
			path[count].x = path[count-1].x;
			path[count].y = path[count-1].y + atoi(token+1);
		} else if (token[0] == 'D') {
			path[count].x = path[count-1].x;
			path[count].y = path[count-1].y - atoi(token+1);
		}

		count++;
		token = strtok(NULL,",");
	}

	*size = count;

	struct point* shortPath = malloc(count*sizeof(struct point));
	for(int i=0; i<count; i++){
		shortPath[i] = path[i];
	}

	free(path);
	return shortPath;
}

struct point* findIntersection(struct point p1a, struct point p1b, struct point p2a, struct point p2b){
	// if both lines are vertical, x coordinates must match,
	// and y coords must overlap in range. Return the lowest (abs) intersecting y value
	if (isVertical(p1a,p1b) && isVertical(p2a,p2b)){
		if (p1a.x == p2a.x) {
			int upper = max(p2a.y,p2b.y);
			int lower = min(p2a.y,p2b.y);
			if ((p1a.y >= lower && p1a.y <= upper) || (p2a.y >= lower && p2a.y <= upper)) {
				int arr[4] = {p1a.y,p1b.y,p2a.y,p2b.y};
				sortLowToHigh(arr,4);

				struct point* intersect = malloc(sizeof(struct point));
				intersect -> x = p1a.x;
				if (abs(arr[1]) < abs(arr[2])){
					intersect -> y = arr[1];
				} else {
					intersect -> y = arr[2];
				}

				return intersect;
			}
		}
		return NULL;
	}
	// if neither line is vertical, y coordinates must match,
	// and x coords must overlap in range. Return the lowest (abs) intersecting x value
	if (!isVertical(p1a,p1b) && !isVertical(p2a,p2b)){
		if (p1a.y == p2a.y) {
			int upper = max(p2a.x,p2b.x);
			int lower = min(p2a.x,p2b.x);
			if ((p1a.x >= lower && p1a.x <= upper) || (p2a.x >= lower && p2a.x <= upper)) {
				int arr[4] = {p1a.x,p1b.x,p2a.x,p2b.x};
				sortLowToHigh(arr,4);

				struct point* intersect = malloc(sizeof(struct point));
				intersect -> y = p1a.y;
				if (abs(arr[1]) < abs(arr[2])){
					intersect -> x = arr[1];
				} else {
					intersect -> x = arr[2];
				}

				return intersect;
			}
		}
		return NULL;
	}

	// if one line is vertical, x coord of that line must be within the x coords of the horizontal line
	// and y coord of horizontal line must be within y coords of vertical line
	if (isVertical(p1a,p1b)){
		if(p1a.x >= min(p2a.x,p2b.x) && p1a.x <= max(p2a.x,p2b.x)){
			if (p2a.y >= min(p1a.y,p1b.y) && p2a.y <= max(p1a.y,p1b.y)){
				struct point* intersect = malloc(sizeof(struct point));
				intersect -> x = p1a.x;
				intersect -> y = p2a.y;
				return intersect;
			}
		}
	} else {
		if(p1a.y >= min(p2a.y,p2b.y) && p1a.y <= max(p2a.y,p2b.y)){
			if (p2a.x >= min(p1a.x,p1b.x) && p2a.x <= max(p1a.x,p1b.x)){
				struct point* intersect = malloc(sizeof(struct point));
				intersect -> x = p2a.x;
				intersect -> y = p1a.y;
				return intersect;
			}
		}
	}

	return NULL;
}

void printPoint(struct point p){
	printf("{%d,%d}\n",p.x,p.y);
}

_Bool isVertical(struct point p1, struct point p2){
	return (p1.x == p2.x);
}

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

void sortLowToHigh(int* arr, int size){
	int count;
	do {
		count = 0;
		for (int i=0; i<size-1; i++){
			if (arr[i] > arr[i+1]) {
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				count++;
			}
		}
	} while(count > 0);
}
