#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u32 x;
    u32 y;
    u32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} VecData;

typedef struct {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} ItemData;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(void *, s16);

extern s32 D_80045340;
extern ItemData D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D7960[];
extern u8 D_80170838[16];
extern u8 D_80170EA8;
extern u8 D_80174038[];
extern u8 D_80174078[];

/* Updates item use, its visual effect, and the actor's return to idle. */
void func_801729A0(void *actor, VecData *motion, void *sprite, void *actor_data)
{
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_5, &&kind_6, &&kind_7
    };
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail register colouring depends on it */
    s32 use_player = 0;
    void *effect = (void *)zero;
    void *target;
    u8 *item_slot;
    u8 *turn_state;
    ShortVec sound_pos;
    u8 phase;

    phase = FIELD(actor, u8, 0x9B);
    switch (phase) {
    case 0:
        if (FIELD(actor_data, u32, 0x1C) & 0x2000) {
            u32 kind_index;

            kind_index = (FIELD(actor_data, u16, 0x46) & 0x3FFF) - 1;
            if (kind_index >= 7) {
                goto kind_default;
            }
            (void)kind_labels;
            goto *(((void **)D_80170838)[kind_index]);

kind_7:
            use_player = 1;
            goto kind_3;
kind_6:
            use_player = 1;
            goto kind_2;
kind_5:
            use_player = 1;
            goto kind_1;
        }

        {
            s32 action_kind;

            action_kind = FIELD(actor_data, u16, 0x46) & 0x3FFF;
            if (action_kind == 2) {
                goto kind_2;
            }
            if (action_kind < 3) {
                item_slot = 0;
                if (action_kind == 1) {
                    goto kind_1;
                }
                goto selection_ready;
            }
            if (action_kind != 3) {
                item_slot = 0;
                goto selection_ready;
            }
        }

kind_3:
        item_slot = (u8 *)actor_data + 0xE;
        goto selection_ready;
kind_2:
        item_slot = (u8 *)actor_data + 0xB;
        goto selection_ready;
kind_1:
        item_slot = (u8 *)actor_data + 8;
        goto selection_ready;
kind_default:
        item_slot = 0;

selection_ready:
        if (*item_slot == 0) {
            goto empty_selection;
        }
        FIELD(actor, u16, 0x98) &= 0xFF7F;
        {
            s32 player_target;

            player_target = use_player;
            ASM_KEEP(player_target);   /* MATCH pin: retail basic-block layout depends on it */
            if (player_target != 0) {
                target = D_800814A8;
                FIELD(actor_data, void *, 0x60) = target;
                goto copy_active_coords;
            }
        }

        {
            u8 item_id;

            item_id = *item_slot;
            if (D_8006DE24[item_id].type == 2) {
                target = FIELD(actor_data, void *, 0x60);
                if (target != 0) {
                    register u8 *target_sprite ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                    target_sprite = FIELD(target, u8 *, -0x14);
                    FIELD(actor_data, u8, 0x72) = target_sprite[0x24];
                    FIELD(actor_data, u8, 0x73) = target_sprite[0x25];
                    goto invoke_item;
                }
            } else {
                register s32 target_x ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                s32 target_y;

                target = func_800A05A4(
                    actor_data,
                    FIELD(sprite, u8, 0x24),
                    FIELD(sprite, u8, 0x25),
                    FIELD(actor_data, s16, 0x2A),
                    0x10);
                FIELD(actor_data, void *, 0x60) = target;
                target_x = FIELD(actor_data, s8, 0x72);
                target_y = FIELD(actor_data, s8, 0x73);
                if (target_x < 0) {
                    target_x = -target_x;
                }
                if (target_y < 0) {
                    target_y = -target_y;
                }
                FIELD(actor_data, u8, 0x72) = target_x;
                FIELD(actor_data, u8, 0x73) = target_y;
            }
        }

invoke_item:
        sound_pos.x = motion->x >> 16;
        sound_pos.y = motion->y >> 16;
        sound_pos.z = motion->z >> 16;

        if (!(FIELD(actor, u16, 0x98) & 0x2000)) {
            void *new_effect;

            new_effect = func_8003FD64(0x112, D_80083498);
            effect = new_effect;
            ASM_KEEP(new_effect);   /* MATCH pin: retail register colouring depends on it */
            FIELD(actor, void *, 0xA8) = new_effect;
            if (effect != 0) {
                VecData *effect_motion;

                func_8004491C(effect, &D_80045340);
                FIELD(effect, void *, 0x10) = D_800D7960;
                effect_motion = FIELD(effect, VecData *, 8);
                *effect_motion = *motion;
                FIELD(effect, u8, 0xBB) = 0;
                FIELD(effect, u16, 0x4A) = FIELD(actor_data, u16, 0x2A);
                {
                    s32 sprite_flags = FIELD(sprite, s32, 0x28);
                    register void *effect_sprite ASM_REG("$4") = FIELD(effect, void *, 0x0C);   /* MATCH pin: retail register colouring depends on it */

                    FIELD(effect_sprite, u16, 0x1E) = 0x1000;
                    FIELD(effect_sprite, u16, 0x1C) = 0x1000;
                    FIELD(effect_sprite, s32, 0x28) = sprite_flags;
                    FIELD(effect_sprite, u16, 0x14) = FIELD(sprite, u16, 0x14);
                    FIELD(effect_sprite, u16, 0x12) = FIELD(sprite, u16, 0x12);
                    {
                        s32 sprite_link = FIELD(sprite, s32, 0x0C);

                        FIELD(effect_sprite, void *, 0x2C) = D_80174078;
                        FIELD(effect_sprite, s32, 0x0C) = sprite_link;
                    }
                }
            }
            FIELD(actor, u16, 0x98) |= 0x2000;
        }

        {
            void *effect_sprite;
            u8 *animations;
            s32 direction;

            effect_sprite = FIELD(actor, void *, 0xA8);
            effect_sprite = FIELD(effect_sprite, void *, 0x0C);
            animations = FIELD(effect_sprite, u8 *, 0x2C);
            direction = ((D_80083228 + FIELD(actor_data, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(effect_sprite, animations[direction], 0);
        }
        if (func_800A94A0(actor_data, item_slot, use_player,
                          (u16 *)((u8 *)actor + 0x98)) == 0) {
            return;
        }
        FIELD(actor, u16, 0x98) &= 0xDFFF;
        FIELD(sprite, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(&sound_pos, (*item_slot - 1) % 3);
        FIELD(actor, u8, 0x9B)++;
        return;

empty_selection:
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
        D_8008346C = 0;
        FIELD(D_800814A8, u16, 0xA6)--;
        func_800A4ACC(actor_data);
        FIELD(actor_data, u8, 0x6D)--;
        FIELD(actor, void *, 0x8C) = &D_80170EA8;
        FIELD(actor_data, u8, 0x73) = 0;
        FIELD(actor_data, u8, 0x72) = 0;
        FIELD(actor_data, u16, 0x46) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            FIELD(sprite, u16, 0x14) |= 0x800;
            return;
        }
        FIELD(sprite, u16, 0x14) &= 0xF7FF;
        FIELD(actor, u8, 0x9B)++;
        /* fallthrough */

    case 2:
        if (FIELD(actor, void *, 0xA8) != 0) {
            effect = FIELD(actor, void *, 0xA8);
            *FIELD(effect, VecData *, 8) = *motion;
        }
        if ((FIELD(sprite, s8, 4) != 4 ||
             !(FIELD(sprite, u16, 0x14) & 0x1000)) &&
            !(FIELD(sprite, u16, 0x14) & 0xE000)) {
            return;
        }
        FIELD(actor, u16, 0x98) |= 0x80;
        if (!(FIELD(sprite, u16, 0x14) & 0xE000)) {
            return;
        }
        if (FIELD(actor, void *, 0xA8) != 0) {
            FIELD(effect, u8, 0xBB) = 0xFF;
            FIELD(actor, void *, 0xA8) = 0;
        }
        FIELD(sprite, void *, 0x2C) = D_80174038;
        func_80047784(
            sprite,
            D_80174038[((D_80083228 + FIELD(actor_data, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
        turn_state = (u8 *)&D_80083460;
        if (FIELD(turn_state, s32, 0x0C) != 0) {
            return;
        }
        FIELD(turn_state, u16, 0x0A)--;
        FIELD(sprite, u16, 0x14) &= 0xF7FF;
        FIELD(actor, void *, 0x8C) = &D_80170EA8;
        func_800A4ACC(actor_data);
        if (FIELD(actor_data, s8, 0x6D) > 0) {
            FIELD(actor_data, u8, 0x6D)--;
        }
        FIELD(actor_data, u8, 0x73) = 0;
        FIELD(actor_data, u8, 0x72) = 0;
        FIELD(actor_data, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
        return;

    default:
        return;
    }
}
