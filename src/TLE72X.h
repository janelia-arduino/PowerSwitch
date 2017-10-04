// ----------------------------------------------------------------------------
// TLE72X.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef TLE72X_H
#define TLE72X_H
#include <Arduino.h>
#include <SPI.h>


class TLE72X
{
public:
  TLE72X();
  TLE72X(const size_t cs_pin, const int reset_pin=-1);

  void setup(const size_t ic_count=1);

  static void usingInterrupt(const IRQ_NUMBER_t interrupt_number);
  static void notUsingInterrupt(const IRQ_NUMBER_t interrupt_number);

  void setChannels(const uint32_t channels);
  void setChannelOn(const size_t channel);
  void setChannelOff(const size_t channel);
  void setChannelsOn(const uint32_t channels);
  void setChannelsOff(const uint32_t channels);
  void toggleChannel(const size_t channel);
  void toggleChannels(const uint32_t channels);
  void toggleAllChannels();
  void setAllChannelsOn();
  void setAllChannelsOff();
  void setChannelOnAllOthersOff(const size_t channel);
  void setChannelOffAllOthersOn(const size_t channel);
  void setChannelsOnAllOthersOff(const uint32_t channels);
  void setChannelsOffAllOthersOn(const uint32_t channels);
  uint32_t getChannelsOn();
  size_t getChannelCount();
  void reset();
  void setChannelsMap(const uint32_t channels);
  void setChannelMapTrue(const size_t channel);
  void setChannelMapFalse(const size_t channel);
  void setAllChannelsMapTrue();
  void setAllChannelsMapFalse();
  void setChannelsBoolean(const uint32_t bool_state);
  void setChannelBooleanAnd(const size_t channel);
  void setChannelBooleanOr(const size_t channel);
  void setAllChannelsBooleanAnd();
  void setAllChannelsBooleanOr();

private:
  const static uint32_t spi_clock_ = 4000000;
  const static uint8_t spi_bit_order_ = MSBFIRST;
  const static uint8_t spi_mode_ = SPI_MODE1;
  const static size_t IC_COUNT_MIN = 1;
  const static size_t IC_COUNT_MAX = 4;

  const static size_t CHANNEL_COUNT_PER_IC = 8;
  const static size_t CHANNEL_COUNT_MAX = 32;

  const static size_t RESET_DELAY = 200;

  const static byte CMD_DIAGNOSIS = 0b11<<6;
  const static byte CMD_READ = 0b01<<6;
  const static byte CMD_RESET = 0b10<<6;
  const static byte CMD_WRITE = 0b11<<6;

  const static byte ADDR_MAP = 0b001; // Input Mapping Register
  const static byte ADDR_BOL = 0b010; // Boolean Operation Register
  const static byte ADDR_OVL = 0b011; // Overload Behavior Register
  const static byte ADDR_OVT = 0b100; // Overtemperature Behavior Register
  const static byte ADDR_SLE = 0b101; // Switching Speed / Slew Rate Register
  const static byte ADDR_STA = 0b110; // Output State Register
  const static byte ADDR_CTL = 0b111; // Serial Output Control Register

  size_t cs_pin_;
  int reset_pin_;
  boolean initialized_;
  uint32_t channels_;
  uint32_t mapped_;
  uint32_t bool_state_;
  size_t ic_count_;

};

#endif