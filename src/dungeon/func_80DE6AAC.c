#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

s32 create_directional_effect_object(E_801742AC_S_80DE6AAC_2 *source, void *initial_position, E_801742AC_S_80DE6AAC_4 *tile_origin) {
    SpriteFrameState *sprite;
    E_801742AC_S_80DE6AAC_5 *position;
    E_801742AC_S_80DE6AAC_1 *effect_state;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_state = effect + 0x20;
        ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_10 = advance_effect_record_counters;
        ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_20 = 0;
        effect_state->unk_02 = (s16)(((u16)source->unk_2A >> 9) & 7);
        sprite = ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_0C;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->clut = 0x7E40;
        sprite->flags = (u16)(sprite->flags | 0x100);
        func_8003DB94(sprite, &D_800DEEC0, 0);
        func_800478B8(sprite);
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        register_node(effect, project_sprite_chain);
        position = ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_08;
        *(E_801742AC_Copy24 *)position = *(E_801742AC_Copy24 *)initial_position;
        {
            s32 world_y;
            s32 direction_offset;
            s32 height_limit;
            s32 world_x;

            direction_offset = effect_state->unk_02 * 2;
            world_x = (s32)((tile_origin->unk_24 + *(u16 *)((u8 *)dir_step_x + direction_offset)) << 0x10) >> 0xA;
            world_y = (s32)((tile_origin->unk_25 + *(u16 *)((u8 *)dir_step_y + direction_offset)) << 0x10) >> 0xA;
            position->unk_02 = (s16)(world_x + 0x20);
            position->unk_06 = (s16)(world_y + 0x20);
            height_limit = sample_terrain_surface_height(world_x & 0xFFC0, world_y & 0xFFC0, (s16)(source->unk_88 - 0x20)) << 0x10;
            if (height_limit < position->unk_08) {
                position->unk_08 = height_limit;
            }
        }
        return (s32)effect;
    }
    return 0;
}

/* MECHANISM: A typed 24-byte assignment restores the packed lw/sw copy and natural seven-register
   frame. An unsigned color byte plus a post-copy schedule seam fixes the immediate and held table-base
   order. The moved shape selects 2.7.2-cdk-G0. */
