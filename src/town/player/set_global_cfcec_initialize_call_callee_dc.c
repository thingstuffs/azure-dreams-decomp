#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */
extern s8 D_800CFCEC;

typedef struct S_80096758_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80096758_0;   /* arg0 in set_global_800_cfcec_initialize_call_callee_800954_dc */


void clear_the_global_state_s_fifth_word_copy_source_s_second(S_80096758_0 *);
/* Set D_800CFCEC, initialize the record, and call clear_the_global_state_s_fifth_word_copy_source_s_second. */
void set_global_800_cfcec_initialize_call_callee_800954_dc(S_80096758_0 *record, s32 initial_value) {
    D_800CFCEC = 1;
    record->unk_04 = initial_value;
    record->unk_10 = 0;
    clear_the_global_state_s_fifth_word_copy_source_s_second(record);
}
