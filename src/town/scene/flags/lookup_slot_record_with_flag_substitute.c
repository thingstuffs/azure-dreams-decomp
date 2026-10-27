#include "script_symbols.h"
#include "common.h"

extern u8 D_80017A20[9];
extern u8 D_80017B5C[9];
extern u8 D_80018CC0[9];
extern u8 D_80018D9F[9];
extern u8 D_80018E42[9];

extern void *func_80016F14(void *, void *, void *, s32);
extern s32 func_80016EB8(void *, void *, s32);
extern void func_8001779C(u16);
extern s32 func_8001781C(s32 flag_index); /* placed copy of get_script_flag_mask */
extern s32 func_80017948(s32 target_value); /* placed copy of record_value_table_contains */

/* Look up the slot's record, substituting fixed records when it is claimed or the 7-flag is set. */
void *lookup_slot_record_with_flag_substitute(void *slot, s32 unused, s32 context)
{
    void *result;

    result = func_80016F14(D_80017A20, D_80017B5C, slot, context);
    if (func_80016EB8(D_80017A20, slot, context) != 0) {
        if (func_8001781C(F_sbs36_pad19) != 0) {
            result = D_80018D9F;
        } else {
            result = D_80018CC0;
        }
    } else {
        func_8001779C(F_sbs36_pad19);
    }
    if (func_80017948(7) != 0) {
        result = D_80018E42;
    }
    return result;
}
