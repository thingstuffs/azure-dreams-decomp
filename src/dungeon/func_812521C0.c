#include "common.h"


extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();
extern void func_80171B5C() __attribute__((noreturn));
extern void func_80171BBC() __attribute__((noreturn));

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80173E8C[8];


typedef struct S_801719C0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_801719C0_0;   /* arg3 in func_801719C0 */

typedef struct S_801719C0_1 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801719C0_1;   /* arg2 in func_801719C0 */

typedef struct S_801719C0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x3];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_801719C0_2;   /* arg0 in func_801719C0 */

typedef struct S_801719C0_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801719C0_3;   /* entry in func_801719C0 */

typedef struct S_801719C0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801719C0_4;   /* (u8 *)arg3 + ((S_801719C0_0 *)arg3)->unk_8A.s in func_801719C0 */

void func_801719C0(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 mode;
    s32 count;
    s32 old_x;
    s32 old_y;
    u8 *entry;

    if (((S_801719C0_0 *)arg3)->unk_71.s <= 0) {
        return;
    }
    if (((S_801719C0_0 *)arg3)->unk_71.u <= ((S_801719C0_0 *)arg3)->unk_8A.s) {
        return;
    }

    if (((S_801719C0_1 *)arg2)->unk_2C != D_80173E8C) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80173E8C;
        func_80047784(
            arg2,
            D_80173E8C[((D_80083228 + ((S_801719C0_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801719C0_1 *)arg2)->unk_05 = 1;
        ((S_801719C0_2 *)arg0)->unk_A2 = 0;
        ((S_801719C0_2 *)arg0)->unk_9E = 0;
    }

    entry = (u8 *)arg3 + ((S_801719C0_0 *)arg3)->unk_8A.s;
    if (((S_801719C0_1 *)arg2)->unk_24 == ((S_801719C0_3 *)entry)->unk_74 &&
        ((S_801719C0_1 *)arg2)->unk_25 == ((S_801719C0_3 *)entry)->unk_7C) {
        u16 v88 = ((S_801719C0_0 *)arg3)->unk_88;
        ((S_801719C0_2 *)arg0)->unk_92 += 0x20;
        ((S_801719C0_0 *)arg3)->unk_88 = v88 - 0x20;
        ((S_801719C0_0 *)arg3)->unk_8A.u++;
        func_80171B5C(entry);
        return;
    }

    old_x = ((S_801719C0_1 *)arg2)->unk_24;
    old_y = ((S_801719C0_1 *)arg2)->unk_25;
    mode = 0x3000;
    if (((S_801719C0_0 *)arg3)->unk_1C & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, mode);

    ((S_801719C0_1 *)arg2)->unk_24 =
        ((S_801719C0_4 *)((u8 *)arg3 + ((S_801719C0_0 *)arg3)->unk_8A.s))->unk_74;
    ((S_801719C0_1 *)arg2)->unk_25 =
        ((S_801719C0_4 *)((u8 *)arg3 + ((S_801719C0_0 *)arg3)->unk_8A.s))->unk_7C;
    ((S_801719C0_0 *)arg3)->unk_8A.u++;

    func_8009A21C(((S_801719C0_1 *)arg2)->unk_24, ((S_801719C0_1 *)arg2)->unk_25,
                  (((S_801719C0_0 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    ((S_801719C0_0 *)arg3)->unk_2A =
        func_800A0818(old_x, old_y, ((S_801719C0_1 *)arg2)->unk_24,
                      ((S_801719C0_1 *)arg2)->unk_25, (u8 *)arg0 + 0x98);
    ((S_801719C0_2 *)arg0)->unk_9A = 0xF;
    ((S_801719C0_2 *)arg0)->unk_8C = 0;
    (*(s32 *)((u8 *)arg3 + (0x1C))) |= 0x40000000;

    if (D_80083462 & 0x80) {
        ((S_801719C0_2 *)arg0)->unk_96 = 0;
        func_80171BBC();
        return;
    }

    ((S_801719C0_2 *)arg0)->unk_96 = 8;
    count = ((S_801719C0_0 *)arg3)->unk_71.u;
    if (count > 0) {
        ((S_801719C0_2 *)arg0)->unk_96 = 8 / count;
    }
}
