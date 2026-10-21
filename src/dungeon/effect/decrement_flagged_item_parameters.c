#include "dungeon/effect/decrement_flagged_item_parameters.h"

void (*const dungeon_1966800_entry)(void *, void *) = decrement_flagged_item_parameters;
#include "dungeon/effect/decrement_flagged_item_parameters.h"
#include "shared/sprite_frame_state.h"

void decrement_flagged_item_parameters(void *action, void *saved_position)
{
    void *owner_work;
    ObjectNodeHeader *owner;
    ObjectNodeHeader *effect;
    SpriteFrameState *effect_part;
    SpriteFrameState *offset_part;
    SpriteFrameState *source_part;
    void *position;
    ActorRecord *shared_data;
    u8 *effect_work;
    DungeonGlobalStatus *shared_state;
    s16 offsets[3];
    s32 state;
    s32 timer;
    u16 action_flags;
    s32 event_code;
    s32 color_index;
    u8 *colors;
    timer = (*((u16 *) (((u8 *) action) + 0x50))) - 1;
    owner_work = *((void **) (((u8 *) action) + 0));
    state = *((s16 *) (((u8 *) action) + 0xA));
    owner = (ObjectNodeHeader *) (((u8 *) owner_work) - 0x20);
    *((u16 *) (((u8 *) action) + 0x50)) = timer;
    switch (state) {
    case 0:
        *((s32 *) (((u8 *) primary_actor_record) + 0xF4)) = 0;

        *((s32 *) (((u8 *) saved_position) + 0)) = *((s32 *) (((u8 *) owner->unk_08) + 0));
        *((s32 *) (((u8 *) saved_position) + 4)) = *((s32 *) (((u8 *) owner->unk_08) + 4));
        *((s32 *) (((u8 *) saved_position) + 8)) = *((s32 *) (((u8 *) owner->unk_08) + 8));
        (*((u16 *) (((u8 *) action) + 0xA)))++;
    case 1:
        if (((*((u16 *) (((u8 *) (*((void **) (((u8 *) action) + 4)))) + 0))) & 0x80) == 0) {
            return;
        }

        shared_data = primary_actor_record;
        *((u16 *) (((u8 *) action) + 0x50)) = 10;
        (*((u16 *) (((u8 *) shared_data) + 0xA6)))--;
        *((u8 *) (((u8 *) shared_data) + 0xA8)) = *((u8 *) (((u8 *) action) + 8));
        effect = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
        if (effect != 0) {
            offset_part = owner->unk_0C;
            if (resolve_record_orientation_or_fallback(*(s32 *)&offset_part->source, offset_part, offsets, 0) == 0) {
                offsets[2] = 0;
                offsets[1] = 0;
                offsets[0] = 0;
            }
            effect->unk_10 = &D_80024374;
            *((void **) (((u8 *) effect) + 0x20)) = action;
            register_node(effect, project_sprite_chain);
            source_part = ((ObjectNodeHeader *) owner_work)[-1].unk_0C;
            effect_part = effect->unk_0C;
            effect_part->unk_28 = source_part->unk_28;
            effect_part->flags = source_part->flags & 0x97FF;
            colors = source_part->frameTable;
            effect_part->frameTable = colors;
            color_index = ((g_game_work.view.camera_rotation.parts.viewAngle + (*((s16 *) (((u8 *) owner_work) + 0x2A)))) + 0x100) >> 9;
            colors += color_index & 7;
            select_sprite_entry(effect_part, *colors, 0);
            effect_part->scale_y = ONE;
            effect_part->scale_x = ONE;
            effect_part->color.word = 0x80FF;
            effect_work = ((u8 *) effect) + 0x20;
            effect_part->tpage_abr = 0x20;
            effect_part->clut -= 0x80;
            effect_part->flags |= 0xC;
            position = owner->unk_08;
            *((s32 *) (((u8 *) effect_work) + 0x1C)) = (*((s32 *) (((u8 *) position) + 0))) + (offsets[0] << 16);
            position = owner->unk_08;
            *((s32 *) (((u8 *) effect_work) + 0x20)) = (*((s32 *) (((u8 *) position) + 4))) + (offsets[1] << 16);
            position = owner->unk_08;
            *((s32 *) (((u8 *) effect_work) + 0x24)) = (*((s32 *) (((u8 *) position) + 8))) + (offsets[2] << 16);
            {
                void *owner_position;
                void *effect_position;
                u16 coord_integer;
                owner_position = owner->unk_08;
                effect_position = effect->unk_08;
                coord_integer = *((u16 *) (((u8 *) owner_position) + 2));
                *((u16 *) (((u8 *) effect_work) + 0xC)) = coord_integer;
                *((u16 *) (((u8 *) effect_position) + 2)) = coord_integer;
                owner_position = owner->unk_08;
                effect_position = effect->unk_08;
                coord_integer = *((u16 *) (((u8 *) owner_position) + 6));
                *((u16 *) (((u8 *) effect_work) + 0xE)) = coord_integer;
                *((u16 *) (((u8 *) effect_position) + 6)) = coord_integer;
                owner_position = owner->unk_08;
                effect_position = effect->unk_08;
                coord_integer = *((u16 *) (((u8 *) owner_position) + 0xA));
                *((u16 *) (((u8 *) effect_work) + 0x10)) = coord_integer;
                *((u16 *) (((u8 *) effect_position) + 0xA)) = coord_integer;
            }
            if (func_80053EF0(4) != 2) {
                event_code = 0x300;
            }
            else {
                event_code = 0x4300;
            }
            play_sound_if_enabled(event_code);
        }
        (*((u16 *) (((u8 *) action) + 0xA)))++;
        return;
    case 2:
        if (((s32) (timer << 16)) > 0) {
            return;
        }

        *((u16 *) (((u8 *) action) + 0x50)) = 8;
        (*((u16 *) (((u8 *) action) + 0xA)))++;
        return;
    case 3:
        if (((reference_tile_object.sprite_flags & 0x8000) == 0) && (((s32) (timer << 16)) >= 0)) {
            return;
        }

        action_flags = *((u16 *) (((u8 *) action) + 0x52));
        if ((*((s16 *) (((u8 *) action) + 0x52))) & 0x8000) {
            *((u16 *) (((u8 *) action) + 0x52)) = action_flags & 0x7FFF;
            return;
        }
        shared_state = &g_dungeon_status;
        *((s32 *) (((u8 *) shared_state) + 0xC)) = 0;
        (*((u16 *) (((u8 *) shared_state) + 0xA)))--;
        *((u16 *) (((u8 *) action) + (-2))) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
