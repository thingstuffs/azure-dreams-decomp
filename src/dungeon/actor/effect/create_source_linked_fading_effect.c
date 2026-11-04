#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node/allocation.h"
#include "engine/node.h"

   /* arg0 in create_source_linked_fading_effect */

   /* ((S_800CB4C0_6 *)arg0)->unk_08 in create_source_linked_fading_effect */

void select_record_entry_and_value(void *state, void *entries, short index);  /* extern */
extern void fade_effect_primitive(void *effect, void *unused, SpriteFrameState *primitive);
#include "shared/sprite_source.h"
#include "dungeon/actor/effect.h"
#include "dungeon/effect.h"
extern SpriteSourceEntry D_800E02CC[];

/* Creates an object with shared or copied source coordinates and initializes its display state. */
void *create_source_linked_fading_effect(ObjectNodeHeader *source, s16 copy_position) {
    s32 display_value;
    SpriteFrameState *display;
    ObjectNodeHeader *object;
    SourceLinkedFadeEffectBody *state;
    SpriteFrameState *source_display;
    ObjectPosition *position;

    object = allocate_list_node(0x100, &source->next);
    if (object != NULL) {
        object->update_callback = &fade_effect_primitive;
        register_node(object, project_sprite_chain);
        display = object->sprite;
        select_record_entry_and_value(display, &D_800E02CC, 0);
        display->scale_y = 0x1400;
        display->scale_x = 0x1400;
        display->tpage_abr = 0x20;
        display->flags = (u16) (display->flags | 0xC);
        if ((copy_position << 0x10) == 0) {
            object->position = source->position;
        } else {
            position = object->position;
            position->x.w.i = (u16) source->position->x.unsigned_parts.integer;
            position->y.w.i = (u16) source->position->y.unsigned_parts.integer;
            position->z.w.i = (u16) source->position->z.unsigned_parts.integer;
            source_display = source->sprite;
            display_value = source_display->color.word;
            display->tpage_abr = 0x60;
            display->color.word = display_value;
        }

        display->depth_bias = -1;
        state = NODE_BODY(object);
        state->unk_A8 = source;
        state->unk_B4 = copy_position;
        state->unk_96 = 8;
    }
    return object;
}
