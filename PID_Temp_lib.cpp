#include "PID_Temp_lib.h"


PIDLIB:: PIDLIB(){
 
     prevhumid=0;

     KP=1;
     KI=1;
     KD=1;
     MIN=0;
     MAX=255;
    window_start=millis();
    size_window=5000;
    newoutput=0;
    prev_input=0;
    unsigned long prev_time= millis();

}

void PIDLIB:: tune_values (double Kp, double Ki, double Kd) //this function will allow the user to tune the PID controller
{
    KP=Kp;
    KI=Ki;
    KD=Kd;
}

int PIDLIB:: Get_user_input()
{
    while (Serial.available() == 0) {
  }

return Serial.parseInt();

}

void PIDLIB:: set_init(int Setp) //this public function allows the user to pick a desired Setpoint
{
   
    setpoint= Setp;
}

int PIDLIB:: get_setpoint()
{
  return setpoint;
}

double PIDLIB:: get_output(){
    return final_output;
}

int PIDLIB:: get_relay_state(){
    return Relay_state;
}

void PIDLIB:: control(float * input){
//in this function the output of the PID controller will be calculated
//first calculate time difference since last time, then the different errors needed for the P I and D will be calculated
//once the output signal is found it will be mapped to a value of zero or one to determine if the relay should be turned on or off

unsigned long current_time= millis();
double change_time= (double) (current_time - prev_time);

error_present= (double) setpoint- *input;
error_deriv= *input - prev_input;
sum_of_errors += error_present * change_time; 
double delta_error= (error_deriv - lasterror)/change_time;


double output =  (KP * error_present + KI * sum_of_errors - KD * delta_error) /1000 ;

final_output= output;
prev_time=current_time;
lasterror=error_deriv;

}


//This function contrls the relay basing itself not only on the current value of the temperature and the setpoint itself but it takes into account the output of the PID controller. If the output of the last it is less than -1 the system will getdhut down. This treshhold value used to determine when to shut of the relays was picked after several tests.
//This is mainly beacause the PID controler calculates the power that should be given to the heater but we are using a on off system so we need to know for wht value the heater should be kept on on for which it shoul get turned off.
//this code takes also in cosideration the build in cock so if the PID system for some reason does not behave correctly for a period of time, the heater after a set ampunt of time will get shut off automatically to avoid uncontroled overheating.
void PIDLIB::Relay_control(float * input, int RELAY_PIN)
{
 
   if (final_output<-1)// previously this value was 2
   {
      Relay_state=0;
   }
   else if (final_output==0)
   {
      if (millis() - window_start > size_window)
            { //time to shift the Relay Window
                window_start += size_window;
                }
          if (final_output < millis() - window_start ||*input < setpoint )
          {
            Relay_state=1;
          }
          else 
          {
            Relay_state=0;
            
          }
   }
    else {
      Relay_state=1;
   }

      if(*input >= setpoint || Relay_state==0)
      {
        digitalWrite(RELAY_PIN, LOW);
        //Serial.println("Relays OFF");
      }
      else if(*input < setpoint || Relay_state==1){
        digitalWrite(RELAY_PIN, HIGH);
        //Serial.println("Relays ON");
      }
      else {
        digitalWrite(RELAY_PIN, LOW);
        //Serial.println("Relays OFF");
  }
}
 void PIDLIB:: leakage_detector(int * humid)
 {
    int difference = *humid - prevhumid;

    if (difference >= 50)
    {
      Serial.println("Leakage detected");
    }
prevhumid= *humid;
 }
