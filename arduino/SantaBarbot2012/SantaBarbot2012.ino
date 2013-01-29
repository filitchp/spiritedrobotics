#include <SoftwareSerial.h>
#include <TimerOne.h>
#include <SPI.h>
#include <TCL.h>

//constants 
#define LEDS 25
enum states { 
  IDLE, WAITING_ORDER, POURING, COMPLETE };
  
enum led_modes {
  FORWARD, BACKWARD, COUNTER};

//cheap timer scalers
boolean hz100 = false;
int ten_to_50 = 0;
int fifty_to_100;

//variables for manipulating LED colors
float inc_a = 1;
float inc_b = 2;
float inc_c = 4;
float fader_color[3] = {0,0,0};
int orb_a = 0;
int orb_b = 7;
int debugRGB[3] = {64,128,255};

// state
int state = WAITING_ORDER;
unsigned long startPourMS = 0;

// -----------------------
// Communication
// -----------------------
// Basic
#define START    0xFE
#define END      0xFD
// Query
#define READY    0x01
#define RECIPE   0x10
// Response
#define ACK      0x0F
#define NACK     0xF0

// Pins
#define PIN_VODKA    2
#define PIN_RUM      3
#define PIN_WHISKEY  4
#define PIN_GIN      5
#define PIN_OJ       6
#define PIN_LIME     7
#define PIN_COKE     8
#define PIN_GB       9
#define PIN_PHOTO_INT 10 

//just for convienence
uint8_t drink_pins[8] = {
  PIN_VODKA, PIN_RUM, PIN_WHISKEY, PIN_GIN, PIN_OJ, PIN_LIME, PIN_COKE, PIN_GB };

// Indeces
#define IDX_VODKA    0
#define IDX_RUM      1
#define IDX_WHISKEY  2
#define IDX_GIN      3
#define IDX_OJ       4
#define IDX_LIME     5
#define IDX_COKE     6
#define IDX_GB       7

//uint8_t drink_idx[8] = {
//  IDX_VODKA, IDX_RUM, IDX_WHISKEY, IDX_GIN, IDX_OJ, IDX_LIME, IDX_COKE, IDX_GB };

// This value sets the maximum each pump can pour to 6 oz (mRecipe[i] = 0xFC -> 6 oz)
#define VAL_TO_MS   90

// Global variables
unsigned char mStart;
unsigned char mCommand;
unsigned char mEnd;
uint16_t mRecipe[8];

// Current ingredient
unsigned char mCur = 0;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void red()
{
  debugRGB[0] = 255;
  debugRGB[1] = 0;
  debugRGB[2] = 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void green()
{
  debugRGB[0] = 0;
  debugRGB[1] = 255;
  debugRGB[2] = 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void blue()
{
  debugRGB[0] = 0;
  debugRGB[1] = 0;
  debugRGB[2] = 255;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void white()
{
  debugRGB[0] = 255;
  debugRGB[1] = 255;
  debugRGB[2] = 255;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void clearStartCmdEnd()
{
  mStart = 0;
  mCommand = 0;
  mEnd = 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void sendAck()
{
  Serial.write(START);
  Serial.write(ACK);
  Serial.write(END);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void sendNack()
{
  Serial.write(START);
  Serial.write(NACK);
  Serial.write(END);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup()  
{  

  TCL.begin(); // LED Chain library
  update_fader(); // Update the colors along the strand of LEDs
  Timer1.initialize(10000); // set a timer of length 10000 microseconds  (10ms)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine

  clearStartCmdEnd();

  Serial.begin(9600);

  pinMode(PIN_VODKA,   OUTPUT);
  pinMode(PIN_RUM,     OUTPUT);
  pinMode(PIN_WHISKEY, OUTPUT);
  pinMode(PIN_OJ,      OUTPUT);
  pinMode(PIN_GIN,     OUTPUT);
  pinMode(PIN_LIME,    OUTPUT);
  pinMode(PIN_COKE,    OUTPUT);
  pinMode(PIN_GB,      OUTPUT);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop() // run over and over
{

  boolean hz20 = false;
  boolean hz10 = false;
  
  if (hz100)
  {
    hz100 = false;
  }
  
  if (ten_to_50 > 5)
  {
    ten_to_50 = 0;
    hz20 = true;
    fifty_to_100++;
    if (fifty_to_100 > 2)
    {
      fifty_to_100 = 0;
      hz10 = true;
    }
  }
  
  switch(state)
  {
    case IDLE:
      state = WAITING_ORDER;
      
      if(hz20)
      {
        update_fader();
      }
      blue();
      break;
      
    case WAITING_ORDER:
    
      if(hz10)
      {
        update_orbs(COUNTER); 
      }
      
      green();
      break;
      
    // -------------------------------------------
    //              Make my drink!!
    // -------------------------------------------
    case POURING:
      
      boolean done;
      done = true;
      
      if(hz10)
      {
        update_lit(); 
      }
      red();
      
      // Sequential operation
      if (mCur < 8)
      {
        done = false;
        if((millis() - startPourMS) < ((unsigned long)mRecipe[mCur]))
        {
          // Turn on pump / keep pumping
          digitalWrite(drink_pins[mCur], HIGH);
        }
        else
        {
          // Turn off pump
          digitalWrite(drink_pins[mCur], LOW);
          
          // Advance to next pump
          mCur++;
          startPourMS = millis();
        }
      }
      else
      {
        done = true;
        mCur = 0; 
      }
      
      // Simultaneous operation
      /*
      unsigned char i;
      for (i = 0; i < 8; i++)
      {
        // turn on pumps that need to pour, turn off pumps that are done
        if((millis() - startPourMS) < ((unsigned long)mRecipe[i]))
        {
          // Turn on pump
          digitalWrite(drink_pins[i], HIGH);
          done = false;
        }
        else
        {
          // Turn off pump
          digitalWrite(drink_pins[i], LOW);
        }
      }
      */
  
      if (done)
      {
        state = WAITING_ORDER;
      }
  
      break;
      
    //case COMPLETE:
      // write this later, just switch states for now
    //  state = IDLE; 
    //  debugRGB[1] = 0;
    //  break;
  }

  // -------------------------------------------
  //              Communication
  // -------------------------------------------
  // Do not have a start byte
  if (!mStart)
  {
    if (Serial.available())
    {
      // read the incoming byte:
      mStart = Serial.read();

      if (mStart != START)
      {
        // Not actually a valid start byte...
        mStart = 0x00;
      }
    }
  }

  // Have a start byte but NOT a command
  if (mStart && !mCommand)
  {
    if (Serial.available())
    {
      mCommand = Serial.read();

      switch (mCommand)
      {
        // These are valid commands, keep going...
      case READY:
      case RECIPE:
        break;
      default: // Unknown command
        clearStartCmdEnd();
        Serial.flush();         
        break;
      }
    }
  }

  // Have a start byte AND a command
  if (mStart && mCommand)
  {
    if (Serial.available())
    {
      // The following byte is determined by the command
      switch (mCommand)
      {       
        case READY:
          // Read end byte
          mEnd = Serial.read();
  
          // Verify end byte and reply
          if (mEnd == END)
          {
            // Recipe in progress, send NACK
            if (state != WAITING_ORDER)
            {
              sendNack();
            }
            else
            {
              sendAck();
            }
          }
  
          clearStartCmdEnd();
          break;

        case RECIPE:
          if (state != WAITING_ORDER)
          {
            sendNack();
            clearStartCmdEnd();
            Serial.flush(); // Flush because we likely got a recipe
          }
          else
          {    
            
            if (Serial.available() >= 9)
            {
              // Read recipe
              mRecipe[IDX_VODKA]   = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_RUM]     = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_WHISKEY] = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_GIN]     = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_OJ]      = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_LIME]    = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_COKE]    = ((uint16_t)Serial.read())*VAL_TO_MS;
              mRecipe[IDX_GB]      = ((uint16_t)Serial.read())*VAL_TO_MS;
              
              mEnd = Serial.read();
  
              if (mEnd == END)
              {
                sendAck();
                
                state = POURING;
                startPourMS = millis();
              }
              else
              {
                sendNack();
              }
  
              clearStartCmdEnd();
              Serial.flush(); // Flush just in case...
            }
          }
          break;

        default: // Unknown command
          clearStartCmdEnd();
          Serial.flush();
          break;
      }
    } 
  }
}

void timerIsr()
{
  hz100 = true;
  ten_to_50++;
}













