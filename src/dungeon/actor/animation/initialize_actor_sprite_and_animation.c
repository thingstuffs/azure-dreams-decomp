#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/level.h"
#include "engine/graphics.h"

struct ObjectNodeHeader;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "dungeon/player/object.h"
#include "dungeon/effect/screen.h"

struct Source_827C;

extern s32 load_and_publish_texture_resource_pair(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern struct Source_827C * bind_sprite_resource_slot_record(struct Source_827C *source, short entry_id);
extern s32 find_active_rect_containing_point(s32 point_x, s32 point_y);

extern s32 loaded_entity_sprite_resource[];
extern s8 spell_effect_selector_cache[];

/* Initialize an entity sprite, its position, and direction-dependent display flags. */
void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags)
{
    s32 extra_flags;
    s32 mode;
    s32 entity_kind;
    ActorRecord *entity_data;

    entity_data = (ActorRecord *)((ObjectNodeHeader *)entity + 1);
    extra_flags = init_flags & ~3;
    mode = init_flags & 3;

    if (mode == 2) {
        if ((extra_flags << 16) == 0) {
            sprite->animation_resource =
                load_and_publish_texture_resource_pair(entity_data->species);
        } else {
            sprite->animation_resource = loaded_entity_sprite_resource[0];
        }
        spell_effect_selector_cache[0] = -1;
    } else {
        if (entity_data->species != 0x38) {
            load_and_upload_sprite_resource(entity_data->species);
        }
        entity_kind = entity_data->species;
        bind_sprite_resource_slot_record(entity, entity_kind);
    }

    sprite->room_index =
        find_active_rect_containing_point(sprite->tile_x,
                      sprite->tile_y);
    set_record_integer_tile_center(position,
                  sprite->tile_x,
                  sprite->tile_y);

    entity_data->ground_height =
        sample_terrain_surface_height(*(u16 *)((u8 *)position + 2),
                      *(u16 *)((u8 *)position + 6),
                      (s16)(*(u16 *)((u8 *)position + 0xA) - 0x20));

    sprite->scale_y = 0x1000;
    sprite->scale_x = 0x1000;
    sprite->color.word = 0x2C808080;
    sprite->flags |= 0x8000;

    select_sprite_entry(sprite,
                  (*(u8 **)&sprite->frameTable)[
                      ((g_game_work.view.camera_rotation.parts.viewAngle + entity_data->facing + 0x100) >> 9) & 7],
                  0);

    clear_entry_flag_and_link_owner(entity);
    if ((entity_data->flags14 & 0x4000) == 0) {
        copy_indexed_entry_data(entity_data);
    }

    cycle_map_cell_flags(sprite->tile_x,
                  sprite->tile_y,
                  (entity_data->flags1C & 0x2000) ? 0x300 : 0x3000);

    entity_data->movement_queue_state = 0;
    entity_data->flags1C |= 0x40000000;
    create_tracked_effect(entity, 0, (u8 *)sprite + 0x2C, &entity_data->facing);

    if (dir_sprite_flag[
            ((g_game_work.view.camera_rotation.parts.viewAngle + entity_data->facing + 0x100) >> 9) & 7] != 0) {
        sprite->flags |= 1;
        return;
    }
    sprite->flags &= 0xFFFE;
}
