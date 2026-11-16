#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item.h"

extern s32 *D_8001371C;

/* Stores address 0x80013720 in the pointer slot at 0x8001371C. */
void reset_timed_sequence_data(void) {
    (*(__typeof__(D_8001371C) *)0x8001371C) = (s32 *) 0x80013720;
}
