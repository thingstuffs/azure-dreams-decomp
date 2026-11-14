#include "common.h"
#include "engine/graphics.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "frontend/settings.h"
#include "frontend/settings/initialization.h"
#include "frontend/settings/owner_linked_body.h"

/* Creates a type 0x136 object and initializes its position and rendering state. */
void *create_settings_sprite_object(SettingsPositionPair *position, s32 object_value, s32 render_value, SettingsScreenBody *extra_value) {
    ObjectNodeHeader *object;
    SpriteFrameState *render_state;

    object = allocate_flagged_object_node(0x136);
    if (object != 0) {
        object->update_callback = (void *)object_value;
        object->position->x.v = (s32) position->x.v;
        object->position->y.v = (s32) position->y.v;
        register_node(object, draw_linked_sprites);
        render_state = object->sprite;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->source = render_value;
        render_state->color.word = 0x808080;
        ((SettingsOwnerLinkedBody *)NODE_BODY(object))->owner = extra_value;
    }
    return object;
}
