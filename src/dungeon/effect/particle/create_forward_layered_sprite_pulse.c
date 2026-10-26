#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#include "records/Rec_D_80082E80.h"

struct Dst;
struct Elem;

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2];
    u16 field_02;
} DirectionEntryFieldView_813307FC;

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 words[8];
} __attribute__((packed)) LocalTable;

void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern u8 ribbon_sprite_entries[];
extern LocalTable D_8016482C;
void update_flickering_layer_sprite(void *effect_data, void *unused, SpriteFrameState *effect);
extern s32 beldo_actor_nodes;

typedef struct S_801677FC_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801677FC_0;   /* (void *)D_80175D50 in create_forward_layered_sprite_pulse */

typedef struct S_801677FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801677FC_1;

typedef struct S_801677FC_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801677FC_5;

typedef struct S_801677FC_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801677FC_6;

/* Spawn sixteen effects offset in the current object's facing direction with increasing sizes. */
void create_forward_layered_sprite_pulse(void)
{
    LocalTable direction_offsets;
    s32 size_step;
    s32 effect_index;
    u8 *direction_entry;
    SpriteFrameState *render_flags;
    ObjectPosition *effect_pos;
    SpriteFrameState *sprite;
    S_801677FC_5 *source_pos;
    S_801677FC_6 *source_state;
    ObjectNodeHeader *effect;
    S_801677FC_1 *effect_state;

    direction_offsets = D_8016482C;
    effect_index = 0;
    source_state = (void *)beldo_actor_nodes + 0x20;
    source_pos = ((S_801677FC_0 *)((void *)beldo_actor_nodes))->unk_08;
    do {
        effect = allocate_flagged_object_node(0x212);
        if (effect != NULL) {
            effect_state = ((void *)effect) + 0x20;
            effect_state->unk_18 = 0xE;
            effect_state->unk_1A = 0xE;
            effect->update_callback = update_flickering_layer_sprite;
            register_node(effect, project_sprite_chain);
            render_flags = effect->sprite;
            render_flags->tpage_abr = 0x60;
            render_flags->flags =
                (u16)(render_flags->flags | 0xC);
            effect_pos = effect->position;
            effect_pos->x.v = source_pos->unk_00;
            effect_pos->y.v = source_pos->unk_04;
            effect_pos->z.v =
                source_pos->unk_08 + (s32)0xFFCE0000;
            effect_pos->x.w.i =
                (u16)(*(u16 *)&effect_pos->x.w.i +
                ((*(s16 *)((u8 *)(&direction_offsets) + ((source_state->unk_2A >> 7) & 0x1C))) * 0x14));
            size_step = effect_index << 9;
            direction_entry = (u8 *)&direction_offsets + ((source_state->unk_2A >> 7) & 0x1C);
            effect_pos->y.w.i =
                (u16)(*(u16 *)&effect_pos->y.w.i +
                ((s16)((DirectionEntryFieldView_813307FC *)direction_entry)->field_02 * 0x14));
            sprite = effect->sprite;
            sprite->scale_x = (s16)(size_step + 0x1C00);
            sprite->scale_y = (s16)(size_step + 0x1400);
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            sprite->depth_bias = 0;
            sprite->clut = 0x7DCF;
            sprite->flags =
                (u16)(sprite->flags | 0x100);
            select_record_entry_and_value(sprite, ribbon_sprite_entries, 0);
        }
        effect_index += 1;
    } while (effect_index < 0x10);
}
