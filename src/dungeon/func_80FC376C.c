#include "shared/entity.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

typedef struct ParticleObjectView {
    u8 pad_00[0x8];
    void * position;
    void * sprite;
    void * source;
    u8 pad_14[0xA6];
    u8 phase;
} ParticleObjectView;

typedef struct ParticlePositionView {
    s32 x;
    s32 y;
    u32 z;
} ParticlePositionView;

typedef struct ParticleSpriteView {
    void * source;
    u8 sourceIndex;
    u8 sourceFrame;
    u8 pad_06[0x2];
    u32 texture;
    u32 color;
    u16 angle;
    u8 pad_12[0x2];
    u16 flags;
    u8 pad_16[0x6];
    u16 scaleX;
    u16 scaleY;
} ParticleSpriteView;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, void *, void *, void *);
extern s32 process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *, void *, void *, void *, void *);

extern void func_8015F910(void);
extern void func_8015FB68(void *, void *, void *, void *);
extern s32 func_80160314(void *, void *, void *, void *);
extern void func_80160514(void *, void *, void *, void *);
extern s32 func_80160658(void *, void *, void *, s32);
extern void func_80162250(void *, void *, void *, void *);

extern void *D_800814A8[3];
extern u8 D_800DEA68[];
extern u8 D_80163174[];
extern u8 D_80163258[];
extern u8 D_80163260[];
extern u8 D_80163290[];
extern u8 D_80163298[];
extern u8 D_801632A0[];

void update_actor_action_sequence_and_recovery(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *entity)
{
    u16 initial_flags = g_dungeon_status.flags;
    void *current_frames;
    u8 *direction_frames;
    s32 facing_aux;
    s8 tile_index;

    if (initial_flags & 0x1000) {
        action->behavior = 0xE;
        func_8015F910();
        return;
    }

    if (entity->tileY == 0) {
        advance_actor_pending_action(action, motion, sprite, entity);
        {
            void *current =
                sprite->directionFrames;
            void *table;
            table = (u8 *)&D_80163298;
            current_frames = current;
            direction_frames = table;
            if (current_frames != direction_frames) {
                u32 direction_index;

                sprite->directionFrames = direction_frames;
                direction_index = ((g_game_work.view.viewAngle +
                    entity->facing + 0x100) >> 9) & 7;
                /* Keep the integer addition order used by the retail compiler. */
                select_sprite_entry(sprite,
                    *(u8 *)((u32)direction_index + (u32)direction_frames),
                    0);
            }
            return;
        }
    }

    if (entity->flags1C & 0x200) {
        if (sprite->directionFrames == D_80163298) {
            action->behavior = 0xD;
            action->phase = 1;
            action->nextAction.code = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action, motion, sprite, D_80163298) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            begin_pushed_actor_move(action, motion, sprite, entity);
            return;
        }

        {
            u32 state;
            u32 current_state = action->behavior;
            state = 0xE;
            if (current_state != state) {
                if (sprite->directionFrames != D_80163258) {
                    sprite->directionFrames = D_80163258;
                    select_sprite_entry(sprite,
                        D_80163258[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                }
                action->behavior = state;
            }
        }

        if (entity->flags14 & 0x20000) {
            switch (action->effectState.signedPhase) {
            case 0:
                if (sprite->directionFrames != D_801632A0) {
                    g_dungeon_status.unk_0A++;
                    action->saved.facing = (u16)(entity->facing);
                    entity->facing =
                        (entity->unk_6A + 0x800) & 0xFFF;
                    sprite->flags &= 0x9FFF;
                    action->effectTicks = 300;
                }
                action->effectState.phase++;
                return;

            case 1:
            {
                u16 timer = action->effectTicks - 1;

                action->effectTicks = timer;
                if ((s16)timer <= 0 ||
                    entity->unk_64 != 0) {
                    g_dungeon_status.unk_0A--;
                    motion->unk_10 = 0;
                    motion->unk_0C = 0;
                    set_record_integer_tile_center(motion,
                        sprite->position.tile.x, sprite->position.tile.y);
                    entity->flags14 &= ~0x20000;
                    action->effectState.phase = 0;
                    return;
                }
                if (entity->flags14 & 0x1000000) {
                    action->effectState.phase++;
                    sprite->directionFrames = D_801632A0;
                    select_sprite_entry(sprite,
                        D_801632A0[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    action->effectTicks = 0;
                    return;
                }
                return;
            }

            case 2:
            {
                s32 scale;
                ParticleObjectView *effect_object;
                ParticleSpriteView *effect_sprite;
                ParticlePositionView *effect_position;
                u32 color;
                u32 height_word;
                u32 texture;

                motion->unk_0C =
                    dir_step_x[((s32)(entity->unk_6A << 16)) >> 25] << 16;
                motion->unk_10 =
                    dir_step_y[((s32)(entity->unk_6A << 16)) >> 25] << 16;
                scale = func_800644B8((s16)action->effectTicks << 8);
                motion->unk_0C = motion->unk_0C +
                    (motion->unk_0C * scale >> 9);
                scale = func_800644B8((s16)action->effectTicks << 8);
                motion->unk_10 = motion->unk_10 +
                    (motion->unk_10 * scale >> 9);

                effect_object = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
                if (effect_object != 0) {
                    register_node(effect_object, project_sprite_chain);
                    effect_position = effect_object->position;
                    effect_object->source = D_80163174;
                    effect_sprite = effect_object->sprite;
                    effect_position->x = motion->x.v;
                    effect_position = effect_object->position;
                    effect_position->y = motion->y.v;
                    effect_position = effect_object->position;
                    height_word = motion->z.v;
                    color = 0x00800000;
                    effect_position->z = height_word;
                    effect_sprite->scaleY = 0x1000;
                    effect_sprite->scaleX = 0x1000;
                    effect_sprite->angle = 0;
                    effect_sprite->source = D_800DEA68;
                    effect_sprite->flags |= 0xC;
                    texture = ((u32)((SpriteSourceEntry *)D_800DEA68)->unk_04);
                    color |= 0x8080;
                    effect_sprite->sourceIndex = 0;
                    effect_sprite->sourceFrame = 0;
                    effect_sprite->color = color;
                    effect_sprite->texture = texture;
                    effect_object->phase = 0;
                }

                {
                    u16 old_timer = action->effectTicks;
                    action->effectTicks = old_timer + 1;
                    if ((s16)old_timer >= 3) {
                        sprite->flags &= 0xF7FF;
                        motion->unk_10 = 0;
                        motion->unk_0C = 0;
                        action->effectTicks = 4;
                        action->effectState.phase++;
                        return;
                    }
                }
                return;
            }

            case 3:
            {
                u16 timer = action->effectTicks - 1;

                action->effectTicks = timer;
                if ((s16)timer <= 0) {
                    sprite->flags &= 0xF7FF;
                    motion->unk_10 = 0;
                    motion->unk_0C = 0;
                    action->effectTicks = 3;
                    action->effectState.phase++;
                    return;
                }
                return;
            }

            case 4:
            {
                s32 x;
                s32 y;
                s32 tile_y_world;
                s32 tile_x_world;
                s32 offset_y;
                s32 offset_x;
                u16 timer;

                tile_x_world = sprite->position.tile.x << 6;
                offset_x = motion->x.w.i - 0x20;
                x = tile_x_world - offset_x;
                motion->unk_0C = (s32)((u32)x << 15) >> 1;
                tile_y_world = sprite->position.tile.y << 6;
                offset_y = motion->y.w.i - 0x20;
                y = tile_y_world - offset_y;
                motion->unk_10 = (s32)((u32)y << 15) >> 1;
                timer = action->effectTicks - 1;
                action->effectTicks = timer;
                if ((s16)timer <= 0) {
                    g_dungeon_status.unk_0A--;
                    motion->unk_10 = 0;
                    motion->unk_0C = 0;
                    set_record_integer_tile_center(motion,
                        sprite->position.tile.x, sprite->position.tile.y);
                    entity->flags14 &= ~0x20000;
                    entity->facing = action->saved.facing;
                    sprite->directionFrames = D_80163258;
                    select_sprite_entry(sprite,
                        D_80163258[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    action->effectState.phase = 0;
                    return;
                }
                return;
            }
            default:
                return;
            }
        } else {
            action->flags &= 0xFFF3;
            if (entity->unk_64 == 0 ||
                begin_ready_actor_directional_action(action, motion, sprite, D_80163260) == 0) {
                if (entity->flags1C & 0x80000) {
                    begin_actor_move_to_target_facing(action, motion, sprite, entity);
                    func_80162250(action, motion, sprite, entity);
                    return;
                }
                if ((s16)can_entity_gain_level(entity) != 0) {
                    process_selected_actor_record(action, motion, sprite, entity);
                }
            } else {
                return;
            }
        }
    }

    tile_index = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->tileIndex.signedIndex = tile_index;

    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (sprite->position.packed == ((TilePairView *)&D_80082E80.tileX)->packed) {
            func_8015FB68(action, motion, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if ((g_dungeon_status.flags & 0x2000) &&
                ((s16)check_entity_relation(entity,
                    (u8 *)((EntityRec *)(D_800814A8[0]))->unk_58 + 0x20) != 0)) {
                return;
            }
            if ((s16)func_80160658(action, motion, sprite, 0) == 0) {
                return;
            }
            entity->unk_46 |= 0x4000;
            if (!(entity->unk_46 & 0x8000)) {
                func_8015FB68(action, motion, sprite, entity);
                return;
            }
        }

        switch (entity->unk_46 & 0x3FFF) {
        case 8:
        case 9:
        {
            u32 case_flags;
            if ((entity->unk_46 & 0x3FFF) == 9) {
                case_flags = action->flags | 0x8000;
            } else {
                case_flags = action->flags & 0x7FFF;
            }
            action->flags = case_flags;
        }
            if ((s16)func_80160314(action, motion, sprite, entity) != 0) {
                return;
            }
            func_80160514(action, motion, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            s16 facing_angle;
            void *player;

            facing_angle = get_rounded_facing_and_rounding_flag(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tileX, D_80082E80.tileY,
                &facing_aux);
            player = D_800814A8[0];
            entity->facing = facing_angle;
            if (((EntityRec *)player)->unk_9A == 0x11) {
                begin_actor_spell_action(action, motion, sprite, D_80163290, update_actor_action_sequence_and_recovery);
                return;
            }
        }
        case 12:
            update_actor_status_and_food(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(action, motion, sprite, D_80163290, update_actor_action_sequence_and_recovery);
            return;

        case 4:
        case 10:
        case 11:
        default:
            func_8015FB68(action, motion, sprite, entity);
            return;
        }
    }

    {
        u32 final_flags =
            entity->flags1C;
        if (!(final_flags & 0x2000)) {
            if ((tile_index < 0) || !(D_800E2970[tile_index].flags & 2)) {
                u32 final_mask =
                    final_flags & 0x430;
                if (!final_mask) {

                    if ((s16)compare_monster_neighbor_values(
                            sprite->position.tile.x, sprite->position.tile.y,
                            D_80082E80.tileX, D_80082E80.tileY) != 0) {
                        entity->facing = get_rounded_facing_and_rounding_flag(
                            sprite->position.tile.x, sprite->position.tile.y,
                            D_80082E80.tileX, D_80082E80.tileY,
                            &facing_aux);
                    }
                }
            }
        }
    }

    if (!(g_dungeon_status.flags & 0x2000) &&
        !(sprite->flags & 0x40)) {
        current_frames =
            sprite->directionFrames;
        direction_frames = (u8 *)&D_80163258;
        if (current_frames != direction_frames) {
            u32 direction_index;

            sprite->directionFrames = direction_frames;
            direction_index = ((g_game_work.view.viewAngle +
                entity->facing + 0x100) >> 9) & 7;
            /* Keep the integer addition order used by the retail compiler. */
            select_sprite_entry(sprite,
                *(u8 *)((u32)direction_index + (u32)direction_frames),
                0);
        }
    }

    return;
}
