#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_800247B8_arg0.h"
#include "shared/dungeon_moving_views.h"

#define UNALIGNED32(expr) (expr)

typedef struct {
    u8 bytes[12];
} Block12;

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 D_800D4954;
extern Block12 D_800E233C;

typedef struct S_800D4AB0_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
    u8 pad_5E[0x2A];
    void * unk_88;
} S_800D4AB0_0;

typedef struct S_800D4AB0_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800D4AB0_2;

typedef struct S_800D4AB0_5_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800D4AB0_5_pre;   /* the 0x18 bytes before ((Rec_func_800247B8_arg0 *)arg0)->unk_88 in create_attached_effect, addressed as ((Rec_func_800247B8_arg0 *)arg0)->unk_88[-1] */

/* Creates an effect linked to the owner with an offset position and initialized render data. */
void create_attached_effect(Rec_func_800247B8_arg0 *owner) {
    ObjectPosition *position;
    SpriteFrameState *render_data;
    ObjectNodeHeader *effect;
    S_800D4AB0_0 *effect_state;
    MovingPosition *source_position;

    effect = allocate_flagged_object_node(0x12);
    effect_state = ((void *)effect) + 0x20;
    if (effect != 0) {
        effect_state->unk_5A = 0x78;
        effect_state->unk_5C = 0x78;
        effect_state->unk_88 = owner->unk_88;
        effect->update_callback = &D_800D4954;
        register_node(effect, project_sprite_chain);
        render_data = effect->sprite;
        render_data->tpage_abr = 0x60;
        render_data->depth_bias = 0;
        render_data->flags = render_data->flags | 0xC;
        source_position = ((S_800D4AB0_5_pre *)(owner->unk_88))[-1].unk_00;
        position = effect->position;
        position->x.w.i = source_position->x;
        position->y.w.i = source_position->y;
        position->z.w.i = source_position->z - 0x32;
        render_data = effect->sprite;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        render_data->scale_y = 0;
        render_data->scale_x = 0;
        (*(Block12 *)((u8 *)effect + 0x96)) = D_800E233C;
        render_data->source = ((void *)effect) + 0x96;
    }
}
