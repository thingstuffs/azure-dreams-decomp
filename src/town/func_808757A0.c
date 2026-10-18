#include "common.h"


/* Set the value at 0x807003B4 to 9. */
void set_devkit_value_to_nine(void) {
    *(s32 *)0x807003B4 = 9;
}
