#include "filter.h"

static int len; // length of the filter
static int head; // an index/pointer that refers to the most recent field updated with a new value

static double avg; // the average value (which is the result of the filter)
static double data[100]; // stores data
static double weights[100]; // stores the distribution of data

void filter_init(){
    len = 100; //sample size (100 by default)

    //cleaned up
    double totalWeights = len;
    for (int i = 0; i < len; i++){
        data[i] = 0;
	    weights[i] = 1 / totalWeights;
    }

    avg = 0;
    head = 0;
}


int filter_addData(double input){
    // if the data array is null, return immediately with error
    if (data == NULL) {
        return -1;
    }

    //re-evaluate averages and cycle head such that only 100 (len) values are considered in the filter
    avg = avg + ((input - data[head])/len);
    data[head] = input;
    head++;
    if (head == len) {
        head = 0;
    }
    return 0;
}

int filter_noWeight(){
    return 1;
}

double filter_getData(){
    return avg;
}

double filter_getGauss(){
    double gauss = 0;
    int head_copy = head;
    for (int i = 0; i < len; i++){
        gauss += weights[i] * data[head_copy];
        head_copy++;
        if(head_copy == len)
        head_copy = 0;
    }
    return gauss;
}