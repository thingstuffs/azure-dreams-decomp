#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

typedef struct S_80174320_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x53];
    s8 unk_9B;
    u8 pad_9C[0x16];
    s16 unk_B2;
} S_80174320_1;   /* obj in advance_boss_command_stream */

typedef struct S_80174320_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80174320_2;   /* ctx in advance_boss_command_stream */

extern void select_sprite_entry(void *, u8, s32);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern void retain_spawn_resource(s16 entry_type, s16 entry_key);
extern void update_actor_status_and_mp(void *);
extern void advance_boss_actor_movement_state(void *, void *, void *, void *);
extern void create_linked_facing_sprite(u8, u8, s16);
extern void create_boss_offset_effect(void);
extern void update_boss_timed_animation(void *, void *, SpriteFrameState *, void *);

#include "dungeon/monster/ghosh.h"
extern u8 D_80174A9C[];
extern u8 ghosh_command_f8_frames[];
extern u8 ghosh_command_f0_frames[];
extern u8 *ghosh_command_stream;
extern s16 ghosh_command_ticks;

/* Advance the command stream and update the object's direction, animation, and effects. */
s32 advance_boss_command_stream(void *object_arg, void *context_arg, void *entity_arg) {
    s32 audio_param;
    s16 elapsed_ticks;
    s32 command;
    s32 opcode;
    u16 entity_flag;
    u8 command_byte;
    u8 duration;
    u8 *stream;
    void *call_obj;
    void *obj;
    SpriteFrameState *entity;
    register s32 result;
    void *old_anim;
    u8 *anim;
    u8 audio_x;
    u8 audio_y;
    s32 angle;
    u16 obj_flags;

    call_obj = object_arg;
    entity = entity_arg;
    obj = object_arg;
    if (entity->flags & 0x40) {
        return 0;
    }

    stream = ghosh_command_stream;
    if (stream == 0) {
        result = 0;
        return result;
    }

    command_byte = stream[1];
    command = command_byte & 0xFF;
    if (command == 0) {
        ((S_80174320_1 *)obj)->unk_B2 = 0;
        update_actor_status_and_mp(obj);
        return 0;
    }

    duration = stream[0];
    elapsed_ticks = *(u16 *)&ghosh_command_ticks + 1;
    ghosh_command_ticks = elapsed_ticks;
    if ((s32)duration < elapsed_ticks) {
        ghosh_command_stream = stream + 2;
        ghosh_command_ticks = 0;
        ((S_80174320_1 *)obj)->unk_9B = 0;
    }

    angle = command_byte & 7;
    obj_flags = ((S_80174320_1 *)obj)->unk_46;
    angle <<= 9;
    ((S_80174320_1 *)obj)->unk_2A = angle;
    obj_flags |= 0x8000;
    ((S_80174320_1 *)obj)->unk_46 = obj_flags;
    opcode = command & 0xF8;

    switch (opcode) {
    case 8:
        call_obj = obj;
        advance_boss_actor_movement_state(call_obj, context_arg, entity, call_obj);
        result = 0;
        return result;
    case 0xC0:
        ((S_80174320_1 *)obj)->unk_9B = 0;
                        /* fall through */
    case 0xC8:
        update_boss_timed_animation(call_obj, context_arg, entity, obj);
        break;
    case 0x10:
        old_anim = entity->frameTable;
        anim = ghosh_direction_frames;
        if (old_anim != anim) {
            (entity->frameTable) = anim;
            select_sprite_entry(entity,
                *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7) + (u32)anim),
                0);
        }
        break;
    case 0xF8:
        old_anim = entity->frameTable;
        anim = ghosh_command_f8_frames;
        if (old_anim != anim) {
            (entity->frameTable) = anim;
            select_sprite_entry(entity,
                *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7) + (u32)anim),
                0);
        }
        break;
    case 0xF0:
        old_anim = entity->frameTable;
        anim = ghosh_command_f0_frames;
        if (old_anim != anim) {
            (entity->frameTable) = anim;
            select_sprite_entry(entity,
                *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7) + (u32)anim),
                0);
        }
        break;
    case 0xE8:
        old_anim = entity->frameTable;
        anim = D_80174A9C;
        if (old_anim != anim) {
            (entity->frameTable) = anim;
            select_sprite_entry(entity,
                anim[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            create_linked_facing_sprite(entity->tile_x, entity->tile_y,
                ((S_80174320_2 *)context_arg)->unk_0A);
            retain_spawn_resource(0x15, 1);
        }
        break;
    case 0xD8:
        old_anim = entity->frameTable;
        anim = D_80174A9C;
        if (old_anim != anim) {
            (entity->frameTable) = anim;
            select_sprite_entry(entity,
                anim[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            entity->flags |= 0x800;
        }
        break;
    case 0xD0:
        entity_flag = entity->flags & 0x800;
        entity->flags = entity_flag;
        if (entity_flag != 0) {
            entity->flags = 0;
        }
        break;
    case 0xE0:
        anim = ghosh_direction_frames + 0x50;
        if (*(u8 **)&entity->frameTable != anim) {
            (entity->frameTable) = anim;
            select_sprite_entry(entity,
                anim[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174320_1 *)obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            create_boss_offset_effect();
            audio_x = entity->tile_x;
            audio_y = entity->tile_y;
            audio_param = 0x3000;
            if (((S_80174320_1 *)obj)->unk_1C & 0x2000) {
                audio_param = 0x300;
            }
            update_map_cell_flags_with_item_limit(audio_x, audio_y, audio_param);
        }
        break;
    }
    update_actor_status_and_mp(obj);
    return 0;
}
