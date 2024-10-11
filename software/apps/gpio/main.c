// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

#define P0_DIR (*(volatile uint32_t *)(0x50000000 + 0x514))
#define P0_OUT (*(volatile uint32_t *)(0x50000000 + 0x504))

void mic_LED_on(void) {
  P0_DIR = 1 << 20;
  P0_OUT = 1 << 20;
}

void mic_LED_off(void) {
  P0_DIR = 0 << 20;
  P0_OUT = 0 << 20;
}

//  bool - pin state (true == high) high is off
bool check_btnA(void) {
  return gpio_read(14);
}

bool check_btnB(void) {
  return gpio_read(23);
}

void turn_on_all_LEDs(void) {
  // Turn on all LEDs on the back of the Microbit
  // Add code here
  int gpio_nums[] = {21, 22, 15, 24, 19, 28, 11, 31, 37, 30};
  int dir = 1;
  for (uint32_t i = 0; i<10; i++) {
    gpio_config(gpio_nums[i], dir);
  }

  // rows
  for (uint32_t i = 0; i<5; i++) {
    gpio_set(gpio_nums[i]);
  }

  // cols
  for (uint32_t i = 5; i<10; i++) {
    gpio_clear(gpio_nums[i]);
  }
}

int main(void) {
  printf("Board started!\n");
  gpio_print();

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code hereP0_OUT
  // P0_DIR = 1 << 20;
  // P0_OUT = 1 << 20;

  // loop forever
  printf("Looping\n");
  gpio_set(14); // set turns it off
  gpio_set(23);
  gpio_config(14, 0);
  gpio_config(23, 0);

  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    if (check_btnA() == 0) {
      mic_LED_on();
      gpio_set(14);
    } else if (check_btnB() == 0) {
      mic_LED_off();
      gpio_set(23);

    }

    nrf_delay_ms(100);
  }
}

