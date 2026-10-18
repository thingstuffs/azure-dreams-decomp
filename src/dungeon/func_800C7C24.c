#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"


extern void adjust_source_value_and_finalize();
extern void display_fixed_item_action_message();
extern void * spawn_randomized_particle_burst();
extern s32 roll_threshold_effect_variant_a();
extern void wrap_position_and_set_state_value();
extern s32 D_800DCF1C;
extern M2C_UNK D_800E1C14;



typedef struct S_800CD384_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD384_0_pre;   /* the 0x14 bytes before object in attempt_trap_request_eight_slots, addressed as object[-1] */


typedef struct S_800CD384_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD384_1;   /* entry in attempt_trap_request_eight_slots */

/* Run the 8-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise apply the effect and raise the tile marker unless the owning entry is flagged. */
s32 attempt_trap_request_eight_slots(void *object) {
    s32 amount;
    S_800CD384_1 *entry;

    amount = 0x40;
    if (D_800E3D40 != 0) {
        amount = 0x400;
    }
    if (roll_threshold_effect_variant_a(object, amount, 8) == 0) {
        if (((EntityRec *)object)->flags14 & 0x4000) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    adjust_source_value_and_finalize(object, &D_800E1C14);
    if ((*(u8 *)((u8 *)&((EntityRec *)object)->unk_10 + 3)) == 0) {
        wrap_position_and_set_state_value(D_800DCF1C);
    }
    entry = ((S_800CD384_0_pre *)object)[-1].unk_00;
    if (!(entry->unk_14 & 0x8000)) {
        spawn_randomized_particle_burst((entry->unk_24 << 6) | 0x20,
                      (entry->unk_25 << 6) | 0x20,
                      ((EntityRec *)object)->unk_88, 0x802080, 0x20, 1);
    }
    return 1;
}
