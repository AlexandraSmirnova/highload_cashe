#include <fstream>
#include <vector>
#ifndef GNUPLOT_H
#define GNUPLOT_H

using namespace std;

 class Gnuplot
{
    public:
        Gnuplot(const char*);
        virtual ~Gnuplot();

        void printDataToFile(vector<size_t>, vector<double>,  const char*);
        void createScript(vector<const char*>, vector<const char*>,  size_t, size_t, size_t);
        void runScript();
    private:
        const char* script;
};

#endif // GNUPLOT_H
