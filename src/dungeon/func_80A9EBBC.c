#include "modules/dungeon_resource08_slot0.h"
#include "shared/sprite_frame_state.h"

void create_positioned_sprite_effect(M2C_UNK unused, EntityRec *source_pos, void *unused_context) {
    R08_801743BC_S_801743BC_0 *effect;
    SpriteFrameState *sprite;
    MovingPosition *effect_pos;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect->unk_3A = 0x2D;
        effect->unk_10 = ((void *)update_timed_effect_and_expire);
        register_node(effect, project_sprite_chain);
        effect_pos = effect->unk_08;
        effect_pos->unk_02 = (u16) ((u16)source_pos->x.w.i);
        effect_pos->unk_06 = (u16) ((u16)source_pos->y.w.i);
        effect_pos->unk_0A = (u16) ((u16)source_pos->z.w.i);
        sprite = effect->unk_0C;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.r = 0;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->flags = (u16) (sprite->flags | 0x80);
    }
}
