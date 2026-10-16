#include "common.h"


/* Set the value at 0x807003B4 to 9. */
void townSetDevkitValueToNine(void) {
    *(s32 *)0x807003B4 = 9;
}
