#include "modules/trap_effects_candidate.h"
#include "common.h"



extern s32 try_apply_confusion_status(void *object, s32 amount, s32 slots);
extern void display_fixed_item_action_message();
extern void * spawn_randomized_particle_burst();
extern s32 play_sound_if_enabled();

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
} Entry;

/* Run the 0x10-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise raise the tile effect and sound 0x611 unless the owning entry is flagged. */
s32 attempt_trap_request_ten_slots(void *object) {
    s32 amount = 0x40;
    Entry *entry;

    if (D_800E3D40 != 0) {
        amount = 0x400;
    }
    if (try_apply_confusion_status(object, amount, 0x10) == 0) {
        if (*(u8 *)((u8 *)object + 0x13) == 0) {
            display_fixed_item_action_message();
            return 1;
        }
        return 1;
    }
    entry = *(Entry **)((u8 *)object - 0x14);
    if (!(entry->flags & 0x8000)) {
        spawn_randomized_particle_burst((entry->x << 6) | 0x20,
                      (entry->y << 6) | 0x20,
                      *(s16 *)((u8 *)object + 0x88), 0x802020, 0x20, 0);
        play_sound_if_enabled(0x611);
    }
    return 1;
}
