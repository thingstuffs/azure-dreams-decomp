#include "common.h"
#include "dungeon/effect.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"

typedef struct {
    u8 before_sprite[8];
    ObjectPosition *sprite; /* The node position slot at +8. */
    SpriteFrameState *render;
    void *callback;
    u8 before_work[0xC];
    JitterEffectBody work[1]; /* Body at node +0x20. */
} Effect;

/* Create a positioned effect and set its animation and lifetime parameters. */
ObjectNodeHeader *create_jittering_effect(void *source, s32 x, s32 y, s32 z, ObjectPosition *position, struct SpritePartCommand *command, s16 frame, ObjectPosition *anchor, s32 phase) {
    ObjectNodeHeader *node;
    Effect *effect;
    ObjectPosition *sprite;
    JitterEffectBody *work;
    SpriteFrameState *render;
    effect = allocate_list_node(0x212, source);
    node = (ObjectNodeHeader *)effect;
    if (effect != 0) {
        effect->callback = jitter_effect_position_and_fade;
        register_node(node, draw_linked_segment_aligned_quads);
        sprite = effect->sprite;
        sprite->x.w.i = (u16)position->x.w.i;
        sprite->y.w.i = (u16)position->y.w.i;
        sprite->z.w.i = (u16)position->z.w.i;
        work = effect->work;
        ((Fixed1616 *)&sprite->velocity_x)->w.i = x;
        work->base_position[0] = x;
        ((Fixed1616 *)&sprite->velocity_y)->w.i = y;
        work->base_position[1] = y;
        ((Fixed1616 *)&sprite->velocity_z)->w.i = z;
        work->base_position[2] = z;
        render = effect->render;
        render->source = command;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;
        render->color.word = 0x808080;
        {
            s32 index = frame;
            if (index != 0) {
                render->tpage_abr = (index - 1) << 5;
                render->flags |= 0xC;
            }
        }
        work->unk_2E = 8;
        work->fade = 0x80;
        work->anchor = anchor;
        work->phase = phase;
    }
    return node;
}
