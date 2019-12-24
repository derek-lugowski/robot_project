

void right_turn(int time, int speed);
void left_turn(int time, int speed);

void drive_forward(int time, int speed);
void drive_backward(int time, int speed);

void fright_turn(int time, int speed);
void fleft_turn(int time, int speed);

void sright_turn(int time, int speed);
void sleft_turn(int time, int speed);

void servo_control(int time, int speedL, int speedR);

void servo_control(int time, int speedL, int speedR){
  servo_speed(12, speedL); //left
  servo_speed(13, -1*speedR); //right
  pause(time);
}  

void fright_turn(int time, int speed)
{
  servo_speed(12, speed);
  servo_speed(13, speed);
  pause(time);
}

void fleft_turn(int time, int speed)
{
  servo_speed(12, -1*speed);
  servo_speed(13, -1*speed);
  pause(time);
}

void right_turn(int time, int speed){
  servo_speed(12, speed);
  servo_speed(13, 0);
  pause(time);
}  
void left_turn(int time, int speed){
  servo_speed(12, 0);
  servo_speed(13, speed*(-1));
  pause(time);
}  
void sright_turn(int time, int speed){
  servo_speed(12, speed);
  servo_speed(13, speed/4);
  pause(time);
}
void sleft_turn(int time, int speed){
  servo_speed(12, (-1)*speed/4);
  servo_speed(13, speed*(-1));
  pause(time);
}

void drive_forward(int time, int speed){
  servo_speed(12, speed); //left
  servo_speed(13, -1*speed); //right
  pause(time);
}  
void drive_backward(int time, int speed){
  servo_speed(12, -1*speed);
  servo_speed(13, speed);
  pause(time);
} 
