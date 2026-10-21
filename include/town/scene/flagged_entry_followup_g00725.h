/* G00725: Append flagged entries and follow four linked entries.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8032EA2C.
 * Exclude the weaker left CL/CXP:10/8 join; right CXP:8/10 has no join.
 */
#ifndef TOWN_SCENE_FLAGGED_ENTRY_FOLLOWUP_G00725_H
#define TOWN_SCENE_FLAGGED_ENTRY_FOLLOWUP_G00725_H

#include "common.h"

/* TOWN bank at file 0x400A38..0x4012C8 (link delta 0x7FC16000) is a copy of
 * the matched module at TOWN file 0x2AE364..0x2AEBF4 (delta 0x7FD6A800): the 2192 bytes
 * are identical except relocated fields, and 11 of 12 bank-local calls land on the
 * mirrored function starts at this delta.  This row mirrors process_lshop_value
 * (src/town/func_8032EAE8.c).  Evidence: docs/evidence/r121_rem_opus.md. */
/* = process_lshop_entries of the reference module (src/town/func_8032EA2C.c). */
extern void lookup_entry_with_default_fallback(void *entries, s32 entry_mode);

/* Functions defined in this translation unit. */
void process_flagged_entries_mode_append(void *entries);
void process_flagged_entries_follow_four(u8 *entries);

#endif
