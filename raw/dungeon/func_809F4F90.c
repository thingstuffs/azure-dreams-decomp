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

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

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
    register s32 heading ASM_REG("$19");
    register s32 offset ASM_REG("$4");
    register s32 scaled ASM_REG("$2");
    s32 state;
    register s32 counter ASM_REG("$19");
    s32 rng;
    register s32 fall_speed ASM_REG("$3");
    u16 flags;
    s32 velocity;
    s32 origin;
    s32 origin_y;
    s32 vx;
    s32 vy;
    s32 vz;
    register u32 color ASM_REG("$4");
    s32 sprite_value;
    u8 *sprite_data;
    s32 x_step;
    s32 y_step;
    register s32 x_pos ASM_REG("$4");
    register u16 heading_raw ASM_REG("$2");
    void *object;
    void *part;
    void *sprite;
    register void *arg0 ASM_REG("$20");
    void *arg1;
    void *arg2;
    void *arg3;
    register u8 *x_base ASM_REG("$3");

    arg0 = in0;
    arg1 = in1;
    arg2 = in2;
    arg3 = in3;
    x_base = (u8 *)0x80070000;
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    ASM_KEEP(x_base);

    heading_raw = FIELD(arg3, u16, 0x2A);
    ASM_KEEP(heading_raw);
    x_base -= 0x3328;
    ASM_KEEP_NV(x_base);
    heading = heading_raw >> 8;
    offset = heading & 0xE;
    ASM_KEEP(offset);
    x_base = (u8 *)((az_uptr)offset + (az_uptr)x_base);
    x_step = *(s16 *)x_base;
    y_step = *(s16 *)(offset + (u8 *)D_8006CCE8);
    FIELD(arg0, u16, 0x96)--;

    if ((u32)(FIELD(arg0, u8, 0x9B) - 1) < 3U) {
        counter = 15;
        stack_value = (x_step << 5) - 8;
        do {
            object = func_8003FD64(0x312, &D_80083498);
            if (object != NULL) {
                func_8004491C(object, &D_80045340);
                part = (u8 *)object + 0x20;
                FIELD(object, void *, 0x10) = D_801743EC;
                sprite = FIELD(object, void *, 0xC);
                if (FIELD(arg0, u8, 0x9B) < 3U) {
                    FIELD(part, s16, 0xC) = FIELD(arg1, u16, 2) + (rand() & 0xF) - 8;
                    rng = rand();
                    fall_speed = -0x500;
                    ASM_KEEP(fall_speed);
                    x_pos = FIELD(arg1, u16, 6);
                    rng &= 0xF;
                    FIELD(part, s16, 0x16) = fall_speed;
                    x_pos += rng;
                    x_pos -= 8;
                } else {
                    FIELD(part, s16, 0xC) = FIELD(arg1, u16, 2) + (rand() & 0xF) + stack_value;
                    rng = rand();
                    fall_speed = -0x200;
                    ASM_KEEP(fall_speed);
                    x_pos = FIELD(arg1, u16, 6);
                    rng &= 0xF;
                    FIELD(part, s16, 0x16) = fall_speed;
                    x_pos += rng;
                    rng = (y_step << 5) - 8;
                    x_pos += rng;
                }
                FIELD(part, s16, 0xE) = x_pos;
                FIELD(part, s16, 0x10) = FIELD(arg1, u16, 0xA) + 8;
                FIELD(part, s16, 0x14) = rand();
                heading_raw = FIELD(arg3, u16, 0x2A);
                do {
                    color = 0x00C00000;
                } while (0);
                ASM_KEEP(color);
                FIELD(part, volatile s16, 0x4C) = 0;
                FIELD(part, volatile s16, 0x48) = 0;
                FIELD(part, volatile u16, 0x18) = heading_raw;
                FIELD(sprite, s16, 0x1E) = 0x1000;
                FIELD(sprite, s16, 0x1C) = 0x1000;
                FIELD(sprite, s16, 0x10) = 0x60;
                sprite_data = D_800DEC28;
                FIELD(sprite, void *, 0) = sprite_data;
                FIELD(sprite, u16, 0x14) |= 0xC;
                sprite_value = *(s32 *)(sprite_data + 4);
                color |= 0xC0C0;
                FIELD(sprite, s8, 4) = 0;
                FIELD(sprite, s8, 5) = 0;
                FIELD(sprite, s32, 0xC) = color;
                FIELD(sprite, s32, 8) = sprite_value;
            }
            counter--;
        } while (counter >= 0);
    }

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        flags = FIELD(arg2, u16, 0x14);
        if (flags & 0x8000) {
            FIELD(arg0, u8, 0x9B) = 0xFF;
            FIELD(arg2, u16, 0x14) |= 0x6000;
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
            goto end;
        }
        if (flags & 0xE000) {
            table0 = D_80175160;
            FIELD(arg2, void *, 0x2C) = table0;
            floor0 = D_80083228 + FIELD(arg3, s16, 0x2A);
            slot0 = ((floor0 + 0x100) >> 9) & 7;
            func_80047784(arg2, table0[slot0], 0);
            FIELD(arg1, s32, 0xC) = (-x_step) << 0x12;
            FIELD(arg1, s32, 0x10) = (-y_step) << 0x12;
            FIELD(arg0, u16, 0x98) |= 8;
            FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
            FIELD(arg3, s32, 0x1C) &= 0xFFFBFFFF;
            FIELD(arg0, u16, 0x96) = 4;
            FIELD(arg1, s32, 0x14) = 0xFFFC0000;
            goto advance;
        }
        goto end;

    case 1:
        velocity = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) = velocity + (velocity >> 2);
        if (FIELD(arg0, s16, 0x96) <= 0) {
            FIELD(arg0, s16, 0x96) = 3;
            FIELD(arg0, u8, 0x9B)++;
            goto end;
        }
        goto end;

    case 2:
        vx = FIELD(arg1, s32, 0xC);
        vy = FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 0xC) = vx - (vx >> 2);
        vz = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x10) = vy - (vy >> 2);
        FIELD(arg1, s32, 0x14) = vz - (vz >> 2);
        if (FIELD(arg0, s16, 0x96) <= 0) {
            FIELD(arg0, s16, 0x96) = 7;
            FIELD(arg1, s32, 0xC) = x_step << 0x12;
            FIELD(arg1, s32, 0x10) = y_step << 0x12;
            FIELD(arg1, s32, 0x14) = 0x30000;
            func_800A56E0(0x80E);
            goto advance;
        }
        goto end;

advance:
        FIELD(arg0, u8, 0x9B)++;
        goto end;

    case 3:
        FIELD(arg1, s32, 0xC) += x_step << 0x12;
        FIELD(arg1, s32, 0x10) += y_step << 0x12;
        if (FIELD(arg0, s16, 0x96) < 2) {
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0xC) = 0;
        }
        if (FIELD(arg0, s16, 0x96) == 1) {
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
            func_800A56E0(0x808);
        }
        if (FIELD(arg0, s16, 0x96) <= 0) {
            FIELD(arg1, s32, 0x14) = 0xFFF60000;
            FIELD(arg0, s16, 0x96) = 0x14;
            FIELD(arg0, u8, 0x9B) = 0xFF;
        }
        goto end;

    case 0xFF:
        scaled = FIELD(arg2, u8, 0x24) << 6;
        origin = FIELD(arg1, s16, 2) - 0x20;
        ASM_KEEP_NV(origin);
        scaled -= origin;
        scaled <<= 0xF;
        ASM_KEEP_NV(scaled);
        scaled >>= 1;
        FIELD(arg1, s32, 0xC) = scaled;
        ASM_KEEP(scaled);
        scaled = FIELD(arg2, u8, 0x25) << 6;
        origin_y = FIELD(arg1, s16, 6) - 0x20;
        ASM_KEEP(origin_y);
        scaled -= origin_y;
        scaled <<= 0xF;
        ASM_KEEP_NV(scaled);
        scaled >>= 1;
        FIELD(arg1, s32, 0x10) = scaled;
        if (FIELD(arg0, s16, 0x96) >= 0xA) {
            FIELD(arg1, s32, 0x14) += 0x10000;
        } else {
            FIELD(arg1, s32, 0x14) = -FIELD(arg0, s16, 0x92) << 0xD;
        }
        if (FIELD(arg0, s16, 0x96) > 0 && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            goto end;
        }
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg3, s32, 0x1C) |= 0x40000;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 0x100);
        FIELD(arg0, void *, 0x8C) = D_80171400;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, s32, 0x1C) |= 0x08000000;
        FIELD(arg0, s16, 0xA8) = 7;
        table1 = D_80175148;
        FIELD(arg2, void *, 0x2C) = table1;
        floor1 = D_80083228 + FIELD(arg3, s16, 0x2A);
        slot1 = ((floor1 + 0x100) >> 9) & 7;
        func_80047784(arg2, table1[slot1], 2);
        if (FIELD(arg3, s8, 0x6D) == 0) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
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
