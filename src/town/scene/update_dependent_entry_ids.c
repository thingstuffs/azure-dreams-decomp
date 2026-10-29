#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene.h"


/* Updates two dependent IDs according to the checked ID's status, then updates the checked ID. */
void update_dependent_entry_ids(s16 checked_id, s16 first_id, s16 second_id)
{
    s16 saved_first_id;
    s16 first_id_copy;
    s16 saved_second_id;
    s16 saved_checked_id;

    saved_first_id = first_id;
    saved_second_id = second_id;
    saved_checked_id = checked_id;
    first_id_copy = saved_first_id;

    if (get_script_flag_mask(checked_id) != 0) {
        set_script_flag_bit(saved_first_id);
        set_script_flag_bit(saved_second_id);
    } else {
        clear_script_flag_bit(first_id_copy);
    }
    set_script_flag_bit(saved_checked_id);
}
