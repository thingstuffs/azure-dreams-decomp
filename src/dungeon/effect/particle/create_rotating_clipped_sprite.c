#include "shared/object_node.h"
#include "dungeon/effect/particle.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

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
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Child;

typedef struct {
    u8 pad0[8];
    u32 *buffer;
    Child *child;
    void *field10;
} Object;

typedef struct {
    u8 pad0[0x18];
    s16 field18;
    s16 field1A;
    u8 pad1C[0xC];
    Packed12 blob;
} Subobject;

extern u8 encounter_object_position_template[12];

/* Creates an object at an offset position and initializes its selected variant. */
void create_rotating_clipped_sprite(u32 *source_pos, s16 variant) {
    u32 *buffer;
    Child *child;
    Subobject *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        state = (Subobject *)((u8 *)object + 0x20);
        state->field18 = 0x1E;
        state->field1A = 0x1E;
        if ((variant << 0x10) == 0) {
            object->update_callback = tick_rotating_rect_effect;
        } else {
            object->update_callback = update_reverse_rotating_clipped_sprite;
        }
        register_node(object, project_sprite_chain);
        child = *(Child * *)&object->sprite;
        child->field10 = 0x20;
        child->field6 = 0;
        child->field14 |= 0xC;
        buffer = *(u32 * *)&object->position;
        buffer[0] = source_pos[0];
        buffer[1] = source_pos[1];
        buffer[2] = source_pos[2] + 0xFF880000;
        child = *(Child * *)&object->sprite;
        child->field1E = 0x1000;
        child->field1C = 0x1000;
        child->fieldE = 0x80;
        child->fieldD = 0x80;
        child->fieldC = 0x80;
        child->field14 |= 0x80;
        state->blob = *(Packed12 *)encounter_object_position_template;
        child->field8 = &state->blob;
    }
}
