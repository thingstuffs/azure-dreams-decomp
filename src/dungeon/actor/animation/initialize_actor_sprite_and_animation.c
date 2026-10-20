#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"

extern void select_sprite_entry();
extern s32 func_80047D44();
extern void load_and_upload_sprite_resource();
extern void bind_sprite_resource_slot_record();
extern void clear_entry_flag_and_link_owner();
extern void cycle_map_cell_flags();
extern s32 find_active_rect_containing_point();
extern void set_record_integer_tile_center();
extern void copy_indexed_entry_data();
extern void create_tracked_effect();
extern s32 sample_terrain_surface_height();

extern s32 D_80081488[];
extern s8 D_800DCF4D[];

/* Initialize an entity sprite, its position, and direction-dependent display flags. */
void initialize_actor_sprite_and_animation(void *entity, void *position, void *sprite, s32 init_flags)
{
    s32 extra_flags;
    s32 mode;
    s32 entity_kind;
    u8 *entity_data;

    entity_data = (u8 *)entity + 0x20;
    extra_flags = init_flags & ~3;
    mode = init_flags & 3;

    if (mode == 2) {
        if ((extra_flags << 16) == 0) {
            *(s32 *)((u8 *)sprite + 0x28) =
                func_80047D44(*(u8 *)(entity_data + 0x13));
        } else {
            *(s32 *)((u8 *)sprite + 0x28) = D_80081488[0];
        }
        D_800DCF4D[0] = -1;
    } else {
        if (*(u8 *)(entity_data + 0x13) != 0x38) {
            load_and_upload_sprite_resource(*(u8 *)(entity_data + 0x13));
        }
        entity_kind = *(u8 *)(entity_data + 0x13);
        bind_sprite_resource_slot_record(entity, entity_kind);
    }

    *(s8 *)((u8 *)sprite + 0x26) =
        find_active_rect_containing_point(*(u8 *)((u8 *)sprite + 0x24),
                      *(u8 *)((u8 *)sprite + 0x25));
    set_record_integer_tile_center(position,
                  *(u8 *)((u8 *)sprite + 0x24),
                  *(u8 *)((u8 *)sprite + 0x25));

    *(s16 *)(entity_data + 0x88) =
        sample_terrain_surface_height(*(u16 *)((u8 *)position + 2),
                      *(u16 *)((u8 *)position + 6),
                      (s16)(*(u16 *)((u8 *)position + 0xA) - 0x20));

    *(s16 *)((u8 *)sprite + 0x1E) = 0x1000;
    *(s16 *)((u8 *)sprite + 0x1C) = 0x1000;
    *(s32 *)((u8 *)sprite + 0xC) = 0x2C808080;
    *(u16 *)((u8 *)sprite + 0x14) |= 0x8000;

    select_sprite_entry(sprite,
                  (*(u8 **)((u8 *)sprite + 0x2C))[
                      ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(entity_data + 0x2A) + 0x100) >> 9) & 7],
                  0);

    clear_entry_flag_and_link_owner(entity);
    if ((*(s32 *)(entity_data + 0x14) & 0x4000) == 0) {
        copy_indexed_entry_data(entity_data);
    }

    cycle_map_cell_flags(*(u8 *)((u8 *)sprite + 0x24),
                  *(u8 *)((u8 *)sprite + 0x25),
                  (*(s32 *)(entity_data + 0x1C) & 0x2000) ? 0x300 : 0x3000);

    *(s8 *)(entity_data + 0x71) = 0;
    *(s32 *)(entity_data + 0x1C) |= 0x40000000;
    create_tracked_effect(entity, 0, (u8 *)sprite + 0x2C, entity_data + 0x2A);

    if (dir_sprite_flag[
            ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(entity_data + 0x2A) + 0x100) >> 9) & 7] != 0) {
        *(u16 *)((u8 *)sprite + 0x14) |= 1;
        return;
    }
    *(u16 *)((u8 *)sprite + 0x14) &= 0xFFFE;
}
