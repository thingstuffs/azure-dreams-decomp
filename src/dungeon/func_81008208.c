#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173A08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xC];
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_80173A08_0;   /* arg0 in func_80173A08 */




typedef struct S_80173A08_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80173A08_4;   /* global_base in func_80173A08 */

typedef struct S_80173A08_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173A08_5;   /* map_base in func_80173A08 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171058[];
extern u8 D_801748A0[];
extern u8 D_801748A8[];
extern u8 D_801748B0[];

void func_80173A08(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch[2];
    s32 state;
    s32 remaining;
    s32 tile_x;
    s32 x;
    s32 temp_v0;
    s32 velocity;
    s32 y;
    s32 sum;
    s32 counter;
    s32 entity_mask;
    s32 timer;
    s32 flags;
    s32 index;
    register u8 *table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *global_base;
    u8 *map_base;

    state = ((S_80173A08_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto tick;

state_zero:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto tick;
    }
    table = D_801748A0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    ((S_80173A08_0 *)arg0)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_80173A08_0 *)arg0)->unk_B0.s = 5;
    ((S_80173A08_0 *)arg0)->unk_A0 = 0;
    ((S_80173A08_0 *)arg0)->unk_9B++;
    goto tick;

state_one:
    ((S_80173A08_0 *)arg0)->unk_90 += 0xC0000;
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto tick;
    }
    table = D_801748A8;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    ((S_80173A08_0 *)arg0)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_80173A08_0 *)arg0)->unk_B0.s = 5;
    ((S_80173A08_0 *)arg0)->unk_A0 = 0;
    ((S_80173A08_0 *)arg0)->unk_90 -= 0x400000;
    ((S_80173A08_0 *)arg0)->unk_9B++;

state_two:
    remaining = ((S_80173A08_0 *)arg0)->unk_B0.s;
    ((S_80173A08_0 *)arg0)->unk_90 -= ((S_80173A08_0 *)arg0)->unk_A0;
    if (remaining != 0) {
        tile_x = ((Rec_D_80082E80 *)arg2)->unk_24;
        x = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
        tile_x <<= 6;
        x -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((tile_x - x) << 16) / remaining;

        y = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
        y -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)arg2)->unk_25 << 6) - y) << 16) /
            ((S_80173A08_0 *)arg0)->unk_B0.s;

        temp_v0 = (0 - func_800644B8(((S_80173A08_0 *)arg0)->unk_B0.s * 0x199)) << 10;
        ((S_80173A08_0 *)arg0)->unk_A0 = temp_v0 + (temp_v0 >> 1);
    }

    sum = ((S_80173A08_0 *)arg0)->unk_90;
    velocity = ((S_80173A08_0 *)arg0)->unk_A0;
    counter = ((S_80173A08_0 *)arg0)->unk_B0.u;
    sum += velocity;
    counter -= 1;
    ((S_80173A08_0 *)arg0)->unk_B0.u = counter;
    ((S_80173A08_0 *)arg0)->unk_90 = sum;
    if ((counter << 16) >= 0) {
        goto state_three;
    }

    entity_mask = 0x08000000;
    ASM_KEEP(entity_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80173A08_0 *)arg0)->unk_90 = 0;
    ((S_80173A08_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 |= entity_mask;
    table = D_801748B0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    ((S_80173A08_0 *)arg0)->unk_9B++;

state_three:
    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x08000000)) {
        goto tick;
    }
    ((S_80173A08_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    table = D_801748B0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    ((S_80173A08_0 *)arg0)->unk_9B++;

tick:
    timer = ((S_80173A08_0 *)arg0)->unk_96 - 1;
    ((S_80173A08_0 *)arg0)->unk_96 = timer;
    if ((timer << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global_base = (u8 *)&D_80083460;
    if (((S_80173A08_4 *)global_base)->unk_08.s != 0) {
        ((S_80173A08_4 *)global_base)->unk_08.u--;
    }

    flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    if (flags & 0x2000) {
        if (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) {
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
        }
        goto finish;
    }
    if (flags & 0x410) {
        goto finish;
    }
    if (flags & 0x20000) {
        map_base = D_80082E80;
        ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
            ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
            ((S_80173A08_5 *)map_base)->unk_24, ((S_80173A08_5 *)map_base)->unk_25, scratch);
    }

finish:
    ((S_80173A08_0 *)arg0)->unk_8C = D_80171058;
    func_800A9A04(arg3);
}
