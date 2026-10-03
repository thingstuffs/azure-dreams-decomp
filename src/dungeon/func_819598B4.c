#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/object_flags.h"

typedef struct S_819598B4_0_pre {
    u16 unk_00;
} S_819598B4_0_pre;   /* the 0x2 bytes before state in func_819598B4, addressed as state[-1] */

typedef struct S_819598B4_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xA];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
    u8 pad_3A[0x2];
    s16 unk_3C;
} S_819598B4_0;   /* state in func_819598B4 */

typedef struct S_819598B4_1 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { u32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xE];
    u16 unk_1E;
} S_819598B4_1;   /* parameters in func_819598B4 */

typedef struct S_819598B4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 n; u16 v; } unk_0A;   /* accessed as both */
} S_819598B4_2;   /* values in func_819598B4 */

typedef struct S_819598B4_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_819598B4_3;   /* D_800E3D7C[0] in func_819598B4 */


extern s32 func_80025604();
extern s32 func_80026384();

extern u16 D_800281F8[];
extern u8 D_80028220[];

void func_819598B4(void *state, S_819598B4_2 *values, S_819598B4_1 *parameters) {
    s16 value0A;
    s16 value3C;
    s32 byteDistance;
    s16 timerNextFirst;
    s16 timerNextSecond;
    s16 stateId;
    u16 value1E;
    s32 byteValue;
    s32 nextByteValue;
    u8 tickCountNext;
    u8 byteNext;

    D_800281F8[0]++;
    stateId = ((S_819598B4_0 *)state)->unk_2C.s;
    switch (stateId) {
    case 0:
        value1E = parameters->unk_1E;
        byteValue = parameters->unk_0C.at00.v;
        parameters->unk_1E = (u16)(value1E + ((s32)(0x1000 - value1E) / ((S_819598B4_0 *)state)->unk_30));
        byteDistance = 0x80 - byteValue;
        value3C = ((S_819598B4_0 *)state)->unk_3C;
        nextByteValue = byteValue + ((byteDistance - value3C) / ((S_819598B4_0 *)state)->unk_30);
        parameters->unk_0C.at00.v = nextByteValue;
        parameters->unk_0C.at01.v = nextByteValue;
        parameters->unk_0C.at02.v = nextByteValue;
        values->unk_02 = (s16)((u16)values->unk_02 + ((s32)(((S_819598B4_0 *)state)->unk_14
            - values->unk_02) / ((S_819598B4_0 *)state)->unk_30));
        values->unk_06 = (s16)((u16)values->unk_06 + ((s32)(((S_819598B4_0 *)state)->unk_16
            - values->unk_06) / ((S_819598B4_0 *)state)->unk_30));
        value0A = values->unk_0A.n;
        values->unk_0A.n = (s16)(values->unk_0A.v + ((s32)(((S_819598B4_0 *)state)->unk_18
            - value0A) / ((S_819598B4_0 *)state)->unk_30));
        timerNextFirst = (u16)((S_819598B4_0 *)state)->unk_30 - 1;
        ((S_819598B4_0 *)state)->unk_30 = timerNextFirst;
        if ((timerNextFirst << 0x10) <= 0) {
            ((S_819598B4_0 *)state)->unk_30 = 0x10;
            parameters->unk_1E = 0x1000;
            parameters->unk_0C.at00u.v = 0x00808080;
            if (((S_819598B4_0 *)state)->unk_3C != 0) {
                ((S_819598B4_0 *)state)->unk_2C.s = 2;
            } else {
                ((S_819598B4_0 *)state)->unk_2C.s++;
            }
        }
        break;
    case 1:
        if (((S_819598B4_0 *)state)->unk_38 == 0) {
            if (func_80026384(((S_819598B4_0 *)state)->unk_1C, ((S_819598B4_0 *)state)->unk_1E,
                ((S_819598B4_0 *)state)->unk_20, D_800E3D7C->facing) == 0) {
                break;
            }
            func_80025604(((S_819598B4_0 *)state)->unk_1C, ((S_819598B4_0 *)state)->unk_1E,
                ((S_819598B4_0 *)state)->unk_20);
        }
        ((S_819598B4_0 *)state)->unk_30 = 0x10;
        ((S_819598B4_0 *)state)->unk_2C.s++;
        break;
    case 2:
        byteNext = parameters->unk_0C.at00.v;
        byteNext -= (s32)byteNext / ((S_819598B4_0 *)state)->unk_30;
        parameters->unk_0C.at00.v = byteNext;
        parameters->unk_0C.at01.v = byteNext;
        parameters->unk_0C.at02.v = byteNext;
        timerNextSecond = (u16)((S_819598B4_0 *)state)->unk_30 - 1;
        ((S_819598B4_0 *)state)->unk_30 = timerNextSecond;
        if ((timerNextSecond << 0x10) <= 0) {
            ((S_819598B4_0_pre *)state)[-1].unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }

    if (((S_819598B4_0 *)state)->unk_38 != 0) {
        return;
    }
    if (((S_819598B4_0 *)state)->unk_3C != 0) {
        return;
    }
    tickCountNext = D_80028220[9] + 1;
    D_80028220[9] = tickCountNext;
    if ((u32)(tickCountNext & 0xFF) >= 0x20U) {
        D_80028220[9] = 0;
    }
}
