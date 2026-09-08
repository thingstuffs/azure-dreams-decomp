#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173A20_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
} S_80173A20_0;   /* actor in func_80173A20 */


typedef struct S_80173A20_2 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80173A20_2;   /* shadow in func_80173A20 */

typedef struct S_80173A20_3 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0xA];
    u32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 s; s16 u; } unk_88;   /* accessed as both */
} S_80173A20_3;   /* creature in func_80173A20 */

typedef struct S_80173A20_4 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} S_80173A20_4;   /* object in func_80173A20 */



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
    switch (((S_80173A20_0 *)actor)->unk_9B) {
    case 0: {
        u16 flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v;

        if (flags & 0x8000) {
            ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v = flags | 0x6000;
            ((S_80173A20_0 *)actor)->unk_9B = 2;
            return;
        }
        ((S_80173A20_0 *)actor)->unk_9B = 1;
    }
        /* fall through */
    case 1:
        if (((((Rec_D_80082E80 *)entity)->unk_04.as_s8 == 8) &&
             (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000)) {
            func_80174460(creature);
            func_800A56E0(0x80C);
            func_80174084(actor, context, entity);
            ((S_80173A20_0 *)actor)->unk_A4 = func_801742AC(actor, context, entity);
            ((S_80173A20_0 *)actor)->unk_9B++;
        }
        return;

    case 2: {
        s32 value;
        register s32 total ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 bump ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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

        if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }

        shadow = ((S_80173A20_0 *)actor)->unk_A4;
        ((S_80173A20_2 *)shadow)->unk_1E |= 0x8000;

        flag = D_800814A0;
        shifted = ((S_80173A20_3 *)creature)->unk_2A >> 8;
        raw = ((S_80173A20_3 *)creature)->unk_88.s;
        D_800814A0 = flag | 0x8000;

        xbase = (u8 *)&D_8006CCD8;
        index = shifted & 0xE;
        xoff = (s16 *)(xbase + index);
        xarg = ((((Rec_D_80082E80 *)entity)->unk_24 + *xoff) << 6) & 0xFFC0;
        yoff = (s16 *)((u8 *)&D_8006CCE8 + index);
        height = func_800BCB04(xarg,
            ((((Rec_D_80082E80 *)entity)->unk_25 + *yoff) << 6) & 0xFFC0,
            (s16)(raw - 0x20));

        if (((S_80173A20_3 *)creature)->unk_88.u < height) {
            height = ((S_80173A20_3 *)creature)->unk_88.s;
        }

        bit = ((S_80173A20_3 *)creature)->unk_1C & 0x2000;
        object = func_800D3F74(
            bit != 0,
            (s16)(((Rec_D_80082E80 *)entity)->unk_24 + (u16)*xoff),
            (s16)(((Rec_D_80082E80 *)entity)->unk_25 + (u16)*yoff),
            height);
        func_80042640(object, 0x36);

        bump = (((S_80173A20_3 *)creature)->unk_11 * 2) + (func_800A6D30() & 3);
        total = ((S_80173A20_4 *)object)->unk_29 + bump;
        value = total;
        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (total >= 0x100) {
            value = 0xFF;
        }
        ((S_80173A20_4 *)object)->unk_28 = value;
        ((S_80173A20_4 *)object)->unk_29 = value;

        func_800AD594(creature, 0x400);
        func_800A2B04(context, ((Rec_D_80082E80 *)entity)->unk_24,
                     ((Rec_D_80082E80 *)entity)->unk_25);
        ((S_80173A20_0 *)actor)->unk_8C = D_80170E5C;
        D_8008346C = 0;
        (*(u16 *)((u8 *)creature + 0x46)) &= 0x7FFF;
        return;
    }
    }
}
