#include "robotdriver/motioncontroller.h"
#include "robotdriver/speedcontroller.h"
#include "robotdriver/headingcontroller.h"
#include "robotdriver/motordriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sliceNumber = 0;
double angle = 0;
char uselessStr[20];


void turnGalette(struct motionElement * element) {
	setTargetHeading(angle, NULL);
}
void returnToStart() {
	queueSpeedChange(-0.3, NULL);
	queueStopAt(0, NULL);
}

void giveSlice() {
	static int slices[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
	int randomNum = rand() % sliceNumber;
	printf("lol\n" );
	queueSpeedChange(0.3, NULL);
	queueStopAt(300, turnGalette);

	while(slices[randomNum]) {
		randomNum = rand() % sliceNumber;
	}
	slices[randomNum] = 1;
	angle = 360.0*randomNum/sliceNumber;

	printf("Presser ENTRER pour finir ...");
	fflush(stdin);
	uselessStr[0] = getchar();
	setTargetHeading(0, returnToStart);
}

int main() {
	int remainingSlices;

	time_t t;
	srand((unsigned) time(&t));

	// initialize the motion controller
	initMotionController();
	// reset robot distance
	setRobotDistance(0);
	setRobotHeading(0);
	fastSpeedChange(0);

	// get the number of slices
	while(sliceNumber < 1 || sliceNumber > 16) {
		printf("Nombre de parts dans la galette ? ");
		scanf("%d", &sliceNumber);
		printf("\n");
	}
	remainingSlices = sliceNumber;

	uselessStr[0] = getchar();
	while(remainingSlices > 0) {
		fflush(stdin);
		printf("Presser ENTRER pour distribuer une part ...");
		uselessStr[0] = getchar();
		giveSlice();
		remainingSlices--;
	}
	return 0;
}
