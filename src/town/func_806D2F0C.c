#include "common.h"

typedef struct S_8001670C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
} S_8001670C_0;   /* index * 8 + records in process_flag_test_record */

typedef struct S_8001670C_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    s16 unk_18;
} S_8001670C_1;   /* ctx in process_flag_test_record */

typedef struct S_8001670C_2 {
    s16 unk_00;
    s16 unk_02;
} S_8001670C_2;   /* pair in process_flag_test_record */


extern s32 attach_global_data_and_invoke_callback(u32, s32);
extern void update_flag_test_target(s16 sourceId, s16 targetId);
extern s32 check_all_flag_test_bits(s16 *flag_ids);
extern void set_flag_test_indexed_bit(s32);

/* Processes the selected record's pair and optional context action, then returns the record's value. */
s32 process_flag_test_record(u32 records, s32 condition_arg, u32 context, s32 record_selector)
{
    s32 record_index;
    u32 pair;

    record_index = attach_global_data_and_invoke_callback(records, record_selector);
    pair = (((S_8001670C_0 *)(record_index * 8 + records))->unk_02 * 4)
    + ((S_8001670C_1 *)context)->unk_14;
    update_flag_test_target(((S_8001670C_2 *)pair)->unk_00, ((S_8001670C_2 *)pair)->unk_02);
    if (condition_arg != 0 && check_all_flag_test_bits(condition_arg) != 0) {
        set_flag_test_indexed_bit(((S_8001670C_1 *)context)->unk_18);
    }
    return ((S_8001670C_0 *)(record_index * 8 + records))->unk_04;
}
