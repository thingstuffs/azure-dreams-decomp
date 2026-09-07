#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80042640(void *, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);
extern void *func_800D3F74(s32, s16, s16, s16);
extern void func_80174084(void *, void *, void *);
extern void *func_801742AC(void *, void *, void *);
extern void func_80174460(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;
extern s32 D_8008346C;
extern u8 D_80170E5C[];

void func_80173A20(void *actor, void *context, void *entity, void *creature)
{
    switch (FIELD(actor, u8, 0x9B)) {
    case 0: {
        u16 flags = FIELD(entity, u16, 0x14);

        if (flags & 0x8000) {
            FIELD(entity, u16, 0x14) = flags | 0x6000;
            FIELD(actor, u8, 0x9B) = 2;
            return;
        }
        FIELD(actor, u8, 0x9B) = 1;
    }
        /* fall through */
    case 1:
        if (((FIELD(entity, s8, 4) == 8) &&
             (FIELD(entity, u16, 0x14) & 0x1000)) ||
            (FIELD(entity, u16, 0x14) & 0xE000)) {
            func_80174460(creature);
            func_800A56E0(0x80C);
            func_80174084(actor, context, entity);
            FIELD(actor, void *, 0xA4) = func_801742AC(actor, context, entity);
            FIELD(actor, u8, 0x9B)++;
        }
        return;

    case 2: {
        register s32 value ASM_REG("$2");
        register s32 total ASM_REG("$3");
        register s32 bump ASM_REG("$4");
        u32 index;
        u32 shifted;
        u8 *xbase;
        u32 bit;
        s32 flag;
        s16 height;
        u16 raw;
        s32 xarg;
        s16 *xoff;
        s16 *yoff;
        void *shadow;
        void *object;

        if (!(FIELD(entity, u16, 0x14) & 0xE000)) {
            return;
        }

        shadow = FIELD(actor, void *, 0xA4);
        FIELD(shadow, u16, 0x1E) |= 0x8000;

        flag = D_800814A0;
        shifted = FIELD(creature, u16, 0x2A) >> 8;
        raw = FIELD(creature, u16, 0x88);
        D_800814A0 = flag | 0x8000;

        xbase = (u8 *)&D_8006CCD8;
        index = shifted & 0xE;
        xoff = (s16 *)(xbase + index);
        xarg = ((FIELD(entity, u8, 0x24) + *xoff) << 6) & 0xFFC0;
        yoff = (s16 *)((u8 *)&D_8006CCE8 + index);
        height = func_800BCB04(xarg,
            ((FIELD(entity, u8, 0x25) + *yoff) << 6) & 0xFFC0,
            (s16)(raw - 0x20));

        if (FIELD(creature, s16, 0x88) < height) {
            height = FIELD(creature, u16, 0x88);
        }

        bit = FIELD(creature, u32, 0x1C) & 0x2000;
        object = func_800D3F74(
            bit != 0,
            (s16)(FIELD(entity, u8, 0x24) + (u16)*xoff),
            (s16)(FIELD(entity, u8, 0x25) + (u16)*yoff),
            height);
        func_80042640(object, 0x36);

        bump = (FIELD(creature, u8, 0x11) * 2) + (func_800A6D30() & 3);
        total = FIELD(object, u8, 0x29) + bump;
        value = total;
        ASM_KEEP(value);
        if (total >= 0x100) {
            value = 0xFF;
        }
        FIELD(object, u8, 0x28) = value;
        FIELD(object, u8, 0x29) = value;

        func_800AD594(creature, 0x400);
        func_800A2B04(context, FIELD(entity, u8, 0x24),
                     FIELD(entity, u8, 0x25));
        FIELD(actor, void *, 0x8C) = D_80170E5C;
        D_8008346C = 0;
        FIELD(creature, u16, 0x46) &= 0x7FFF;
        return;
    }
    }
}
