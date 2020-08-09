#ifndef HIH6130_HPP
#define HIH6130_HPP

#include <string>

const unsigned char WR_BUFFER_SIZE = 1U;
const unsigned char RD_BUFFER_SIZE = 4U;

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
        HIH6130(std::string device, unsigned int address = 0x27U);
        ~HIH6130();
        bool getMeasurement();
        double getTemperature() const;
        double getHumidity() const;
};

std::ostream& operator<<(std::ostream& output, HIH6130 const& sensor);

#endif /* HIH6130_HPP */
