#include "script_symbols.h"
#include "common.h"


s32 func_80017B24();
s32 * func_80017BDC(void *, void *, s32, s32);
s32 func_8001856C(s32);
s32 func_800187D8();
extern s32 D_80018974;
extern s32 D_80018AD0;
extern s32 D_80019F15;
extern s32 D_8001A0A1;

/* Look up the slot's record; when it is already claimed, substitute one of two fixed records. */
s32 *lookup_slot_record_with_substitute(s32 slot, s32 unused, s32 context) {
    s32 *record;
    s32 *result;

    record = func_80017BDC(&D_80018974, &D_80018AD0, slot, context);
    result = record;
    if (func_80017B24(&D_80018974, slot, context) != 0) {
        if (func_800187D8(8) != 0) {
            result = &D_8001A0A1;
        } else {
            func_8001856C(F_gym_build);
            result = &D_80019F15;
        }
    }
    return result;
}
