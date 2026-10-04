#include "common.h"
#include "shared/record_ptrs.h"

extern u32 func_800A2BDC(void *entity);
extern s32 func_800A41F0(void *entity);
extern s32 func_8009B7E4(void *object, void *context);
extern void func_8009A3D0(s32 x, s32 y, s32 flag_mask);
extern void func_8009A21C(s32 x, s32 y, s32 flags);
extern void func_800AA508(void *entity, void *unused_1, void *unused_2, void *unused_3);
extern void func_800AA5E4(void *entity, void *unused, void *position, void *entity_state);

/* Try to move the entity, update positional sounds, and select the next action state. */
s32 func_800AA36C(void *action, void *context, void *position, void *entity) {
    s32 move_result;
    s16 old_x;
    s16 old_y;
    u32 entity_flags;
    u32 post_flags;
    u8 player_state;

    if (((func_800A2BDC(entity) << 16) == 0) &&
        ((*(u16 *)((u8 *)action - 2) & 0x8000) == 0) &&
        ((*(u32 *)((u8 *)entity + 0x1C) & 0x80000) == 0) &&
        ((*(u32 *)((u8 *)entity + 0x14) & 0x100000) == 0) &&
        ((player_state = *(u8 *)((u8 *)D_800814A8 + 0x9A)) != 0x18) &&
        (player_state != 0x11) &&
        ((func_800A41F0(entity) << 16) != 0)) {
        old_x = *(u8 *)((u8 *)position + 0x24);
        old_y = *(u8 *)((u8 *)position + 0x25);
        move_result = (s16)func_8009B7E4(position, entity);
        if (move_result != 0) {
            entity_flags = *(u32 *)((u8 *)entity + 0x1C) | 0x40000000;
            *(u32 *)((u8 *)entity + 0x1C) = entity_flags;
            func_8009A3D0(old_x, old_y, (entity_flags & 0x2000) ? 0x300 : 0x3000);
            post_flags = *(u32 *)((u8 *)entity + 0x1C);
            func_8009A21C(*(u8 *)((u8 *)position + 0x24),
                          *(u8 *)((u8 *)position + 0x25),
                          (post_flags & 0x2000) ? 0x300 : 0x3000);

            if (move_result == 1) {
                func_800AA508(action, context, position, entity);
                return 1;
            } else {
                func_800AA5E4(action, context, position, entity);
                return 1;
            }
        }
    }
    return 0;
}
