/* G00721: Initialize and resolve event selection with a fallback entry.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8046AC60, CL:town/func_8046AC98.
 * Only the two strong CL gaps are included; complete file edges remain unknown.
 */
#include "town/scene/event_selection_g00721.h"
#include "town/scene.h"

/* Return the candidate if check_event_value_in_list succeeds, otherwise use find_first_enabled_entry_id. */
s32 choose_valid_entry_or_fallback(s32 candidate) {
    if (check_event_value_in_list(candidate) != 0) {
        return candidate;
    }
    return find_first_enabled_entry_id();
}

void initialize_event_selection_state(s32 unused, s32 unused_second)
{
    town_event_state->entry_index = 0xFF;
    if (count_enabled_town_entries() != 0) {
        town_event_state->selected_entry = reset_event_selection_and_advance();
        town_event_state->selection_mode = 2;
        town_selected_valid_entry[0] = choose_valid_entry_or_fallback(town_event_state->selected_entry);
    } else {
        town_event_state->selection_mode = 1;
    }
}

/* Applies flag-dependent setup or forwards the arguments to the fallback handler. */
s32 handle_event_or_fallback(s32 fallback_first, s32 fallback_second) {
    LocalValues indexed_values;
    void *page;
    s32 second_or_base;

    second_or_base = fallback_second;
    indexed_values = D_80019164;
    if (func_8001E670(F_end_ending_step0) != 0) {
        if (func_8001E670(F_sbs01_pad19) == 0) {
            town_event_state->dispatchState = 1;
        } else {
            town_event_state->dispatchState = 2;
        }
    }

    if (town_event_state->dispatchState == 0) {
        second_or_base = 0x80010000;
        page = (void *)second_or_base;
        (*(UseValue *)((u8 *)(((Rec_D_80016000 *)(((S_8001BD20_0 *)page)->unk_6000))->services) + 0x2EC))(
            (*(s16 *)((u8 *)(indexed_values.value)
                + (*(GetIndex *)((u8 *)(((Rec_D_80016000 *)(((S_8001BD20_0 *)page)->unk_6000))->services)
                + 0x2D4))(0) * 2)),
            0x100);

        (*(CallPair *)((u8 *)(((Rec_D_80016000 *)(((S_8001BD20_0 *)page)->unk_6000))->services) + 0x2F8))(0x27, 0x200);

        ((TownPositionState *)(((Rec_D_80016000 *)((*(void * *)((u8 *)page + 0x6000))))->position))->unk_40 = D_8001F2D4;

        if ((*(GetIndex *)((u8 *)(((Rec_D_80016000 *)(((S_8001BD20_0 *)page)->unk_6000))->services) + 0x2D4))(0) == 2) {
            *(*(GetHalfword *)((u8 *)(((Rec_D_80016000 *)(((S_8001BD20_0 *)page)->unk_6000))->services) + 0x314))(0xC20,
                0x4A0) = 0x25;

            *(*(GetHalfword *)((u8 *)(((Rec_D_80016000 *)(((S_8001BD20_0 *)page)->unk_6000))->services) + 0x314))(0xD20,
                0x4A0) = 0x25;
        }
        return 1;
    }

    initialize_event_selection_state(fallback_first, second_or_base);
    return 0;
}
