#include "common.h"

typedef s32 M2C_UNK;

extern s32 resolve_entry_flag();
extern s32 apply_entry_position();
extern void set_script_flag_bit();
extern M2C_UNK D_8001BB94;
extern M2C_UNK D_8001C358;
extern u8 D_8001E891;

/* Resolve a table result and apply the conditional override or fallback action. */
s32 dispatch_entry_or_process_fallback(s32 context, s32 unused, M2C_UNK entry_key) {
    M2C_UNK result;

    result = apply_entry_position(&D_8001BB94, &D_8001C358, context, entry_key);
    if (resolve_entry_flag(&D_8001BB94, context, entry_key) != 0) {
        return (s32)&D_8001E891;
    }
    set_script_flag_bit(0x1457);
    return result;
}
