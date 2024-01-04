//this example from :https://www.woolseyworkshop.com/2018/06/20/blink-making-an-led-blink-on-a-raspberry-pi/
#include <pigpio.h> //liberary repo:https://github.com/joan2937/pigpio/blob/master/pigpio.c#L8826
#include <iostream>
#include <csignal>//https://github.com/GitMasterNikanjam/RaspberryPi_utility/wiki/csignal-Library
using namespace std;
const int Led=21; //BCM  
volatile sig_atomic_t signal_received=0;
void signalHandler(int signal)
{
        cout<<"signal received: "<<signal;
        signal_received=signal;
}
int main()
{
        if(gpioInitialise()==PI_INIT_FAILED)
        {
            cout<<"Error: Cannot intialize GPIO"<<endl;
        }
        else
        {
            gpioSetMode(Led,PI_OUTPUT);
            signal(SIGINT,signalHandler);
            cout<<"Press CTRL-C to exit"<<endl;
            while(!signal_received) 
            {
                gpioWrite(Led,PI_HIGH);
                time_sleep(2);
                gpioWrite(Led,PI_LOW);
                time_sleep(2);
            }
            gpioSetMode(Led,PI_INPUT);
            gpioTerminate();

        }
    return 0;
}