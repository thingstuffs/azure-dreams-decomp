#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);


extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s16);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_800DAE44(EntityRec *source_pos, s16 initial_value);

extern u8 D_80171138[];
extern u8 D_80174AD4[];


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
} S_80172A40_0;   /* arg0 in func_80172A40 */

typedef struct S_80172A40_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A40_2_pre;   /* the 0x14 bytes before target in func_80172A40, addressed as target[-1] */

typedef struct S_80172A40_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A40_3;   /* record in func_80172A40 */

typedef struct S_80172A40_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A40_4;   /* arg2 in func_80172A40 */


/* Updates the selected action's targeting, motion, and completion state. */
void func_80172A40(void *owner_input, EntityRec *motion_input, void *actor_input, EntityRec *object)
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
                    object->target = func_800A05A4(
                        object, ((S_80172A40_4 *)actor_input)->unk_24, ((S_80172A40_4 *)actor_input)->unk_25,
                        object->facing, 0x10);

                    abs_x = abs(object->unk_72);
                    abs_y = abs(object->unk_73);
                    object->unk_72 = abs_x;
                    object->unk_73 = abs_y;
                }
            }

            if (func_800A94A0(object, item_slot, special,
                              (u16 *)((u8 *)owner_input + 0x98)) == 0) {
                return;
            }
            ((S_80172A40_4 *)actor_input)->unk_14 &= 0xF7FF;
            func_800DAE44(motion_input, 4);
            func_800A56E0(0x703);
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
        func_800A2B04(motion_input, ((S_80172A40_4 *)actor_input)->unk_24, ((S_80172A40_4 *)actor_input)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(object);
        (*(u8 *)&object->unk_6D)--;
        ((S_80172A40_0 *)owner_input)->unk_8C = D_80171138;
        object->unk_73 = 0;
        object->unk_72 = 0;
        object->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
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
        func_800A2B04(motion_input, ((S_80172A40_4 *)actor_input)->unk_24, ((S_80172A40_4 *)actor_input)->unk_25);
        ((S_80172A40_0 *)owner_input)->unk_98 &= 0xFFF7;
        (*(u32 *)&object->flags1C) |= 0x08000000;
        (*(u32 *)&object->flags1C) |= 0x00040000;

        if (((S_80172A40_4 *)actor_input)->unk_2C != D_80174AD4) {
            (*(u8 * *)((u8 *)actor_input + 0x2C)) = D_80174AD4;
            func_80047784(actor_input,
                          D_80174AD4[((gameWork.view.viewAngle +
                                       object->facing + 0x100) >> 9) & 7],
                          ((S_80172A40_0 *)owner_input)->unk_A0);
        }

        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
        ((S_80172A40_4 *)actor_input)->unk_14 &= 0xF7FF;
        ((S_80172A40_0 *)owner_input)->unk_8C = D_80171138;
        func_800A4ACC(object);
        if (object->unk_6D > 0) {
            (*(u8 *)&object->unk_6D)--;
        }
        object->unk_73 = 0;
        object->unk_72 = 0;
        object->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    default:
        return;
    }
}
