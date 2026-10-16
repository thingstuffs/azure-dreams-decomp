#include "modules/trap_effects_candidate.h"
#include "common.h"



extern s32 dungeonTryApplyConfusionStatus(void *object, s32 amount, s32 slots);
extern void func_800A6508();
extern void * dungeonSpawnRandomizedParticleBurst();
extern s32 func_800A56E0();

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
} Entry;

/* Run the 0x10-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise raise the tile effect and sound 0x611 unless the owning entry is flagged. */
s32 dungeonAttemptTrapRequestTenSlots(void *object) {
    s32 amount = 0x40;
    Entry *entry;

    if (D_800E3D40 != 0) {
        amount = 0x400;
    }
    if (dungeonTryApplyConfusionStatus(object, amount, 0x10) == 0) {
        if (*(u8 *)((u8 *)object + 0x13) == 0) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    entry = *(Entry **)((u8 *)object - 0x14);
    if (!(entry->flags & 0x8000)) {
        dungeonSpawnRandomizedParticleBurst((entry->x << 6) | 0x20,
                      (entry->y << 6) | 0x20,
                      *(s16 *)((u8 *)object + 0x88), 0x802020, 0x20, 0);
        func_800A56E0(0x611);
    }
    return 1;
}
