/*

 * PR_CNC.h
 *
 *  Created on: 10 de may. de 2017
 *      Author: santi
 */

#ifndef PR_CNC_H_
#define PR_CNC_H_


#define M1_STEP 54
#define M1_DIR  55
#define M1_ENA  38

#define M2_STEP 60
#define M2_DIR  61
#define M2_ENA  56

// limit switches
#define SWITCH1 3
#define SWITCH2 14


#define ARC_CW          1
#define ARC_CCW         -1
// Arcs are split into many line segments.  How long are the segments?
#define MM_PER_SEGMENT  10

#define MAX_BUF        64  // What is the longest message Arduino can store?
#define STEPS_PER_TURN 400  // depends on your stepper motor.  most are 200.
#define MIN_STEP_DELAY 50
#define MAX_FEEDRATE   (1000000/MIN_STEP_DELAY)
#define MIN_FEEDRATE   0.01


uint8_t  	buffer[MAX_BUF];  	// Donde se almacenan las lineas hasta que llega una nueva
uint16_t   	sofar;      // lineas en el buffer
uint32_t 	px, py;		// posición

// velocidades
uint32_t 	fr = 0; 	 	// human version
uint32_t 	step_delay;		// machine version

uint8_t 	mode_abs=1;	   	// Modo de desplazamiento


/**
 * First thing this machine does on startup.  Runs only once.
 */
void setup() {
  Serial.begin(BAUD);  	// inicia comunicación
  setup_controller();	//inicializacion
  position(0,0);  		// ubicacion de comienzo
  feedrate((MAX_FEEDRATE + MIN_FEEDRATE)/2);  // velocidad por default

  help();
  ready();
}


/**
 * After setup() this machine will repeat loop() forever.
 */
void loop() {
  while(Serial.available() > 0) {
    char c = Serial.read();
    if(sofar<MAX_BUF-1) buffer[sofar++]=c;  // store it
    if((c=='\n') || (c == '\r')) {
      // entire message received
      buffer[sofar]=0;  // end the buffer so string functions work right
      processCommand();  // do something with the command
      ready();
    }
  }
}

/**
 * Set the logical position
 * @input npx new position x
 * @input npy new position y
 */
void position(float npx,float npy) {
  // here is a good place to add sanity tests
  px=npx;
  py=npy;
}

/**
 * prepares the input buffer to receive a new message and tells the serial connected device it is ready for more.
 */
void ready() {
  sofar=0;  // clear input buffer
  Serial.print(F(">"));  // signal ready to receive input
}

void pause(long ms) {
  delay(ms/1000);
  delayMicroseconds(ms%1000);  // delayMicroseconds doesn't work for values > ~16k.
}

/**
 * Read the input buffer and find any recognized commands.  One G or M command per line.
 */
void processCommand() {
  int cmd = parsenumber('G',-1);
  switch(cmd) {
  case  0:
  case  1: { // line
    feedrate(parsenumber('F',fr));
    line( parsenumber('X',(mode_abs?px:0)) + (mode_abs?0:px),
          parsenumber('Y',(mode_abs?py:0)) + (mode_abs?0:py) );
    break;
    }
  case 2:
  case 3: {  // arc
      feedrate(parsenumber('F',fr));
      arc(parsenumber('I',(mode_abs?px:0)) + (mode_abs?0:px),
          parsenumber('J',(mode_abs?py:0)) + (mode_abs?0:py),
          parsenumber('X',(mode_abs?px:0)) + (mode_abs?0:px),
          parsenumber('Y',(mode_abs?py:0)) + (mode_abs?0:py),
          (cmd==2) ? -1 : 1);
      break;
    }
  case  4:  pause(parsenumber('P',0)*1000);  break;  // dwell
  case 90:  mode_abs=1;  break;  // absolute mode
  case 91:  mode_abs=0;  break;  // relative mode
  case 92:  // set logical position
    position( parsenumber('X',0),
              parsenumber('Y',0) );
    break;
  default:  break;
  }

  cmd = parsenumber('M',-1);
  switch(cmd) {
  case 18:  // disable motors
    disable();
    break;
  case 100:  help();  break;
  case 114:  where();  break;
  default:  break;
  }
}


/**
 * Look for character /code/ in the buffer and read the float that immediately follows it.
 * @return the value found.  If nothing is found, /val/ is returned.
 * @input code the character to look for.
 * @input val the return value if /code/ is not found.
 **/
float parsenumber(uint8_t code,uint16_t val) {
  uint8_t *ptr=buffer;

  while(ptr>1 && *ptr && ptr<buffer+sofar) {
    if(*ptr==code) {
      return atof(ptr+1);     	//   <----------------------------------------------
    }
    ptr=strchr(ptr,' ');		//   <----------------------------------------------
  }
  return val;
}

/**
 * Set the feedrate (speed motors will move)
 * @input nfr the new speed in steps/second
 */
void feedrate(float nfr) {
  if(fr==nfr) return;  // same as last time?  quit now.

  if(nfr>MAX_FEEDRATE || nfr<MIN_FEEDRATE) {  // don't allow crazy feed rates
//    Serial.print(F("New feedrate must be greater than "));
//    Serial.print(MIN_FEEDRATE);
//    Serial.print(F("steps/s and less than "));		//   <----------------------------------------------
//    Serial.print(MAX_FEEDRATE);
//    Serial.println(F("steps/s."));
    return;
  }
  step_delay = 1000000/nfr;
  fr = nfr;
}

/**
 * Uses bresenham's line algorithm to move both motors
 * @input newx the destination x position
 * @input newy the destination y position
 **/
void line(uint16_t newx,uint16_t newy) {
  uint16_t i;
  uint16_t over= 0;

  uint16_t dx  = newx-px;
  uint16_t dy  = newy-py;
  uint16_t dirx = dx>0?1:-1;
  uint16_t diry = dy>0?-1:1;  // because the motors are mounted in opposite directions

  dx = abs(dx);
  dy = abs(dy);

  if(dx>dy) {
    over = dx/2;
    for(i=0; i<dx; ++i) {
      m1step(dirx);
      over += dy;
      if(over>=dx) {
        over -= dx;
        m2step(diry);
      }
      pause(step_delay);
    }
  } else {
    over = dy/2;
    for(i=0; i<dy; ++i) {
      m2step(diry);
      over += dx;
      if(over >= dy) {
        over -= dy;
        m1step(dirx);
      }
      pause(step_delay);
    }
  }

  px = newx;
  py = newy;
}


// returns angle of dy/dx as a value from 0...2PI
uint16_t atan3(uint16_t dy,uint16_t dx) {
  uint16_t a = atan2(dy,dx);
  if(a<0) a = (PI*2)+a;
  return a;
}


// This method assumes the limits have already been checked.
// This method assumes the start and end radius match.
// This method assumes arcs are not >180 degrees (PI radians)
// cx/cy - center of circle
// x/y - end position
// dir - ARC_CW or ARC_CCW to control direction of arc
void arc(float cx,float cy,float x,float y,float dir) {
  // get radius
  float dx = px - cx;
  float dy = py - cy;
  float radius=sqrt(dx*dx+dy*dy);

  // find angle of arc (sweep)
  float angle1=atan3(dy,dx);
  float angle2=atan3(y-cy,x-cx);
  float theta=angle2-angle1;

  if(dir>0 && theta<0) angle2+=2*PI;
  else if(dir<0 && theta>0) angle1+=2*PI;

  theta=angle2-angle1;

  // get length of arc
  // float circ=PI*2.0*radius;
  // float len=theta*circ/(PI*2.0);
  // simplifies to
  float len = abs(theta) * radius;

  int i, segments = ceil( len * MM_PER_SEGMENT );

  float nx, ny, angle3, scale;

  for(i=0;i<segments;++i) {
    // interpolate around the arc
    scale = ((float)i)/((float)segments);

    angle3 = ( theta * scale ) + angle1;
    nx = cx + cos(angle3) * radius;
    ny = cy + sin(angle3) * radius;
    // send it to the planner
    line(nx,ny);
  }

  line(x,y);
}


/**
 * write a string followed by a float to the serial line.  Convenient for debugging.
 * @input code the string.
 * @input val the float.
 */
void output(const char *code,float val) {
  Serial.print(code);
  Serial.println(val);
}


/**
 * print the current position, feedrate, and absolute mode.
 */
void where() {
  output("X",px);
  output("Y",py);
  output("F",fr);
  Serial.println(mode_abs?"ABS":"REL");
}


/**
 * display helpful information
 */
void help() {
  Serial.print(F("GcodeCNCDemo2AxisV1 "));
  Serial.println(VERSION);
  Serial.println(F("Commands:"));
  Serial.println(F("G00 [X(steps)] [Y(steps)] [F(feedrate)]; - line"));
  Serial.println(F("G01 [X(steps)] [Y(steps)] [F(feedrate)]; - line"));
  Serial.println(F("G02 [X(steps)] [Y(steps)] [I(steps)] [J(steps)] [F(feedrate)]; - clockwise arc"));
  Serial.println(F("G03 [X(steps)] [Y(steps)] [I(steps)] [J(steps)] [F(feedrate)]; - counter-clockwise arc"));
  Serial.println(F("G04 P[seconds]; - delay"));
  Serial.println(F("G90; - absolute mode"));
  Serial.println(F("G91; - relative mode"));
  Serial.println(F("G92 [X(steps)] [Y(steps)]; - change logical position"));
  Serial.println(F("M18; - disable motors"));
  Serial.println(F("M100; - this help message"));
  Serial.println(F("M114; - report position and feedrate"));
  Serial.println(F("All commands must end with a newline."));
}


#endif /* PR_CNC_H_ */
