#include "common.h"

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

typedef struct S_func_80FDD1A0_1 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x08];
    u16 unk_98;
    u8 pad_9A[0x01];
    u8 unk_9B;
    u8 pad_9C[0x0A];
    u16 unk_A6;
    void *unk_A8;
} S_func_80FDD1A0_1;

typedef struct S_func_80FDD1A0_2 {
    u8 pad_00[0x04];
    s8 unk_04;
    u8 pad_05[0x07];
    s32 unk_0C;
    u8 pad_10[0x02];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x06];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x04];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x02];
    s32 unk_28;
    u8 *unk_2C;
} S_func_80FDD1A0_2;

typedef struct S_func_80FDD1A0_3 {
    u8 pad_00[0x08];
    u8 unk_08;
    u8 pad_09[0x02];
    u8 unk_0B;
    u8 pad_0C[0x02];
    u8 unk_0E;
    u8 pad_0F[0x0D];
    u32 unk_1C;
    u8 pad_20[0x0A];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void *unk_60;
    u8 pad_64[0x09];
    union { s8 s; u8 u; } unk_6D;
    u8 pad_6E[0x04];
    union { s8 s; u8 u; } unk_72;
    union { s8 s; u8 u; } unk_73;
} S_func_80FDD1A0_3;

typedef struct S_func_80FDD1A0_4 {
    u8 pad_00[0x08];
    VecData *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    u8 unk_BB;
} S_func_80FDD1A0_4;

typedef struct S_func_80FDD1A0_5 {
    void *unk_00;
} S_func_80FDD1A0_5;

typedef struct S_func_80FDD1A0_6 {
    u8 pad_00[0x0A];
    u16 unk_0A;
    s32 unk_0C;
} S_func_80FDD1A0_6;

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
void func_801729A0(S_func_80FDD1A0_1 *actor, VecData *motion, S_func_80FDD1A0_2 *sprite, S_func_80FDD1A0_3 *actor_data)
{
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_5, &&kind_6, &&kind_7
    };
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 use_player = 0;
    S_func_80FDD1A0_4 *effect = (void *)zero;
    void *target;
    u8 *item_slot;
    S_func_80FDD1A0_6 *turn_state;
    ShortVec sound_pos;
    u8 phase;

    phase = actor->unk_9B;
    switch (phase) {
    case 0:
        if (actor_data->unk_1C & 0x2000) {
            u32 kind_index;

            kind_index = (actor_data->unk_46 & 0x3FFF) - 1;
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

            action_kind = actor_data->unk_46 & 0x3FFF;
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
        item_slot = &actor_data->unk_0E;
        goto selection_ready;
kind_2:
        item_slot = &actor_data->unk_0B;
        goto selection_ready;
kind_1:
        item_slot = &actor_data->unk_08;
        goto selection_ready;
kind_default:
        item_slot = 0;

selection_ready:
        if (*item_slot == 0) {
            goto empty_selection;
        }
        actor->unk_98 &= 0xFF7F;
        {
            s32 player_target;

            player_target = use_player;
            ASM_KEEP(player_target);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (player_target != 0) {
                target = D_800814A8;
                actor_data->unk_60 = target;
                goto copy_active_coords;
            }
        }

        {
            u8 item_id;

            item_id = *item_slot;
            if (D_8006DE24[item_id].type == 2) {
                target = actor_data->unk_60;
                if (target != 0) {
                    register S_func_80FDD1A0_2 *target_sprite ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

copy_active_coords:
                    target_sprite = ((S_func_80FDD1A0_5 *)((u8 *)target - 0x14))->unk_00;
                    actor_data->unk_72.u = target_sprite->unk_24;
                    actor_data->unk_73.u = target_sprite->unk_25;
                    goto invoke_item;
                }
            } else {
                register s32 target_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                s32 target_y;

                target = func_800A05A4(
                    actor_data,
                    sprite->unk_24,
                    sprite->unk_25,
                    actor_data->unk_2A.s,
                    0x10);
                actor_data->unk_60 = target;
                target_x = actor_data->unk_72.s;
                target_y = actor_data->unk_73.s;
                if (target_x < 0) {
                    target_x = -target_x;
                }
                if (target_y < 0) {
                    target_y = -target_y;
                }
                actor_data->unk_72.u = target_x;
                actor_data->unk_73.u = target_y;
            }
        }

invoke_item:
        sound_pos.x = motion->x >> 16;
        sound_pos.y = motion->y >> 16;
        sound_pos.z = motion->z >> 16;

        if (!(actor->unk_98 & 0x2000)) {
            void *new_effect;

            new_effect = func_8003FD64(0x112, D_80083498);
            effect = new_effect;
            ASM_KEEP(new_effect);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            actor->unk_A8 = new_effect;
            if (effect != 0) {
                VecData *effect_motion;

                func_8004491C(effect, &D_80045340);
                effect->unk_10 = D_800D7960;
                effect_motion = effect->unk_08;
                *effect_motion = *motion;
                effect->unk_BB = 0;
                effect->unk_4A = actor_data->unk_2A.u;
                {
                    s32 sprite_flags = sprite->unk_28;
                    register S_func_80FDD1A0_2 *effect_sprite ASM_REG("$4") = effect->unk_0C;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                    effect_sprite->unk_1E = 0x1000;
                    effect_sprite->unk_1C = 0x1000;
                    effect_sprite->unk_28 = sprite_flags;
                    effect_sprite->unk_14 = sprite->unk_14;
                    effect_sprite->unk_12 = sprite->unk_12;
                    {
                        s32 sprite_link = sprite->unk_0C;

                        effect_sprite->unk_2C = D_80174078;
                        effect_sprite->unk_0C = sprite_link;
                    }
                }
            }
            actor->unk_98 |= 0x2000;
        }

        {
            S_func_80FDD1A0_2 *effect_sprite;
            u8 *animations;
            s32 direction;

            effect_sprite = actor->unk_A8;
            effect_sprite = ((S_func_80FDD1A0_4 *)effect_sprite)->unk_0C;
            animations = effect_sprite->unk_2C;
            direction = ((D_80083228 + actor_data->unk_2A.s + 0x100) >> 9) & 7;
            func_80047784(effect_sprite, animations[direction], 0);
        }
        if (func_800A94A0(actor_data, item_slot, use_player,
                          &actor->unk_98) == 0) {
            return;
        }
        actor->unk_98 &= 0xDFFF;
        sprite->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(&sound_pos, (*item_slot - 1) % 3);
        actor->unk_9B++;
        return;

empty_selection:
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        D_8008346C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(actor_data);
        actor_data->unk_6D.u--;
        actor->unk_8C = &D_80170EA8;
        actor_data->unk_73.u = 0;
        actor_data->unk_72.u = 0;
        actor_data->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            sprite->unk_14 |= 0x800;
            return;
        }
        sprite->unk_14 &= 0xF7FF;
        actor->unk_9B++;
        /* fallthrough */

    case 2:
        if (actor->unk_A8 != 0) {
            effect = actor->unk_A8;
            *effect->unk_08 = *motion;
        }
        if ((sprite->unk_04 != 4 ||
             !(sprite->unk_14 & 0x1000)) &&
            !(sprite->unk_14 & 0xE000)) {
            return;
        }
        actor->unk_98 |= 0x80;
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        if (actor->unk_A8 != 0) {
            effect->unk_BB = 0xFF;
            actor->unk_A8 = 0;
        }
        *(void **)((u8 *)sprite + 0x2C) = D_80174038;
        func_80047784(
            sprite,
            D_80174038[((D_80083228 + actor_data->unk_2A.s + 0x100) >> 9) & 7],
            0);
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        turn_state = (S_func_80FDD1A0_6 *)&D_80083460;
        if (turn_state->unk_0C != 0) {
            return;
        }
        turn_state->unk_0A--;
        sprite->unk_14 &= 0xF7FF;
        actor->unk_8C = &D_80170EA8;
        func_800A4ACC(actor_data);
        if (actor_data->unk_6D.s > 0) {
            actor_data->unk_6D.u--;
        }
        actor_data->unk_73.u = 0;
        actor_data->unk_72.u = 0;
        actor_data->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        return;

    default:
        return;
    }
}
