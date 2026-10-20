#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
void func_80016CC4(void);
extern void initialize_resources_assigns_pointer_lookup();
extern s32 func_8001991C();
extern s32 update_entry_flags();
void func_8001A554(s32);
void func_8001A5CC(s32);
extern s32 func_8001A64C();


/* Advance the town scene: raise 0x94B, then hand back to the scene callback unless flag 0x943 and the step check both pass. */
s32 advance_town_scene_raise_hand(s32 kind, s32 value) {
    func_80016CC4();
    initialize_resources_assigns_pointer_lookup();
    func_8001A554(0x94B);
    if (func_8001A64C(0x943) == 0) {
        D_80016000->unk_20->callback_2F8(0xE, 0x200);
        return 0;
    }
    update_entry_flags();
    if (func_8001991C(kind, value) == 0) {
        D_80016000->unk_20->callback_2F8(0xE, 0x200);
        return 0;
    }
    func_8001A5CC(0x943);
    return 1;
}
