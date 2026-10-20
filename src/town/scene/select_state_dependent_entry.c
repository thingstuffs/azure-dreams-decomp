#include "script_symbols.h"
#include "common.h"

extern s32 get_script_flag_mask(s32 flagIndex);
extern void set_script_flag_bit(s32 bit_index);
extern void *apply_entry_position(void *entries, void *object, s32 context, s32 selection);

extern u8 D_8001BE24[];
extern u8 D_8001C354[];
extern u8 D_8001DCD4[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

/* Selects an entry pointer, with state-dependent alternatives for entry 0x1E. */
void *select_state_dependent_entry(s32 table_index, s32 unused, s32 entry_id) {
    void *result;

    if (entry_id == 0x1E) {
        if (get_script_flag_mask(Ftt_fkoya_isaku_scene00_first) != 0) {
            if (get_script_flag_mask(Ftt_fkoya_isaku_scene00_ok) != 0) {
                result = D_8001E42A;
            } else {
                result = D_8001E16A;
            }
        } else {
            result = D_8001DCD4;
            set_script_flag_bit(Ftt_fkoya_isaku_scene00_first);
        }
    } else {
        result = apply_entry_position(D_8001BE24, D_8001C354, table_index, entry_id);
    }
    return result;
}
