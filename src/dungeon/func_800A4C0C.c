#include "common.h"

extern u32 func_800A2BDC(void *arg0);
extern s32 func_800A41F0(void *arg0);
extern s32 func_8009B7E4(void *arg0, void *arg1);
extern void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2);
extern void func_8009A21C(s32 arg0, s32 arg1, s32 arg2);
extern void func_800AA508(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_800AA5E4(void *arg0, void *arg1, void *arg2, void *arg3);
extern void *D_800814A8[4];

/* Try to move the entity, update positional sounds, and select the next action state. */
s32 func_800AA36C(void *action, void *context, void *position, void *entity) {
    s32 move_result;
    register s32 old_x ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 old_y;
    s32 sound_mode;
    u32 entity_flags;
    u8 player_state;

    if (((func_800A2BDC(entity) << 16) == 0) &&
        ((*(u16 *)((u8 *)action - 2) & 0x8000) == 0) &&
        ((*(volatile u32 *)((u8 *)entity + 0x1C) & 0x80000) == 0) &&
        ((*(u32 *)((u8 *)entity + 0x14) & 0x100000) == 0) &&
        ((player_state = *(u8 *)((u8 *)D_800814A8[0] + 0x9A)) != 0x18) &&
        (player_state != 0x11) &&
        ((func_800A41F0(entity) << 16) != 0)) {
        old_x = *(u8 *)((u8 *)position + 0x24);
        old_y = *(u8 *)((u8 *)position + 0x25);
        move_result = (s16)func_8009B7E4(position, entity);
        sound_mode = 0x3000;
        if (move_result != 0) {
            register u32 move_mask ASM_REG("$3") = 0x40000000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 sound_x = old_x;
            s32 sound_y;
            ASM_KEEP(move_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(sound_x);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            entity_flags = *(u32 *)((u8 *)entity + 0x1C) | move_mask;
            *(u32 *)((u8 *)entity + 0x1C) = entity_flags;
            if (entity_flags & 0x2000) {
                sound_mode = 0x300;
            }
            sound_y = old_y;
            ASM_KEEP(sound_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8009A3D0(sound_x, sound_y, sound_mode);
            entity_flags = *(u32 *)((u8 *)entity + 0x1C);
            func_8009A21C(*(u8 *)((u8 *)position + 0x24),
                          *(u8 *)((u8 *)position + 0x25),
                          (entity_flags & 0x2000) ? 0x300 : 0x3000);

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
