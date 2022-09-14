#ifdef ARDUINO
//============================================================================
// Sketch name : Mock.ino
// Author      : Created by Debinix Team (c).
// Date        : 2022-09-07.
// License     : The MIT License.
// Description :
// Mock methods for Arduino functions. Replace Arduino methods and
// develope code without the hardware. Shows how the mocked function works.
// The mocked functions returns immediately or returns zero.
//
// Add:   #include <Mock.h>
//        using namespace mock;
//        and
//        Prepend all Arduino's calls with 'Mock::'
//
// To revert mocking, remove these changes in the IDE or by shell script.
//
// Source: https://github.com/berrak/Mock
//
//============================================================================

#include <Mock.h>
using namespace mock;

// Defaults for an Arduino Uno
#define MVVCC 5000			// microcontroller VCC in millivolt
#define ADC_BITS 1024		// microcontroller ADC bits resolution
#define PWM 128             // 50% PWM duty cycle

int dwrite_pin = 13;
int awrite_pin = 9 ;
int dread_pin  = 8 ;
int aread_pin = A0 ;

int map_in_value = ADC_BITS/2;
long mapped_value = Mock::map(map_in_value, aread_pin, ADC_BITS-1, aread_pin, MVVCC);

void setup() {

    Serial.begin(9600);
    delay(2000);

    Serial.println("Mocked Ardiono methods returns zero, or returns directly.");

    // Mocked Arduino calls
    Mock::pinMode(dwrite_pin,OUTPUT);		// digitalWrite
    Mock::pinMode(awrite_pin,OUTPUT);		// analogWrite

    Mock::pinMode(dread_pin,INPUT_PULLUP);	// digitalRead
    Mock::pinMode(aread_pin,INPUT);       	// analogRead - optional

}

void loop() {

    Serial.print("Mock::millis(): ");
    Serial.println(Mock::millis());

    Serial.print("Mock::analogRead(): ");
    Serial.println(Mock::analogRead(aread_pin));

    Serial.print("Mock::digitalRead(): ");
    Serial.println(Mock::digitalRead (dread_pin));

    Serial.println("Mock::analogWrite(): NOP");
    Mock::analogWrite (awrite_pin, PWM); 

    Serial.print("Mock::analogRead(): ");
    Serial.println(Mock::analogRead (aread_pin));

    // map() is not mocked, but included in the
    // library for Arduino method completeness
    Serial.print("The map() return value should be ~2500: ");
    Serial.println(mapped_value);

    testMockedDigitalWrite();

    delay(3000);
    Serial.println();

}

// Mocked 10 x blink LED_BUILTIN
void testMockedDigitalWrite(void) {

#ifdef LED_BUILTIN
    Serial.println("10 x Mock::digitalWrite() - LED_BUILTIN will not blink");
    for (int cnt = 0; cnt < 10 ; cnt++){
        Mock::digitalWrite(LED_BUILTIN, HIGH);
        delay(125);
        Mock::digitalWrite(LED_BUILTIN, LOW);
        delay(125);
    }
#endif
}

#endif // ARDUINO

