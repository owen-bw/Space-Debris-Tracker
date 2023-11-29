#include <string>

using namespace std;

struct location {
    double x;
    double y;
    double z;
};

class Debris {
    string id;
    int epochYear;
    float epochDay;
    float inclination;
    float rightAscension;
    float eccentricity;
    

    public:
    location GetLocation(int month, int day, int year, int hour, int minutes, int seconds);
};