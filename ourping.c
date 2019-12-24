#include "simpletools.h"

int ping(int pinin, int pinout)
{
  low(pinin);
  pulse_out(pinin, 10);
  return pulse_in(pinout, 1);
}

int ping_cm(int pinin, int pinout)
{
  long tEcho = ping(pinin, pinout);
  int cmDist = tEcho / 58;
  return cmDist;
}

int ping_inches(int pinin, int pinout) 
{
  long tEcho = ping(pinin, pinout);
  int inDist = tEcho / 148;
  return inDist;
}
