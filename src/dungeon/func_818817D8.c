#include "modules/dungeon_ovl_18a0800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024FD8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024FD8_0;

   /* arg0 in create_effect_render_object */

typedef struct S_80024FD8_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024FD8_4;

/* Creates a render object at the supplied position and initializes its effect state. */
void *create_effect_render_object(MovingPosition *source_pos, s16 effect_param, s16 size)
{
    s32 signed_size;
    s32 render_code;
    u16 object_count;
    SpriteFrameState *render_state;
    void *object;
    MovingPosition *position;
    S_80024FD8_4 *effect_state;

    object = func_8003FC64(0x202);
    if (object != 0) {
        ((S_80024FD8_0 *)object)->unk_10 = move_and_fade_effect;
        register_node(object, (s32)draw_linked_sprites_clipped);
        position = ((S_80024FD8_0 *)object)->unk_08;
        position->unk_02 = source_pos->unk_02;
        position->unk_06 = source_pos->unk_06;
        position->unk_0A = source_pos->unk_0A;
        render_state = ((S_80024FD8_0 *)object)->unk_0C;
        render_state->color.word = 0x808080;
        render_state->scale_x = 0x400;
        render_state->scale_y = 0x1CCC;
        func_8003DB94(render_state, D_80025854, 0);
        signed_size = (s16)size;
        render_state->angle_y = (signed_size << 8) - 0x400;
        render_code = 0x60;
        effect_state = (u8 *)object + 0x20;
        render_state->tpage_abr = render_code;
        object_count = (*(u16 *)D_800257CC);
        render_state->angle_x = 0x400;
        effect_state->unk_24 = size;
        effect_state->unk_14 = effect_param;
        effect_state->unk_1E = signed_size * 2;
        (*(u16 *)D_800257CC) = object_count + 1;
    }
    return object;
}

