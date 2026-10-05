#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern u8 D_800E1035[];

extern void func_800A6480(void *actor);
extern s32 func_800AD6FC(void *state, s32 mode, s32 item);
extern void func_800A5F38(void *object_context, s32 target);
extern void func_80098B38(s32 slot);
extern void func_800997FC(void *context);

/* Handle an item against a target using its type flags, decrementing the counter on fallback. */
s32 func_800BE4E8(void *target, s32 item) {
    u32 type_flags;

    if ((u32) target <= 0x9FFFFFFFU) {
        func_800A6480(target);
        type_flags = D_800DDE84[((u8 *) target)[0x13]];
        if (func_800AD6FC(target, (type_flags >> 2) & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
        func_80098B38(item);
    } else {
        func_800997FC(D_800E1035);
    }

    dungeonStatus.unk_0A -= 1;
    return 1;
}
