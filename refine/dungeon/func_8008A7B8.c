#include "common.h"

extern void *D_80088848[];
void func_80048A44();
s32 func_80094F74();
s32 func_80099F04();
s32 func_80099F70();
s32 func_800A2B04();
extern s16 D_80083228;
extern s32 D_80083460;
extern s16 D_80083464;
extern s32 D_8008ACDC;
extern s32 D_8008EAC8;
extern u8 D_800DD040[];
extern u8 D_800DD058[];
extern u8 D_800DD0C8[];

/* Updates timed movement and directional animation, then selects the next handler. */
void func_8008FF18(u8 *entity_in, s32 *motion_in, u16 *sprite_in, s32 *actor_in) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    u8 *entity = entity_in;
    s32 *motion = motion_in;
    register u16 *sprite ASM_REG("$18") = sprite_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 *actor ASM_REG("$19") = actor_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 *move_state;
    s32 vertical_speed;
    u8 phase;
    s32 start_y;
    s16 frames_left;
    u8 *anim_table;
    u8 *next_handler;
    u16 *move_flags;

    phase = *(u8 *)(entity + 0x9B);
    if (phase >= 0xDU) {
        goto block_25;
    }
    (void)jt_keep; goto *D_80088848[(u32)(phase)];
jt_c0:
jt_c8:
jt_c10:
    if (!(*(u16 *)((u8 *)sprite + 0x14) & 0x6000)) {
        goto block_25;
    }
    phase = *(u8 *)(entity + 0x9B);
    vertical_speed = 8;
    if (phase == 0) {
        vertical_speed = 0xFFF00000;
    } else {
        if (phase != vertical_speed) {
            vertical_speed = 0xFFEC0000;
        } else {
            vertical_speed = 0xFFF80000;
        }
    }
    *(s32 *)((u8 *)motion + 0x14) = vertical_speed;
    if (!(*(s32 *)((u8 *)actor + 0x1C) & 0x100000)) {
        goto block_9;
    }
    anim_table = D_800DD0C8;
    goto block_10;
block_9:
    anim_table = D_800DD040;
block_10:
    *(u8 **)((u8 *)sprite + 0x2C) = anim_table;
    func_80099F70(*(s32 *)((u8 *)actor + 0x5C));
    func_80099F04(*(s32 *)((u8 *)actor + 0x5C));
    move_flags = (u16 *)&D_80083460;
    move_flags[1] = (u16) (move_flags[1] | 0x812);
    *(u16 *)((u8 *)entity + 0x98) = (u16) (*(u16 *)((u8 *)entity + 0x98) & 0xFFF3);
    func_80048A44(sprite, *(*(u8 **)((u8 *)sprite + 0x2C) + (((s32) (D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7)), 0, 1);
    goto block_19;
jt_c1:
jt_c9:
jt_c11:
    move_state = (s16 *)&D_80083460;
    if (move_state[2] != 0) {
        s32 target_x;
        s32 start_x;
        target_x = *(u8 *)((u8 *)sprite + 0x24);
        target_x <<= 6;
        start_x = *(s16 *)((u8 *)motion + 2);
        start_x -= 0x20;
        *(s32 *)((u8 *)motion + 0xC) = ((target_x - start_x) << 0x10) / (s16) move_state[2];
        start_y = *(s16 *)((u8 *)motion + 6) - 0x20;
        *(s32 *)((u8 *)motion + 0x10) = (s32) ((s32) ((*(u8 *)((u8 *)sprite + 0x25) << 6) - start_y) << 0x10) / (s16) move_state[2];
    }
    frames_left = (u16) move_state[2] - 1;
    move_state[2] = frames_left;
    if ((frames_left << 0x10) > 0) {
        goto block_25;
    }
    move_state[2] = 0;
    *(s32 *)((u8 *)motion + 0x10) = 0;
    *(s32 *)((u8 *)motion + 0xC) = 0;
    func_800A2B04(motion, *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25));
    if (!(*(s32 *)((u8 *)actor + 0x1C) & 0x100000)) {
        goto block_17;
    }
    if ((func_80094F74(entity, motion, sprite, actor) << 0x10) <= 0) {
        goto block_25;
    }
    next_handler = (u8 *)&D_8008EAC8;
    goto block_24;
block_17:
    if ((u8) *(u8 *)(entity + 0x9B) < 0xAU) {
        goto block_22;
    }
    *(u8 **)((u8 *)sprite + 0x2C) = D_800DD058;
    func_80048A44(sprite, *(*(u8 **)((u8 *)sprite + 0x2C) + (((s32) (D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7)), 0, 1);
    move_state[2] = 1;
block_19:
    *(u8 *)(entity + 0x9B) = (u8) (*(u8 *)(entity + 0x9B) + 1);
    return;
jt_c12:
    if (!(*(u16 *)((u8 *)sprite + 0x14) & 0x6000)) {
        goto block_25;
    }
    D_80083464 = 0;
block_22:
    if ((func_80094F74(entity, motion, sprite, actor) << 0x10) <= 0) {
        goto block_25;
    }
    next_handler = (u8 *)&D_8008ACDC;
block_24:
    *(u8 **)((u8 *)entity + 0x8C) = next_handler;
block_25:
    return;
}
