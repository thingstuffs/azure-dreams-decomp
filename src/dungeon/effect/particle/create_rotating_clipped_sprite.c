#include "shared/object_node.h"
#include "dungeon/effect/particle.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "dungeon/monster/beldo_large/encounter_position_data.h"

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

typedef struct {
    u8 pad0[6];
    s16 depth_bias;
    void *source;
    u8 color_r;
    u8 color_g;
    u8 color_b;
    u8 padF;
    s16 tpage_abr;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} Child;

typedef struct {
    u8 pad0[8];
    u32 *buffer;
    Child *child;
    void *field10;
} Object;

typedef struct {
    u8 pad0[0x18];
    s16 ticks_remaining;
    s16 field1A;
    u8 pad1C[0xC];
    Packed12 blob;
} Subobject;


/* Creates an object at an offset position and initializes its selected variant. */
void create_rotating_clipped_sprite(u32 *source_pos, s16 variant) {
    u32 *buffer;
    Child *child;
    Subobject *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        state = NODE_BODY(object);
        state->ticks_remaining = 0x1E;
        state->field1A = 0x1E;
        if ((variant << 0x10) == 0) {
            object->update_callback = tick_rotating_rect_effect;
        } else {
            object->update_callback = update_reverse_rotating_clipped_sprite;
        }
        register_node(object, project_sprite_chain);
        child = *(Child * *)&object->sprite;
        child->tpage_abr = 0x20;
        child->depth_bias = 0;
        child->flags |= 0xC;
        buffer = *(u32 * *)&object->position;
        buffer[0] = source_pos[0];
        buffer[1] = source_pos[1];
        buffer[2] = source_pos[2] + 0xFF880000;
        child = *(Child * *)&object->sprite;
        child->scale_y = 0x1000;
        child->scale_x = 0x1000;
        child->color_b = 0x80;
        child->color_g = 0x80;
        child->color_r = 0x80;
        child->flags |= 0x80;
        state->blob = *(Packed12 *)&encounter_object_position_template;
        child->source = &state->blob;
    }
}
