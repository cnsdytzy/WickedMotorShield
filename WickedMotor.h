/* Copyright (C) 2014 by Victor Aprea <victor.aprea@wickeddevice.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#ifndef _WICKED_MOTOR_H
#define _WICKED_MOTOR_H

#if ARDUINO >= 100
  #include <Arduino.h>  // Arduino 1.0
#else
  #include <WProgram.h> // Arduino 0022
#endif

#include <stdint.h>

#define DIR_CCW	(0)
#define DIR_CW  (1)

#define BRAKE_OFF  (0)
#define BRAKE_HARD (1)
#define BRAKE_SOFT (2)

#define M1  (0)
#define M2  (1)
#define M3  (2)
#define M4  (3)
#define M5  (4)
#define M6  (5)

// these bits are in shift register 1
#define M4_DIR_MASK    (0x80)
#define M4_BRAKE_MASK  (0x40)
#define M1_DIR_MASK    (0x20)
#define M1_BRAKE_MASK  (0x10)
#define M2_DIR_MASK    (0x08)
#define M2_BRAKE_MASK  (0x04)
#define M3_DIR_MASK    (0x02)
#define M3_BRAKE_MASK  (0x01)

// these bits are in shift register 2
#define M6_DIR_MASK    (0x80)
#define M6_BRAKE_MASK  (0x40)
#define M5_DIR_MASK    (0x20)
#define M5_BRAKE_MASK  (0x10)

#define M2_PWM_PIN (9)
#define M3_PWM_PIN (5)
#define M4_PWM_PIN (10)
#define M5_PWM_PIN (6)

#define RCIN1      (1) 
#define RCIN2      (2)

class WickedMotor{
 private:
   uint8_t first_shift_register;
   uint8_t second_shift_register;
   uint8_t SERIAL_DATA_PIN;
   uint8_t M1_PWM_PIN;   
   uint8_t M6_PWM_PIN;
   uint8_t RCIN1_PIN;
   uint8_t RCIN2_PIN;
   uint8_t old_dir[6];
   void load_shift_register(void);
   uint8_t get_shift_register_value(uint8_t motor_number);
   void set_shift_register_value(uint8_t motor_number, uint8_t value);  
   void apply_mask(uint8_t * shift_register_value, uint8_t mask, uint8_t operation);
   uint8_t filter_mask(uint8_t shift_regsiter_value, uint8_t mask);
   uint8_t get_motor_direction(uint8_t motor_number);  
   uint8_t get_rc_input_pin(uint8_t rc_input_number);
 public:
   WickedMotor(uint8_t serial_data_pin = 12, uint8_t m1_pwm_pin = 11, uint8_t m6_pwm_pin = 3, uint8_t rcin1_pin = 4, uint8_t rcin2_pin = 8); // defaults for arduino uno
   void setSpeed(uint8_t motor_number, uint8_t pwm_val);            // 0..255
   void setDirection(uint8_t motor_number, uint8_t direction);      // DIR_CCW, DIR_CW
   void setBrake(uint8_t motor_number, uint8_t brake_type);         // HARD, SOFT, OFF
   uint16_t currentSense(uint8_t motor_number);                     // returns current ADC value associated with motor
   uint32_t getRCIN(uint8_t rc_input_number, uint32_t timeout = 0); // returns the result for pulseIn for the requested channel
};

#endif /* _WICKED_MOTOR_SHIELD_H */
