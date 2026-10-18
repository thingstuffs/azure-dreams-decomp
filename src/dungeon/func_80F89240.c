#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);


extern s32 get_cd_command_queue_depth(void);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_source_positioned_object(EntityRec *source_pos, s16 initial_value);



typedef struct S_80172A40_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80172A40_0;   /* arg0 in update_bank_actor_targeted_action */

typedef struct S_80172A40_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A40_2_pre;   /* the 0x14 bytes before target in update_bank_actor_targeted_action, addressed as target[-1] */

typedef struct S_80172A40_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A40_3;   /* record in update_bank_actor_targeted_action */

typedef struct S_80172A40_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A40_4;   /* arg2 in update_bank_actor_targeted_action */


/* Updates the selected action's targeting, motion, and completion state. */
void update_bank_actor_targeted_action(void *owner_input, EntityRec *motion_input, void *actor_input, EntityRec *object)
{
    s16 special;
    u8 *item_slot;
    s32 state;
    s32 slot_kind;
    s32 special_copy;
    u8 *item_entry;
    u8 *item_table;
    void *target;
    void *target_record;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    s32 slot_index;
    s32 item_id;


    state = ((S_80172A40_0 *)owner_input)->unk_9B;
    special = 0;
    switch (state) {
    case 0:
        if (((u32)object->flags1C) & 0x2000) {
            slot_index = (object->unk_46 & 0x3FFF) - 1;
            switch (slot_index) {
            case 6:
                special = 1;
                /* fall through */
            case 2:
                item_slot = (u8 *)object + 0xE;
                break;
            case 5:
                special = 1;
                /* fall through */
            case 1:
                item_slot = (u8 *)object + 0xB;
                break;
            case 4:
                special = 1;
                /* fall through */
            case 0:
                item_slot = (u8 *)object + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            slot_kind = object->unk_46 & 0x3FFF;
            switch (slot_kind) {
            case 3:
                item_slot = (u8 *)object + 0xE;
                break;
            case 2:
                item_slot = (u8 *)object + 0xB;
                break;
            case 1:
                item_slot = (u8 *)object + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_80172A40_0 *)owner_input)->unk_98 &= 0xFF7F;

            special_copy = special;
            if (special_copy) {
                target = D_800814A8;
                object->target = target;
                target_record = ((S_80172A40_2_pre *)target)[-1].unk_00;
                object->unk_72 = ((S_80172A40_3 *)target_record)->unk_24;
                object->unk_73 = ((S_80172A40_3 *)target_record)->unk_25;
            } else {
                item_table = D_8006DE24;
                item_id = *item_slot;
                item_entry = item_table + item_id * 20;
                if (item_entry[0x12] == 2) {
                    target = object->target;
                    if (target != 0) {
                        target_record = ((S_80172A40_2_pre *)target)[-1].unk_00;
                        object->unk_72 = ((S_80172A40_3 *)target_record)->unk_24;
                        object->unk_73 = ((S_80172A40_3 *)target_record)->unk_25;
                    }
                } else {
                    object->target = scan_monster_along_heading(
                        object, ((S_80172A40_4 *)actor_input)->unk_24, ((S_80172A40_4 *)actor_input)->unk_25,
                        object->facing, 0x10);

                    abs_x = abs(object->unk_72);
                    abs_y = abs(object->unk_73);
                    object->unk_72 = abs_x;
                    object->unk_73 = abs_y;
                }
            }

            if (create_actor_spell_effect(object, item_slot, special,
                              (u16 *)((u8 *)owner_input + 0x98)) == 0) {
                return;
            }
            ((S_80172A40_4 *)actor_input)->unk_14 &= 0xF7FF;
            create_source_positioned_object(motion_input, 4);
            play_sound_if_enabled(0x703);
            ((S_80172A40_0 *)owner_input)->unk_96.u = 4;
            ((S_80172A40_0 *)owner_input)->unk_9B++;
            ((S_80172A40_0 *)owner_input)->unk_98 |= 8;
            (*(u32 *)&object->flags1C) &= 0xF7FFFFFF;
            (*(u32 *)&object->flags1C) &= 0xFFFBFFFF;
            return;
        }

        motion_input->flags14 = 0;
        motion_input->unk_10 = 0;
        motion_input->unk_0C = 0;
        set_record_integer_tile_center(motion_input, ((S_80172A40_4 *)actor_input)->unk_24, ((S_80172A40_4 *)actor_input)->unk_25);
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(object);
        (*(u8 *)&object->unk_6D)--;
        ((S_80172A40_0 *)owner_input)->unk_8C = update_bank_actor_state;
        object->unk_73 = 0;
        object->unk_72 = 0;
        object->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((S_80172A40_4 *)actor_input)->unk_14 |= 0x800;
            return;
        }
        ((S_80172A40_4 *)actor_input)->unk_14 &= 0xF7FF;
        ((S_80172A40_0 *)owner_input)->unk_9B++;
                        /* fall through */

    case 2:
        ((S_80172A40_0 *)owner_input)->unk_92 +=
            (-0x30 - ((S_80172A40_0 *)owner_input)->unk_92) >> 3;
        ((S_80172A40_0 *)owner_input)->unk_96.u--;
        if (((S_80172A40_0 *)owner_input)->unk_96.s > 0) {
            if ((((S_80172A40_4 *)actor_input)->unk_14 & 0xE000) == 0) {
                return;
            }
        }
        ((S_80172A40_0 *)owner_input)->unk_98 |= 0x80;
        if ((((S_80172A40_4 *)actor_input)->unk_14 & 0xE000) == 0) {
            return;
        }

        motion_input->flags14 = 0;
        motion_input->unk_10 = 0;
        motion_input->unk_0C = 0;
        set_record_integer_tile_center(motion_input, ((S_80172A40_4 *)actor_input)->unk_24, ((S_80172A40_4 *)actor_input)->unk_25);
        ((S_80172A40_0 *)owner_input)->unk_98 &= 0xFFF7;
        (*(u32 *)&object->flags1C) |= 0x08000000;
        (*(u32 *)&object->flags1C) |= 0x00040000;

        if (((S_80172A40_4 *)actor_input)->unk_2C != D_80174AD4) {
            (*(u8 * *)((u8 *)actor_input + 0x2C)) = D_80174AD4;
            func_80047784(actor_input,
                          D_80174AD4[((g_game_work.view.viewAngle +
                                       object->facing + 0x100) >> 9) & 7],
                          ((S_80172A40_0 *)owner_input)->unk_A0);
        }

        if (((s32)g_dungeon_status.unk_0C) != 0) {
            return;
        }
        g_dungeon_status.unk_0A--;
        ((S_80172A40_4 *)actor_input)->unk_14 &= 0xF7FF;
        ((S_80172A40_0 *)owner_input)->unk_8C = update_bank_actor_state;
        advance_status_timers(object);
        if (object->unk_6D > 0) {
            (*(u8 *)&object->unk_6D)--;
        }
        object->unk_73 = 0;
        object->unk_72 = 0;
        object->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    default:
        return;
    }
}

