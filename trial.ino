#define ULTO_SERVO 10
#include <Servo.h>
Servo s[12];
int servopos[12];
#define HIP_NEUTRAL 90
#define KNEE_NEUTRAL 90
#define KNEE_UP 120

void setLeg(int legnum, int hippos, int kneepos)
{
  if (legnum % 6 > 2){
    hippos = 180 - hippos;
  }
  if (legnum*2 == ULTO_SERVO){
    hippos = 180 - hippos;
  }
  
  s[legnum*2+1].write(kneepos);//first raises or lowers knee then moves hip
  s[legnum*2].write(hippos);
  servopos[legnum*2] = hippos;
  servopos[legnum*2+1] = kneepos;
}


void tripod_gait(int offset, int hip_forward, int hip_backward, int knee_up , int knee_down=KNEE_NEUTRAL, int dela=200)
{
  offset = offset * 2;
  /*for offset values:
   * 0:forward
   * 1:right forward
   * 2:right backward
   * 3:backward
   * 4:left backward
   * 5:left forward
   */

  //tripod0 up and then forward in air or just forward in air
  setLeg(0+offset, HIP_NEUTRAL, knee_up);
  setLeg(2+offset, hip_forward, knee_up);
  setLeg(4+offset, hip_forward, knee_up);
  delay(dela);
  
  //tripod1 backward in ground
  setLeg(1+offset, hip_backward, knee_down);
  setLeg(3+offset, HIP_NEUTRAL, knee_down);
  setLeg(5+offset, hip_backward, knee_down);
  delay(dela);
  
  //setting tripod0 leg down
  setLeg(0+offset, HIP_NEUTRAL, knee_down);
  setLeg(2+offset, hip_forward, knee_down);
  setLeg(4+offset, hip_forward, knee_down);
  delay(dela);
  
  //lifting tripod1
  setLeg(1+offset, hip_backward, knee_up);
  setLeg(3+offset, HIP_NEUTRAL, knee_up);
  setLeg(5+offset, hip_backward, knee_up);
  delay(dela);

  //tripod1 forward in air
  setLeg(1+offset, hip_forward, knee_up);
  setLeg(3+offset, hip_forward, knee_up);
  setLeg(5+offset, HIP_NEUTRAL, knee_up);
  delay(dela);
 
  //tripod0 backward in ground
  setLeg(0+offset, hip_backward, knee_down);
  setLeg(2+offset, HIP_NEUTRAL, knee_down);
  setLeg(4+offset, hip_backward, knee_down);
  delay(dela);
  
  //set tripod1 down 
  setLeg(1+offset, hip_forward, knee_down);
  setLeg(3+offset, hip_forward, knee_down);
  setLeg(5+offset, HIP_NEUTRAL, knee_down);
  delay(dela);

  //set tripod0 up
  setLeg(0+offset, hip_backward, knee_up);
  setLeg(2+offset, HIP_NEUTRAL, knee_up);
  setLeg(4+offset, hip_backward, knee_up);
  delay(dela);
  
}

void side_ways(int offset, int hip_forward=160, int hip_backward=50, int knee_up=130, int knee_down=KNEE_NEUTRAL, int ld=70)
{
  static int  phase = 0;
  switch(phase
  setLeg(0+offset, HIP_NEUTRAL, knee_up);
  setLeg(2+offset, hip_forward, knee_up);
  setLeg(4+offset, hip_forward, knee_up);
  delay(ld);

  ///down
  setLeg(0+offset, HIP_NEUTRAL, knee_down);
  setLeg(2+offset, hip_forward, knee_down);
  setLeg(4+offset, hip_forward, knee_down);
  delay(ld);
  
  ///next set of legs up
  setLeg(1+offset, HIP_NEUTRAL, knee_up);
  setLeg(3+offset, HIP_NEUTRAL, knee_up);
  setLeg(5+offset, HIP_NEUTRAL, knee_up);
  delay(ld);
  ///
  setLeg(2+offset ,HIP_NEUTRAL , knee_down);
  setLeg(4+offset, HIP_NEUTRAL, knee_down);
  delay(ld);
  
  setLeg(1+offset, hip_forward, knee_up);
  setLeg(5+offset, hip_forward, knee_up);
  delay(ld);
  ///

  setLeg(1+offset, hip_forward, knee_down);
  setLeg(3+offset, HIP_NEUTRAL, knee_down);
  setLeg(5+offset, hip_forward, knee_down);
  delay(ld);
  
  setLeg(1+offset, HIP_NEUTRAL, knee_down);
  setLeg(3+offset, HIP_NEUTRAL, knee_down);
  setLeg(5+offset, HIP_NEUTRAL, knee_down);
  delay(ld);
  phase++;
}


void turn(bool dir, int hip_forward, int hip_backward, int knee_up, int knee_down=KNEE_NEUTRAL, int dela=200, int offset = 0)
{
  //dir False:anticlockwise
  //dir True:clockwise
  if (dir == false)
  {
    hip_forward = 180 - hip_forward;
    hip_backward = 180 - hip_backward;
  }

 

      //lift tripod0 up and set hips  clockwise
      setLeg(0+offset, hip_backward, knee_up);
      setLeg(2+offset, hip_backward, knee_up);
      setLeg(4+offset, hip_forward, knee_up);
      delay(dela);
    
      //move tripod1 anti clockwise at hips in ground
      setLeg(1+offset, hip_forward, knee_down);
      setLeg(3+offset, hip_backward, knee_down);
      setLeg(5+offset, hip_backward, knee_down);
      delay(dela);
    
      //set tripod0 down
      setLeg(0+offset, hip_backward, knee_down);
      setLeg(2+offset, hip_backward, knee_down);
      setLeg(4+offset, hip_forward, knee_down);
      delay(dela);
    
      //lift tripod 1 and move it cw at hips
      setLeg(1+offset, hip_backward, knee_up);
      setLeg(3+offset, hip_forward, knee_up);
      setLeg(5+offset, hip_forward, knee_up);
      delay(dela);
    
      //move lowered tripod0 anti cw at hips
      setLeg(0+offset, hip_forward, knee_down);
      setLeg(2+offset, hip_forward, knee_down);
      setLeg(4+offset, hip_backward, knee_down);
      delay(dela);
      
}

void set_legs_to_initial_position()
{
  for(int i = 0; i<6; i++)
  {
    if (servopos[i*2]  != 90)//if hips are not in proper position first lift knee then fix hips which is done autpmatically by setLeg
    {
      setLeg(i, HIP_NEUTRAL, KNEE_UP);
      setLeg(i, HIP_NEUTRAL, KNEE_NEUTRAL);
      continue;
    }
    setLeg(i, HIP_NEUTRAL, KNEE_NEUTRAL);//if code reaches here knee is up but leg is alright
  }
}

void initialize()
{
  for (int i = 0; i<12; i++)
  {
    s[i].write(90);
    servopos[i] = 90;
  }
}
void setup() {
 
  // put your setup code here, to run once:
  for(int i = 0; i< 12; i++)
  {
    s[i].attach(i+2);
  }
  initialize();
  delay(3000);
  Serial.begin(9600); 
}
char c;
void loop() 
{
 
  if (Serial.available()>0)
  {
    int offset;
    
   q:  c = Serial.read();
  /*/  if ( c == a )
    {
      goto q;
    }*/
    
    switch(c)
    {
      case 'B':
        offset = 0;

        tripod_gait(offset, 130, 50, 130 , 90, 100);
        
        break;
      case 'F':
        offset = 0;
         tripod_gait(offset, 130, 50, 130 , 90, 100);
        break;
      case 'L':
         side_ways(4);
         break;
      case 'R':
        side_ways(1);
        break;
      case 'G':
        offset = 5;
         tripod_gait(offset, 130, 50, 130 , 90, 100);
        break;
      case 'I':
        offset = 1;
         tripod_gait(offset, 130, 50, 130 , 90, 100);
        break;
      case 'H':
        offset = 3;
         tripod_gait(offset, 130, 50, 130 , 90, 100);
        break;
      case 'J':
        offset = 2;
         tripod_gait(offset, 130, 50, 130 , 90, 100);
        break;
      case 'S':
        set_legs_to_initial_position();
        break;  
    }
   
   
  }

}
