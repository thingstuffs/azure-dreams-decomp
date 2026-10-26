/* Group history
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01209 - CL:town/func_8046C280, CL:town/func_8046C414, CL:town/func_80477674, CL:town/func_8047BE74, PD:town/image_3ef000:8001B0D0, PD:town/ll34_400000_80016000:80018E44.
 */
#include "town/scene/history.h"

/* Advance the group counter and prepend the entry to its twelve-entry history. */
void prepend_entry_to_group_history(s32 entry_index, s32 lookup_arg1, s32 lookup_arg2, s32 lookup_arg3) {
    extern Lookup D_8001902C[][3];
    s32 group_id;
    s32 state_base;
    s32 variant;
    s32 slot_index;
    u8 *slot;
    u8 *history;
    s32 old_entry;
    s32 entry_id;
    TownStateRecord *group_state;
    Lookup *limits;
    u8 *page;
    S_8001D188_1 *cursor;
    s16 *entries;
    s32 next_count;
    s32 count;
    s32 history_base;

    do {
        page = (u8 *)0x80010000;
    } while (0);
    state_base = (s32)((S_8001D188_3 *)page)->unk_6000->town_state;
    entry_id = entry_index;
    variant = query_priority_event_state();
    cursor = ((S_8001D188_0 *)page)->unk_6000;
    cursor = cursor->unk_24;
    cursor = cursor->unk_6C;
    entries = cursor->unk_1EC;
    /* BYTES: LOOP_END note barrier between the counter update + reread and the limits address (sched1/sched2). */
    do {
        group_id = *(s16 *)((u8 *)entries + (entry_id * 0x14));
        group_state = state_base + group_id;
        next_count = group_state->headIndices[0];
        next_count += 1;
        group_state->headIndices[0] = next_count;
        count = group_state->headIndices[0];
    } while (0);
    limits = D_8001902C[0];
    if (count >= limits[group_id * 3 + variant].flag) {
        group_state->headIndices[0] = 0U;
    }
    slot_index = 0;
    history_base = ((s16)group_id * 0xC) + state_base;
    history = (u8 *)(history_base + 0x3640);
    do {
        slot = history + slot_index;
        old_entry = *slot;
        *slot = entry_id;
        do {
            slot_index += 1;
        } while (0);
        entry_id = old_entry;
    } while (slot_index < 0xC);
}

/* Select a vertex relative to the list head, print its coordinates, and return its address. */
void *get_indexed_vertex_and_trace(s32 group, s32 n, s32 lookup_variant) {
    extern Lookup D_8001902C[][3];
    s32 lookup_flag;
    s32 head;
    Entry *ptr;
    s32 delta;

    if (group >= 10) {
        return 0;
    }
    lookup_flag = D_8001902C[group][lookup_variant].flag;
    head = town_scene_root->town_state->headIndices[group];
    ptr = D_8001902C[group][lookup_variant].entries;
    town_scene_root->services->callback_168(D_8001916C, D_80019178, n);
    town_scene_root->services->callback_168(D_8001916C, D_8001917C, head);
    delta = n - head;
    if (lookup_flag != 0) {
        if (delta >= 0) {
            delta++;
            n = lookup_flag - delta;
        } else {
            n = head - n - 1;
        }
    }
    town_scene_root->services->callback_168(D_8001916C, D_80019178, n);
    town_scene_root->services->callback_168(D_8001916C, D_80019184, ptr[n].vx);
    town_scene_root->services->callback_168(D_8001916C, D_80019190, ptr[n].vy);
    return &ptr[n];
}
