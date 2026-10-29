#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/player/state.h"

typedef struct S_800161C0_0 {
    u8 pad_00[0x24];
    void * unk_24;
} S_800161C0_0;   /* *(void **)D_80016000 in advance_floor_event_counter */

typedef struct S_800161C0_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800161C0_1;   /* ((S_800161C0_0 *)(*(void **)D_80016000))->unk_24 in advance_floor_event_counter */

typedef struct S_800161C0_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800161C0_2;   /* ((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)D_80016000))->unk_24))->unk_74 in advance_floor_event_counter */

extern void func_8001DCD4(s32 slot_id);

#define CURRENT_FLOOR() \
((S_800161C0_2 *)(((S_800161C0_1 *)(((S_800161C0_0 *)(*(void **)((s8 *)(&town_scene_root))))->unk_24))->unk_74))->unk_2A

/* Advance the counter up to five and process the current floor unless an early exit applies. */
s32 advance_floor_event_counter(Rec_func_800165F4_arg0 *fallback_arg_a, s32 fallback_arg_b) {
    s32 count;
    s32 next_count;
    s32 capped_count;

    if (get_script_flag_mask(Ft_s07_mia_bikou_end) != 0) {
        set_indexed_entry_flag(fallback_arg_a, fallback_arg_b);
        return 1;
    }

    count = read_script_flag_range(Ftt_pad83, 3);
    if ((CURRENT_FLOOR() == 7) && (count >= 5)) {
        return 1;
    }

    next_count = count + 1;
    capped_count = 5;
    if (next_count < 6) {
        capped_count = next_count;
    }
    write_script_flag_range(Ftt_pad83, capped_count, 3);
    func_8001DCD4(CURRENT_FLOOR());
    return 0;
}
