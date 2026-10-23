#include "common.h"

typedef struct {
    u8 pad0[0x10];
    s32 *field_10;
    u8 pad14[0x0C];
    s32 *field_20;
} TownContext;

typedef struct {
    u8 pad0[0x0C];
    s32 field_C;
    s32 field_10;
} TownState;

typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    u8 pad6[0x16];
    void *field_1C;
} TownObject;

extern s32 map_scene_selector_alias;
extern TownContext scene_object_list_anchor;
extern s32 D_800A5440;
extern s32 D_800A549C;
extern s32 D_800A54FC;
extern s32 D_800A5638;
extern s32 map_view_transition_address;
extern s32 D_800A5A98;
extern TownState town_position_reference_state;

extern s32 service_script_controller(void);
extern s32 runtime_estimate_vector_length(s32, s32);

/* Pick the title-screen object's next handler and timing from the current scene and progress flags. */
void select_title_object_handler(TownObject *obj)
{
    if ((scene_object_list_anchor.field_10 == &D_800A5638) &&
        ((scene_object_list_anchor.field_20 == &D_800A5A98) ||
         (scene_object_list_anchor.field_20 == &map_view_transition_address))) {
        obj->field_2 = 0x80;
        obj->field_4 = 0x300;
        obj->field_1C = &D_800A5440;
        return;
    }

    if ((runtime_estimate_vector_length(town_position_reference_state.field_C,
                       town_position_reference_state.field_10) > 0xDFFFF) &&
        ((s16)map_scene_selector_alias != 0xC)) {
        obj->field_4 = 0x448;
        obj->field_1C = &D_800A549C;
        return;
    }

    if (service_script_controller() != 0) {
        if (map_scene_selector_alias == 0x38000C) {
            obj->field_4 = 0x448;
        } else {
            obj->field_4 = 0x380;
        }
        obj->field_1C = &D_800A54FC;
    }
}
