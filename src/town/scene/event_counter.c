/* Event counter reset and threshold
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/image_49e800:80019178, PD:town/ll34_49e800_80016000:80019178.
 * PD:town/image_49e800:80019178
 * PD:town/ll34_49e800_80016000:80019178
 */
#include "town/scene.h"

/* Private declarations retained from the member sources. */
/* Event counter reset and threshold */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/image_49e800:80019178, PD:town/ll34_49e800_80016000:80019178. */

#include "common.h"
#include "script_symbols.h"
#include "town/player/script_flags.h"

extern s32 D_80019178[];

/* Apply the fixed operation codes and clear the first D_80019178 entry. */
void reset_sbs11_flags_and_counter(void) {
    set_script_flag_bit(F_sbs11_pad02);
    clear_script_flag_bit(F_sbs11_pad31);
    clear_script_flag_bit(F_sbs11_pad28);
    clear_script_flag_bit(F_sbs11_pad29);
    D_80019178[0] = 0;
}

/* Increment the counter and report whether it has reached three. */
s32 bump_event_counter_to_three(void) {
    s32 count;

    count = D_80019178[0] + 1;
    D_80019178[0] = count;
    return count >= 3;
}
