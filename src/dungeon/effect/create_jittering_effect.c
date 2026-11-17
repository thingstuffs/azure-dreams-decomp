#include "common.h"
#include "dungeon/effect.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"

typedef struct {
    u8 before_sprite[8];
    void *sprite;
    void *render;
    void *callback;
    u8 before_work[0xC];
    u8 work[0x3E];
} Effect;
extern u8 linked_mesh_processor_address [ ];

/* Create a positioned effect and set its animation and lifetime parameters. */
void *create_jittering_effect(void *source, s32 x, s32 y, s32 z, ObjectPosition *position, s32 texture, s16 frame, s32 lifetime, s32 timer) {
    Effect *effect;
    ObjectPosition *sprite;
    u8 *work;
    SpriteFrameState *render;
    effect = allocate_list_node(0x212, source);
    if (effect != 0) {
        effect->callback = jitter_effect_position_and_fade;
        register_node(effect, linked_mesh_processor_address);
        sprite = effect->sprite;
        sprite->x.w.i = (u16)position->x.w.i;
        sprite->y.w.i = (u16)position->y.w.i;
        sprite->z.w.i = (u16)position->z.w.i;
        work = effect->work;
        *(s16 *)(((u8 *)sprite) + 0xE) = x;
        *(s16 *)(work + 0x18) = x;
        *(s16 *)(((u8 *)sprite) + 0x12) = y;
        *(s16 *)(work + 0x1A) = y;
        *(s16 *)(((u8 *)sprite) + 0x16) = z;
        *(s16 *)(work + 0x1C) = z;
        render = effect->render;
        render->source = texture;
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
        *(s16 *)(work + 0x2E) = 8;
        *(s16 *)(work + 0x3C) = 0x80;
        *(s32 *)(work + 0x14) = lifetime;
        *(s16 *)(work + 0x32) = timer;
    }
    return effect;
}
