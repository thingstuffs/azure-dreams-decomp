#include "common.h"

typedef struct S_80174600_0 {
    u8 pad_00[0xC];
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80174600_0;   /* arg2 in func_80174600 */

typedef struct S_80174600_1 {
    u8 pad_00[0x1A];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
} S_80174600_1;   /* p in func_80174600 */



extern s32 D_800814A0;

void func_80174600(void *arg0, s32 arg1, void *arg2)
{
    u8 *p = arg0;
    s16 timer;
    s32 value;
    s32 diff;
    u8 channel;

    ((S_80174600_0 *)arg2)->unk_1A += 0x320;

    if (((S_80174600_1 *)p)->unk_1A.s >= 0x33) {
        ((S_80174600_0 *)arg2)->unk_0C = (p[0] * (0x41 - ((S_80174600_1 *)p)->unk_1A.s)) / 14;
        ((S_80174600_0 *)arg2)->unk_0D = (p[1] * (0x41 - ((S_80174600_1 *)p)->unk_1A.s)) / 14;
        ((S_80174600_0 *)arg2)->unk_0E = (p[2] * (0x41 - ((S_80174600_1 *)p)->unk_1A.s)) / 14;
    } else if (((S_80174600_1 *)p)->unk_1A.s < 0x1A) {
        if (((S_80174600_1 *)p)->unk_1A.s >= 0x10) {
            diff = (p[0] - p[1]) / (((S_80174600_1 *)p)->unk_1A.s - 0xF);
            channel = p[1] + diff;
            p[1] = channel;
            ((S_80174600_0 *)arg2)->unk_0D = channel;

            diff = (p[0] - p[2]) / (((S_80174600_1 *)p)->unk_1A.s - 0xF);
            channel = p[2] + diff;
            p[2] = channel;
            ((S_80174600_0 *)arg2)->unk_0E = channel;
        } else if (((S_80174600_1 *)p)->unk_1A.s >= 8) {
            value = p[0] * (((S_80174600_1 *)p)->unk_1A.s - 8);
            if (value < 0) {
                value += 7;
            }
            ((S_80174600_0 *)arg2)->unk_0C = value >> 3;

            value = p[1] * (((S_80174600_1 *)p)->unk_1A.s - 8);
            if (value < 0) {
                value += 7;
            }
            ((S_80174600_0 *)arg2)->unk_0D = value >> 3;

            value = p[2] * (((S_80174600_1 *)p)->unk_1A.s - 8);
            ((S_80174600_0 *)arg2)->unk_0E = value / 8;
        } else {
            ((S_80174600_1 *)p)->unk_1A.s = 0;
        }
    }

    timer = ((S_80174600_1 *)p)->unk_1A.u - 1;
    ((S_80174600_1 *)p)->unk_1A.s = timer;
    if ((timer << 16) <= 0) {
        (*(u16 *)((u8 *)p + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
