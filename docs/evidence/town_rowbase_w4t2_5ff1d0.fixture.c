#include "common.h"
extern s32 func_80017A54();
extern s32 *func_80017B0C();
extern s32 func_80018604(void);
extern s32 D_80018750, D_800188BC, D_8001A41C;
extern s32 D_80018D54, D_80018F15, D_800190C3;
s32 *func_800160F8(s32 lookup_key, s32 unused, s32 entry_id) {
    s32 *entry;
    entry = func_80017B0C(&D_80018750, &D_800188BC, lookup_key, entry_id);
    if (func_80017A54(&D_80018750, lookup_key, entry_id) != 0) {
        if (entry_id == 0x26) entry = &D_8001A41C;
    }
    if (func_80018604() == 0) {
        if (entry_id == 0x34) entry = &D_80018D54;
        else if (entry_id == 0x35) entry = &D_80018F15;
        else if (entry_id == 0x36) entry = &D_800190C3;
    }
    return entry;
}
