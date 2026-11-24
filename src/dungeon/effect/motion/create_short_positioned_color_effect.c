#include "dungeon/effect/shade.h"
#include "common.h"
#include "dungeon/effect/emission_data.h"
#include "dungeon/effect/head_bank_imports.h"
#include "dungeon/effect/particle.h"
#include "shared/dungeon_effect_source.h"
#include "shared/dungeon_moving_views.h"

extern s32 D_8010D648;

/* Create a colored effect at its source position. */
void create_short_positioned_color_effect(ColorEffectSource *source, s32 color)
{
    SourceColorEffect *effect;
    SpriteFrameState *render;
    MovingPosition *position;
    u32 packed_color;

    effect = func_8003CF18(18);
    if (effect != 0) {
        render = effect->render;
        effect->update_callback = &D_8010D648;
        effect->source = source;
        effect->lifetime = 0x32;
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
        packed_color = *&color;
        render->scale_y = 4096;
        render->scale_x = 4096;
        render->color.word = packed_color;
        effect->color = packed_color;
        render->clut = 0x7DCE;
        render->flags |= 0x100;
        func_8003A7C4(render, positioned_effect_source, 0);
        emitted_effect_counter[0]++;
    }
}
