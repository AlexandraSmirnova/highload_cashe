#include "Gnuplot.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>

using namespace std;

Gnuplot::Gnuplot(const char* file) : script(file)
{
}


Gnuplot::~Gnuplot()
{
}

void Gnuplot::createScript(vector<const char*> path_files, vector<const char*> titles, size_t max_x, size_t max_y, size_t min_x)
{
    fstream fp;
    fp.open(script);
    fp << "set terminal x11 size 1360, 700" << endl;
    fp << "set title 'Result'" << endl;
    fp << "set xlabel 'X'" << endl;
    fp << "set ylabel 'Y'" << endl;
    fp << "set xrange ["<< min_x <<":" << max_x << "]" << endl;
    fp << "set yrange [0.0:" << max_y << "]" << endl;
    fp << "set logscale x" << endl;
    fp << "set grid" << endl;
    for(unsigned int i = 0; i < path_files.size() ; i++ )
    {
        fp << "plot \'" << path_files[i] << "\' using 1:2 w l lw 2 title \'" << titles[i] << "\'";
        if(i < path_files.size()-1)
            fp << ",\\";
        fp << endl;
    }
    fp << "pause -1" << endl;
    fp.close();

}

void Gnuplot::runScript()
{
    char* str = new char(strlen("gnuplot ") + strlen(script));

    strcpy(str, "gnuplot ");
    strcat(str, script);
    system(str);

    delete str;
}


void Gnuplot::printDataToFile(vector<size_t> dataX, vector<double> dataY, const char* dataFile)
{
        fstream fp;
        fp.open(dataFile);

        cout  << dataFile << endl;
        for(unsigned int i = 0; i < dataY.size() ; i++)
        {

            fp << dataX[i] << " " << dataY[i] << endl;
            cout << dataX[i] << " " << dataY[i] << endl;
        }
        fp.close();
}


