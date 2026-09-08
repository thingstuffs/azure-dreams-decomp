#include "common.h"

extern s8 D_80082668[9];
extern s32 D_80097D2C[3];

/* Initializes object fields from input data and clears the shared flag. */
void func_80098834(void *object, void *init_data) {
    u16 current_value;
    u16 initial_value;

    *(s32 *)((s8 *)object + 0) = (s32)&D_80097D2C[0];
    *(u16 *)((s8 *)object + 0x30) = *(u16 *)((s8 *)init_data + 2);
    current_value = *(u16 *)((s8 *)object + 0x10);
    initial_value = *(u16 *)((s8 *)init_data + 6);
    *(u16 *)((s8 *)object + 0x0e) = current_value;
    *(u16 *)((s8 *)object + 0x32) = initial_value;
    D_80082668[0] = 0;
}
