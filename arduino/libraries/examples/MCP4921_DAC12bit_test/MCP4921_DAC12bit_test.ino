/*
  MCP4921_DAC12bit_test.ino - Arduino Library Example sketch for the Microchip 
                     MCP4921 12-Bit Voltage Output Digital-to-Analog Converter
                     with Internal VREF and SPI Interface.
  Created by Craig Wm. Versek, 2013-05-29
  Released into the public domain.
*/

#include <SPI.h>
#include <MCP4921_DAC12bit.h>

#define V_REF 3.29
#define V_MIN -V_REF/2.0
#define V_MAX  V_REF/2.0
#define NUM_STEPS 20
#define DELAY_ms 2000

//configure the DAC chip
MCP4921_DAC12bitClass voltageDAC(3,  //slaveSelectLowPin
                                 3,   //ldacLowPin
                                 V_REF/2.0 //reference voltage
                                );


void setup() {
  Serial.begin(9600);
  //start up the SPI bus                   
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  //start controlling the voltage supply
  voltageDAC.begin();
}

void loop() {
  float voltage_step = (V_MAX - V_MIN)/NUM_STEPS;
  float voltage = V_MIN; 
  for (int i=0; i <= NUM_STEPS; i++){
    voltage = V_MIN + voltage_step*i;
    voltageDAC.setVoltageOutput(voltage + V_REF/2.0);
    Serial.print("voltage = ");      
    Serial.println(voltage);
    while (Serial.read() != '\n'){};
  }  
}
