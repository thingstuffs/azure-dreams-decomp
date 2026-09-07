#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t az_uptr;
#else
typedef u32 az_uptr;
#endif

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172790_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172790_0;   /* arg3 in func_80172790 */

typedef struct S_80172790_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80172790_1;   /* arg0 in func_80172790 */

typedef struct S_80172790_2 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80172790_2;   /* object in func_80172790 */

typedef struct S_80172790_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
    volatile u16 unk_18;
    u8 pad_1A[0x2E];
    volatile s16 unk_48;
    u8 pad_4A[0x2];
    volatile s16 unk_4C;
} S_80172790_3;   /* part in func_80172790 */

typedef struct S_80172790_4 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172790_4;   /* arg1 in func_80172790 */

typedef struct S_80172790_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
} S_80172790_5;   /* sprite in func_80172790 */

typedef struct S_80172790_6 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172790_6;   /* arg2 in func_80172790 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80045340;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern s32 D_80083498;
extern u8 D_800DEC28[];
extern void *D_800E3DE8;
extern u8 D_80171400[];
extern u8 D_801743EC[];
extern u8 D_80175148[];
extern u8 D_80175160[];

void func_80172790(void *in0, void *in1, void *in2, void *in3)
{
    s32 stack_value;
    u8 *table0;
    s32 floor0;
    s32 slot0;
    u8 *table1;
    s32 floor1;
    s32 slot1;
    register s32 heading ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 offset ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 scaled ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 state;
    register s32 counter ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    s32 rng;
    s32 fall_speed;
    u16 flags;
    s32 velocity;
    s32 origin;
    s32 origin_y;
    s32 vx;
    s32 vy;
    s32 vz;
    u32 color;
    s32 sprite_value;
    u8 *sprite_data;
    s32 x_step;
    s32 y_step;
    s32 x_pos;
    u16 heading_raw;
    void *object;
    void *part;
    void *sprite;
    void *arg0;
    void *arg1;
    void *arg2;
    void *arg3;
    register u8 *x_base ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    arg0 = in0;
    arg1 = in1;
    arg2 = in2;
    arg3 = in3;
    x_base = (u8 *)0x80070000;
    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(x_base);   /* MATCH pin: retail immediate-load split depends on it */

    heading_raw = ((S_80172790_0 *)arg3)->unk_2A.s;
    ASM_KEEP(heading_raw);   /* MATCH pin: load-bearing for the whole function shape */
    x_base -= 0x3328;
    heading = heading_raw >> 8;
    offset = heading & 0xE;
    ASM_KEEP(offset);   /* MATCH pin: load-bearing for the whole function shape */
    x_base = (u8 *)((az_uptr)offset + (az_uptr)x_base);
    x_step = *(s16 *)x_base;
    y_step = *(s16 *)(offset + (u8 *)D_8006CCE8);
    ((S_80172790_1 *)arg0)->unk_96.s--;

    if ((u32)(((S_80172790_1 *)arg0)->unk_9B - 1) < 3U) {
        counter = 15;
        stack_value = (x_step << 5) - 8;
        do {
            object = func_8003FD64(0x312, &D_80083498);
            if (object != NULL) {
                func_8004491C(object, &D_80045340);
                part = (u8 *)object + 0x20;
                ((S_80172790_2 *)object)->unk_10 = D_801743EC;
                sprite = ((S_80172790_2 *)object)->unk_0C;
                if (((S_80172790_1 *)arg0)->unk_9B < 3U) {
                    ((S_80172790_3 *)part)->unk_0C = ((S_80172790_4 *)arg1)->unk_02.s + (rand() & 0xF) - 8;
                    rng = rand();
                    fall_speed = -0x500;
                    ASM_KEEP(fall_speed);   /* MATCH pin: retail register colouring depends on it */
                    x_pos = ((S_80172790_4 *)arg1)->unk_06.s;
                    rng &= 0xF;
                    ((S_80172790_3 *)part)->unk_16 = fall_speed;
                    x_pos += rng;
                    x_pos -= 8;
                } else {
                    ((S_80172790_3 *)part)->unk_0C = ((S_80172790_4 *)arg1)->unk_02.s + (rand() & 0xF) + stack_value;
                    rng = rand();
                    fall_speed = -0x200;
                    ASM_KEEP(fall_speed);   /* MATCH pin: retail register colouring depends on it */
                    x_pos = ((S_80172790_4 *)arg1)->unk_06.s;
                    rng &= 0xF;
                    ((S_80172790_3 *)part)->unk_16 = fall_speed;
                    x_pos += rng;
                    rng = (y_step << 5) - 8;
                    x_pos += rng;
                }
                ((S_80172790_3 *)part)->unk_0E = x_pos;
                ((S_80172790_3 *)part)->unk_10 = ((S_80172790_4 *)arg1)->unk_0A + 8;
                ((S_80172790_3 *)part)->unk_14 = rand();
                heading_raw = ((S_80172790_0 *)arg3)->unk_2A.s;
                do {
                    color = 0x00C00000;
                } while (0);
                ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
                ((S_80172790_3 *)part)->unk_4C = 0;
                ((S_80172790_3 *)part)->unk_48 = 0;
                ((S_80172790_3 *)part)->unk_18 = heading_raw;
                (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
                (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
                (*(s16 *)((u8 *)sprite + 0x10)) = 0x60;
                sprite_data = D_800DEC28;
                (*(void * *)((u8 *)sprite + 0)) = sprite_data;
                (*(u16 *)((u8 *)sprite + 0x14)) |= 0xC;
                sprite_value = *(s32 *)(sprite_data + 4);
                color |= 0xC0C0;
                ((S_80172790_5 *)sprite)->unk_04 = 0;
                ((S_80172790_5 *)sprite)->unk_05 = 0;
                (*(s32 *)((u8 *)sprite + 0xC)) = color;
                ((S_80172790_5 *)sprite)->unk_08 = sprite_value;
            }
            counter--;
        } while (counter >= 0);
    }

    state = ((S_80172790_1 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        flags = ((S_80172790_6 *)arg2)->unk_14;
        if (flags & 0x8000) {
            ((S_80172790_1 *)arg0)->unk_9B = 0xFF;
            ((S_80172790_6 *)arg2)->unk_14 |= 0x6000;
            func_8009C12C(arg3, arg2, ((S_80172790_0 *)arg3)->unk_2A.u, 1);
            goto end;
        }
        if (flags & 0xE000) {
            table0 = D_80175160;
            (*(void * *)((u8 *)arg2 + 0x2C)) = table0;
            floor0 = D_80083228 + ((S_80172790_0 *)arg3)->unk_2A.u;
            slot0 = ((floor0 + 0x100) >> 9) & 7;
            func_80047784(arg2, table0[slot0], 0);
            ((S_80172790_4 *)arg1)->unk_0C = (-x_step) << 0x12;
            ((S_80172790_4 *)arg1)->unk_10 = (-y_step) << 0x12;
            ((S_80172790_1 *)arg0)->unk_98 |= 8;
            ((S_80172790_0 *)arg3)->unk_1C &= 0xF7FFFFFF;
            ((S_80172790_0 *)arg3)->unk_1C &= 0xFFFBFFFF;
            ((S_80172790_1 *)arg0)->unk_96.s = 4;
            ((S_80172790_4 *)arg1)->unk_14 = 0xFFFC0000;
            goto advance;
        }
        goto end;

    case 1:
        velocity = ((S_80172790_4 *)arg1)->unk_14;
        ((S_80172790_4 *)arg1)->unk_14 = velocity + (velocity >> 2);
        if (((S_80172790_1 *)arg0)->unk_96.u <= 0) {
            ((S_80172790_1 *)arg0)->unk_96.u = 3;
            ((S_80172790_1 *)arg0)->unk_9B++;
            goto end;
        }
        goto end;

    case 2:
        vx = ((S_80172790_4 *)arg1)->unk_0C;
        vy = ((S_80172790_4 *)arg1)->unk_10;
        ((S_80172790_4 *)arg1)->unk_0C = vx - (vx >> 2);
        vz = ((S_80172790_4 *)arg1)->unk_14;
        ((S_80172790_4 *)arg1)->unk_10 = vy - (vy >> 2);
        ((S_80172790_4 *)arg1)->unk_14 = vz - (vz >> 2);
        if (((S_80172790_1 *)arg0)->unk_96.u <= 0) {
            ((S_80172790_1 *)arg0)->unk_96.u = 7;
            ((S_80172790_4 *)arg1)->unk_0C = x_step << 0x12;
            ((S_80172790_4 *)arg1)->unk_10 = y_step << 0x12;
            ((S_80172790_4 *)arg1)->unk_14 = 0x30000;
            func_800A56E0(0x80E);
            goto advance;
        }
        goto end;

advance:
        ((S_80172790_1 *)arg0)->unk_9B++;
        goto end;

    case 3:
        ((S_80172790_4 *)arg1)->unk_0C += x_step << 0x12;
        ((S_80172790_4 *)arg1)->unk_10 += y_step << 0x12;
        if (((S_80172790_1 *)arg0)->unk_96.u < 2) {
            ((S_80172790_4 *)arg1)->unk_10 = 0;
            ((S_80172790_4 *)arg1)->unk_0C = 0;
        }
        if (((S_80172790_1 *)arg0)->unk_96.u == 1) {
            func_8009C12C(arg3, arg2, ((S_80172790_0 *)arg3)->unk_2A.u, 1);
            func_800A56E0(0x808);
        }
        if (((S_80172790_1 *)arg0)->unk_96.u <= 0) {
            ((S_80172790_4 *)arg1)->unk_14 = 0xFFF60000;
            ((S_80172790_1 *)arg0)->unk_96.u = 0x14;
            ((S_80172790_1 *)arg0)->unk_9B = 0xFF;
        }
        goto end;

    case 0xFF:
        scaled = ((S_80172790_6 *)arg2)->unk_24 << 6;
        origin = ((S_80172790_4 *)arg1)->unk_02.u - 0x20;
        scaled -= origin;
        scaled <<= 0xF;
        scaled >>= 1;
        ((S_80172790_4 *)arg1)->unk_0C = scaled;
        scaled = ((S_80172790_6 *)arg2)->unk_25 << 6;
        origin_y = ((S_80172790_4 *)arg1)->unk_06.u - 0x20;
        scaled -= origin_y;
        scaled <<= 0xF;
        scaled >>= 1;
        ((S_80172790_4 *)arg1)->unk_10 = scaled;
        if (((S_80172790_1 *)arg0)->unk_96.u >= 0xA) {
            ((S_80172790_4 *)arg1)->unk_14 += 0x10000;
        } else {
            ((S_80172790_4 *)arg1)->unk_14 = -((S_80172790_1 *)arg0)->unk_92 << 0xD;
        }
        if (((S_80172790_1 *)arg0)->unk_96.u > 0 && !(((S_80172790_6 *)arg2)->unk_14 & 0x8000)) {
            goto end;
        }
        ((S_80172790_4 *)arg1)->unk_10 = 0;
        ((S_80172790_4 *)arg1)->unk_0C = 0;
        ((S_80172790_0 *)arg3)->unk_1C |= 0x40000;
        func_800A2B04(arg1, ((S_80172790_6 *)arg2)->unk_24, ((S_80172790_6 *)arg2)->unk_25);
        func_800AD594(arg3, 0x100);
        ((S_80172790_1 *)arg0)->unk_8C = D_80171400;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((S_80172790_4 *)arg1)->unk_14 = 0;
        ((S_80172790_1 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172790_0 *)arg3)->unk_1C |= 0x08000000;
        ((S_80172790_1 *)arg0)->unk_A8 = 7;
        table1 = D_80175148;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table1;
        floor1 = D_80083228 + ((S_80172790_0 *)arg3)->unk_2A.u;
        slot1 = ((floor1 + 0x100) >> 9) & 7;
        func_80047784(arg2, table1[slot1], 2);
        if (((S_80172790_0 *)arg3)->unk_6D == 0) {
            ((S_80172790_0 *)arg3)->unk_46 &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)arg3 - 0x20;
        }
        goto end;

    default:
        goto end;
    }
end:
    return;
}
