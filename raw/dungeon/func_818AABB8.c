#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80024630(void) __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern u8 D_800240D8[];
extern u8 D_800777DC[];

void *func_800243B8(void *arg0, void *arg1, void *arg2)
{
    s16 amplitude;
    s32 angle_x;
    s32 angle_y;
    void *obj;
    void *data;
    void *sprite;
    void *position;
    register void *ret ASM_REG("$2");
    register s32 tail_z ASM_REG("$4");

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        data = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_800240D8;
        FIELD(obj, void *, 0x20) = arg0;
        FIELD(data, s16, 0x34) = 0;
        FIELD(data, s16, 0x36) = 0;
        FIELD(data, u16, 0x3A) = FIELD(arg0, u16, 0x12);

        amplitude = func_80069EF8() % 48;
        angle_x = func_80069EF8() % 0x1000;
        angle_y = func_80069EF8() % 0x1000;

        FIELD(data, s32, 4) = FIELD(arg1, s32, 0);
        FIELD(data, s32, 8) = FIELD(arg1, s32, 4);
        FIELD(data, s32, 0xC) = FIELD(arg1, s32, 8);

        {
            s32 tx, ty;
            register s32 raw_tx ASM_REG("$2");
            register s32 trig_arg ASM_REG("$4");
            raw_tx = func_800644B8(angle_x);
            trig_arg = angle_y;
            ASM_KEEP4(raw_tx, trig_arg, raw_tx, trig_arg);
            tx = raw_tx;
            ty = func_800644B8(trig_arg);
            tx >>= 4;
            ty >>= 4;
            FIELD(data, s32, 0x1C) = FIELD(arg2, s32, 0) +
                (tx * ty * amplitude);
        }

        {
            s32 tx, ty;
            register s32 raw_tx ASM_REG("$2");
            register s32 trig_arg ASM_REG("$4");
            raw_tx = func_800644B8(angle_x);
            trig_arg = angle_y;
            ASM_KEEP4(raw_tx, trig_arg, raw_tx, trig_arg);
            tx = raw_tx;
            ty = func_80064584(trig_arg);
            tx >>= 4;
            ty >>= 4;
            FIELD(data, s32, 0x20) = FIELD(arg2, s32, 4) +
                (tx * ty * amplitude);
        }

        {
            s32 trig_x;
            trig_x = func_80064584(angle_x);
            FIELD(data, s32, 0x24) = FIELD(arg2, s32, 8) +
                (((trig_x >> 4) * amplitude) << 8);
        }

        FIELD(data, s32, 0x28) = FIELD(data, s32, 0x1C) - FIELD(arg1, s32, 0);
        FIELD(data, s32, 0x2C) = FIELD(data, s32, 0x20) - FIELD(arg1, s32, 4);
        FIELD(data, s32, 0x30) = FIELD(data, s32, 0x24) - FIELD(arg1, s32, 8);

        sprite = FIELD(obj, void *, 0xC);
        FIELD(sprite, u8, 0xE) = 0xFF;
        FIELD(sprite, u8, 0xD) = 0xFF;
        FIELD(sprite, u8, 0xC) = 0xFF;
        FIELD(sprite, s16, 0x1E) = 0x300;
        FIELD(sprite, s16, 0x1C) = 0x300;
        FIELD(sprite, s16, 0x1A) = func_80069EF8() % 0x1000;
        FIELD(sprite, s16, 0x12) = 0x7E06;
        FIELD(sprite, void *, 8) = D_800777DC;
        FIELD(sprite, u16, 0x14) |= 0x100;
        FIELD(sprite, u16, 0x10) |= 0x60;
        FIELD(sprite, u16, 0x14) |= 0xC;

        position = FIELD(obj, void *, 8);
        FIELD(position, s32, 0) = FIELD(arg1, s32, 0);
        FIELD(position, s32, 4) = FIELD(arg1, s32, 4);
        tail_z = FIELD(arg1, s32, 8);
        ASM_UNDEF(ret);
        ret = obj;
        ASM_KEEP4(ret, tail_z, ret, tail_z);
        FIELD(position, s32, 8) = tail_z;
        func_80024630();
    }
    ret = NULL;
    ASM_KEEP(ret);
    return ret;
}
