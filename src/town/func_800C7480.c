#include "common.h"

typedef struct {
    s32 unk0;
    void *unk4;
} Entry;

extern Entry D_80082660[];
extern s32 D_80082A38[];

extern s32 func_800C2B6C(s32, void *);

/* anyone_org_ang_get: store the actor's converted original angle in the script variables. */
void anyone_org_ang_get(s32 actor_id, void *script_context) {
    s32 *script_vars = D_80082A38;
    void *actor;

    if (actor_id != 0) {
        actor = D_80082660[actor_id].unk4;
        if (actor != 0) {
            script_vars[0x12] = func_800C2B6C(*(s16 *)((u8 *)actor + 0x8E), script_context);
        }
    }
}
