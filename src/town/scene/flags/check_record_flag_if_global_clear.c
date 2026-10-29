#include "common.h"
#include "town/scene/flags/event_checks.h"
#include "town/scene/flags.h"

/* This TOWN module's copy of check_flag_test_record (src/town/func_806D2D84.c). */

typedef struct FlagTestRecord {
    u8 pad_00[0x18];
    s16 flag;
} FlagTestRecord;

extern s32 func_80016C38(s32 flag);
extern s16 D_80016036;

/* Check the record flag only when the global flag is clear. */
s32 check_record_flag_if_global_clear(void *object) {
    FlagTestRecord *record = object;
    s32 flag_set;

    flag_set = 0;
    if (func_80016C38(D_80016036) == 0) {
        flag_set = func_80016C38(record->flag) != 0;
    }
    return flag_set;
}
