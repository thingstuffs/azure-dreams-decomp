#include "frontend/settings/controller_body.h"
#include "modules/main_title_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "frontend/settings.h"
#include "main/data.h"
#include "slus.h"
#include "frontend/card.h"

struct Dst;
struct Elem;
extern s8 animation_tick_scale;

typedef struct { s32 a, b, c; } Desc3;

/* Creates a controller and its linked sprites and effect objects. */
void create_settings_controller(void) {
    SettingsVisualEffectBody *visual;
    s32 sprite_ids[3];
    s32 child_index;
    s32 sprite_y;
    s32 start_delay;
    s32 unit_scale;
    s32 sprite_id;
    SettingsEffectObjectBody *child_state;
    SpriteFrameState *sprite;
    ObjectNodeHeader *object;
    SettingsSyncObjectBody *effect_state;
    SettingsMenuBody *parent_state;
    void *id_offset;
    SettingsControllerChildNode **child_slot;

    parent_state = NULL;
    *(Desc3 *)sprite_ids = *(Desc3 *)&D_80088760;
    animation_tick_scale = 1;
    object = allocate_flagged_object_node(0x11);
    if (object != NULL) {
        parent_state = NODE_BODY(object);
        object->update_callback = (void *)update_settings_menu_animation;
        register_node(object, queue_settings_sprite_grid);
        parent_state->counter = 0x708;
        object->position->y.w.i = 0xF0;
        parent_state->fade.unk_2 = 0;
        parent_state->fade.param = 0x40;
    }
    child_index = 2;
    start_delay = 0x3C;
    sprite_y = 0xC8;
    unit_scale = 0x1000;
    child_slot = &parent_state->slotsA[1];
    do {
        object = allocate_flagged_object_node(0x111);
        child_slot[1] = (void *)object;
        id_offset = (void *)(child_index << 2);
        if (object != NULL) {
            child_state = NODE_BODY(object);
            sprite = object->sprite;
            object->update_callback = (void *)update_settings_effect_object;
            register_node(object, &draw_linked_sprites);
            object->position->x.w.i = -0x40;
            object->position->y.w.i = sprite_y;
            object->position->velocity_x = 0x150000;
            sprite->scale_y = unit_scale;
            sprite->scale_x = unit_scale;
            sprite_id = *(s32 *)((s8 *)sprite_ids + (s32)id_offset);
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
            sprite->color.word = 0x808080;
            sprite->source = sprite_id;
            child_state->owner = parent_state;
            child_state->index = child_index;
            child_state->ticks = start_delay;
        }
        start_delay -= 0x1E;
        sprite_y -= 0x10;
        child_index -= 1;
        child_slot--;
    } while (child_index >= 0);
    object = allocate_flagged_object_node(1);
    if (object != NULL) {
        object->update_callback = (void *)sync_object_with_sub_object;
        register_node(object, &display_registration_tag);
        effect_state = NODE_BODY(object);
        effect_state->position_y = 0x60;
        effect_state->position_delta = -0x100;
        effect_state->width = 0x80;
        effect_state->height = 0x10;
        effect_state->value = 0;
        effect_state->flags = 3;
        effect_state->color = 0x606060;
        effect_state->state = 0;
        effect_state->child = parent_state;
    }
    child_index = 1;
    do {
        object = allocate_flagged_object_node(0x111);
        parent_state->slotsB[child_index] = (void *)object;
        if (object != NULL) {
            child_state = NODE_BODY(object);
            sprite = object->sprite;
            object->update_callback = (void *)update_settings_phase_motion;
            register_node(object, &draw_linked_sprites);
            object->position->y.w.i = 0xE9;
            if (child_index != 0) {
                object->position->x.w.i = -0x15;
                object->position->velocity_x = 0x160000;
                select_record_entry_and_value(sprite, &D_8008B270, 0);
            } else {
                object->position->x.w.i = 0x155;
                object->position->velocity_x = 0xFFEA0000;
                select_record_entry_and_value(sprite, &D_8008B230, 0);
            }
            object->position->velocity_y = 0xFFF80000;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->color.word = 0x808080;
            child_state->owner = parent_state;
            child_state->index = child_index;
        }
        child_index -= 1;
    } while (child_index >= 0);
    object = allocate_flagged_object_node(1);
    if (object != NULL) {
        object->update_callback = (void *)update_settings_effect;
        visual = NODE_BODY(object);
        visual->owner = parent_state;
        visual->angle = 0xE00;
    }
}
