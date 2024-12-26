#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

// Second pin must be n+1
#define ENCODER_FIRST_PIN 0
#define ENCODER_REVERSE true

#define PPR 360
#define TARGET_STEPS 144

constexpr uint32_t gcd(uint32_t n, uint32_t m) {
  return m == 0 ? n : gcd(m, n % m);
}

constexpr uint32_t FOUND_GCD = gcd(PPR * 4, TARGET_STEPS);
constexpr uint32_t THRESHOLD = PPR * 4 / FOUND_GCD;
constexpr uint32_t ENCODER_STEP = TARGET_STEPS / FOUND_GCD;

void encoder_init(void);
void encoder_task(void);

uint8_t get_encoder_value(void);

#endif /* ENCODER_H */
