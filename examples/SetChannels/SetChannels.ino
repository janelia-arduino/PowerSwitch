#include <Arduino.h>
#include <SPI.h>
#include <Streaming.h>
#include <TLE72X.h>


const long BAUDRATE = 115200;
const size_t LOOP_DELAY = 1000;
const size_t CS_PIN = 10;
const size_t ENABLE_PIN = 3;
const size_t RESET_PIN = 2;
const size_t IC_COUNT = 1;
// IC_COUNT is the number of power switch IC chips connected in a
// daisy chain on the pcb. There are 8 power switch channels per IC.

// Instantiate TLE72X
TLE72X power_switch = TLE72X(CS_PIN,RESET_PIN);

int channel_count;
uint32_t channels;
uint32_t bit;

void setup()
{
  // Setup serial communications
  Serial.begin(BAUDRATE);

  power_switch.setup(IC_COUNT);

  channel_count = power_switch.getChannelCount();

  pinMode(ENABLE_PIN,OUTPUT);
  digitalWrite(ENABLE_PIN,HIGH);
}

void loop()
{
  for (int channel = -1; channel < channel_count; ++channel)
  {
    if (0 <= channel)
    {
      bit = 1;
      bit = bit << channel;
      channels = channels | bit;
    }
    else
    {
      channels = 0;
    }
    power_switch.setChannels(channels);
    Serial << "channels = " << _BIN(channels) << endl;
    delay(LOOP_DELAY);
  }
}
