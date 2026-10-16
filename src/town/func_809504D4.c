#include "common.h"

/* This TOWN module's copy of townCheckFlagTestRecord (src/town/func_806D2D84.c). */

typedef struct FlagTestRecord {
    u8 pad_00[0x18];
    s16 flag;
} FlagTestRecord;

extern s32 func_80016C34(s32 flag);
extern s16 D_80016ED6;

/* Check the record flag only when the global flag is clear. */
s32 func_800164D4(FlagTestRecord *record) {
    s32 flag_set;

    flag_set = 0;
    if (func_80016C34(D_80016ED6) == 0) {
        flag_set = func_80016C34(record->flag) != 0;
    }
    return flag_set;
}
