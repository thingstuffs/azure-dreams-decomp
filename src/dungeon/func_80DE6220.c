#include "common.h"
#include "records/Rec_func_80173204_arg0.h"
#include "records/Rec_D_80082E80.h"



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

/* Advance the actor state and spawn an adjacent object when entity flags allow. */
void func_80173A20(void *actor, void *context, void *entity, void *creature)
{
    switch (((Rec_func_80173204_arg0 *)actor)->unk_9B) {
    case 0: {
        u16 entity_flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v;

        if (entity_flags & 0x8000) {
            ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v = entity_flags | 0x6000;
            ((Rec_func_80173204_arg0 *)actor)->unk_9B = 2;
            return;
        }
        ((Rec_func_80173204_arg0 *)actor)->unk_9B = 1;
    }
        /* fall through */
    case 1:
        if (((((Rec_D_80082E80 *)entity)->unk_04.as_s8 == 8) &&
             (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000)) {
            func_80174460(creature);
            func_800A56E0(0x80C);
            func_80174084(actor, context, entity);
            ((Rec_func_80173204_arg0 *)actor)->unk_A4 = func_801742AC(actor, context, entity);
            ((Rec_func_80173204_arg0 *)actor)->unk_9B++;
        }
        return;

    case 2: {
        s32 object_value;
        register s32 value_total ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 value_bonus ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u32 offset_index;
        u32 direction_bits;
        u8 *x_offsets;
        u32 object_flag;
        s32 global_flags;
        s16 spawn_height;
        u16 creature_height;
        s32 world_x;
        s16 *x_offset;
        s16 *y_offset;
        void *shadow;
        void *object;

        if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }

        shadow = ((Rec_func_80173204_arg0 *)actor)->unk_A4;
        ((S_80173A20_2 *)shadow)->unk_1E |= 0x8000;

        global_flags = D_800814A0;
        direction_bits = ((S_80173A20_3 *)creature)->unk_2A >> 8;
        creature_height = ((S_80173A20_3 *)creature)->unk_88.s;
        D_800814A0 = global_flags | 0x8000;

        x_offsets = (u8 *)&D_8006CCD8;
        offset_index = direction_bits & 0xE;
        x_offset = (s16 *)(x_offsets + offset_index);
        world_x = ((((Rec_D_80082E80 *)entity)->unk_24 + *x_offset) << 6) & 0xFFC0;
        y_offset = (s16 *)((u8 *)&D_8006CCE8 + offset_index);
        spawn_height = func_800BCB04(world_x,
            ((((Rec_D_80082E80 *)entity)->unk_25 + *y_offset) << 6) & 0xFFC0,
            (s16)(creature_height - 0x20));

        if (((S_80173A20_3 *)creature)->unk_88.u < spawn_height) {
            spawn_height = ((S_80173A20_3 *)creature)->unk_88.s;
        }

        object_flag = ((S_80173A20_3 *)creature)->unk_1C & 0x2000;
        object = func_800D3F74(
            object_flag != 0,
            (s16)(((Rec_D_80082E80 *)entity)->unk_24 + (u16)*x_offset),
            (s16)(((Rec_D_80082E80 *)entity)->unk_25 + (u16)*y_offset),
            spawn_height);
        func_80042640(object, 0x36);

        value_bonus = (((S_80173A20_3 *)creature)->unk_11 * 2) + (func_800A6D30() & 3);
        value_total = ((S_80173A20_4 *)object)->unk_29 + value_bonus;
        object_value = value_total;
        ASM_KEEP(object_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (value_total >= 0x100) {
            object_value = 0xFF;
        }
        ((S_80173A20_4 *)object)->unk_28 = object_value;
        ((S_80173A20_4 *)object)->unk_29 = object_value;

        func_800AD594(creature, 0x400);
        func_800A2B04(context, ((Rec_D_80082E80 *)entity)->unk_24,
                     ((Rec_D_80082E80 *)entity)->unk_25);
        ((Rec_func_80173204_arg0 *)actor)->unk_8C.as_pv = D_80170E5C;
        D_8008346C = 0;
        (*(u16 *)((u8 *)creature + 0x46)) &= 0x7FFF;
        return;
    }
    }
}
