#include "common.h"

typedef struct {
    s32 unk0;       /* 0x00 */
    s16 *unk4;      /* 0x04 */
} Entry;            /* size 8 */

extern Entry D_80082660[];
extern s32 D_80082A38[64];

/* anyone_org_pos_get: copy the actor's original position to script variables. */
void anyone_org_pos_get(s32 actor_id) {
    s32 *script_vars = D_80082A38;
    s16 *actor;
    s16 *position_data;

    if (actor_id != 0) {
        actor = D_80082660[actor_id].unk4;
        if (actor != 0) {
            position_data = (s16 *)((u8 *)actor + 0x20);
            script_vars[0x13] = *(s16 *)((u8 *)position_data + 0x84);
            script_vars[0x14] = *(s16 *)((u8 *)position_data + 0x86);
        }
    }
}
