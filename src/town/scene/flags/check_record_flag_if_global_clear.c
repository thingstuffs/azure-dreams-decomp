#include "common.h"
#include "town/scene/flags/event_checks.h"
#include "town/scene/flags.h"

/* This TOWN module's copy of check_flag_test_record (src/town/func_806D2D84.c). */

typedef struct FlagTestRecord {
    u8 pad_00[0x18];
    s16 flag;
} FlagTestRecord;

extern s32 test_object_bitmap_bit(s32 flag);
extern s16 D_80016036;

/* Check the record flag only when the global flag is clear. */
s32 check_record_flag_if_global_clear(void *object) {
    FlagTestRecord *record = object;
    s32 flag_set;

    flag_set = 0;
    if (test_object_bitmap_bit(D_80016036) == 0) {
        flag_set = test_object_bitmap_bit(record->flag) != 0;
    }
    return flag_set;
}
