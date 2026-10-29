#include "town/scene.h"
#include "records/Rec_func_800165F4_arg0.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

/* Set the object's script flag under flag 1455, then process the entry. */
s32 process_entry_with_script_flag(Rec_func_800165F4_arg0 *object, s32 entry_index)
{
    if (get_script_flag_mask(0x1455) != 0) {
        set_script_flag_bit(object->unk_18);
    }
    return process_checked_entry(object, entry_index);
}
