#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern void func_80016CC4(void);
extern void initialize_resources_assigns_pointer_lookup(void);
extern s32 func_8001991C(s32, s32);
extern void update_entry_flags(void);
extern void func_8001A5CC(s32);
extern s32 func_8001A64C(s32);

typedef void (*Callback)(s32, s32);

/* Advance the town scene: clear flag 0x943 when it is set and the step check passes, otherwise hand back to the scene callback. */
s32 advance_town_scene_flag_step(s32 kind, s32 value) {
    func_80016CC4();
    initialize_resources_assigns_pointer_lookup();

    if (func_8001A64C(F_sbs32_pad25) != 0) {
        update_entry_flags();
        if (func_8001991C(kind, value) != 0) {
            func_8001A5CC(F_sbs32_pad25);
            return 1;
        }
    }

    (*(Callback *)((u8 *)((void **)*(void **)((u8 *)(&D_80016000)))[8] + 0x2F8))(0xE, 0x200);
    return 0;
}
