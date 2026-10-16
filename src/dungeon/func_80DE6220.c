#include "modules/dungeon_ovl_e0365c.h"

void func_80173A20(void *actor, void *context, void *entity, void *creature)
{
    switch (((Rec_func_80173204_arg0 *)actor)->unk_9B) {
    case 0:
    {
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

    case 2:
    {
        s16 object_value;
        s32 value_total;
        s32 value_bonus;
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
        ((E_80173A20_S_80173A20_2 *)shadow)->unk_1E |= 0x8000;

        global_flags = objectFlagBlock.flags;
        direction_bits = ((E_80173A20_S_80173A20_3 *)creature)->unk_2A >> 8;
        creature_height = ((E_80173A20_S_80173A20_3 *)creature)->unk_88.s;
        objectFlagBlock.flags = global_flags | 0x8000;

        x_offsets = (u8 *)((s8 *)dirStepX);
        offset_index = direction_bits & 0xE;
        x_offset = (s16 *)(x_offsets + offset_index);
        world_x = ((((Rec_D_80082E80 *)entity)->unk_24 + *x_offset) << 6) & 0xFFC0;
        y_offset = (s16 *)((u8 *)((s8 *)dirStepY) + offset_index);
        spawn_height = func_800BCB04(world_x,
            ((((Rec_D_80082E80 *)entity)->unk_25 + *y_offset) << 6) & 0xFFC0,
            (s16)(creature_height - 0x20));

        if (((E_80173A20_S_80173A20_3 *)creature)->unk_88.u < spawn_height) {
            spawn_height = ((E_80173A20_S_80173A20_3 *)creature)->unk_88.s;
        }

        object_flag = ((E_80173A20_S_80173A20_3 *)creature)->unk_1C & 0x2000;
        object = func_800D3F74(
            object_flag != 0,
            (s16)(((Rec_D_80082E80 *)entity)->unk_24 + (u16)*x_offset),
            (s16)(((Rec_D_80082E80 *)entity)->unk_25 + (u16)*y_offset),
            spawn_height);
        func_80042640(object, 0x36);

        value_bonus = (((E_80173A20_S_80173A20_3 *)creature)->unk_11 * 2) + (func_800A6D30() & 3);
        value_total = ((E_80173A20_S_80173A20_4 *)object)->unk_29 + value_bonus;
        object_value = value_total;
        if (value_total >= 0x100) {
            object_value = 0xFF;
        }
        ((E_80173A20_S_80173A20_4 *)object)->unk_28 = object_value;
        ((E_80173A20_S_80173A20_4 *)object)->unk_29 = object_value;

        func_800AD594(creature, 0x400);
        func_800A2B04(context, ((Rec_D_80082E80 *)entity)->unk_24,
                      ((Rec_D_80082E80 *)entity)->unk_25);
        ((Rec_func_80173204_arg0 *)actor)->unk_8C.as_pv = func_80170E5C;
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)creature + 0x46)) &= 0x7FFF;
        return;
    }
    }
}
