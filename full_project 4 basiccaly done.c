// Full project code

// Derek Lugowski
// Josh Valiquette
// Morgan Grona
// Leo Rogers


// ~~~ INCLUDED FILES ~~~

#include <stdio.h>
#include <stdlib.h>
#include "simpletools.h"
#include "adcDCpropab.h"
#include "servo.h"
#include "wavplayer.h"
#include "ourping.h"
#include "drive.h"
//#include "ourfunctions.h" // for any of our functions that we create.




// ~~~ MACROS ~~~

#define VOLUME 8                      // volume macro for the speaker
#define FAST_LIGHTS 200
#define SLOW_LIGHTS 700

#define F3 175
#define C4 261
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define NN 100000

/* #define C3 131
#define D3 147
#define E3 165
#define B2 123
#define A2 110
*/

#define Z1 13
#define Z2 12
#define Z3 10



// ~~~ FUNCTION PROTOTYPES ~~~

void light_pattern_scared();
void avoid();
void shake();
void forward_dart();
void button_test();
void angry_sound();
void scared_sound();
void tickle_tail();
void happy_sound();
void fun_sound();

void Gocry();
void look();


// ~~~ GLOBAL VARIABLES ~~~
// volatile data can be accessed from any cog that is running.
  volatile int red_light = 11;//pin              //set the pin for the red light.
  volatile int yellow_light = 14;//pin           //set the pin for the yellow light.
  volatile int green_light = 15;//pin             // set the pin for the green light
  volatile int light_timing = 700;           // 700 for regular scared 400 for triggered scared.
 
  int sense_right = 6;//pin           IR sense right
  int sense_left = 7;//pin            IR sense left
  int sense_back = 3;//pin            IR sense back
  int flex_resistor = 0;//pin
  int IR_out = 5;//pin                IR out pin
 
 int moe = 0;
 int seen = 0;
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  volatile int emotion_counter = 0;//          select emotion: 0 = scared, 1 = ?, 2 = ?, 3 = ?
  int moo = 1;
  int trigger_light_level; //                    light level to trigger reaction
  int light_sensor = 3;//pin
  int button_pin = 0;//pin            0V not pressed (5V pressed)
  int sound_out = 4;//pin             Piezo speaker pin
  int trigger_pin = 8;//pin           this is the pin for trigger on the ultrasonic range finder.
  int echo_pin = 9;//pin              echo pin for the ultrasonic range finder
  volatile int angry_light = 0;
  int trigger_distance = 8; // distance in inches for something in front of robot to trigger reaction
 // int sad_notes[] = { E3, NN, NN, NN, NN, D3, NN, NN, NN, NN, C3, NN, NN, NN, NN, NN, NN, NN, NN, B2,  NN, NN, NN, NN, NN, NN, NN, NN, NN, NN, A2};
   int sad_notes[] = {Z1, Z1, NN, NN, NN, NN, NN, NN, Z2, Z2, NN, NN, NN, NN, NN, NN, NN, Z3, Z3};
  
  
  
// ~~~ MAIN FUNCTION ~~~

int main()
{
  
  // ~~~ INITIALIZERS AND SUCH ~~~
  
  adc_init(21, 20, 19, 18);         // Initilize analogue to digital converter. This has to be done once if you want to use the A/D converter.
  //sd_mount(22, 23, 24, 25);         // Mount sd card with sound files
  //wav_volume(VOLUME);                 // Set volume of speaker
  drive_forward(0, 0);          //set servo speed to be zero
  servo_setramp(12, 4);               //set ramp speeds for servos
  servo_setramp(13, 4);
  trigger_light_level = adc_in(light_sensor) - 500;  //         light level to trigger sensor
  
  

  
  
  // ~~~ LOCAL VARIABLES FOR MAIN ~~~
  
  
////////////////////////////////////////////////////////////////////////  int tail_resistance_level;
  int *sound_cog;
  
  
  int tail_resistance_level = 1900;
  
  
  
  int startup_loop[] = {C4, E4, G4, E4, C4, E4, G4, E4, C4, E4, G4, E4, C4, C4};
  int i = 0;
  // ~~~ STARTUP OTHER COGS ~~~
  
   cog_run(light_pattern_scared, 64);
   cog_run(button_test, 256);
   //cog_end(light_pattern_cog); // this is how you would end a cog that is running
  
  
  
  
  
  // ~~~ WHILE LOOP FOR MAIN ~~~
  for(i = 0; i<14; i++)
  {
    freqout(sound_out, 100, startup_loop[i]);
    pause(10);
  }    
  while(1)
  {
    pause(100);
    //putChar(HOME);
    print("emotion counter is: %d\n", emotion_counter);
    switch(emotion_counter)
    {
      case 0: //scared
        drive_forward(10, 20);
        if(ping_inches(trigger_pin, echo_pin) < trigger_distance){   //checking if something in front
          avoid();  // function to avoid an object in front of robot   
        }
        
        
        if(adc_in(light_sensor) < trigger_light_level)
        {
          sound_cog = cog_run(scared_sound, 32);
          shake();  // function to shake robot in fear
          cog_end(sound_cog);
        }
        
        tail_resistance_level = adc_in(flex_resistor);
        if(tail_resistance_level < 1950 || tail_resistance_level > 2200)
        {
          forward_dart();  //function to dart forward to avoid tail touching
        }  
        break;
       
      case 1:
        drive_forward(10, 20);
        tail_resistance_level = adc_in(flex_resistor);
        if(ping_inches(trigger_pin, echo_pin) < trigger_distance )   //checking if something in front
          {
          angry_light = 1;
          sound_cog = cog_run(angry_sound, 32);
          forward_dart();
          cog_end(sound_cog);
          }
        freqout(IR_out, 1, 38000);
        if (input(sense_right) != 1 )
          {
          angry_light = 1;
          sound_cog = cog_run(angry_sound, 32);
          fright_turn(600,100);
          forward_dart();
          cog_end(sound_cog);
          
         }
        freqout(IR_out, 1, 38000);
        if(input(sense_left) != 1 )
          {
          angry_light = 1;
          sound_cog = cog_run(angry_sound, 32);
          fleft_turn(600,100);
          forward_dart();
          cog_end(sound_cog);
          }
          tail_resistance_level = adc_in(flex_resistor);
          freqout(IR_out, 1, 38000);
        if(input(sense_back) != 1   || tail_resistance_level < 1950 || tail_resistance_level > 2200)
          {
          angry_light = 1;
          sound_cog = cog_run(angry_sound, 32);
          fright_turn(1100,170);
          forward_dart();
          cog_end(sound_cog);
          }                        
          angry_light = 0;
        break;
       
      case 2:
          	drive_forward(700, 30);
	         
          if(moe == 5)
          { 
          moe = 0;
            drive_forward(1, 0); 
            pause(10); 
           fright_turn(500, 50*moo);      // look left           time / speed
           look();
	          fright_turn(1000, -50*moo);      // look right
           look();
           fright_turn(500, 50*moo);      // look left
         }           
         moe ++;
	          look();
        
        break;
        
        
      case 3:
      drive_forward(10, 60);
        tail_resistance_level = adc_in(flex_resistor);
        if(tail_resistance_level < 1950 || tail_resistance_level > 2200)
        {
        sound_cog = cog_run(fun_sound, 256);
        tickle_tail();
        cog_end(sound_cog);
        }  
        
        if(ping_inches(trigger_pin, echo_pin) < trigger_distance)
        {   
        happy_sound();
        fleft_turn(2000, 100);
        }
        break;
        
        
        
      case 4: //love
        servo_control(10, 20, 50); // time = 10ms, left servo speed = 20, right servo speed = 50
        
        while(ping_inches(trigger_pin, echo_pin) < 12)
          {
            high(red_light);
            drive_forward(100, 40);
            if(ping_inches(trigger_pin, echo_pin) < 2)
            {
              drive_forward(0,0);
              for(i = 600; i < 850; i++)
                freqout(sound_out, 1, i*15);
              for(i= 850; i> 600; i--)
                freqout(sound_out, 1, i*17);
            }              
            while(ping_inches(trigger_pin, echo_pin) < 2)
              drive_forward(50, 0);
          }            
        
        freqout(IR_out, 1, 38000);
        if(input(sense_right) != 1)
        {
          high(red_light);
          left_turn(2000, -60);        
        }          
        if(input(sense_left) != 1)
        {
          high(red_light);
          right_turn(2000, -60);
        }          
        if(input(sense_back) != 1)
        {
          high(red_light);
          fleft_turn(1900, 60);
        }          
        low(red_light);
        
      break;
      
      default:
        emotion_counter = 0;
    }      
    
  }
}



// ~~~ FUNCTION DEFINITIONS ~~~

void light_pattern_scared()
{
  while(1)
  {
    switch(emotion_counter)
    {
      case 0:
       high(red_light);
       high(yellow_light);
       high(green_light);
       pause(100);
       low(red_light);
       low(yellow_light);
       low(green_light);
       pause(100);
       high(red_light);
       high(yellow_light);
       high(green_light);
       pause(100);
       low(red_light);
       low(yellow_light);
       low(green_light);
       pause(light_timing);
       break;
       
      case 1:
       high(red_light);
       while (angry_light)
       {
         pause(100);
         low(red_light);
         pause(100);
         high(red_light);
         pause(100);
         pause(100);
         low(red_light);
         pause(100);
         high(red_light);
         pause(100);
       }  
        low(red_light);       
      break;
      
      case 2:
      break;
      
      case 3:
      pause(5000);
      freqout(sound_out, 100, C4);
      pause(200);
      freqout(sound_out, 50, C4);
      pause(200);
      freqout(sound_out, 100, F4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 100, F4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 100, F4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 50, E4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 150, G4);
      pause(3000);
      /*freqout(sound_out, 50, C4);
      freqout(sound_out, 50, C4);
      freqout(sound_out, 50, C4);
      freqout(sound_out, 50, C4);
      freqout(sound_out, 50, C4);
      freqout(sound_out, 50, C4);
      freqout(sound_out, 50, C4);
      */
      
      break;
      case 4:
      break;
   }     
  }    
}

void avoid() //scared
{
  light_timing = FAST_LIGHTS;
  fright_turn(1500, 100);      // 180deg turn
  drive_forward(3000, 100);     // run away approx 3 sec
  drive_forward(1, 0);          //stop
  light_timing = SLOW_LIGHTS;
}  


void shake()// scared
{
  light_timing = FAST_LIGHTS; 
  servo_setramp(12, 100);
  servo_setramp(13,100);
  while(adc_in(light_sensor) < trigger_light_level)
  {
    fright_turn(20, 20);
    fleft_turn(40, 20);

  }  
  servo_setramp(12, 4);
  servo_setramp(13, 4);  
  light_timing = SLOW_LIGHTS;
}  

void forward_dart() //scared
{
  light_timing = FAST_LIGHTS;

  drive_forward(2000, 100); // dart forward for approx 2 seconds
  drive_forward(1, 0);      // stop
  light_timing = SLOW_LIGHTS;
}  


void button_test() // cog run
{
  pause(1000);
  while(1)
  {
    pause(10);
    if(input(button_pin) == 1)
    {
      emotion_counter ++;
      freqout(sound_out, 500, C4);
      while(input(button_pin) == 1)
        pause(100);
    }
  }      
}  

void angry_sound() //angry
{
  while(1)
  {
    freqout( sound_out, 200,C4);
    pause(25);
    freqout(sound_out, 200, F3);
    pause(25);
  }
}      

void scared_sound() // scared
{
  for(int i = 100; i<700; i++)
  {
    freqout(sound_out, 1, i*10);
  }    
  
}  

/// MORGANS --------------------

 void look() // sad
{	
  seen = 0;
  high(green_light);

        freqout(IR_out, 1, 38000);
        if (input(sense_right) != 1 )
          {
            fright_turn(1200,50);
            seen = 1;
         }           
        else if(input(sense_left) != 1 )
        {
          fleft_turn(1200,50);
           seen = 1;
         } 
        else if(input(sense_back) != 1 )
        {
          fright_turn(1200,100);
          seen = 1;
        }          

	      if (seen == 1) 
          drive_forward(100, -10); // drive BACKWARDS
          
       if (ping_inches(trigger_pin, echo_pin) < trigger_distance || seen == 1)   //checking if something in front
		Gocry();
 
	low(green_light);
}
	
 void Gocry() //sad
{
	drive_forward(1, 0); 
	drive_forward(300, -10); // drive BACKWARDS
 
 while(ping_inches(trigger_pin, echo_pin) < (trigger_distance / (trigger_distance * 4)) );  //checking if something in front
		for(int i = 0, n = 31 ; i < n ; i++ ) 
		  freqout(sound_out, 100, sad_notes[i]);
 drive_forward(1, 0);          //stop
  pause(50);
  fright_turn(4800, 25*moo);    // turn around
  pause(50);
   drive_forward(200, 30);
  for(int i = 0, n = 31 ; i < n ; i++ ) 
		  freqout(sound_out, 100, sad_notes[i]);

        if(moo>0) 
          moo = -1;
        else
          moo = 1;
}

/// NOT MORGNS  -----------------------
/// Leo -------------------------------
void tickle_tail() //happy
{
  high(red_light);
  freqout(sound_out, 150, A4);
  high(yellow_light);
  freqout(sound_out, 150, B4);
  high(green_light);
  freqout(sound_out, 300, C5);
  low(red_light);
  freqout(sound_out, 150, A4);
  low(yellow_light);
  freqout(sound_out, 150, B4);
  low(green_light);
  freqout(sound_out, 150, C5);
  servo_speed(12, 0);
  servo_speed(13, 0);
  pause(500);
  fright_turn(300, 100);
  high(red_light);
  freqout(sound_out, 150, A4);
  high(yellow_light);
  freqout(sound_out, 150, B4);
  high(green_light);
  freqout(sound_out, 300, C5);
  low(red_light);
  freqout(sound_out, 150, A4);
  low(yellow_light);
  freqout(sound_out, 150, B4);
  low(green_light);
  freqout(sound_out, 150, C5);
}  

void happy_sound() // happy
{ 
  high(red_light);
  freqout(sound_out, 150, A4);
  high(yellow_light);
  freqout(sound_out, 150, B4);
  high(green_light);
  freqout(sound_out, 150, C5);
  low(red_light);
  pause(50);
  low(yellow_light);
  pause(50);
  low(green_light);
  
}  
void fun_sound()
{
  freqout(sound_out, 100, C4);
      pause(200);
      freqout(sound_out, 50, C4);
      pause(200);
      freqout(sound_out, 100, F4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 100, F4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 100, F4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 50, E4);
      pause(200);
      freqout(sound_out, 50, F4);
      pause(200);
      freqout(sound_out, 150, G4);
    }      
// Not leo