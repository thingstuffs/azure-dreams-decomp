/* Relink of matched dungeon/dungeonUpdateGlobalEffectObject at file 0x1274248; imports and data use paired retail relocations. */
#define objectFlagBlock D_800803D4
#include "common.h"
#include "shared/object_flags.h"

extern u8 *D_8014F710;

extern void func_800A1F74(void *record);
extern void townInitializeIndexedObjectAndLookupValue(s32 x, s32 y, s32 flag_mask);
extern void func_80098E28(void *node);

/* Updates the active object, triggers its positional effect, and clears its slot. */
void func_8014EA48(void) {
    u8 **active_slot;
    u8 *active_obj;

    active_slot = &D_8014F710;
    active_obj = *active_slot;
    if (active_obj != 0) {
        u8 *obj_state = active_obj + 0x20;
        u8 *obj_data = *(u8 **)(active_obj + 0xC);
        s32 sound_x;
        s32 sound_y;
        s32 effect_id;

        func_800A1F74(obj_state);
        sound_x = obj_data[0x24];
        sound_y = obj_data[0x25];
        effect_id = 0x3000;
        if (*(u32 *)(obj_state + 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        townInitializeIndexedObjectAndLookupValue(sound_x, sound_y, effect_id);
        func_80098E28(obj_state);
        *(u16 *)(obj_state - 2) |= 0x8000;
        *active_slot = 0;
        objectFlagBlock.flags |= 0x8000;
    }
}
