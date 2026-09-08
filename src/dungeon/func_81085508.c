#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172D08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xB];
    u8 unk_AF;
} S_80172D08_0;   /* arg0 in func_80172D08 */


typedef struct S_80172D08_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_80172D08_2;   /* arg3 in func_80172D08 */

typedef struct S_80172D08_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172D08_3;   /* arg1 in func_80172D08 */

typedef struct S_80172D08_4_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80172D08_4_pre;   /* the 0x18 bytes before owner in func_80172D08, addressed as owner[-1] */

typedef struct S_80172D08_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80172D08_4;   /* owner in func_80172D08 */

typedef struct S_80172D08_5 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80172D08_5;   /* ((S_80172D08_2 *)arg3)->unk_60 in func_80172D08 */



extern s32 func_800644B8(s32);
extern s32 func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800A44E0(s32, s32, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s32 func_800BCB04(s32, s32, s16);
extern void func_80174A6C(void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_8008346C;
extern u8 D_800DDC40[];
extern u8 D_80170838[16];
extern u8 D_80170E94;

void func_80172D08(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&state_zero, &&state_one,
                                       &&state_two, &&state_three,
                                       &&state_four };

    state = ((S_80172D08_0 *)arg0)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    (void)keepalive;
    goto *(((void **)D_80170838)[state]);

state_zero: {
    s32 direction;
    s32 value;

    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172D08_0 *)arg0)->unk_9B = 4;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80172D08_2 *)arg3)->unk_2A.s, 1);
        return;
    }

    ((S_80172D08_0 *)arg0)->unk_AF = 0;
    if (((S_80172D08_2 *)arg3)->unk_60 == 0) {
        direction = (((S_80172D08_2 *)arg3)->unk_2A.u >> 9) & 7;
        if ((s16)func_800A44E0(((Rec_D_80082E80 *)arg2)->unk_24 << 6,
                               ((Rec_D_80082E80 *)arg2)->unk_25 << 6,
                               ((S_80172D08_2 *)arg3)->unk_88.s,
                               direction << 9) == 0) {
            value = func_800BCB04(
                (((((Rec_D_80082E80 *)arg2)->unk_24 +
                   ((s16 *)&D_8006CCD8)[direction]) << 6) + 0x20) & 0xFFE0,
                (((((Rec_D_80082E80 *)arg2)->unk_25 +
                   ((s16 *)&D_8006CCE8)[direction]) << 6) + 0x20) & 0xFFE0,
                (s16)(((S_80172D08_2 *)arg3)->unk_88.u - 0x20));
            if ((u16)(value - ((S_80172D08_2 *)arg3)->unk_88.u + 0x3F) >= 0x7F) {
                ((S_80172D08_0 *)arg0)->unk_AF = 1;
            }
        } else {
            ((S_80172D08_0 *)arg0)->unk_AF = 1;
        }
    }

    ((S_80172D08_3 *)arg1)->unk_14 = 0;
    ((S_80172D08_3 *)arg1)->unk_10 = 0;
    ((S_80172D08_3 *)arg1)->unk_0C = 0;
    ((S_80172D08_0 *)arg0)->unk_96.s = 6;
    ((S_80172D08_0 *)arg0)->unk_9B++;
}

state_one: {
    s16 timer;
    s32 direction;

    timer = ((S_80172D08_0 *)arg0)->unk_96.u - 1;
    ((S_80172D08_0 *)arg0)->unk_96.u = timer;
    if ((timer << 16) != 0) {
        return;
    }

    if (((S_80172D08_0 *)arg0)->unk_AF == 0) {
        direction = (((S_80172D08_2 *)arg3)->unk_2A.u >> 8) & 0xE;
        ((S_80172D08_3 *)arg1)->unk_0C =
            (((s16 *)&D_8006CCD8)[direction >> 1] << 22) / 8;
        ((S_80172D08_3 *)arg1)->unk_10 =
            (((s16 *)&D_8006CCE8)[direction >> 1] << 22) / 8;
    }
    ((S_80172D08_0 *)arg0)->unk_98 |= 0xC;
    ((S_80172D08_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_80172D08_0 *)arg0)->unk_A0 = 0;
    ((S_80172D08_0 *)arg0)->unk_96.s = 0x10;
    ((S_80172D08_0 *)arg0)->unk_9B++;
    return;
}

state_two: {
    s16 timer;
    s16 next_timer;
    register s32 vertical_out ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 vertical_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ((S_80172D08_0 *)arg0)->unk_90 -= ((S_80172D08_0 *)arg0)->unk_A0;
    timer = ((S_80172D08_0 *)arg0)->unk_96.s;
    if (timer >= 9) {
        if (((S_80172D08_2 *)arg3)->unk_60 != 0) {
            register s32 scaled_value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 scale ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 vertical ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 scaled_shifted;
            s32 value;
            void *owner;

            owner = ((S_80172D08_2 *)arg3)->unk_60;
            owner = ((S_80172D08_4_pre *)owner)[-1].unk_00;
            value = func_800644B8(((S_80172D08_0 *)arg0)->unk_96.s << 7) >> 4;
            scale = D_800DDC40[
                ((S_80172D08_5 *)(((S_80172D08_2 *)arg3)->unk_60))->unk_13] + 0x20;
            scaled_value = value * scale;
            vertical = (((S_80172D08_4 *)owner)->unk_0A - ((S_80172D08_2 *)arg3)->unk_88.s) << 13;
            vertical *= 0x11 - ((S_80172D08_0 *)arg0)->unk_96.s;
            scaled_shifted = scaled_value << 8;
            vertical_out = vertical - scaled_shifted;
            goto store_vertical;
        } else if (((S_80172D08_0 *)arg0)->unk_AF != 0) {
            s32 value;

            value = func_800644B8(((S_80172D08_0 *)arg0)->unk_96.s << 7) >> 4;
            ((S_80172D08_0 *)arg0)->unk_A0 = -((value * 3) << 13);
        } else {
            s32 direction;
            s32 scaled_vertical;
            s32 terrain_height;
            register s32 signed_terrain_height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 value;
            s32 vertical;

            direction = (((S_80172D08_2 *)arg3)->unk_2A.u >> 8) & 0xE;
            terrain_height = func_800BCB04(
                (((((Rec_D_80082E80 *)arg2)->unk_24 +
                   ((s16 *)&D_8006CCD8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (((((Rec_D_80082E80 *)arg2)->unk_25 +
                   ((s16 *)&D_8006CCE8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (s16)(((S_80172D08_2 *)arg3)->unk_88.u - 0x20));
            value = func_800644B8(((S_80172D08_0 *)arg0)->unk_96.s << 7);
            signed_terrain_height = terrain_height << 16;
            signed_terrain_height >>= 16;
            vertical = (signed_terrain_height - ((S_80172D08_2 *)arg3)->unk_88.s) << 13;
            scaled_vertical = vertical * (0x11 - ((S_80172D08_0 *)arg0)->unk_96.s);
            value = ((value >> 4) * 3) << 13;
            ((S_80172D08_0 *)arg0)->unk_A0 = scaled_vertical - value;
        }
    } else {
        ((S_80172D08_3 *)arg1)->unk_10 = 0;
        ((S_80172D08_3 *)arg1)->unk_0C = 0;
        vertical_step = 0x40000;
        vertical_out = ((S_80172D08_0 *)arg0)->unk_A0 + vertical_step;
store_vertical:
        ((S_80172D08_0 *)arg0)->unk_A0 = vertical_out;
    }

    ((S_80172D08_0 *)arg0)->unk_90 += ((S_80172D08_0 *)arg0)->unk_A0;
    next_timer = ((S_80172D08_0 *)arg0)->unk_96.u - 1;
    ((S_80172D08_0 *)arg0)->unk_96.u = next_timer;
    if (next_timer > 0) {
        return;
    }
    func_800A56E0(0x803);
    ((S_80172D08_0 *)arg0)->unk_9B++;
    return;
}

state_three: {
    s32 direction;

    if (((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 0xC) &&
         (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        if (func_8009C12C(arg3, arg2, ((S_80172D08_2 *)arg3)->unk_2A.s, 1) != 0) {
            func_800A56E0(0x809);
            func_80174A6C(arg0, arg1, arg2);
        }
    }

    if (((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 0x14) &&
         (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        if (((S_80172D08_0 *)arg0)->unk_AF == 0) {
            direction = (((S_80172D08_2 *)arg3)->unk_2A.u >> 8) & 0xE;
            ((S_80172D08_3 *)arg1)->unk_0C =
                -((((s16 *)&D_8006CCD8)[direction >> 1] << 22) / 8);
            ((S_80172D08_3 *)arg1)->unk_10 =
                -((((s16 *)&D_8006CCE8)[direction >> 1] << 22) / 8);
        }
        ((S_80172D08_0 *)arg0)->unk_96.s = 8;
        ((S_80172D08_0 *)arg0)->unk_9B++;
    }
    return;
}

state_four: {
    s16 timer;

    ((S_80172D08_0 *)arg0)->unk_90 -= ((S_80172D08_0 *)arg0)->unk_A0;
    timer = ((S_80172D08_0 *)arg0)->unk_96.u - 1;
    ((S_80172D08_0 *)arg0)->unk_96.u = timer;
    if (timer >= 0) {
        if (((S_80172D08_2 *)arg3)->unk_60 != 0) {
            s32 movement;
            s32 random_value;
            s32 scaled_movement;
            void *owner;

            owner = ((S_80172D08_2 *)arg3)->unk_60;
            owner = ((S_80172D08_4_pre *)owner)[-1].unk_00;
            random_value = func_800644B8(((S_80172D08_0 *)arg0)->unk_96.s << 8);
            movement = ((S_80172D08_4 *)owner)->unk_0A -
                       D_800DDC40[((S_80172D08_5 *)(((S_80172D08_2 *)arg3)->unk_60))->unk_13] -
                       ((S_80172D08_2 *)arg3)->unk_88.s;
            movement <<= 13;
            scaled_movement = movement * ((S_80172D08_0 *)arg0)->unk_96.s;
            random_value = (random_value >> 4) << 13;
            ((S_80172D08_0 *)arg0)->unk_A0 = scaled_movement - random_value;
        } else if (((S_80172D08_0 *)arg0)->unk_AF != 0) {
            s32 value;

            value = func_800644B8(((S_80172D08_0 *)arg0)->unk_96.s << 8) >> 4;
            ((S_80172D08_0 *)arg0)->unk_A0 =
                -(((S_80172D08_0 *)arg0)->unk_96.s << 19) - (value << 13);
            goto vertical_done;
        } else {
            s32 direction;
            s32 movement;
            s32 random_value;
            s32 scaled_movement;
            s32 terrain_height;
            register s32 signed_terrain_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 base_height;

            direction = (((S_80172D08_2 *)arg3)->unk_2A.u >> 8) & 0xE;
            terrain_height = func_800BCB04(
                (((((Rec_D_80082E80 *)arg2)->unk_24 +
                   ((s16 *)&D_8006CCD8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (((((Rec_D_80082E80 *)arg2)->unk_25 +
                   ((s16 *)&D_8006CCE8)[direction >> 1]) << 6) + 0x20) & 0xFFE0,
                (s16)(((S_80172D08_2 *)arg3)->unk_88.u - 0x20));
            random_value = func_800644B8(((S_80172D08_0 *)arg0)->unk_96.s << 8);
            signed_terrain_height = terrain_height << 16;
            signed_terrain_height >>= 16;
            base_height = ((S_80172D08_2 *)arg3)->unk_88.s;
            base_height += 0x40;
            movement = signed_terrain_height - base_height;
            movement <<= 13;
            scaled_movement = movement * ((S_80172D08_0 *)arg0)->unk_96.s;
            random_value = (random_value >> 4) << 13;
            ((S_80172D08_0 *)arg0)->unk_A0 = scaled_movement - random_value;
        }
    } else {
        ((S_80172D08_3 *)arg1)->unk_14 = 0;
        ((S_80172D08_3 *)arg1)->unk_10 = 0;
        ((S_80172D08_3 *)arg1)->unk_0C = 0;
        ((S_80172D08_0 *)arg0)->unk_A0 = 0;
    }

vertical_done:
    ((S_80172D08_0 *)arg0)->unk_90 += ((S_80172D08_0 *)arg0)->unk_A0;
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        ((S_80172D08_3 *)arg1)->unk_14 = 0;
        ((S_80172D08_3 *)arg1)->unk_10 = 0;
        ((S_80172D08_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24,
                      ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3, 0x200);
        ((S_80172D08_0 *)arg0)->unk_8C = &D_80170E94;
        D_8008346C = 0;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        ((S_80172D08_0 *)arg0)->unk_98 &= 0xFFF3;
        ((S_80172D08_2 *)arg3)->unk_1C |= 0x08000000;
        func_800A4ACC(arg3);
    }
}
}
