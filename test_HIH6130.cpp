#include "HIH6130.hpp"
#include <iostream>

ostream& operator<<(ostream& output, HIH6130 const& self)
{
  output << '(' << self.getTemperature() << ", " << self.getHumidity() << ')';
  return output;
}

int main()
{
    HIH6130 mySensor("/dev/i2c-1");
    (void)mySensor.getMeasurement();
    std::cout << "Temperature:\t" << mySensor.getTemperature() << " °C"  << std::endl;
    std::cout << "Humidity:\t"    << mySensor.getHumidity()    << " %RH" << std::endl;
    std::cout << mySensor << std::endl;
    return 0;
}
