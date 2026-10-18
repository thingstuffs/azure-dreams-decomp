#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"


typedef struct S_800A6620_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A6620_1_pre;   /* the 0x14 bytes before object in release_entity_slot_and_update_flags, addressed as object[-1] */

typedef struct S_800A6620_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x23];
    u8 unk_43;
    u8 unk_44;
} S_800A6620_1;   /* object in release_entity_slot_and_update_flags */

typedef struct S_800A6620_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800A6620_2;   /* entry in release_entity_slot_and_update_flags */

typedef struct S_800A6620_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A6620_3;   /* owner in release_entity_slot_and_update_flags */


extern void build_entity_slot_snapshot(void *ptr, void *object);
extern s32 func_80042900(void *object, s32 value);
extern void clear_slot_and_update_linked_state(void *handle);
extern void unlink_entity_node(void *object);
extern void update_map_cell_flags_with_item_limit(u8 sound_x, u8 sound_y, s32 sound_mode);
extern s16 find_entity_slot_by_field_ac(void *object);
extern void detach_record_and_update_slot_state(void *object);

extern void *D_800E3DF0[];

/* Removes the object from its slot, performs flagged cleanup, and releases its handle. */
s16 release_entity_slot_and_update_flags(void *handle, s32 extra_cleanup)
{
    s32 sound_mode;
    s32 index;
    void **object_slot;
    void **object_table;
    void *object;
    void *state_entry;
    void *owner;
    u8 sound_x;
    u8 sound_y;

    object_table = D_800E3DF0;
    index = ((u8 *)handle)[3] & 0x1F;
    object_slot = &object_table[index];
    object = *object_slot;
    *object_slot = 0;
    index = ((S_800A6620_1 *)object)->unk_43;

    if (index < 0x40) {
        ((S_800A6620_1 *)object)->unk_44 = 0;
        build_entity_slot_snapshot((void *)(0x80010A80 + index * 0x54), object);
    }

    if (((u8 *)handle)[3] & 0x20) {
        index = find_entity_slot_by_field_ac(object);
        if (index >= 0) {
            state_entry = (void *)(index * 4 + ((s32)D_800E3D7C));
            ((S_800A6620_2 *)state_entry)->unk_AC = 0;
            ((S_800A6620_2 *)state_entry)->unk_D0 = 0;
        }

        if ((func_80042900(object, 0x1B) << 16) == 0) {
            owner = ((S_800A6620_1_pre *)object)[-1].unk_00;
            sound_x = ((S_800A6620_3 *)owner)->unk_24;
            sound_y = ((S_800A6620_3 *)owner)->unk_25;
            sound_mode = 0x3000;
            if (((S_800A6620_1 *)object)->unk_1C & 0x2000) {
                sound_mode = 0x300;
            }
            update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_mode);
        }

        if (extra_cleanup != 0) {
            detach_record_and_update_slot_state(object);
        }
        unlink_entity_node(object);
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }

    clear_slot_and_update_linked_state(handle);
    return index;
}
