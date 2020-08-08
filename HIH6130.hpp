#ifndef HIH6130_HPP
#define HIH6130_HPP

#include <string>

using namespace std;

const unsigned char WR_BUFFER_SIZE = 1;
const unsigned char RD_BUFFER_SIZE = 4;

class HIH6130
{
    private:
        int fd;
        bool is_open;
        bool is_connected;
        unsigned char writeBuffer[WR_BUFFER_SIZE];
        unsigned char readBuffer [RD_BUFFER_SIZE];
        double temperature;
        double humidity;
        void setTemperature();
        void setHumidity();
    
    public:
        HIH6130(string device, unsigned int address = 0x27U);
        ~HIH6130();
        bool getMeasurement();
        double getTemperature() const;
        double getHumidity() const;
};

ostream& operator<<(ostream& output, HIH6130 const& self)
{
  output << '(' << self.getTemperature() << ", " << self.getHumidity() << ')';
  return output;
}

#endif /* HIH6130_HPP */
