#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Offset3;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position3;

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorPart;

extern s32 D_800814A0;
extern u8 D_800DDC42;

extern void func_800F749C(void *, Position3 *, void *);
extern void func_800F7830(void) __attribute__((noreturn));

void func_807AFDEC(void *arg0, Position3 *arg1, ColorPart *arg2)
{
    void *call_base;
    Offset3 offset;
    Position3 *source;
    s32 color;
    u16 value;
    s16 timer;

    offset.x = 0;
    offset.y = 0;
    offset.z = -D_800DDC42 - 8;

    source = FIELD(FIELD(arg0, void *, 0), Position3 *, -0x18);
    value = source->x;
    arg1->x = value;
    arg1->y = source->y + offset.y;
    arg1->z = source->z + offset.z;

    if (FIELD(arg0, s16, 8) == 0) {
        color = arg2->b | (arg2->r | arg2->g);
        color += (0xC0 - color) / FIELD(arg0, s16, 0xC);

        if (FIELD(FIELD(arg0, void *, 0), s32, 0x14) & 1) {
            arg2->r = color;
        }
        if (FIELD(FIELD(arg0, void *, 0), s32, 0x14) & 4) {
            arg2->g = color;
        }
        if (FIELD(FIELD(arg0, void *, 0), s32, 0x14) & 2) {
            arg2->b = color;
        }

        {
            call_base = (u8 *)arg0 - 0x20;

            if (FIELD(arg0, s16, 0xC) >= 8) {
                func_800F749C(call_base, arg1, FIELD(arg0, void *, 0));
                func_800F749C(call_base, arg1, FIELD(arg0, void *, 0));
                func_800F749C(call_base, arg1, FIELD(arg0, void *, 0));
            }

            timer = FIELD(arg0, u16, 0xC) - 1;
            FIELD(arg0, u16, 0xC) = timer;
            if ((timer << 16) <= 0) {
                FIELD(arg0, u16, 0xC) = 8;
                FIELD(arg0, u16, 8)++;
                func_800F7830();
            }
        }
    } else {
        color = arg2->b | (arg2->r | arg2->g);
        color += -color / FIELD(arg0, s16, 0xC);

        if (FIELD(FIELD(arg0, void *, 0), s32, 0x14) & 1) {
            arg2->r = color;
        }
        if (FIELD(FIELD(arg0, void *, 0), s32, 0x14) & 4) {
            arg2->g = color;
        }
        if (FIELD(FIELD(arg0, void *, 0), s32, 0x14) & 2) {
            arg2->b = color;
        }

        timer = FIELD(arg0, u16, 0xC) - 1;
        FIELD(arg0, u16, 0xC) = timer;
        if ((timer << 16) <= 0) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
