#include "shared/sprite_frame_state.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "dungeon/monster/beldo_large.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} __attribute__((packed)) PackedVec3i;

typedef struct {
    u8 pad0[6];
    s16 field6;
    void *field8;
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} SubObject;

typedef struct {
    u8 pad0[8];
    Vec3i *field8;
    SubObject *fieldC;
    void *field10;
    u8 pad14[0x24];
    s16 field38;
    u8 pad3A[0xE];
    PackedVec3i field48;
} Object;


extern u8 encounter_object_position_template[12];


/* Create and initialize an object at the global position. */
void create_player_centered_sequence_effect(void)
{
    ObjectNodeHeader * object;
    SpriteFrameState *sub_object;
    ObjectPosition *position;
    PlayerCenteredSequenceEffectBody *effect_state;

    object = allocate_flagged_object_node(0x12);
    if (object != NULL) {
        effect_state = NODE_BODY(object);
        effect_state->ticks_remaining = 0;
        (object->update_callback) = update_staged_particle_emitter;
        register_node(object, project_sprite_chain);

        sub_object = object-> sprite;
        sub_object->tpage_abr = 0x20;
        sub_object->depth_bias = 0;
        sub_object->flags |= 0xC;

        position = object->position;
        position->x.v = view_reference_entity.x.v;
        position->y.v = view_reference_entity.y.v;
        position->z.v = view_reference_entity.z.v;

        sub_object = object-> sprite;
        sub_object->scale_y = 0x1000;
        sub_object->scale_x = 0x1000;
        sub_object->color.c.b = 0x80;
        sub_object->color.c.g = 0x80;
        sub_object->color.c.r = 0x80;
        sub_object->flags |= 0x80;

        (*(PackedVec3i *)((u8 *)object + 0x48)) = *(PackedVec3i *)encounter_object_position_template;
        sub_object->source = (u8 *)object + 0x48;
    }
}
