#include "common.h"
#include "script_symbols.h"
#include "town/scene.h"
#include "town/scene/record_actions.h"
#include "town/player/script_flags.h"

s32 prepare_choice_and_mark_ending_step(TownObjectSet *context, s32 index)
{
    context->choices[index].value = populate_records_and_normalize_kind();
    set_script_flag_bit(F_end_ending_step0);
    return 0;
}
