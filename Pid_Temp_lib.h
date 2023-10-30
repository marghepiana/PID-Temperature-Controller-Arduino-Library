#ifndef PID_Temp_lib
#define PID_Temp_lib
//This header file create the PID class, since this will be inserted in the arduino library as a 
//PID temperature controller.

#if (ARDUINO >= 100)
  #include <Arduino.h>
#endif

class PIDLIB{
    public:

        //Constructor
         PIDLIB();

        //setting different values

        void set_init(int Setp);
        void tune_values(double KP, double KI, double KD);
        double get_output();
        int get_relay_state();
        int get_setpoint();
        int Get_user_input();

        //funtion that does all the work 
        void control(float * input );
        void Relay_control(float * input, int RELAY_PIN);
        void leakage_detector(int * humid);

    private:

    double error_present, lasterror, sum_of_errors, prev_time, KI, KP,KD,  MIN,MAX, final_output, newoutput, error_deriv;
    int Relay_state, RELAY_PIN;
    int *input;
    int prev_input;
    int prevhumid;
    int size_window;
    int window_start;
    int setpoint;
    
};

#endif
