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
boolean ten_ms = false;
int ten_to_50 = 0;
int fifty_to_100;

//variables for manipulating LED colors
float inc_a = 1;
float inc_b = 2;
float inc_c = 4;
float fader_color[3] = {
  0,0,0};
int orb_a = 0;
int orb_b = 7;

// state
int state = IDLE;
int start_pour_ms = 0;
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

uint8_t drink_idx[8] = {
  IDX_VODKA, IDX_RUM, IDX_WHISKEY, IDX_GIN, IDX_OJ, IDX_LIME, IDX_COKE, IDX_GB };

#define VAL_TO_MS   64

// Global variables
unsigned char mStart;
unsigned char mCommand;
unsigned char mEnd;
unsigned char mRecipe[8];

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void clearStartStopEnd()
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

  clearStartStopEnd();

  Serial.begin(9600);

  pinMode(PIN_VODKA,   OUTPUT);
  pinMode(PIN_RUM,     OUTPUT);
  pinMode(PIN_WHISKEY, OUTPUT);
  pinMode(PIN_OJ,      OUTPUT);
  pinMode(PIN_GIN,      OUTPUT);
  pinMode(PIN_LIME,    OUTPUT);
  pinMode(PIN_COKE,    OUTPUT);
  pinMode(PIN_GB,      OUTPUT);

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop() // run over and over
{
  // Serial.
  //digitalWrite( 13, HIGH );   // set the LED on

  // -------------------------------------------
  //              Make my drink!!
  // -------------------------------------------

  if(ten_ms){
    ten_ms = false;
    //state = WAITING_ORDER;
  }
  if(ten_to_50 > 5){
    ten_to_50 = 0;
    fifty_to_100++;

    switch(state){
    case IDLE:
      update_fader();
      state = WAITING_ORDER;
      break;
    case WAITING_ORDER:
      if(fifty_to_100 > 2){
        fifty_to_100 = 0;
        update_orbs(COUNTER); // Initialize orb_a at 0 and orb_b at 4 if switching to the other modes
      case POURING:
        int i;
         boolean done = true;
         // turn on pumps that need to pour, turn off pumps that are done
        for (i = 0; i < 8; i++){
          if((millis() - start_pour_ms) < mRecipe[drink_idx[i]]){
            digitalWrite(drink_pins[i], HIGH);
            done = false;
          }
          else if((millis() - start_pour_ms) >= mRecipe[drink_idx[i]]){
            digitalWrite(drink_pins[i], LOW);
          }
        }
        if (done){
          state = COMPLETE;}
        // jsut in case we need to debug; delete me later
        //        if((millis() - start_pour_ms) < mRecipe[IDX_VODKA])
        //          digitalWrite(PIN_VODKA, HIGH);
        //        else if((millis() - start_pour_ms) >= mRecipe[IDX_VODKA])
        //          digitalWrite(PIN_VODKA, LOW);
        //
        //
        //
        //        digitalWrite(PIN_WHISKEY, HIGH);
        //        delay(whiskeyDelay);
        //        digitalWrite(PIN_WHISKEY, LOW);
        //
        //        digitalWrite(PIN_OJ, HIGH);
        //        delay(ojDelay);
        //        digitalWrite(PIN_OJ, LOW);
        //
        //        digitalWrite(PIN_TS, HIGH);
        //        delay(tsDelay);
        //        digitalWrite(PIN_TS, LOW);
        //
        //        digitalWrite(PIN_LIME, HIGH);
        //        delay(limeDelay);
        //        digitalWrite(PIN_LIME, LOW);
        //
        //        digitalWrite(PIN_COKE, HIGH);
        //        delay(cokeDelay);
        //        digitalWrite(PIN_COKE, LOW);
        //
        //        digitalWrite(PIN_GB, HIGH);
        //        delay(gbDelay);
        //        digitalWrite(PIN_GB, LOW);


      }
      break;
    case COMPLETE:
      write this later, just switch states for now
     state = IDLE; 
      break;
    }
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
        clearStartStopEnd();
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

        clearStartStopEnd();

        break;

      case RECIPE:
        if (state != WAITING_ORDER)
        {
          sendNack();
          clearStartStopEnd();         
        }
        else
        {    
          //Serial.write(START);
          //Serial.write(ACK);
          //Serial.write(END);

          //clearStartStopEnd();

          if (Serial.available() >= 9)
          {
            mRecipe[IDX_VODKA]   = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_RUM]     = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_WHISKEY] = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_OJ]      = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_GIN]     = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_LIME]    = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_COKE]    = ((uint16_t)Serial.read())*VAL_TO_MS;
            mRecipe[IDX_GB]      = ((uint16_t)Serial.read())*VAL_TO_MS;
            mEnd                 = ((uint16_t)Serial.read())*VAL_TO_MS;

            if (mEnd == END)
            {
              sendAck();
            }
            else
            {
              sendNack();
            }

            clearStartStopEnd();

          }
        }
        state = POURING;
        start_pour_ms = millis();
        break;

      default: // Unknown command
        clearStartStopEnd();
        Serial.flush();         
        break;
      }
    } 
  }
}

void timerIsr()
{
  ten_ms = true;
  ten_to_50++;
}







