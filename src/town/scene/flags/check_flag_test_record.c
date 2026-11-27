#include "common.h"
#include "town/scene/flags/event_checks.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

s32 test_object_bitmap_bit(s32 flagIndex);                             /* extern */
extern s16 repeat_entry_flag_id;

typedef struct S_80016584_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016584_0;   /* arg0 in check_flag_test_record */

/* Check the record flag only when the global flag is clear. */
s32 check_flag_test_record(void *object) {
    S_80016584_0 *record = object;
    s32 flag_set;

    flag_set = 0;
    if (test_object_bitmap_bit((*(__typeof__(repeat_entry_flag_id) *)0x800160B2)) == 0) {
        flag_set = test_object_bitmap_bit(record->unk_18) != 0;
    }
    return flag_set;
}
