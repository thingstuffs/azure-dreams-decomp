#include "dungeon/effect/decrement_flagged_item_parameters.h"

void (*const dungeon_1966800_entry)(void *, void *) = decrement_flagged_item_parameters;

void decrement_flagged_item_parameters(void *action, void *saved_position)
{
    void *owner_work;
    u8 *owner;
    void *effect;
    void *effect_part;
    void *offset_part;
    void *source_part;
    void *position;
    EntityRec *shared_data;
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
    owner = ((u8 *) owner_work) - 0x20;
    *((u16 *) (((u8 *) action) + 0x50)) = timer;
    switch (state) {
    case 0:
        *((s32 *) (((u8 *) D_800814A8) + 0xF4)) = 0;

        *((s32 *) (((u8 *) saved_position) + 0)) = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 0));
        *((s32 *) (((u8 *) saved_position) + 4)) = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 4));
        *((s32 *) (((u8 *) saved_position) + 8)) = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 8));
        (*((u16 *) (((u8 *) action) + 0xA)))++;
    case 1:
        if (((*((u16 *) (((u8 *) (*((void **) (((u8 *) action) + 4)))) + 0))) & 0x80) == 0) {
            return;
        }

        shared_data = D_800814A8;
        *((u16 *) (((u8 *) action) + 0x50)) = 10;
        (*((u16 *) (((u8 *) shared_data) + 0xA6)))--;
        *((u8 *) (((u8 *) shared_data) + 0xA8)) = *((u8 *) (((u8 *) action) + 8));
        effect = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
        if (effect != 0) {
            offset_part = *((void **) (((u8 *) owner) + 0xC));
            if (resolve_record_orientation_or_fallback(*((s32 *) (((u8 *) offset_part) + 8)), offset_part, offsets, 0) == 0) {
                offsets[2] = 0;
                offsets[1] = 0;
                offsets[0] = 0;
            }
            *((void **) (((u8 *) effect) + 0x10)) = &D_80024374;
            *((void **) (((u8 *) effect) + 0x20)) = action;
            register_node(effect, project_sprite_chain);
            source_part = *((void **) (((u8 *) owner_work) + (-0x14)));
            effect_part = *((void **) (((u8 *) effect) + 0xC));
            *((s32 *) (((u8 *) effect_part) + 0x28)) = *((s32 *) (((u8 *) source_part) + 0x28));
            *((u16 *) (((u8 *) effect_part) + 0x14)) = (*((u16 *) (((u8 *) source_part) + 0x14))) & 0x97FF;
            colors = *((u8 **) (((u8 *) source_part) + 0x2C));
            *((u8 **) (((u8 *) effect_part) + 0x2C)) = colors;
            color_index = ((g_game_work.view.viewAngle + (*((s16 *) (((u8 *) owner_work) + 0x2A)))) + 0x100) >> 9;
            colors += color_index & 7;
            select_sprite_entry(effect_part, *colors, 0);
            *((s16 *) (((u8 *) effect_part) + 0x1E)) = 0x1000;
            *((s16 *) (((u8 *) effect_part) + 0x1C)) = 0x1000;
            *((s32 *) (((u8 *) effect_part) + 0xC)) = 0x80FF;
            effect_work = ((u8 *) effect) + 0x20;
            *((s16 *) (((u8 *) effect_part) + 0x10)) = 0x20;
            *((u16 *) (((u8 *) effect_part) + 0x12)) -= 0x80;
            *((u16 *) (((u8 *) effect_part) + 0x14)) |= 0xC;
            position = *((void **) (((u8 *) owner) + 8));
            *((s32 *) (((u8 *) effect_work) + 0x1C)) = (*((s32 *) (((u8 *) position) + 0))) + (offsets[0] << 16);
            position = *((void **) (((u8 *) owner) + 8));
            *((s32 *) (((u8 *) effect_work) + 0x20)) = (*((s32 *) (((u8 *) position) + 4))) + (offsets[1] << 16);
            position = *((void **) (((u8 *) owner) + 8));
            *((s32 *) (((u8 *) effect_work) + 0x24)) = (*((s32 *) (((u8 *) position) + 8))) + (offsets[2] << 16);
            {
                void *owner_position;
                void *effect_position;
                u16 coord_integer;
                owner_position = *((void **) (((u8 *) owner) + 8));
                effect_position = *((void **) (((u8 *) effect) + 8));
                coord_integer = *((u16 *) (((u8 *) owner_position) + 2));
                *((u16 *) (((u8 *) effect_work) + 0xC)) = coord_integer;
                *((u16 *) (((u8 *) effect_position) + 2)) = coord_integer;
                owner_position = *((void **) (((u8 *) owner) + 8));
                effect_position = *((void **) (((u8 *) effect) + 8));
                coord_integer = *((u16 *) (((u8 *) owner_position) + 6));
                *((u16 *) (((u8 *) effect_work) + 0xE)) = coord_integer;
                *((u16 *) (((u8 *) effect_position) + 6)) = coord_integer;
                owner_position = *((void **) (((u8 *) owner) + 8));
                effect_position = *((void **) (((u8 *) effect) + 8));
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
        if (((D_80082E80.unk_014 & 0x8000) == 0) && (((s32) (timer << 16)) >= 0)) {
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
