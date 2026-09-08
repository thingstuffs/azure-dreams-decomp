#include "common.h"

extern void *func_80016D98(s32 arg0);
extern s32 func_800178A8(void *arg0, s32 arg1, s32 arg2);
extern void *func_80017960(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_80018594(s32 arg0);

extern u8 D_800189AC[16];
extern u8 D_80018B94[16];
extern u8 D_80018FFC[16];

/* Looks up an entry or selects a fallback, with a special case for entry 0x1C. */
void *func_806D42B4(s32 lookup_key, s32 unused, s32 entry_id) {
    void *entry;

    entry = func_80016D98(entry_id);
    if (entry != 0) {
        return entry;
    }
    func_80018594(0x1451);
    entry = func_80017960(&D_800189AC, &D_80018B94, lookup_key, entry_id);
    if ((entry_id == 0x1C) && (func_800178A8(&D_800189AC, lookup_key, 0x1C) != 0)) {
        entry = &D_80018FFC;
    }
    return entry;
}
