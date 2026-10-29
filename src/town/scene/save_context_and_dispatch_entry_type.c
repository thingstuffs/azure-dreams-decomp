#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"


typedef void (*TownCallback)(void *, s32, s32);


typedef struct S_8001A3FC_1 {
    u8 unk_00;
    u8 pad_01[0xF];
    s32 unk_10;
} S_8001A3FC_1;   /* entry in save_context_and_dispatch_entry_type */


extern s32 D_8001C370;
extern s32 scene_current_entry_value;

/* Save the current context value and dispatch the selected entry's type callback. */
void save_context_and_dispatch_entry_type(void) {
    s32 *entry_base;
    S_8001A3FC_1 *entry;
    s32 type;
    s32 entry_index;
    s32 entry_offset;

    entry_base = &D_8001C370;
    entry_index = town_scene_root->unk_14;
    entry_offset = entry_index * 0x1C;
    entry = (void *)(entry_offset + *entry_base);
    type = entry->unk_00;
    scene_current_entry_value = ((s32)town_scene_root->unk_00);
    (*(TownCallback *)((u8 *)((entry->unk_00 * 0x10) +
              entry->unk_10) + 4))(entry, type,
                           ((s32)town_scene_root->unk_00));
}
