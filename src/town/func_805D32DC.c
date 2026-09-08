#include "common.h"

typedef struct TownRecord {
    s8 pad0[8];
    s32 index;
    s8 padC[0x34];
    u8 *entries;
} TownRecord;

extern void func_80017E1C(void);
extern s32 func_80018618(void);
extern s32 func_800194D8(s32);
extern s8 D_80016000[];
extern s32 D_80019AFC;

/* Loads the current entry's value, conditionally clears it, and handles the follow-up check. */
s32 func_805D32DC(void) {
    TownRecord *record;

    record = *(TownRecord **)D_80016000;
    D_80019AFC = record->entries[(record->index * 8) + 4];
    if (func_80018618() != 0) {
        TownRecord *clear_record;

        clear_record = *(TownRecord **)D_80016000;
        clear_record->entries[(clear_record->index * 8) + 4] = 0;
        D_80019AFC = 0;
    }
    if (func_800194D8(0x638) == 0) {
        func_80017E1C();
    }
    return 0;
}
