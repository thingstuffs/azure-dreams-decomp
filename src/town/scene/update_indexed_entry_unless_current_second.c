#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern void func_80016CC4(void);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s32 town_table_contains_first_byte(s32);

typedef void (*TownCallback)(s32, s32);

/* Checks town event conditions and invokes the object callback when they are met. */
s32 update_indexed_entry_unless_current(void) {
    s8 *callback_owner;
    s32 status;

    func_80016CC4();
    if (town_table_contains_first_byte(0xB) != 0) {
        func_8001A554(F_sbs32_pad17);
    }

    if (func_8001A64C(F_sbs32_pad32) == 0) {
        func_8001A554(F_sbs32_pad28);
        return 1;
    }

    if (func_8001A64C(F_sbs32_pad28) == 0) {
        func_8001A554(F_sbs32_pad24);
        callback_owner = *(s8 **)(*(s8 **)((s8 *)(&town_scene_root)) + 0x20);
        (*(TownCallback *)(callback_owner + 0x2F8))(0xE, 0x200);
        status = 0;
    } else {
        status = 1;
    }
    return status;
}
