#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"


typedef struct S_800A1B44_1 {
    s32 unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
} S_800A1B44_1;   /* Pointer addresses record offset 0x14. */


s32 update_actor_proximity_flag(); /* extern */

/* Update proximity state for each actor in the list. */
void update_all_actor_proximity_flags(s16 near_limit, s16 far_limit) {
    void *actor;

    actor = (void *) (D_800E3D7C->next_actor_header + 0x20);
    if (actor != ((EntityRec *)D_800E3D7C)) {
        do {
            update_actor_proximity_flag(((S_800A1B44_1 *)((u8 *)actor - 0x14))->unk_00, actor, near_limit, far_limit,
                (void *) ((s32) actor + 0x9C));
            actor = (void *) (((S_800A1B44_1 *)((u8 *)actor - 0x14))->unk_70 + 0x20);
        } while (actor != ((EntityRec *)D_800E3D7C));
    }
}
