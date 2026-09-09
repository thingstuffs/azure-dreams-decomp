#include "common.h"

typedef struct {
    u32 unk0;
    void *unk4;
} Entry;

extern Entry D_80082660[];
extern s32 D_80082A38[64];

/* anyone_now_pos_get: store the actor's current position in the script variables. */
void anyone_now_pos_get(s32 actor_id) {
    s32 *script_vars = D_80082A38;
    void *actor;
    s16 *position;

    if (actor_id != 0) {
        actor = D_80082660[actor_id].unk4;
        if (actor != 0) {
            position = *(s16 **)((u8 *)actor + 8);
            script_vars[0x13] = position[1];
            script_vars[0x14] = position[3];
            script_vars[0x15] = position[5];
        }
    }
}
