#include "shared/sprite_source.h"
#include "common.h"

#include "engine/effect.h"
#include "engine/resource.h"
#include "slus.h"
#include "slus/data.h"

/* Initialize the fade sprite and position for the current source and set the next step. */
void initialize_shared_sprite_fade_display(void) {
    FadeManagerBody *context = &fade_manager_state;
    ObjectNodeHeader *root = NODE_HEADER(context);
    SpriteFrameState *dst = root->sprite;
    ObjectPosition *vec = root->position;

    dst->scale_y = 0x200;
    dst->scale_x = 0x200;
    dst->color.word = 0x808080;
    dst->source = D_800F26F8;
    dst->unk_00 = 0;
    dst->unk_04 = 0;
    dst->frame_ticks = 0;
    select_record_entry_and_value(dst, context->source, 0);
    dst->flags = 0;
    dst->tpage_abr = 0;

    if (context->source == (SpriteSourceEntry *)flagged_effect_source_1 ||
        context->source == (SpriteSourceEntry *)flagged_effect_source_0) {
        dst->flags |= 0x400;
    }

    vec->x.w.i = 0x54;
    vec->y.w.i = 0x8D;
    vec->z.w.i = 0x10;
    context->step = ramp_fade_up_fast;
    set_fade_has_source(context, dst);
}
