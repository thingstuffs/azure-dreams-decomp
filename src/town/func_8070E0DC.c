#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80016CC4();
extern void func_80016DBC();
extern s32 func_8001991C();
extern s32 func_80019988();
extern M2C_UNK func_8001A554();
extern M2C_UNK func_8001A5CC();
extern s32 func_8001A64C();


/* Advance the town scene: raise 0x94B, then hand back to the scene callback unless flag 0x943 and the step check both pass. */
s32 func_800170DC(s32 kind, s32 value) {
    func_80016CC4();
    func_80016DBC();
    func_8001A554(0x94B);
    if (func_8001A64C(0x943) == 0) {
        D_80016000->unk_20->callback_2F8(0xE, 0x200);
        return 0;
    }
    func_80019988();
    if (func_8001991C(kind, value) == 0) {
        D_80016000->unk_20->callback_2F8(0xE, 0x200);
        return 0;
    }
    func_8001A5CC(0x943);
    return 1;
}
