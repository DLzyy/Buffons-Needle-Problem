#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define PI 3.1415926535897931L
#define FREQUENCY (long double)intersectionCount/(long double)totalTimes

enum{DOWN, UP};

long double needleLength; // 针的长度
long double parallelLineSpacing; // 平行线间距

unsigned int targetTimes; // 目标次数
unsigned int totalTimes; // 总次数
unsigned int intersectionCount; // 相交次数

unsigned int ThrowNeedle(void); //投一次针， 返回交点数量
long double CalculatePI(); // 计算圆周率


int main(int argc, char *argv[]) {
    if (argc == 1) {
        needleLength = 1.0L;
        parallelLineSpacing = 1.5L;
        targetTimes = 5000U;
    }
    else if (argc == 4) {
        needleLength = atof(*++argv);
        parallelLineSpacing = atof(*++argv);
        targetTimes = atoi(*++argv);
        if (needleLength >= parallelLineSpacing) {
            printf("The length of the needle must be less than the spacing of parallel lines.");
            return 1;
        }
    }
    else {
        printf("Usage: needle [Length of the needle, Spacing of parallel lines, Total number of times]");
        return 1;
    }
    srand((unsigned int)time(NULL));
    printf("Throwing:\n");
    for (totalTimes = 0; totalTimes < targetTimes; totalTimes++) {
        intersectionCount += ThrowNeedle();
    }
    printf("\n");
    printf("The length of the needle: %.2f\n", needleLength);
    printf("The spacing of the parallel lines: %.2f\n", parallelLineSpacing);
    printf("Total number of times: %u\n", totalTimes);
    printf("Number of the intersection: %u\n", intersectionCount);
    printf("Frequency: %f\n", FREQUENCY);
    printf("PI: %f\n", CalculatePI());
    return 0;
}

unsigned int ThrowNeedle(void) {
    long double endpoint[2], midpoint, angle, height;
    bool direction, intersection = false;

    //随机生成针
    midpoint = (long double)rand() * (long double)rand() / 1000000.0L;
    angle = (long double)(rand() * rand() % 36000000) / 100000.0L;
    direction = angle > 180.0L ? DOWN : UP;
    angle = angle > 180.0L ? angle-180.0L : angle;
    height = sin(PI/180.0L*angle) * needleLength;
    endpoint[0] = midpoint - (height / 2.0L);
    endpoint[1] = midpoint + (height  / 2.0L);

    //计算交点数
    for (long double i = 0; i <= endpoint[1]; i += parallelLineSpacing) {
        if (i >= endpoint[0] && i <= endpoint[1])
            intersection = true;
    }

    //输出
    printf("Midpoint: %7.2f   ", midpoint);
    printf("Angle: %7.2f   ", direction ? angle : -angle);
    printf("Height: %4.2f   ", height);
    printf("Endpoint: %7.2f %7.2f   ", endpoint[0], endpoint[1]);
    printf("Intersection: %s\n", intersection ? "Yes" : "No");

    return (unsigned int) intersection;
}

long double CalculatePI() {
    return (2.0L * needleLength) / (parallelLineSpacing * FREQUENCY);
}
