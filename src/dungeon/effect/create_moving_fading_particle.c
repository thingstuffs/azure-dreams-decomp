#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "sdk/libgte.h"
#include "dungeon/effect.h"
#include "dungeon/effect/shade/row_quad_colors.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/data.h"

typedef struct ParticleRenderOwner {
    u8 pad_00[0xC];
    void * unk_0C;
} ParticleRenderOwner;

extern s16 D_80026476;
extern void emit_particle_then_wait_for_path_release(void *effect, ObjectPosition *transform, SpriteFrameState *visual);

typedef struct ParticleNode {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 * unk_10;
} ParticleNode;   



typedef struct ParticleState {
    u8 pad_00[0x16];
    s16 angle;
    s16 radius;
    u8 pad_1A[0x2];
    s16 height_offset;
    u8 pad_1E[0x4];
    u16 slot_index;
} ParticleState;   

/* Create the moving particle with display color 0x40E020 and paired trail positions. */
void *create_moving_fading_particle(ObjectPosition *origin, s16 angle, s16 radius, s16 height_offset, ObjectNodeHeader **allocation_head) {
    s16 height;
    u16 slot_index;
    u16 origin_x;
    u16 origin_z;
    u16 origin_y;
    SVECTOR *position_slot;
    SVECTOR *position_table;
    ObjectPosition *positions;
    ObjectNodeHeader *object;
    SVECTOR *paired_slot;
    ParticleState *object_data;

    object = allocate_list_node(0x202, allocation_head);
    if (object != 0) {
        object->update_callback = (void *)emit_particle_then_wait_for_path_release;
        register_node(object, queue_shaded_line_chain);
        positions = object->position;
        positions->x.w.i = (s16) (((u16)(origin->x.w.i)) + ((s32) (rcos(angle) * radius) >> 0xF));
        positions->y.w.i = (s16) (((u16)(origin->y.w.i)) + ((s32) (rsin(angle) * radius) >> 0xF));
        height = ((u16)(origin->z.w.i)) + ((s32) (height_offset << 0x10) >> 0x13);
        positions->z.w.i = height;
        if ((*(s16 *)particle_target_height) < height) {
            positions->z.w.i = (*(s16 *)particle_target_height);
        }
        *((u16 *)&positions->velocity_x + 1) = (u16) ((u16)(origin->x.w.i));
        *((u16 *)&positions->velocity_y + 1) = (u16) ((u16)(origin->y.w.i));
        *((u16 *)&positions->velocity_z + 1) = (u16) ((u16)(origin->z.w.i));
        object_data = (void *) 0x40E020;
        (*(void **)((u8 *)(object->sprite) + 0xC)) = object_data;
        slot_index = (u16)D_80026476;
        object_data = NODE_BODY(object);
        object_data->angle = angle;
        object_data->height_offset = height_offset;
        object_data->radius = radius;
        object_data->slot_index = slot_index;
        if ((s16) slot_index < 0x71) {
            position_table = particle_quad_vertices;
            position_slot = &position_table[(s16) slot_index];
            origin_x = *((u16 *)&positions->velocity_x + 1);
            paired_slot = &position_table[(u32)((s16)slot_index + 16)];
            position_slot->vx = origin_x;
            paired_slot->vx = origin_x;
            origin_y = *((u16 *)&positions->velocity_y + 1);
            position_slot->vy = origin_y;
            paired_slot->vy = origin_y;
            origin_z = *((u16 *)&positions->velocity_z + 1);
            D_80026476 = slot_index + 1;
            position_slot->vz = origin_z;
            paired_slot->vz = origin_z;
        }
    }
    return object;
}
