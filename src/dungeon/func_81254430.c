#include "common.h"

typedef struct {
    u32 value;
    s32 pad[2];
} S_80173F90;

extern S_80173F90 D_80173F90;


/* Resets global state fields and flags and loads the configured value. */
void func_81254430(void) {
    u8 *page = (u8 *)0x80010000;
    u16 flags;
    s32 value;

    flags = *(u16 *)(page + 0x3714);
    *(s16 *)(page + 0x371A) = 0;
    *(s16 *)(page + 0x3718) = 0;
    *(s16 *)(page + 0x3716) = 0;
    *(s16 *)(page + 0x3714) = (flags | 9) & 0xFFEF;
    value = D_80173F90.value;
    *(s32 *)(page + 0x371C) = value;
}
