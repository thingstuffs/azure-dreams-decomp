#include "engine/texture/gp_split_storage.h"

#include "engine/texture/gp_split_storage.h"
#include "engine/sprite.h"

static u16 shared_scroll_frame_id;
u16 sprite_pack_row_cursor = 0;
u16 sprite_pack_column_cursor = 0;
u16 sprite_pack_max_row_step = 0;
void sound_advance_shared_scroll_coordinates(struct S_80048660 *state)
{
    s32 row_step;
    s32 col_step;

    if (g_game_work.unk_004 != shared_scroll_frame_id) {
        sprite_pack_max_row_step = 0;
        sprite_pack_column_cursor = 0;
        sprite_pack_row_cursor = 0;
        shared_scroll_frame_id = g_game_work.unk_004;
    }

    row_step = (s32)(state->field_A + 1) >> 1;
    col_step = state->field_B + 1;

    if ((s32)(sprite_pack_column_cursor + col_step) >= 0x100) {
        sprite_pack_row_cursor = sprite_pack_row_cursor + sprite_pack_max_row_step;
        sprite_pack_column_cursor = 0;
    }

    if ((s32)(sprite_pack_row_cursor + row_step) >= 0x20) {
        sprite_pack_row_cursor = 0;
        sprite_pack_column_cursor = 0;
        sprite_pack_max_row_step = 0;
    }

    state->field_8 = (s8)(sprite_pack_row_cursor << 1);
    state->field_9 = (u8)sprite_pack_column_cursor;

    if ((s32)sprite_pack_max_row_step < row_step) {
        sprite_pack_max_row_step = (u16)row_step;
    }

    sprite_pack_column_cursor = sprite_pack_column_cursor + col_step;
}
