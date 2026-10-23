#include "common.h"
#include "town/scene/entry_flag_queries.h"

/* This TOWN module's copy of check_flag_test_record (src/town/func_806D2D84.c). */

typedef struct FlagTestRecord {
    u8 pad_00[0x18];
    s16 flag;
} FlagTestRecord;

extern s32 func_80016C34(s32 flag);
extern s16 D_80016ED6;

/* Check the record flag only when the global flag is clear. */
s32 test_record_flag_when_enabled(FlagTestRecord *record) {
    s32 flag_set;

    flag_set = 0;
    if (func_80016C34(D_80016ED6) == 0) {
        flag_set = func_80016C34(record->flag) != 0;
    }
    return flag_set;
}
