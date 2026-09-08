#include "common.h"

extern s32 func_80016BC0(void *, void *, s32, s32);
extern s32 func_80016B08(void *, s32, s32);
extern void func_80017674(s32);
extern s32 func_800176F4(s32);

extern u8 D_800178D8[];
extern u8 D_800179CC[];
extern u8 D_80018481[];
extern u8 D_80018642[];
extern u8 D_80018B70[];

/* Looks up entry data and applies entry-specific overrides. */
s32 func_800160C8(s32 lookup_key, s32 unused, s32 entry_id)
{
    s32 entry_data;

    entry_data = func_80016BC0(D_800178D8, D_800179CC, lookup_key, entry_id);

    if (entry_id == 50 && func_80016B08(D_800178D8, lookup_key, 50)) {
        return (s32)D_80018481;
    }
    if (entry_id == 33 && func_80016B08(D_800178D8, lookup_key, 33)) {
        return (s32)D_80018642;
    }
    if (entry_id == 12) {
        if (!func_80016B08(D_800178D8, lookup_key, 12)) {
            func_80017674(0xB11);
        }
        if (func_800176F4(0xB11)) {
            return (s32)D_80018B70;
        }
    }
    return entry_data;
}
