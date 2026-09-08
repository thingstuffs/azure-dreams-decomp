#include "common.h"

extern s32 func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);
extern void func_800185C0(s32);

extern u8 D_800189D8[];
extern u8 D_80019104[];
extern u8 D_8001A212[];
extern u8 D_8001ABCC[];
extern u8 D_80019397[];

/* Looks up an entry and applies conditional overrides for variants 45 through 47. */
s32 func_800165AC(s32 entry_id, s32 unused, s32 variant_id)
{
    s32 default_result;

    default_result = func_80017B0C(D_800189D8, D_80019104, entry_id, variant_id);

    if (variant_id == 45 && func_80017A54(D_800189D8, entry_id, 45)) {
        func_800185C0(0x9AE);
        return (s32)D_8001A212;
    }
    if (variant_id == 46 && func_80017A54(D_800189D8, entry_id, 46)) {
        return (s32)D_8001ABCC;
    }
    if (variant_id == 47 && func_80017A54(D_800189D8, entry_id, 47)) {
        return (s32)D_80019397;
    }
    return default_result;
}
