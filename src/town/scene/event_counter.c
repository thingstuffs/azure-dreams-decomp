/* Event counter reset and threshold
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00647 - PD:town/image_49e800:80019178, PD:town/ll34_49e800_80016000:80019178.
 * PD:town/image_49e800:80019178
 * PD:town/ll34_49e800_80016000:80019178
 */
#include "town/scene.h"

/* Private declarations retained from the member sources. */
/* Event counter reset and threshold */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00647 - PD:town/image_49e800:80019178, PD:town/ll34_49e800_80016000:80019178. */

#include "common.h"
#include "script_symbols.h"

extern void func_80018A64(s32);
extern void func_80018ADC(s32);
extern s32 D_80019178[];

/* Apply the fixed operation codes and clear the first D_80019178 entry. */
void run_events_5a5_5c2_and_reset(void) {
    func_80018A64(F_sbs11_pad02);
    func_80018ADC(F_sbs11_pad31);
    func_80018ADC(F_sbs11_pad28);
    func_80018ADC(F_sbs11_pad29);
    D_80019178[0] = 0;
}

/* Increment the counter and report whether it has reached three. */
s32 increment_and_check_three(void) {
    s32 count;

    count = D_80019178[0] + 1;
    D_80019178[0] = count;
    return count >= 3;
}
