#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_800D4BD4_arg2.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800D4BD4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x14];
    void * unk_24;
} S_800D4BD4_0;   /* state in initialize_effect_object_state */

typedef struct S_800D4BD4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800D4BD4_1;   /* arg0 in initialize_effect_object_state */

extern void register_node(void *, void *);
extern void func_8003DB94(void *, void *, s32);
extern s32 D_800DECF8;

/* Initialize object state and rendering data from the source and position. */
void initialize_effect_object_state(void *object, Rec_func_800D4BD4_arg1 *source, Rec_func_800D4BD4_arg2 *position)
{
    SpriteFrameState *render_config;
    SpriteFrameState *render_data;
    MovingPosition *object_position;
    S_800D4BD4_0 *state;
    s32 source_value;
    u16 flags;

    state = (u8 *)object + 0x20;
    state->unk_24 = source;
    register_node(object, project_sprite_chain);
    render_config = ((S_800D4BD4_1 *)object)->unk_0C;
    render_config->tpage_abr = 0x20;
    render_config->flags = render_config->flags | 0xC;
    object_position = ((S_800D4BD4_1 *)object)->unk_08;
    object_position->unk_02 = position->unk_02.as_u16;
    object_position->unk_06 = position->unk_06.as_u16;
    object_position->unk_0A = position->unk_0A.as_u16;
    render_data = ((S_800D4BD4_1 *)object)->unk_0C;
    render_data->scale_y = 0x800;
    render_data->scale_x = 0x800;
    state->unk_0C = source->unk_0C;
    source_value = source->unk_0C;
    flags = render_data->flags;
    render_data->clut = 0x7DCF;
    flags |= 0x100;
    render_data->color.word = source_value;
    render_data->flags = flags;
    func_8003DB94(render_data, &D_800DECF8, 0);
}
