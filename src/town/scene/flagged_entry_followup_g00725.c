/* G00725: Append flagged entries and follow four linked entries.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8032EA2C.
 * Exclude the weaker left CL/CXP:10/8 join; right CXP:8/10 has no join.
 */
#include "town/scene/flagged_entry_followup_g00725.h"
#include "town/scene.h"

/* Process the flagged entries in mode 0 (append them to the object list). */
void process_flagged_entries_mode_append(void *entries) {
    lookup_entry_with_default_fallback(entries, 0);
}

/* Process the flagged entries that follow the four-byte header, in mode 1. */
void process_flagged_entries_follow_four(u8 *entries) {
    lookup_entry_with_default_fallback(entries + 4, 1);
}
