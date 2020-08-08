#ifndef HIH6130_HPP
#define HIH6130_HPP

#include <string>

using namespace std;

class HIH6130
{
    private:
        int fd;
        bool is_open;
        bool is_connected;
        double temperature;
        double humidity;
    
    public:
        HIH6130(string device, unsigned int address);
        ~HIH6130();
        double getTemperature() const;
        double getHumity() const;
};

#endif /* HIH6130_HPP */
