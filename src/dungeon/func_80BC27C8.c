#include "common.h"

typedef struct S_80171FC8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171FC8_0;   /* arg3 in func_80171FC8 */

typedef struct S_80171FC8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171FC8_1;   /* arg2 in func_80171FC8 */

typedef struct S_80171FC8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171FC8_2;   /* tile in func_80171FC8 */

typedef struct S_80171FC8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_80171FC8_3;   /* arg0 in func_80171FC8 */

typedef struct S_80171FC8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171FC8_4;   /* (u8 *)arg3 + ((S_80171FC8_0 *)arg3)->unk_8A.s in func_80171FC8 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174634[];

void func_80171FC8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 count;
    u16 hp;
    u16 energy;
    u16 step;
    void *tile;

    if (((S_80171FC8_0 *)arg3)->unk_71.s <= 0) {
        return;
    }
    if ((s32)((S_80171FC8_0 *)arg3)->unk_71.u <= ((S_80171FC8_0 *)arg3)->unk_8A.s) {
        return;
    }

    if (((S_80171FC8_1 *)arg2)->unk_2C != D_80174634) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174634;
        func_80047784(arg2,
                     D_80174634[((D_80083228 + ((S_80171FC8_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                     0);
    }

    tile = (u8 *)arg3 + ((S_80171FC8_0 *)arg3)->unk_8A.s;
    if (((S_80171FC8_1 *)arg2)->unk_24 == ((S_80171FC8_2 *)tile)->unk_74 &&
        ((S_80171FC8_1 *)arg2)->unk_25 == ((S_80171FC8_2 *)tile)->unk_7C) {
        hp = ((S_80171FC8_3 *)arg0)->unk_92;
        energy = ((S_80171FC8_0 *)arg3)->unk_88;
        ((S_80171FC8_3 *)arg0)->unk_92 = hp + 0x20;
        step = ((S_80171FC8_0 *)arg3)->unk_8A.u;
        ((S_80171FC8_0 *)arg3)->unk_88 = energy - 0x20;
        ((S_80171FC8_0 *)arg3)->unk_8A.u = step + 1;
        goto update_state;
    }

    flags = ((S_80171FC8_0 *)arg3)->unk_1C;
    old_x = ((S_80171FC8_1 *)arg2)->unk_24;
    old_y = ((S_80171FC8_1 *)arg2)->unk_25;
    distance = 0x3000;
    if (flags & 0x2000) {
        distance = 0x300;
    }
    
    func_8009A3D0(old_x, old_y, distance);

    ((S_80171FC8_1 *)arg2)->unk_24 = ((S_80171FC8_4 *)((u8 *)arg3 + ((S_80171FC8_0 *)arg3)->unk_8A.s))->unk_74;
    ((S_80171FC8_1 *)arg2)->unk_25 = ((S_80171FC8_4 *)((u8 *)arg3 + ((S_80171FC8_0 *)arg3)->unk_8A.s))->unk_7C;
    ((S_80171FC8_0 *)arg3)->unk_8A.u += 1;

    func_8009A21C(((S_80171FC8_1 *)arg2)->unk_24, ((S_80171FC8_1 *)arg2)->unk_25,
                  (((S_80171FC8_0 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    ((S_80171FC8_0 *)arg3)->unk_2A =
        func_800A0818(old_x, old_y, ((S_80171FC8_1 *)arg2)->unk_24,
                      ((S_80171FC8_1 *)arg2)->unk_25, (u8 *)arg0 + 0x98);

update_state:
    ((S_80171FC8_3 *)arg0)->unk_9A = 0xF;
    ((S_80171FC8_3 *)arg0)->unk_8C = 0;
    (*(s32 *)((u8 *)arg3 + 0x1C)) |= 0x40000000;

    if (D_80083462 & 0x80) {
        ((S_80171FC8_3 *)arg0)->unk_96 = 0;
        goto done;
    }

    ((S_80171FC8_3 *)arg0)->unk_96 = 8;
    count = ((S_80171FC8_0 *)arg3)->unk_71.u;
    if (count > 0) {
        ((S_80171FC8_3 *)arg0)->unk_96 = 8 / count;
    }

done:
    return;
}
