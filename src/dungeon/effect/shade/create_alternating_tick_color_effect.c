#include "dungeon/effect/shade.h"
#include "common.h"
#include "dungeon/effect/emission_data.h"
#include "dungeon/effect/head_bank_imports.h"
#include "dungeon/effect/particle.h"
#include "shared/dungeon_effect_source.h"
#include "shared/dungeon_moving_views.h"

void create_alternating_tick_color_effect(ColorEffectSource *source, u32 color)
{
    SourceColorEffect *effect;
    SpriteFrameState *render;
    MovingPosition *position;
    /* BYTES: Taking the address puts the color spill in the allocator call delay slot. */
    u32 *color_value = &color;

    effect = func_8003CF18(18);
    if (effect != 0) {
        render = effect->render;
        effect->update_callback = spawn_alternating_tick_effects;
        effect->source = source;
        effect->lifetime = 55;
        render->tpage_abr = 32;
        render->flags |= 12;

        position = effect->position;
        position->x = source->position->x;
        position->y = source->position->y;
        position->z = source->position->z;

        render = effect->render;
        render->color.c.b = 128;
        render->color.c.g = 128;
        render->color.c.r = 128;
        render->scale_y = 4096;
        render->scale_x = 4096;
        render->color.word = *color_value;
        effect->color = *color_value;
        render->clut = 0x7DCE;
        render->flags |= 0x100;
        func_8003A7C4(render, positioned_effect_source, 0);
        emitted_effect_counter[0]++;
    }
}
