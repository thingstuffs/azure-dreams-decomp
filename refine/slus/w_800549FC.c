#include "common.h"

/* D_800847F0: only a single s16 field is ever touched here (sh of 0/1), but
 * the target addresses it via lui/%lo rather than gp-relative, so it must be
 * declared >8 bytes to force %hi/%lo addressing. */
typedef struct S_800847F0 {
    /* 0x0 */ s16 field0;
    /* 0x2 */ u8 pad2[10];
} S_800847F0;

extern S_800847F0 D_800847F0;

/* Marker-table arrays: only their addresses are taken here (matching the
 * sibling usage in src/w_8004437C.c), never dereferenced. */
extern s32 D_801BEE40[4];
extern s32 D_801C4640[4];

extern void func_800553D4(s32 a0);
extern void func_80055ADC(void *a0, s32 a1);

/* Fires event 0x71 and selects the marker table and flag for types 0x21 and 0x22. */
void func_800549FC(s32 marker_code) {
    u8 marker_type = marker_code & 0xFF;

    func_800553D4(0x71);

    switch (marker_type) {
    case 0x21:
        D_800847F0.field0 = 0;
        func_80055ADC(D_801BEE40, 0);
        break;
    case 0x22:
        D_800847F0.field0 = 1;
        func_80055ADC(D_801C4640, 1);
        break;
    }
}
