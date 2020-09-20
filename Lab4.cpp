/** Simple Sysfs LED control program - written by Derek Molloy
*    simple OOP  struture for the Exploring Raspberry Pi
*
*    Editor: Richie Romero CastleBomber
*    COMP462 Lab 4
*/

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>         // for the microsecond sleep function
using namespace std;
#define GPIO         "/sys/class/gpio/"
#define FLASH_DELAY  1000000 // 1 second

class LED{
   private:                // the following is part of the implementation
      string gpioPath;     // private states
      int    gpioNumber;
      void writeSysfs(string path, string filename, string value);
   public:                 // part of the public interface
      LED(int gpioNumber); // the constructor -- create the object
      virtual void turnOn();
      virtual void turnOff();
      virtual void displayState();
      virtual ~LED();      // the destructor -- called automatically
};

LED::LED(int gpioNumber){  // constructor implementation
   this->gpioNumber = gpioNumber;
   gpioPath = string(GPIO "gpio") + to_string(gpioNumber) + string("/");
   writeSysfs(string(GPIO), "export", to_string(gpioNumber));
   usleep(100000);         // ensure GPIO is exported
   writeSysfs(gpioPath, "direction", "out");
}

// This implementation function is "hidden" outside of the class
void LED::writeSysfs(string path, string filename, string value){
   ofstream fs;
   fs.open((path+filename).c_str());
   fs << value;
   fs.close();
}

void LED::turnOn(){
   writeSysfs(gpioPath, "value", "1");
}

void LED::turnOff(){
   writeSysfs(gpioPath, "value", "0");
}

void LED::displayState(){
   ifstream fs;
   fs.open((gpioPath + "value").c_str());
   string line;
   cout << "The current LED state is ";
   while(getline(fs,line)) cout << line << endl;
   fs.close();
}

LED::~LED(){  // The destructor unexports the sysfs GPIO entries
   cout << "Destroying the LED with GPIO number " << gpioNumber << endl;
   writeSysfs(string(GPIO), "unexport", to_string(gpioNumber));
}

// 4 LEDs used to display 0-15 via binary representaion
int main(int argc, char* argv[]){
   cout << "Starting the makeLEDs program" << endl;
   LED led1(21), led2(6), led3(24), led4(4);          // create four LED objects
   cout << "Flashing the LEDs for X seconds" << endl;

   for(int counter=0; counter<=15; counter++){        // LEDs will alternate
     if(counter == 0){
       led1.turnOff();
       led2.turnOff();
       led3.turnOff();
       led4.turnOff();
     }else if(counter == 1){
       led1.turnOn();
       led2.turnOff();
       led3.turnOff();
       led4.turnOff();
     }else if(counter == 2){
       led1.turnOff();
       led2.turnOn();
       led3.turnOff();
       led4.turnOff();
     }else if(counter == 3){
       led1.turnOn();
       led2.turnOn();
       led3.turnOff();
       led4.turnOff();
     }else if(counter == 4){
       led1.turnOff();
       led2.turnOff();
       led3.turnOn();
       led4.turnOff();
     }else if(counter == 5){
       led1.turnOn();
       led2.turnOff();
       led3.turnOn();
       led4.turnOff();
     }else if(counter == 6){
       led1.turnOff();
       led2.turnOn();
       led3.turnOn();
       led4.turnOff();
     }else if(counter == 7){
       led1.turnOn();
       led2.turnOn();
       led3.turnOn();
       led4.turnOff();
     }else if(counter == 8){
       led1.turnOff();
       led2.turnOff();
       led3.turnOff();
       led4.turnOn();
     }else if(counter == 9){
       led1.turnOn();
       led2.turnOff();
       led3.turnOff();
       led4.turnOn();
     }else if(counter == 10){
       led1.turnOff();
       led2.turnOn();
       led3.turnOff();
       led4.turnOn();
     }else if(counter == 11){
       led1.turnOn();
       led2.turnOn();
       led3.turnOff();
       led4.turnOn();
     }else if(counter == 12){
       led1.turnOff();
       led2.turnOff();
       led3.turnOn();
       led4.turnOn();
     }else if(counter == 13){
       led1.turnOn();
       led2.turnOff();
       led3.turnOn();
       led4.turnOn();
     }else if(counter == 14){
       led1.turnOff();
       led2.turnOn();
       led3.turnOn();
       led4.turnOn();
     }else if(counter == 15){
       led1.turnOn();
       led2.turnOn();
       led3.turnOn();
       led4.turnOn();
     }
      usleep(FLASH_DELAY);         // sleep for 1s

   }
   led1.displayState();            // display final GPIO4 state
   led2.displayState();            // display final GPIO17 state
   led3.displayState();
   led4.displayState();
   cout << "Finished the makeLEDs program" << endl;
   return 0;
}
