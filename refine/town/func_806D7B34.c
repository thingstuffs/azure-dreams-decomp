#include "common.h"

extern s32 func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);

extern u8 D_80018998[];
extern u8 D_80019104[];
extern u8 D_80019AB6[];
extern u8 D_8001ABCC[];
extern u8 D_80019397[];

/* Looks up an entry, substituting fixed data for matching IDs 45 through 47. */
s32 func_80016334(s32 lookup_key, s32 unused, s32 entry_id)
{
    s32 result;

    result = func_80017B0C(D_80018998, D_80019104, lookup_key, entry_id);

    if (entry_id == 45 && func_80017A54(D_80018998, lookup_key, 45)) {
        return (s32)D_80019AB6;
    }
    if (entry_id == 46 && func_80017A54(D_80018998, lookup_key, 46)) {
        return (s32)D_8001ABCC;
    }
    if (entry_id == 47 && func_80017A54(D_80018998, lookup_key, 47)) {
        return (s32)D_80019397;
    }
    return result;
}
