#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

void apply_position_and_mark_sbs18_pad05(TownObjectSet *entry, s32 type, s32 context_value)
{
    set_script_flag_bit(F_sbs18_pad05);
    apply_entry_position(sbs18_choice_position_entries, sbs18_choice_position_flags, entry, context_value);
}
