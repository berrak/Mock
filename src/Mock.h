/*!
 * @file Mock.h
 *
 * This is part of Mock library for the Arduino platform.
 *
 * The MIT license.
 *
 */

#ifndef MOCK_H_
#define MOCK_H_

#ifndef ARDUINO
#include <cstdint>
#endif

/*!
*  \addtogroup mock
*  @{
*/

//! Arduino mocked methods
namespace mock {

//-------------------------------------------------------------------------
/*!
    @brief  Arduino Mock methods and mocked Arduino language constructs.
*/
//-------------------------------------------------------------------------
    class Mock
    {
        public:

            //-------------------------------------------------------------------------
            /*!
                @brief  Constructor.
            */
            //-------------------------------------------------------------------------
            Mock(void){};



            //-------------------------------------------------------------------------
            /*!
                @brief  Deallocate Mock object.
            */
            //-------------------------------------------------------------------------
            ~Mock(void){};



            //-------------------------------------------------------------------------
            /*!
                @brief  Mocked version of Arduino millis().
                @return The mocked millis() value, i.e., zero.
            */
            //-------------------------------------------------------------------------
            static uint32_t millis(void){ return 0L; };



            //-------------------------------------------------------------------------
            /*!
                @brief  Mocked version of Arduino pinMode() returns without action.
                @param  pin
                        Arduino pin number to set the mode.
                @param  mode
                        Sets the mode to INPUT, OUTPUT, or INPUT_PULLUP.
            */
            //-------------------------------------------------------------------------
            static void pinMode(uint8_t pin, uint8_t mode){};



            //-------------------------------------------------------------------------
            /*!
                @brief  Mocked version of Arduino digitalWrite() returns without action.
                @param  pin
                        Arduino pin number for write.
                @param  value
                        Value is either HIGH or LOW.
            */
            //-------------------------------------------------------------------------
            static void digitalWrite(uint8_t pin, uint8_t value){};



            //-------------------------------------------------------------------------
            /*!
                @brief  Mocked version of Arduino digitalRead().
                @param  pin
                        The digital pin to read from.
                @return The mocked digitalRead() value, i.e., zero.
            */
            //-------------------------------------------------------------------------
            static uint16_t digitalRead(uint8_t pin){
            	return 0;
            };



            //-------------------------------------------------------------------------
            /*!
                @brief  Mocked version of Arduino analogWrite() returns without action.
                @param  pin
                        The analog pin to write to.
                @param  value
                        The duty cycle: between 0 (always off) and 255 (always on).
            */
            //-------------------------------------------------------------------------
            static void analogWrite(uint8_t pin, uint16_t value){};


            //-------------------------------------------------------------------------
            /*!
                @brief  Mocked version of Arduino analogRead().
                @param  pin
                        The analog pin to read from.
                @return The mocked analogRead() value, i.e., zero.
            */
            //-------------------------------------------------------------------------
            static uint16_t analogRead(uint8_t pin){
            	return 0 ;
            };



            //-------------------------------------------------------------------------
            /*!
                @brief  Re-maps a number from one range to another. That is, a value of
                        in_min would get mapped to out_min, a value of in_max to out_max,
                        values in-between to values in-between, etc.
                @param  in_value
                        The in value to map.
                @param  in_min
                        The lower bound of the value’s current range.
                @param  in_max
                        The upper bound of the value’s current range.
                @param  out_min
                        The lower bound of the value’s target range.
                @param  out_max
                        The upper bound of the value’s target range.
                @return The mapped value.
            */
            //-------------------------------------------------------------------------
            static uint32_t map(uint32_t in_value, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
                return ((in_value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
            };



//            //-------------------------------------------------------------------------
//            /*!
//                @brief  Gets the current value used in the mocked analogRead().
//                Can be changed with a call to setAnalogValue(new_value).
//                @return The used 'analog_read_value', which is default to zero.
//            */
//            //-------------------------------------------------------------------------
//            uint16_t getAnalogValue(void) {
//            	return analog_read_value ;
//            };
//
//
//
//
//            //-------------------------------------------------------------------------
//            /*!
//                @brief  Sets a new return value for mocked analogRead().
//                @param  new_value
//                        Inject value for mocked analogRead().
//            */
//            //-------------------------------------------------------------------------
//            void setAnalogValue(uint16_t new_value) { analog_read_value = new_value ; };
//
//        private:
//
//            uint16_t analog_read_value; ///< An optional new return value for the mocked analogRead()


    };  /*  class Mock */

}  /* namespace mock */

/*! @} End of Doxygen Groups*/

#ifndef ARDUINO
#define HIGH 0x1            ///< Arduino definition for HIGH
#define LOW  0x0            ///< Arduino definition for LOW

#define INPUT 0x0           ///< Arduino definition for INPUT
#define OUTPUT 0x1          ///< Arduino definition for OUTPUT
#define INPUT_PULLUP 0x2    ///< Arduino definition for INPUT_PULLUP

#define CHANGE 1            ///< Arduino definition for CHANGE
#define FALLING 2           ///< Arduino definition for FALLING
#define RISING 3            ///< Arduino definition for RISING

// Arduino standard typedef's
/** Arduino typedef for word */
typedef uint16_t word;
/** Arduino typedef for boolean */
typedef bool boolean;
/** Arduino typedef for byte */
typedef uint8_t byte;
#endif

#endif /* MOCK_H_ */
