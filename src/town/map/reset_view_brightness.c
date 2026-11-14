#include "common.h"
#include "town/map.h"
#include "town/data.h"

/* Clears the word addressed by view_gray_command. */
void reset_view_brightness(void) {
    *view_gray_command = 0;
}
