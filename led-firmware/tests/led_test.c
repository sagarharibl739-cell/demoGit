#include <assert.h>
#include "led.h"

#include "../src/led.c"

int main(void)
{
    led_init();
    assert(led_state == 0);

    led_on();
    assert(led_state == 1);

    led_toggle();
    assert(led_state == 0);

    led_toggle();
    assert(led_state == 1);

    led_off();
    assert(led_state == 0);

    return 0;
}
