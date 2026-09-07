#include "common.h"

/* Struct type for the entity pointed to by a0 in func_8004397C.
   Only offsets 0x13 and 0x48 are accessed (both bytes); pad to reach them. */
typedef struct {
    u8 pad_0x00[0x13];
    u8 field_0x13;
    u8 pad_0x14[0x48 - 0x13 - 1];
    u8 field_0x48;
} S_8004397C_Entity;

/* >8B hi/lo global; only byte 0 is ever written (sb). Declare as array to force lui/lbu/sb. */
extern u8 D_800E2968[16];

/* summary: if entity's field_0x13 == 0x16 (some "type" tag), inspect field_0x48
   (a sub-state/mode byte) and record a resulting code into D_800E2968:
   0xD -> 0xF, 0xF -> 0xA, otherwise leave D_800E2968 unchanged. */
void func_8004397C(S_8004397C_Entity *a0)
{
    if (a0->field_0x13 == 0x16) {
        u8 v = a0->field_0x48;
        if (v == 0xD) {
            D_800E2968[0] = 0xF;
        } else if (v == 0xF) {
            D_800E2968[0] = 0xA;
        }
    }
}
