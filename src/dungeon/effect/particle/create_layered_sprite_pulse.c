#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"

#include "records/Rec_D_80082E80.h"
#include "dungeon/effect/particle.h"
#include "engine/node.h"
#include "slus.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 ribbon_sprite_entries[];

typedef struct S_801676CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801676CC_0;

/* Creates sixteen effects at the given position with increasing sprite scales. */
void create_layered_sprite_pulse(EntityRec *origin) {
    s16 scale_x;
    s16 scale_y;
    s32 effect_index;
    s16 initial_ticks;
    void *effect_data;
    SpriteFrameState *render_params;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;
    S_801676CC_0 *effect_state;

    effect_index = 0;
    initial_ticks = 0xE;
    effect_data = &update_flickering_layer_sprite;
    scale_y = 0x1000;
    scale_x = 0x1400;
    do {
        effect = allocate_flagged_object_node(0x212);
        if (effect != NULL) {
            effect_state = ((void *)effect) + 0x20;
            effect_state->unk_18 = initial_ticks;
            effect_state->unk_1A = initial_ticks;
            effect->update_callback = effect_data;
            register_node(effect, project_sprite_chain);
            render_params = effect->sprite;
            render_params->tpage_abr = 0x60;
            render_params->flags = (u16) (render_params->flags | 0xC);
            position = effect->position;
            position->x.v = (s32) origin->x.v;
            position->y.v = (s32) origin->y.v;
            position->z.v = (s32) (origin->z.v + 0xFFC00000);
            sprite = effect->sprite;
            sprite->scale_x = scale_x;
            sprite->scale_y = scale_y;
            sprite->color.c.b = 0;
            sprite->color.c.g = 0;
            sprite->color.c.r = 0;
            sprite->depth_bias = 0;
            sprite->clut = 0x7DCF;
            sprite->flags = (u16) (sprite->flags | 0x100);
            select_record_entry_and_value(sprite, ribbon_sprite_entries, 0);
        }
        scale_y += 0x200;
        effect_index += 1;
        scale_x += 0x200;
    } while (effect_index < 0x10);
}
