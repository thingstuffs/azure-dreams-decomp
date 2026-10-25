#include "shared/entity.h"
#include "engine/graphics.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80172A14_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80172A14_0;   /* arg0 in create_boss_linked_effect */

typedef struct S_80172A14_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    void * unk_20;
    void * unk_24;
} S_80172A14_2;

   /* arg1 in create_boss_linked_effect */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);

extern u8 D_80172874[];
extern u8 D_80174ABC[];

/* Create an effect linked to its owner and initialize its position and rendering. */
/* Creates a black Ghosh effect at the supplied position and links its owner and source position for later
 * updates. */
void create_boss_linked_effect(void *owner, MovingPosition *source_pos) {
    SpriteFrameState *render_flags;
    ObjectNodeHeader *effect;
    S_80172A14_2 *effect_state;
    ObjectPosition *effect_pos;

    effect = allocate_list_node(0x12, (u8 *)owner - 0x20);
    if (effect != 0) {
        ((S_80172A14_0 *)owner)->unk_AC = effect;
        effect->update_callback = D_80172874;
        register_node(effect, draw_linked_sprites_clipped);
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_18 = 5;
        effect_state->unk_20 = owner;
        effect_state->unk_24 = source_pos;
        render_flags = effect->sprite;
        render_flags->tpage_abr = 0x40;
        render_flags->flags |= 0xC;
        effect_pos = effect->position;
        effect_pos->x.w.i = source_pos->x;
        effect_pos->y.w.i = source_pos->y;
        effect_pos->z.w.i = source_pos->z;
        render_flags = effect->sprite;
        render_flags->scale_y = 0xA00;
        render_flags->scale_x = 0xA00;
        render_flags->color.c.b = 0;
        render_flags->color.c.g = 0;
        render_flags->color.c.r = 0;
        render_flags->source = D_80174ABC;
    }
}
