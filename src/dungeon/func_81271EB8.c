/* Relink of matched dungeon/func_813262A4; every changed retail word is a paired relocation. */
#define D_8016B778 D_80153514
/* Relink of matched dungeon/func_800D4F00; every changed retail word is a paired relocation. */
#define D_800D8C64 D_80153514
#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 update_actor_transform_from_parent(void);
extern s16 check_actor_floor_trap(s32, s32);
extern u8 D_80153514[];

void func_801556B8(CallbackOwner *owner, s32 unused, s32 first, s32 second) {
    if (update_actor_transform_from_parent() && check_actor_floor_trap(first, second) > 0) {
        owner->callback = D_80153514;
    }
}
