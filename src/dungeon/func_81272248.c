/* Relink of matched dungeon/func_81254248; every changed retail word is a paired relocation. */
#define D_80174710 D_80156710
#include "common.h"
#include "shared/object_flags.h"

extern u8 *D_80156710;

extern void detach_record_and_update_slot_state(void *record);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, s32 flag_mask);
extern void unlink_entity_node(void *node);

/* Updates the active object, triggers its positional effect, and clears its slot. */
void func_80155A48(void) {
    u8 **active_slot;
    u8 *active_obj;

    active_slot = &D_80156710;
    active_obj = *active_slot;
    if (active_obj != 0) {
        u8 *obj_state = active_obj + 0x20;
        u8 *obj_data = *(u8 **)(active_obj + 0xC);
        s32 sound_x;
        s32 sound_y;
        s32 effect_id;

        detach_record_and_update_slot_state(obj_state);
        sound_x = obj_data[0x24];
        sound_y = obj_data[0x25];
        effect_id = 0x3000;
        if (*(u32 *)(obj_state + 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, effect_id);
        unlink_entity_node(obj_state);
        *(u16 *)(obj_state - 2) |= 0x8000;
        *active_slot = 0;
        object_flag_block.flags |= 0x8000;
    }
}
