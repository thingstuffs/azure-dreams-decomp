#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct PairAction {
    u8 pad_00[0x8C];
    s32 *handler;
    union {
        s32 word;
        struct {
            u8 pad_90[2];
            u16 integer;
        } parts;
    } heightOffset;
    u8 pad_94[2];
    s16 ticks;
    u16 flags;
    u8 pad_9A[1];
    u8 phase;
    u8 pad_9C[0xC];
    void *partner;
    s32 savedHandler;
} PairAction;
typedef struct PartnerState {
    u8 pad_00[0x13];
    u8 heightClass;
    u8 pad_14[8];
    s32 flags;
    u8 pad_20[0x68];
    u16 groundHeight;
} PartnerState;
typedef struct CreatureState {
    u8 pad_00[0x1C];
    s32 flags;
    u8 pad_20[0xA];
    u16 facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x25];
    s8 actionsLeft;
    u8 pad_6E[0x1A];
    s16 groundHeight;
} CreatureState;
typedef struct ActorSprite {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    u8 tileX;
    u8 tileY;
    s8 room;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSprite;
typedef struct ActorMotion {
    s32 x;
    s32 y;
    union {
        s32 word;
        struct {
            u8 pad_08[2];
            u16 integer;
        } parts;
    } z;
    s32 dx;
    s32 dy;
    s32 dz;
} ActorMotion;
typedef struct ObjectHeaderTail {
    void *motion;
    void *sprite;
} ObjectHeaderTail;
typedef struct AnimationFrame {
    u8 frame;
} AnimationFrame;
typedef struct DirectionStep {
    s16 step;
} DirectionStep;
typedef struct PartnerAction {
    u8 pad_00[0x8C];
    s32 handler;
    union {
        s32 word;
        struct {
            u8 pad_90[2];
            u16 integer;
        } parts;
    } heightOffset;
    u8 pad_94[4];
    u16 flags;
} PartnerAction;
typedef struct SignedHeight {
    u8 pad_00[0xA];
    s16 integer;
} SignedHeight;

#include "engine/graphics/select_sprite_entry_api.h"
void cycle_map_cell_flags(s16, s16, u16);
s32 func_8009A2B8(s16, s16, s32);
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"
#include "dungeon/actor/state/advance_status_timers_api.h"
s32 select_dungeon_spawn_tile(u8 *, u8 *);
s32 play_sound_if_enabled();
void refresh_actor_proximity_state(u8 *);
struct S_800AD594_0; void reduce_actor_food_meter(struct S_800AD594_0 *, s32);
s16 sample_terrain_surface_height();
extern s16 D_8008146E;
extern s32 D_8016B058;
extern u8 D_8016E888[];
extern u8 D_8016E8F0[];
extern u8 D_8016E8F8[];

/* Updates paired actor movement, tile placement, animations, and restored flags. */
void restore_bank_actor_callback(PairAction *actor, ActorMotion *motion, ActorSprite *sprite, void *entity) {
    ActorMotion *partner_motion;
    s16 saved_x;
    s16 saved_y;
    s32 partner_tile_mask;
    s32 tile_mask;
    s32 restore_tile_mask;
    s32 restore_partner_mask;
    s16 launch_ticks;
    s16 fall_ticks;
    s32 tile_type;
    s16 landing_height;
    s16 rise_ticks;
    s16 return_ticks;
    s32 step_offset;
    s32 direction;
    s32 tile_blocked;
    s32 reverse_angle;
    s32 attempts;
    u16 partner_height;
    u32 state;
    u32 angle;
    u32 partner_flags;
    u32 entity_flags;
    u32 actor_flags;
    u32 cleared_flags;
    u32 sprite_grounded;
    u32 partner_x;
    u32 partner_y;
    u32 sprite_x;
    u32 sprite_y;
    s32 launch_duration;
    s32 x_velocity;
    s32 y_velocity;
    u8 *x_step_table;
    u8 *y_step_table;
    s16 *y_step_ptr;
    u32 final_x;
    u32 final_y;
    void *reset_entity;
    void *finish_entity;
    u32 saved_handler;
    s32 *next_handler;
    u32 active_count;
    u32 height_value;
    u32 height_offset;
    s32 entity_height;
    u32 height_adjust;
    s32 world_coord;
    u8 *anim_table0;
    u8 *anim_table1;
    u8 *anim_table2;
    u8 *anim_table3;
    u32 launch_anim;
    u32 fall_anim;
    u32 rise_anim;
    u32 idle_anim;
    s16 *angle_or_count;
    void *tile_x_ptr;
    ActorSprite *partner_sprite;
    PartnerState *partner;
    PartnerAction *partner_actor;

    partner = actor->partner;
    state = actor->phase;
    partner_actor = (PartnerAction *) partner;
    partner_motion = ((ObjectHeaderTail *) ((u8 *) partner - 0x18))->motion;
    partner_sprite = ((ObjectHeaderTail *) ((u8 *) partner - 0x18))->sprite;
    switch (state) {
    case 0:
        actor->savedHandler = (s32) partner_actor->handler;
        if (partner->flags & 0x40000) {
            actor->flags = (u16) (actor->flags | 0x1000);
        } else {
            actor->flags = (u16) (actor->flags & 0xEFFF);
        }
        if (partner_actor->flags & 8) {
            actor->flags = (u16) (actor->flags | 0x4000);
        } else {
            actor->flags = (u16) (actor->flags & 0xBFFF);
        }
        if (partner_actor->flags & 4) {
            actor->flags = (u16) (actor->flags | 0x2000);
            partner_actor->handler = 0;
            partner_flags = partner->flags;
            partner_sprite = ((ObjectHeaderTail *) ((u8 *) partner - 0x18))->sprite;
        } else {
            actor->flags = (u16) (actor->flags & 0xDFFF);
            partner_actor->handler = 0;
            partner_flags = partner->flags;
            partner_sprite = ((ObjectHeaderTail *) ((u8 *) partner - 0x18))->sprite;
        }
        partner_flags &= 0x2000;
        partner_x = partner_sprite->tileX;
        partner_y = partner_sprite->tileY;
        partner_tile_mask = 0x3000;
        if (partner_flags) {
            partner_tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(partner_x, partner_y, partner_tile_mask);
        sprite_x = sprite->tileX;
        entity_flags = ((CreatureState *)entity)->flags;
        entity_flags &= 0x2000;
        tile_mask = 0x3000;
        sprite_y = sprite->tileY;
        if (entity_flags) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(sprite_x, sprite_y, tile_mask);
        angle = 0xFFFB0000;
        cleared_flags = ((CreatureState *)entity)->flags;
        angle |= 0xFFFF;
        cleared_flags &= angle;
        ((CreatureState *)entity)->flags = cleared_flags;
        actor_flags = (actor->flags);
        angle = ((CreatureState *)entity)->facing;
        actor_flags |= 0xC;
        angle >>= 9;
        actor->flags = actor_flags;
        sprite_grounded = sprite->flags;
        sprite_grounded &= 0x8000;
        direction = angle & 7;
        if (!sprite_grounded) {
            actor->ticks = 0xC;
        } else if (!(partner_sprite->flags & 0x8000)) {
            actor->ticks = 0xC;
        } else {
            actor->ticks = 0;
            actor->phase = 2;
            return;
        }
        x_step_table = ((u8 *)dir_step_x);
        step_offset = direction * 2;
        x_step_table = (u8 *) (step_offset + (u32) x_step_table);
        x_velocity = * (s16 *) x_step_table;
        launch_duration = 0xC;
        x_velocity <<= 0x16;
        x_velocity = x_velocity / launch_duration;
        motion->dx = x_velocity;
        y_step_table = ((u8 *)dir_step_y);
        y_step_ptr = (s16 *) (step_offset + (u32) y_step_table);
        y_velocity = *y_step_ptr;
        y_velocity <<= 0x16;
        y_velocity = y_velocity / (s16) actor->ticks;
        motion->dz = 0;
        motion->dy = y_velocity;
        partner->flags = (s32) (partner->flags & 0xFFFBFFFF);
        partner_actor->flags = (u16) (partner_actor->flags | 0xC);
        anim_table0 = D_8016E8F0;
        angle_or_count = &g_game_work.view.viewAngle;
        sprite->directionFrames = anim_table0;
        launch_anim = ((s32) (*angle_or_count + (s16) ((CreatureState *)entity)->facing + 0x100) >> 9) & 7;
        launch_anim = launch_anim + (u32) anim_table0;
        select_sprite_entry((struct S_80047784 *)(sprite), ((AnimationFrame *) launch_anim)->frame, 0);
        actor->phase = (u8) (actor->phase + 1);
    case 1:
        launch_ticks = (u16) actor->ticks - 1;
        actor->ticks = launch_ticks;
        if (launch_ticks == 8) {
            height_offset = D_800DDC40[partner->heightClass];
            height_value = ((SignedHeight *) partner_motion)->integer;
            entity_height = (s16)((CreatureState *)entity)->groundHeight;
            motion->dz = (s32) ((s32) ((((height_value - entity_height) - height_offset) + 0x10)
                << 0x10) / launch_ticks);
            partner_actor->heightOffset.parts.integer = (u16) (partner_actor->heightOffset.parts.integer + partner->groundHeight);
            partner->groundHeight = 0U;
        }
        if (actor->ticks > 0) {
            return;
        }
        motion->dy = 0;
        motion->dx = 0;
        motion->dz = -0x40000;
        play_sound_if_enabled(0x802);
        {
            fall_anim = 0x10;
            anim_table1 = D_8016E8F8;
            actor->ticks = fall_anim;
        }
        angle_or_count = &g_game_work.view.viewAngle;
        sprite->directionFrames = anim_table1;
        fall_anim = ((s32) (*angle_or_count + (s16) ((CreatureState *)entity)->facing + 0x100) >> 9) & 7;
        fall_anim = fall_anim + (u32) anim_table1;
        select_sprite_entry((struct S_80047784 *)(sprite), ((AnimationFrame *) fall_anim)->frame, 0);
        actor->phase = actor->phase + 1;
        return;
    case 2:
        motion->dz = (s32) (motion->dz + 0xFFFE0000);
        height_adjust = D_800DDC40[partner->heightClass];
        partner_actor->heightOffset.parts.integer = (u16) ((motion->z.parts.integer + height_adjust) - 0x10);
        fall_ticks = (u16) actor->ticks - 1;
        actor->ticks = fall_ticks;
        if ((fall_ticks << 0x10) > 0) {
            if (!(partner_sprite->flags & 0x8000)) {
                return;
            }
        }
        saved_x = partner_sprite->tileX;
        attempts = 0x40;
        reverse_angle = (s16) ((CreatureState *)entity)->facing;
        saved_y = partner_sprite->tileY;
        reverse_angle = (reverse_angle + 0x800) & 0xFFF;
        direction = reverse_angle >> 9;
        /* Search up to 63 alternative tile pairs, then restore the original tile. */
        for (;;) {
            attempts -= 1;
            tile_x_ptr = &partner_sprite->tileX;
            if (attempts <= 0) {
                partner_sprite->tileX = saved_x;
                partner_sprite->tileY = saved_y;
                goto commit_tile_positions;
            }
            tile_type = (s16) select_dungeon_spawn_tile(tile_x_ptr, &partner_sprite->tileY);
            if (tile_type < 0) {
                continue;
            }
            if (tile_type == D_80082E80.unk_026) {
                angle_or_count = &D_8008146E;
                if (*angle_or_count >= 2) {
                    continue;
                }
            }
            tile_blocked = func_8009A2B8(partner_sprite->tileX, partner_sprite->tileY, direction);
            if ((tile_blocked << 0x10) != 0) {
                continue;
            }
            partner_sprite->room = (s8) tile_type;
            sprite->room = (s8) tile_type;
            sprite->tileX = partner_sprite->tileX + dir_step_x[direction];
            sprite->tileY = partner_sprite->tileY + dir_step_y[direction];
            landing_height = sample_terrain_surface_height((sprite->tileX << 6) | 0x20, (sprite->tileY << 6) | 0x20,
                (s16) (motion->z.parts.integer - 0x80));
            ((CreatureState *)entity)->groundHeight = landing_height;
            if (landing_height >= 0x201) {
                continue;
            }
            partner_height = sample_terrain_surface_height((partner_sprite->tileX << 6) | 0x20, (partner_sprite->tileY << 6) | 0x20,
                (s16) (motion->z.parts.integer - 0x80));
            partner->groundHeight = partner_height;
            if ((s16) partner_height >= 0x201) {
                continue;
            }
            if (((CreatureState *)entity)->groundHeight == (s16) partner_height) {
                break;
            }
        }
commit_tile_positions:
        world_coord = partner_sprite->tileX;
        world_coord = ((world_coord << 6) + 0x20) << 0x10;
        partner_motion->x = world_coord;
        motion->x = world_coord;
        world_coord = partner_sprite->tileY;
        world_coord = ((world_coord << 6) + 0x20) << 0x10;
        partner_motion->y = world_coord;
        motion->y = world_coord;
        motion->z.word = (s32) (((s16) partner->groundHeight - 0x100) << 0x10);
        partner_actor->heightOffset.word = (s32) actor->heightOffset.word;
        actor->ticks = 8;
        motion->dz = (s32) ((s32) ((((CreatureState *)entity)->groundHeight << 0x10)
            - motion->z.word) / (s16) actor->ticks);
        anim_table2 = D_8016E8F8;
        angle_or_count = &g_game_work.view.viewAngle;
        *(u8 **)((u8 *)sprite + (u32)&((ActorSprite *)0)->directionFrames) = anim_table2;
        rise_anim = ((s32) (*angle_or_count + (s16) ((CreatureState *)entity)->facing + 0x100) >> 9) & 7;
        rise_anim = rise_anim + (u32) anim_table2;
        select_sprite_entry((struct S_80047784 *)(sprite), ((AnimationFrame *) rise_anim)->frame, 0);
        refresh_actor_proximity_state(entity);
        refresh_actor_proximity_state((u8 *)(partner));
        actor->phase = actor->phase + 1;
        return;
    case 3:
        partner_actor->heightOffset.parts.integer = (u16) (actor->heightOffset.parts.integer + 0x40);
        if ((s16) actor->heightOffset.parts.integer < 0) {
            rise_ticks = (u16) actor->ticks - 1;
            actor->ticks = rise_ticks;
            if ((rise_ticks << 0x10) > 0) {
                return;
            }
            if (!(sprite->flags & 0x8000)) {
                return;
            }
        }
        actor->heightOffset.word = 0;
        partner_actor->heightOffset.word = 0;
        if (actor->flags & 0x1000) {
            partner->flags = (s32) (partner->flags | 0x40000);
        }
        if (!(actor->flags & 0x4000)) {
            partner_actor->flags = (u16) (partner_actor->flags & 0xFFF7);
        }
        if (!(actor->flags & 0x2000)) {
            partner_actor->flags = (u16) (partner_actor->flags & 0xFFFB);
        }
        ((CreatureState *)entity)->flags = (s32) (((CreatureState *)entity)->flags | 0x40000000);
        partner->flags = (s32) (partner->flags | 0x40000000);
        {
            s16 angle_or_duration;
            s32 return_step_offset;

            angle_or_duration = ((CreatureState *)entity)->facing;
            motion->dz = 0;
            actor->ticks = 8;
            direction = angle_or_duration >> 8;
            return_step_offset = direction & 0xE;
            angle_or_duration = 8;
            motion->dx = -(((DirectionStep *)((u8 *)dir_step_x + return_step_offset))->step << 0x16) / angle_or_duration;
            motion->dy = -(((DirectionStep *)((u8 *)dir_step_y + return_step_offset))->step << 0x16) / actor->ticks;
            partner_motion->dz = 0;
            motion->dz = 0;
            actor->phase = actor->phase + 1;
            return;
        }
    case 4:
        return_ticks = (u16) actor->ticks - 1;
        actor->ticks = return_ticks;
        if ((return_ticks << 0x10) > 0) {
            if (!(partner_sprite->flags & 0x8000)) {
                return;
            }
        }
        final_x = sprite->tileX;
        final_x = ((final_x << 6) + 0x20) << 0x10;
        motion->x = final_x;
        final_y = sprite->tileY;
        reset_entity = entity;
        motion->dy = 0;
        motion->dx = 0;
        final_y = ((final_y << 6) + 0x20) << 0x10;
        motion->y = final_y;
        saved_handler = actor->savedHandler;
        partner_actor->handler = saved_handler;
        reduce_actor_food_meter(reset_entity, 0x100);
        next_handler = &D_8016B058;
        actor->handler = next_handler;
        active_count = ((u16)g_dungeon_status.unk_0A);
        finish_entity = entity;
        active_count -= 1;
        g_dungeon_status.unk_0A = active_count;
        advance_status_timers(finish_entity);
        actor->flags = (u16) (actor->flags & 0xFFF3);

        {
            u32 restore_flags;
            u32 restore_mask;
            u32 restore_x;
            u32 restore_y;

            restore_flags = ((CreatureState *)entity)->flags;
            restore_mask = 0x40000;
            restore_flags |= restore_mask;
            ((CreatureState *)entity)->flags = restore_flags;
            restore_flags &= 0x2000;
            restore_x = sprite->tileX;
            restore_y = sprite->tileY;
            restore_tile_mask = 0x3000;
            if (restore_flags) {
                restore_tile_mask = 0x300;
            }
            cycle_map_cell_flags(restore_x, restore_y, restore_tile_mask);
        }
        {
            u32 restore_flags;
            u32 restore_x;
            u32 restore_y;

            restore_flags = partner->flags;
            restore_x = partner_sprite->tileX;
            restore_y = partner_sprite->tileY;
            restore_flags &= 0x2000;
            restore_partner_mask = 0x3000;
            if (restore_flags) {
                restore_partner_mask = 0x300;
            }
            cycle_map_cell_flags(restore_x, restore_y, restore_partner_mask);
        }
        anim_table3 = D_8016E888;
        angle_or_count = &g_game_work.view.viewAngle;
        sprite->directionFrames = anim_table3;
        idle_anim = ((s32) (*angle_or_count + (s16) ((CreatureState *)entity)->facing + 0x100) >> 9) & 7;
        idle_anim = idle_anim + (u32) anim_table3;
        select_sprite_entry((struct S_80047784 *)(sprite), ((AnimationFrame *) idle_anim)->frame, 0);
        ((CreatureState *)entity)->actionsLeft = 0;
        ((CreatureState *)entity)->action = (u16) (((CreatureState *)entity)->action & 0x7FFF);
        actor->phase = actor->phase + 1;
    default:
        return;
    }
}
