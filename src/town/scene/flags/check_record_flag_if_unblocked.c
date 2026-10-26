#include "shared/game_work.h"
#include "town/player/script_flags.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

extern s16 scene_gate_script_flag;
/* Check the record flag only when the global blocking flag is clear. */
s32 check_record_flag_if_unblocked(void *record)
{
    s32 flag_set;
    void *record_copy;
    int initial_result;
    void *flag_record;
    initial_result = 0;
    flag_set = initial_result;
    record_copy = record;
    flag_record = record_copy;
    if (get_script_flag_mask(scene_gate_script_flag) == 0) {
        flag_set = get_script_flag_mask(*(s16 *) (((s8 *) flag_record) + 0x18)) != 0;
    }
    return flag_set;
}
