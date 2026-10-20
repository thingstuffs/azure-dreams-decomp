#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"

struct Dst;
struct Elem;

void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node();
extern s32 rand();
void func_8002418C(void *object_ref, void *unused, void *state);
extern M2C_UNK D_800DEDB0[3];

/* Creates and initializes an effect with a randomized offset from the source position. */
void create_random_offset_sprite_effect(s32 effect_param, void *source_pos)
{
    s32 random_offset;
    SpriteFrameState *sprite;
    int color;
    void *effect_pos;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        *((s32 **)(((s8 *)effect) + 0x10)) = &func_8002418C;
        sprite = *((void **)(((s8 *)effect) + 0xC));
        *((s32 *)(((s8 *)effect) + 0x20)) = effect_param;
        color = 0x80;
        sprite->color.c.b = color;
        sprite->color.c.g = color;
        sprite->color.c.r = color;
        func_8003DB94(sprite, D_800DEDB0, 0);
        sprite->scale_y = 0x1800;
        sprite->scale_x = 0x1800;
        sprite->clut = 0x7E0B;
        sprite->tpage_abr =
            (u16)(sprite->tpage_abr | 0x60);
        sprite->flags =
            (u16)(sprite->flags | 0x10C);
        register_node(effect, project_sprite_chain);
        effect_pos = *((void **)(((s8 *)effect) + 8));
        rand();
        *((u16 *)(((s8 *)effect_pos) + 2)) =
            (u16)(*((u16 *)(((s8 *)source_pos) + 2)));
        *((u16 *)(((s8 *)effect_pos) + 6)) =
            (u16)(*((u16 *)(((s8 *)source_pos) + 6)));
        random_offset = rand();
        *((s16 *)(((s8 *)effect_pos) + 0xA)) =
            (s16)((*((u16 *)(((s8 *)source_pos) + 0xA)) - 0x20) -
                  (random_offset % 16));
    }
}
