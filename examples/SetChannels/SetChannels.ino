#include "Arduino.h"
#include "SPI.h"
#include "Streaming.h"
#include "TLE72X.h"

const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;
const int CS_PIN = 49;
const int IC_COUNT = 2;
// IC_COUNT is the number of power switch IC chips connected in a
// daisy chain on the pcb. There are 8 power switch channels per IC.

// Setting SPI_RESET to true causes the SPI parameters to be reset
// every time before a command is issued over SPI. It could cause
// slight delays and should only be used when you are also
// communicating with other SPI devices with different SPI parameters
const bool SPI_RESET = false;

// Instantiate TLE72X
TLE72X power_switch = TLE72X(CS_PIN);

int channel_count;
uint32_t channels;
uint32_t bit;

void setup()
{
  // Setup serial communications
  Serial.begin(BAUDRATE);

  power_switch.setup(IC_COUNT,SPI_RESET);
  channel_count = power_switch.getChannelCount();
}

void loop()
{
  for (int channel = -1; channel < channel_count; channel++)
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
