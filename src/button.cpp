#include "button.hpp"
#include "logger.hpp"
#include <hardware/gpio.h>
#include <hardware/timer.h>

static button_state_t states[NUM_BUTTONS];

void button_init(void) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    states[i] = (button_state_t){
        .pin_state = false, .transition_time = 0U, .pressed = false};

    gpio_init(BUTTON_TO_PIN_MAP[i]);
    gpio_set_input_enabled(BUTTON_TO_PIN_MAP[i], true);
    gpio_pull_up(BUTTON_TO_PIN_MAP[i]);
  }
}

void button_task(void) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool pin_state = gpio_get(BUTTON_TO_PIN_MAP[i]);
    debounce_funcs[DEFAULT_DEBOUNCE_STRATEGY](&states[i], pin_state);
  }
}

bool button_pressed(button_t button) {
  if (button >= NUM_BUTTONS) {
    return false;
  }

  return states[button].pressed;
}

void debounce_eager(button_state_t *button, bool new_pin_state) {
  // trigger a transition immediately
  // wait the debounce time before allowing a future transition

  uint32_t time_elapsed = time_us_32() - button->transition_time;

  if ((new_pin_state != button->pressed) &&
      (time_elapsed >= DEBOUNCE_TIME_MS)) {
    button->pressed = new_pin_state;
    button->transition_time = time_us_32();
    LOG_DEBUG("BUTTON CHANGED STATES TO %d", new_pin_state);
  }

  // set this in case we switch to deferred while running
  button->pin_state = new_pin_state;
}

void debounce_deferred(button_state_t *button, bool new_pin_state) {
  // do not transition until debounce time

  if (new_pin_state != button->pin_state) {
    button->transition_time = time_us_32();
    button->pin_state = new_pin_state;
  }

  uint32_t time_elapsed = time_us_32() - button->transition_time;

  if ((new_pin_state != button->pressed) &&
      (time_elapsed >= DEBOUNCE_TIME_MS)) {
    button->pressed = new_pin_state;
    LOG_DEBUG("BUTTON CHANGED STATES TO %d", new_pin_state);
  }
}

void debounce_none(button_state_t *button, bool new_pin_state) {
  button->pin_state = new_pin_state;
  button->pressed = new_pin_state;
}
