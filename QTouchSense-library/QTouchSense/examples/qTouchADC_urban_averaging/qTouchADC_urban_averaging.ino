// qTouchADC.ino
#include <avr/io.h>
#include <inttypes.h>

#define PC0 0 // ist das das selbe wie A0 in Arduinosprache?
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5

int16_t idx = 0;
const uint16_t ledFadeTable[32] = {0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255}; // this is an exponential series to model the perception of the LED brightness by the human eye

int value1 = 0;
int value2 = 0;
int ref1 = 0;
int ref2 = 0;
int QTouchDelay = 5;
unsigned int measurement1, measurement2;

void initADC(){
    // ADC
    //DDRB=(0<<PB2)|(0<<PB3)|(0<<PB4); //inputs of ADC-Sensor and ADC-Reference
    ADMUX = (0<<REFS0); //REFS0=0:VCC reference, =1:internal reference 1.1V
    // ADMUX = (0<<REFS0) | (0x00); right two bits select ADC-pin
    ADCSRA = (1<<ADEN)| (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC enable, prescaler 128
}

// pre: adcPin == beliebiger ADC pin, ausser A0. A0 (ADC0/PC0) wird als Referenz gebraucht. 
uint16_t sensePad(uint8_t adcPin, uint8_t refPin, uint8_t samples){
    long _value = 0;
  
  for(int _counter = 0; _counter < samples; _counter ++)
  {
    // first measurement: adcPin low, S/H high
    ADMUX = (0<<REFS0) | (refPin); // set ADC sample+hold condenser to the free A0 (ADC0) 
    delayMicroseconds(QTouchDelay);
    PORTC |= (1<<refPin); //PC0/ADC0 ref/ S/H high (pullup or output, doesn't matter)
    PORTC &= ~(1<<adcPin);
    DDRC |= (1<<adcPin) | (1<<refPin); // both output: adcPin low, S/H (ADC0) high
    delayMicroseconds(QTouchDelay);
    DDRC &= ~((1<<adcPin) | (1<<refPin)); // set pins to Input...
    PORTC &= ~((1<<adcPin) | (1<<refPin)); // ... and low: Tristate

    measurement1 = analogRead(adcPin);
    //measurement1 = ADC;

    // second measurement: adcPin high, S/H low
    ADMUX = (0<<REFS0) | refPin; // set ADC sample+hold condenser to the free PC0 (ADC0)
    delayMicroseconds(QTouchDelay);
    PORTC |= (1<<adcPin); // sensePad/adcPin high
    DDRC |= (1<<adcPin) | (1<<refPin); // both output: adcPin high, S/H (ADC0) low
    delayMicroseconds(QTouchDelay);
    DDRC &= ~((1<<adcPin) | (1<<refPin));
    PORTC &= ~((1<<adcPin) | (1<<refPin));

    measurement2 = analogRead(adcPin);
    //measurement2 = ADC;
    
    _value += (measurement2 - measurement1);
    
  } 
  
  return _value / samples;
}

void setup() {
  initADC();
  Serial.begin(115200);      // open the serial port at 9600 bps: 
  ref1 = sensePad(1, 0, 64);
  ref2 = sensePad(2, 0, 64);
}

void loop() {
  unsigned long time;
  time= micros();
  
  value1 = (sensePad(1, 0, 8) - ref1);
  time= micros() - time;
  
  value2 = (sensePad(2, 0, 8) - ref2);
  
  int16_t idx= (value1); // offset probe_val by value of untouched probe
  if(idx<0) idx= 0; // limit the index!!!
  idx/= 2; // scale the index
  if(idx>31) idx= 31; // limit the index!!!
  
  analogWrite(9, ledFadeTable[idx]);
  
  idx= (value2); // offset probe_val by value of untouched probe
  if(idx<0) idx= 0; // limit the index!!!
  idx/= 2; // scale the index
  if(idx>31) idx= 31; // limit the index!!!
  
  analogWrite(10, ledFadeTable[idx]);
  
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(time);
  Serial.print(' ');
  Serial.println(value2);
	
  delay(10);
}

