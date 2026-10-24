#include "common.h"
#include "town/scene/flags/event_checks.h"
#include "m2c_compat.h"

s32 select_data_array_based_flag();                             /* extern */
extern s16 D_800160B2;

typedef struct S_80016584_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016584_0;   /* arg0 in check_flag_test_record */

/* Check the record flag only when the global flag is clear. */
s32 check_flag_test_record(void *object) {
    S_80016584_0 *record = object;
    s32 flag_set;

    flag_set = 0;
    if (select_data_array_based_flag((*(__typeof__(D_800160B2) *)0x800160B2)) == 0) {
        flag_set = select_data_array_based_flag(record->unk_18) != 0;
    }
    return flag_set;
}
