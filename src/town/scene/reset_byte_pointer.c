#include "common.h"

extern u8 D_80016034[16];
extern u8 *D_80016D08;

/* Reset the byte pointer to the start of its buffer. */
void reset_byte_pointer(void) {
    D_80016D08 = D_80016034;
}
