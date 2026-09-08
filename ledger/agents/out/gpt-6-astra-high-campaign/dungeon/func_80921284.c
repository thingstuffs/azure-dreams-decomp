#include "common.h"

typedef struct {
    u8 pad_0[0x10];
    s16 field_10;
    s16 field_12;
    s16 field_14;
    u16 field_16;
} State;

extern State D_80082E60;
extern s32 D_800E296C[];

/* Set the state values to 0x20 and 0x31 and enable the associated flags. */
void func_800F6284(void) {
    D_80082E60.field_10 = 0x20;
    D_80082E60.field_12 = 0x31;
    D_80082E60.field_16 |= 1;
    D_800E296C[0] |= 0x2000;
}
