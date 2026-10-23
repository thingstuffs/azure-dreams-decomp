#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"

struct Dst;
struct Elem;

void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node();
extern s32 rand();
void func_8002418C(void *object_ref, void *unused, void *state);
#include "shared/sprite_source.h"
extern SpriteSourceEntry rising_sprite_entries[];

/* Creates and initializes an effect with a randomized offset from the source position. */
void create_random_offset_sprite_effect(s32 effect_param, void *source_pos)
{
    s32 random_offset;
    SpriteFrameState *sprite;
    int color;
    ObjectPosition *effect_pos;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect->unk_10 = &func_8002418C;
        sprite = effect->sprite;
        *((s32 *)(((s8 *)effect) + 0x20)) = effect_param;
        color = 0x80;
        sprite->color.c.b = color;
        sprite->color.c.g = color;
        sprite->color.c.r = color;
        select_record_entry_and_value(sprite, rising_sprite_entries, 0);
        sprite->scale_y = 0x1800;
        sprite->scale_x = 0x1800;
        sprite->clut = 0x7E0B;
        sprite->tpage_abr =
            (u16)(sprite->tpage_abr | 0x60);
        sprite->flags =
            (u16)(sprite->flags | 0x10C);
        register_node(effect, project_sprite_chain);
        effect_pos = effect->position;
        rand();
        effect_pos->x.w.i =
            (u16)(*((u16 *)(((s8 *)source_pos) + 2)));
        effect_pos->y.w.i =
            (u16)(*((u16 *)(((s8 *)source_pos) + 6)));
        random_offset = rand();
        effect_pos->z.w.i =
            (s16)((*((u16 *)(((s8 *)source_pos) + 0xA)) - 0x20) -
                  (random_offset % 16));
    }
}
