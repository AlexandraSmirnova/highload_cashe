#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <Gnuplot.h>
#include <algorithm>
#include <vector>
#define NPAD 1
#define X10(a) a a a a a a a a a a
#define X100(a) X10(a) X10(a) X10(a) X10(a) X10(a) X10(a) X10(a) X10(a) X10(a) X10(a)

using namespace std;


struct List {
    struct List* next;
    size_t index[NPAD];
};


vector<int> getRandomArray(int size) {
    vector<int> index_arr(size);

    for(int i = 0 ; i < size; i ++) {
        index_arr[i]=i;
    }
    random_shuffle(index_arr.begin(), index_arr.end());
    return index_arr;
}


List** prepareArray(size_t size) {
    List** measureArray = new List*[size] ;

    measureArray[0] = new List;

    for(size_t i = 1 ; i < size; i++) {
        measureArray[i] = new List;
        measureArray[i-1]->next = measureArray[i];
    }
    measureArray[size - 1]->next = measureArray[0];

    return measureArray;
}


List** prepareArrayRand(size_t size) {
    List** measureArray = new List*[size] ;

    for(size_t i = 0 ; i < size; i++) {
        measureArray[i] = new List;
        measureArray[i]->next = NULL;
    }

    vector<int> randomIndexes = getRandomArray(size);
    int previos = randomIndexes[0];

    for (size_t i = 1; i < size ; ++i) {
        measureArray[previos] -> next= measureArray[randomIndexes[i]];
        previos = randomIndexes[i];
    }
    measureArray[previos] -> next= measureArray[randomIndexes[0]];

    return measureArray;
}


void deleteArray(List** Array, size_t size) {
    for(size_t i = 0; i < size; i++) {
        delete Array[i];
    }
    delete Array;
}


int main() {
    Gnuplot gnuplot("out/script.gt");
    vector<double> measuredTime;
    vector<size_t> sizesList;
    vector<const char*> dataFiles;
    vector<const char*> dataTitles;

    List **measureArr;
    List *head, *current;
    size_t size = 1024 / sizeof(List);
    size_t max_size = 1024;
    double multiplayer = 2;
    int countLoop = 10000;

    cout << "Size of List: " << sizeof(List) << endl;
    while(sizeof(List) * size / 1024 / 256 < max_size) {
        cout << "Size: " << size << endl;
        cout << "Size of all elements: " << size * sizeof(List) << endl;

        measureArr = prepareArray(size);
        head = measureArr[0];
        current = head;
        double resultTime = 0;

        clock_t start = clock();
        for(int j = 0 ; j < countLoop; j++) {
                X100(current = current->next;)
        }
        clock_t end = clock();
        resultTime = ((double) (end - start) * 1000000000 ) / ( countLoop  * 100 * CLOCKS_PER_SEC);
        cout << "Time: " << resultTime << endl;

        measuredTime.push_back(resultTime);
        sizesList.push_back(size * sizeof(List)/1024);

        deleteArray(measureArr, size);
        size = int (size * multiplayer);
    }
    dataFiles.push_back("out/dat.txt");
    dataTitles.push_back("Random acsess");
    gnuplot.createScript(dataFiles, dataTitles, sizesList[sizesList.size() - 1], measuredTime[measuredTime.size() - 1] * 1.2, sizesList[0] );
    gnuplot.printDataToFile(sizesList, measuredTime, dataFiles[0]);
    return 0;
}
