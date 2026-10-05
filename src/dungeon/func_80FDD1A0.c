#include "common.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern int abs(int);

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

extern u8 D_800D7960[];
extern u8 D_80170838[16];
extern u8 D_80170EA8;
extern u8 D_80174038[];
extern u8 D_80174078[];

/* Updates item use, its visual effect, and the actor's return to idle. */
void func_801729A0(S_func_80FDD1A0_1 *actor, VecData *motion, S_func_80FDD1A0_2 *sprite, S_func_80FDD1A0_3 *actor_data)
{
    s16 use_player = 0;
    S_func_80FDD1A0_4 *effect = 0;
    void *target;
    u8 *item_slot;
    S_func_80FDD1A0_2 *effect_sprite;
    ShortVec sound_pos;
    u8 phase;
    u32 kind_index;

    phase = actor->unk_9B;
    switch (phase) {
    case 0:
        if (actor_data->unk_1C & 0x2000) {
            kind_index = (actor_data->unk_46 & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                use_player = 1;
            case 2:
                item_slot = &actor_data->unk_0E;
                break;
            case 5:
                use_player = 1;
            case 1:
                item_slot = &actor_data->unk_0B;
                break;
            case 4:
                use_player = 1;
            case 0:
                item_slot = &actor_data->unk_08;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind = actor_data->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = &actor_data->unk_0E;
                break;
            case 2:
                item_slot = &actor_data->unk_0B;
                break;
            case 1:
                item_slot = &actor_data->unk_08;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            actor->unk_98 &= 0xFF7F;
            {
                s16 player_target;

                player_target = use_player;
                if (player_target != 0) {
                    target = D_800814A8;
                    actor_data->unk_60 = target;
                    {
                        S_func_80FDD1A0_2 *item_id;

                        item_id = ((S_func_80FDD1A0_5 *)((u8 *)target - 0x14))->unk_00;
                        actor_data->unk_72.u = item_id->unk_24;
                        actor_data->unk_73.u = item_id->unk_25;
                    }
                } else {
                    S_func_80FDD1A0_2 *item_id;

                    item_id = (S_func_80FDD1A0_2 *)(*item_slot);
                    if (D_8006DE24[((u8)item_id)].kind == 2) {
                        target = actor_data->unk_60;
                        if (target != 0) {
                            item_id = ((S_func_80FDD1A0_5 *)((u8 *)target - 0x14))->unk_00;
                            actor_data->unk_72.u = item_id->unk_24;
                            actor_data->unk_73.u = item_id->unk_25;
                        }
                    } else {
                        s32 target_x;
                        s32 abs_x;
                        s32 abs_y;
                        s32 target_y;

                        target = func_800A05A4(
                            actor_data,
                            sprite->unk_24,
                            sprite->unk_25,
                            actor_data->unk_2A.s,
                            0x10);
                        actor_data->unk_60 = target;
                        abs_x = abs(actor_data->unk_72.s);
                        abs_y = abs(actor_data->unk_73.s);
                        actor_data->unk_72.u = abs_x;
                        actor_data->unk_73.u = abs_y;
                    }
                }
            }

            sound_pos.x = motion->x >> 16;
            sound_pos.y = motion->y >> 16;
            sound_pos.z = motion->z >> 16;

            if (!(actor->unk_98 & 0x2000)) {
                void *new_effect;

                new_effect = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
                actor->unk_A8 = new_effect;
                effect = new_effect;
                if (effect != 0) {
                    VecData *effect_motion;

                    func_8004491C(effect, func_80045340);
                    effect->unk_10 = D_800D7960;
                    effect_motion = effect->unk_08;
                    *effect_motion = *motion;
                    effect->unk_BB = 0;
                    effect->unk_4A = actor_data->unk_2A.u;
                    {
                        s32 sprite_flags = sprite->unk_28;
                        effect_sprite = effect->unk_0C;

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
                u8 *animations;
                s32 direction;

                effect_sprite = actor->unk_A8;
                effect_sprite = ((S_func_80FDD1A0_4 *)effect_sprite)->unk_0C;
                animations = effect_sprite->unk_2C;
                direction = ((gameWork.view.viewAngle + actor_data->unk_2A.s + 0x100) >> 9) & 7;
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
        }
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        dungeonStatus.unk_0C = 0;
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
            D_80174038[((gameWork.view.viewAngle + actor_data->unk_2A.s + 0x100) >> 9) & 7],
            0);
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
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
