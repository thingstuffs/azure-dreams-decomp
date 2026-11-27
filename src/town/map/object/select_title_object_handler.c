#include "slus/map_state.h"
#include "town/map/object_callbacks_api.h"
#include "slus/town_map_selection_data.h"
#include "common.h"
#include "engine/resource.h"
#include "engine/script.h"
#include "town/map.h"
#include "town/player/effect.h"
#include "town/map/object.h"

typedef struct {
    u8 pad0[0x10];
    s32 *update_callback;
    u8 pad14[0x0C];
    s32 *body_callback;
} TownContext;

typedef struct {
    u8 pad0[0x0C];
    s32 velocity_x;
    s32 velocity_y;
} TownState;

typedef struct town_title_handler_object {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    u8 pad6[0x16];
    void *handler;
} TownObject;

extern TownContext scene_object_list_anchor;

extern s32 D_800A549C;
extern s32 D_800A54FC;
extern s32 D_800A5638;

extern s32 D_800A5A98;
extern TownState town_position_reference_state;

/* Pick the title-screen object's next handler and timing from the current scene and progress flags. */
void select_title_object_handler(TownObject *obj)
{
    if ((scene_object_list_anchor.update_callback == &D_800A5638) &&
        ((scene_object_list_anchor.body_callback == &D_800A5A98) ||
         (scene_object_list_anchor.body_callback == update_object_view_transition))) {
        obj->field_2 = 0x80;
        obj->field_4 = 0x300;
        obj->handler = set_fallback_record_handler;
        return;
    }

    if ((estimate_vector_length(town_position_reference_state.velocity_x,
                       town_position_reference_state.velocity_y) > 0xDFFFF) &&
        (map_runtime_state.scene_selector != 0xC)) {
        obj->field_4 = 0x448;
        obj->handler = &D_800A549C;
        return;
    }

    if (service_script_controller() != 0) {
        if (map_runtime_state.scene_selector == 12 && map_runtime_state.map_index == 56) {
            obj->field_4 = 0x448;
        } else {
            obj->field_4 = 0x380;
        }
        obj->handler = &D_800A54FC;
    }
}
