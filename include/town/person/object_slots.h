#ifndef TOWN_PERSON_OBJECT_SLOTS_H
#define TOWN_PERSON_OBJECT_SLOTS_H
#include "shared/town_object.h"
struct TownObjectRecord;

/* Scene object callbacks that register fixed scene slots. */
struct SpriteFrameState;

void initialize_scene_slot_47_context(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_53(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_55(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_49(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_36(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_45_context(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_18(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_46(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_38(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_30(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_57_context(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_62_context(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_24(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);
void initialize_scene_slot_69(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void set_actor_flag_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

void configure_actor_slot_75_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

void configure_actor_slot_76_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

void configure_actor_slot_77_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

void configure_actor_slot_78_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state);

void initialize_scene_slot_60(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_59(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_83(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_84(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_58(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_62(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_57(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_48(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_47(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_scene_slot_52(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

void initialize_object_slot_0x17(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_28_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_26_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void init_reaction_object_slot_clut(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *state);

void init_person_slot_sixty_one(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *output);

void initialize_reaction_object_type_4_f(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *stateValues);

void configure_actor_slot_25_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void reset_object_substate_and_flag(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_70_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_71_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_72_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_73_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_21_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_44_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_64_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_65_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void configure_actor_slot_66_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords);

void initialize_transform_object(TownObjectRecord *object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_actor_slot_30(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_fifty_one(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_16(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_22(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_nineteen(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_mode_13(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_thirty_five(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_63(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_32(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_four(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void initialize_variant_object(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_thirty_three(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_fifty(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_34(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_14(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_20(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_58(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_43(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_80(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void configure_actor_slot_5(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

void init_person_slot_eight(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

void initialize_object_slot_9_data(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

void initialize_object_slot_9_and_display(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *state);

#endif
