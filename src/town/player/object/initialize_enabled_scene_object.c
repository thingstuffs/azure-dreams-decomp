#include "common.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 test_resident_bitmap_bit();
extern void *create_town_effect_object();
extern s16 query_lowered_transform_position();
extern void handle_insert_initialize_two_values_status_flags();
extern void initialize_optional_object_state();
extern void initialize_object_entries();
extern void set_flagged_entry_values();

extern s8 D_800A6684[];
extern s32 D_800D0C60[];
extern s32 D_800D0C78[];
extern s8 D_800D0C90[];
extern s8 D_800D0CAC[];
extern s8 D_800D0CC4[];
extern s8 D_800D0CE8[];
extern s8 D_800D0D0C[];
extern s8 D_800D0D30[];
extern s8 D_800D0D54[];
extern s32 D_80100E20;
extern void *D_80100E24;
extern void *D_80100E28;
extern void *D_80100E24_R;


/* Creates and initializes the enabled town object using its saved or default position. */
void initialize_enabled_scene_object(void) {
    s8 *object;
    s8 *position;
    s8 *state;
    s32 *saved_position;
    s32 object_resource;
    s32 *default_position;
    s32 coordinate;
    s32 default_z;
    s32 position_y;

    if (test_resident_bitmap_bit(0xD) != 0) {
        if (test_resident_bitmap_bit(0xE) != 0) {
            D_80100E24 = D_800D0D0C;
            D_80100E28 = D_800D0D30;
            D_80100E20 = 0x260000;
        } else {
            D_80100E24 = D_800D0CC4;
            D_80100E28 = D_800D0CE8;
            D_80100E20 = 0x1C0000;
        }
        object = create_town_effect_object(((s8 *)(&D_80083498)), 0, D_800A6684, 0);
        if (object != NULL) {
            position = *(s8 **)(object + 8);
            object_resource = *(s32 *)(object + 0xC);
            saved_position = D_800D0C78;
            *(s32 *)(position + 0) = D_800D0C78[0];
            state = object + 0x20;
            *(s32 *)(position + 4) = saved_position[1];
            *(s32 *)(position + 8) = saved_position[2];
            *(s16 *)(position + 0xA) = query_lowered_transform_position(position);

            if ((u32)(*(s32 *)(position + 8) + 0x300000) > 0x400000U) {
                default_position = D_800D0C60;
                coordinate = default_position[0];
                D_800D0C78[0] = coordinate;
                *(s32 *)(position + 0) = coordinate;
                coordinate = default_position[1];
                saved_position[1] = coordinate;
                *(s32 *)(position + 4) = coordinate;
                default_z = default_position[2];
                saved_position[2] = default_z;
                *(s32 *)(position + 8) = default_z;
            }

            position_y = *(s32 *)(position + 4);
            *(s32 *)(state + 0xA4) = position_y;
            *(s32 *)(state + 0xA0) = position_y;
            handle_insert_initialize_two_values_status_flags(state, position, D_800D0CAC);
            initialize_optional_object_state(state, position, object_resource, D_800D0C90);
            initialize_object_entries(state, object_resource, D_80100E24_R);
            *(s8 **)(state - 0x10) = D_800A6684;
            set_flagged_entry_values(D_800D0D54, 0);
        }
    }
}
