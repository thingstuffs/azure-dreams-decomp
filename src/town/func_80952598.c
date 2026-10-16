#include "common.h"

/* This TOWN module's copy of townCheckFlagTestRecord (src/town/func_806D2D84.c). */

typedef struct FlagTestRecord {
    u8 pad_00[0x18];
    s16 flag;
} FlagTestRecord;

extern s32 func_80016CF8(s32 flag);
extern s16 D_8001607E;

/* Check the record flag only when the global flag is clear. */
s32 func_80016598(FlagTestRecord *record) {
    s32 flag_set;

    flag_set = 0;
    if (func_80016CF8(D_8001607E) == 0) {
        flag_set = func_80016CF8(record->flag) != 0;
    }
    return flag_set;
}
