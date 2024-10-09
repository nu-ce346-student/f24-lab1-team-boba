
#include "gpio.h"
#include "stdio.h"

typedef struct{
  // Step 3:
  // Add register definitions here
  // uint32_t _unused_A1[(0x504)/4 - 1];    // for the unused bits if dont add 504
	uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t _unused_A2[(0x700-0x524)/4 - 1];    // for the unused bits
  // uint32_t RESERVED[43];  //between detectmode and pincnf
  uint32_t PIN_CNF[32];   //array for pin_cnf values of 0 to 31 (32 values)
} gpio_reg_t;

  volatile gpio_reg_t* port0 = (gpio_reg_t*)(0x50000000 + 0x504);
  volatile gpio_reg_t* port1 = (gpio_reg_t*)(0x50000300 + 0x504);

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  uint8_t setnum = 0;
  if (dir == 1) {
    setnum = 3;
  }

  if (gpio_num < 32) {
    port0->PIN_CNF[gpio_num] = setnum;
  } else {
    port1->PIN_CNF[gpio_num] = setnum;
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured
  if (gpio_num < 32) {
    port0->OUT |= 1 << gpio_num; 
  } else {
    port1->OUT |= 1 << gpio_num; 
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  if (gpio_num < 32) {
    port0->OUT &= 0 << gpio_num;
  } else {
    port1->OUT &= 0 << gpio_num;
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured
  if (gpio_num < 32) {
    return (port0->IN >> gpio_num ) & 0x1;
  } else {
    return (port1->IN >> gpio_num ) & 0x1;
  }
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
    // printf("%p\n", &(port0->OUT));
    // printf("Port 0 OUT reg address: %p\n", &(port0->OUT));
    // printf("Port 0 DIR reg address: %p\n", &(port0->DIR));
    // printf("Port 0 PIN_CNF[0] register address: %p\n", &(port0->PIN_CNF));

    // printf("Port 1 OUT reg address: %p\n", &(port1->OUT));
    // printf("Port 1 DIR reg address: %p\n", &(port1->DIR));
    // printf("Port 1 PIN_CNF[0] reg address: %p\n", &(port1->PIN_CNF));
}


