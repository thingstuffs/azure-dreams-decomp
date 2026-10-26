#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct Func800BF66CObject {
    u8 pad00[0x48];
    s32 field48;
    u8 pad4c[4];
    s32 field50;
    u8 pad54[0x52];
    s16 fieldA6;
} Func800BF66CObject;

extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void register_node(void *, void *);
extern void configure_the_set_mode_n_1(void *, s32, void *);
extern u8 D_800BC990[];
extern u8 town_map_motion_defaults[];
extern s32 D_800D211C[];
extern s32 D_800D212C;

/* Initialize the object state, motion, and animation. */
void initialize_object_motion_and_animation(Func800BF66CObject *object, s32 motion, s32 anim) {
    *(void **)((u8 *)object - 0x10) = D_800BC990;
    object->field50 = 0;
    register_node((u8 *)object - 0x20, project_sprite_chain);
    object->fieldA6 = 2;
    configure_the_set_mode_n_1(object, motion, town_map_motion_defaults);
    select_record_entry_and_value(anim, D_800D211C[object->fieldA6], 0);
    object->field48 = D_800D212C;
}
