#include "common.h"
#include "shared/def_table.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

typedef struct Actor {
    u8 pad00[0x14];
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x0A];
    u16 field2a;
    u8 pad2c[0x5C];
    s16 coord88;
    u8 pad8a[0x0E];
    u16 status98;
} Actor;

typedef struct Entity {
    u8 pad00[0x24];
    u8 x;
    u8 y;
} Entity;

extern s32 func_80042900();
extern s16 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 func_8009FD40();
extern s32 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A35D8(s32 left_mask, s32 right_mask);
extern s32 func_800A365C();
extern s32 func_800A6D30(void);

/* Selects a usable ability or adjacent attack and sets the angle toward the target. */
s16 func_800A384C(Actor *actor, Actor *target, u16 *out_angle, s32 prefer_ability)
{
    u16 tile_flags;
    s32 slots_checked;
    s16 selected_action;
    s16 best_score;
    s16 line_valid;
    Entity *actor_entity;
    Actor *self;
    Entity *target_entity;
    DefEntry *ability;
    u8 ability_id;
    s32 effect_id;
    s16 effect_blocked;
    s16 obstacles;
    s32 move_flags;
    s32 path_flags;
    s32 distance;
    s32 angle;
    s16 slot;
    s32 temp;
    s32 offset;
    s16 steps;
    s16 x;
    s16 y;
    s32 score;
    s32 flags;
    s16 dir;

    selected_action = -1;
    best_score = -0x100;
    *out_angle = actor->field2a;
    self = actor;
    target_entity = *(Entity **)((u8 *)target - 0x14);
    actor_entity = *(Entity **)((u8 *)self - 0x14);
    if (abs(actor->coord88 - target->coord88) >= 0x40) {
        return -1;
    }
    line_valid = func_800A365C(actor_entity, target_entity);
    distance = func_8009FD40(target_entity, actor_entity);
    angle = func_800A0818(actor_entity->x, actor_entity->y, target_entity->x, target_entity->y, &tile_flags);
    *out_angle = angle;
    if (prefer_ability == 0 && distance == 1) {
        if ((s16)func_8009A540((u16)((s16)angle >> 9), actor_entity->x, actor_entity->y,
                actor->coord88 - 0x20) != 0) {
            return 8;
        }
    }
    flags = actor->flags14;
    if (!(flags & 0x10000)) {
        actor->flags14 = flags | 0x10000;
        if (func_8009FD40(&D_80082E80, actor_entity) < 0x11
            && ((actor->flags14 & 0x6000) || !(self->status98 & 0x10) || !(func_800A6D30() & 0xF))
            && !(func_800A6D30() & 3) && (s16)func_80042900(actor, 6) == 0) {
            self->status98 |= 0x11;
        } else {
            self->status98 &= 0xFFFE;
        }
    }
    if (self->status98 & 1) {
        slot = dungeonStatus.unk_1E & 3;
        for (slots_checked = 0; slots_checked < 3; slots_checked++, slot++) {
            if (slot == 3) {
                slot = 0;
            }
            offset = slot * 3;
            temp = (s32)actor + offset;
            ability_id = ((u8 *)temp)[8];
            if (ability_id == 0) {
                continue;
            }
            offset = ability_id << 2;
            offset += ability_id;
            offset <<= 2;
            ability = (DefEntry *)((u8 *)D_8006DE24 + offset);
            effect_id = ability->unk_11;
            if ((u32)effect_id >= 0x12) {
                continue;
            }
            effect_blocked = func_80042900(target, (s8)effect_id);
            if (effect_blocked != 0) {
                continue;
            }
            if (ability->unk_13 < distance) {
                continue;
            }
            score = func_800A35D8(ability->unk_10, *(u16 *)&actor->flags14);
            if ((s16)score <= best_score) {
                continue;
            }
            temp = ability->kind;
            if (temp != 1) {
                if (temp == 0 || temp >= 4) {
                    continue;
                }
            } else {
                if (line_valid == 0) {
                    continue;
                }
                x = actor_entity->x;
                y = actor_entity->y;
                dir = (*out_angle >> 9) & 7;
                for (steps = 0; steps < distance; steps++) {
                    func_8009A350(x, y, dir, &tile_flags);
                    move_flags = actor->flags1c;
                    if (!(move_flags & 0x410)) {
                        path_flags = (s16)tile_flags;
                        if (move_flags & 0x2000) {
                            obstacles = path_flags & 0x300;
                        } else {
                            obstacles = path_flags & 0x3000;
                        }
                        if (obstacles != 0) {
                            break;
                        }
                    }
                    x += dirStepX[dir];
                    y += dirStepY[dir];
                }
                if (steps < distance) {
                    continue;
                }
            }
            best_score = score;
            selected_action = slot + 1;
        }
    }
    if (prefer_ability != 0 && distance == 1) {
        if ((s16)func_8009A540((u16)((s16)*out_angle >> 9), actor_entity->x, actor_entity->y,
                actor->coord88 - 0x20) != 0) {
            if (selected_action < 0) {
                selected_action = 8;
            }
        }
    }
    return selected_action;
}
