#include "Arduino.h"
#include "QTouchADCduino.h"

void QTouchADCduinoClass::init()
{
#define CHARGE_DELAY  10 // time it takes for the capacitor to get charged/discharged in microseconds
#define TRANSFER_DELAY  5 // time it takes for the capacitors to exchange charge

#define ADMUX_MASK  0b00001111 // mask the mux bits in the ADMUX register
#define MUX_GND 0b00001111 // mux value for connecting the ADC unit internally to GND
#define MUX_REF_VCC 0b01000000 // value to set the ADC reference to Vcc

  // prepare the ADC unit for one-shot measurements
  // see the atmega328 datasheet for explanations of the registers and values
  ADMUX = 0b01000000; // Vcc as voltage reference (bits76), right adjustment (bit5), use ADC0 as input (bits3210)
  ADCSRA = 0b11000100; // enable ADC (bit7), initialize ADC (bit6), no autotrigger (bit5), don't clear int-flag  (bit4), no interrupt (bit3), clock div by 16@16Mhz=1MHz (bit210) ADC should run at 50kHz to 200kHz, 1MHz gives decreased resolution
  ADCSRB = 0b00000000; // autotrigger source free running (bits210) doesn't apply
  while(ADCSRA & (1<<ADSC)){  } // wait for first conversion to complete 
  
return;
}


uint16_t QTouchADCduinoClass::sense(byte ADCReadPin, byte ADCRef, int samples)
{   
    unsigned int adc1 = 0;
    unsigned int adc2 = 0;

for (int i=0; i<samples; i++) // Repeat the measurement between 1 - 60 times and average to reduce noise
  {
    uint8_t mask= _BV(ADCReadPin) | _BV(ADCRef);
  
  // First measurement  

    DDRC|= mask; // config pins as push-pull output
    // set partner high to charge the s&h cap and pin low to discharge touch probe cap
    PORTC= (PORTC & ~_BV(ADCReadPin)) | _BV(ADCRef); 
    // charge/discharge s&h cap by connecting it to partner
    ADMUX = MUX_REF_VCC | ADCRef; // select partner as input to the ADC unit 
    delayMicroseconds(CHARGE_DELAY); // wait for the touch probe and the s&h cap to be fully charged/dsicharged 
    
    DDRC&= ~mask; // config pins as input
    PORTC&= ~mask; // disable the internal pullup to make the ports high Z 
    // connect touch probe cap to s&h cap to transfer the charge
    ADMUX= MUX_REF_VCC | ADCReadPin; // select pin as ADC input 
    delayMicroseconds(TRANSFER_DELAY); // wait for charge to be transfered  
    // measure
    ADCSRA|= (1<<ADSC); // start measurement 
    while(ADCSRA & (1<<ADSC)){  } // wait for conversion to complete 
    adc1 += analogRead(ADCRef);

  // Second measurement - Do everything again with inverted ref / probe pins
  
    DDRC|= mask; // config pins as push-pull output   
    // set pin high to charge the touch probe and partner low to discharge s&h cap
    PORTC= (PORTC & ~_BV(ADCRef)) | _BV(ADCReadPin); 
    // charge/discharge s&h cap by connecting it to partner
    ADMUX = MUX_REF_VCC | ADCRef; // select partner as input to the ADC unit 
    delayMicroseconds(CHARGE_DELAY); // wait for the touch probe and the s&h cap to be fully charged/dsicharged 
    
    DDRC&= ~mask; // config pins as input
    PORTC&= ~mask; // disable the internal pullup to make the ports high Z 
    // connect touch probe cap to s&h cap to transfer the charge
    ADMUX= MUX_REF_VCC | ADCReadPin; // select pin as ADC input 
    delayMicroseconds(TRANSFER_DELAY); // wait for charge to be transfered  
    // measure
    ADCSRA|= (1<<ADSC); // start measurement 
    while(ADCSRA & (1<<ADSC)){  } // wait for conversion to complete 
    adc2 += analogRead(ADCReadPin);
 } 

  adc1 /= samples; // divide the accumulated measurements by number of samples
  adc2 /= samples;

  return adc2 - adc1; // return conversion result
}

QTouchADCduinoClass QTouchADCduino;
