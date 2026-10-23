#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"

typedef struct ParticleRenderOwner {
    u8 pad_00[0xC];
    void * unk_0C;
} ParticleRenderOwner;

s32 rsin();
s32 rcos();
extern s16 D_80026476;
extern void move_linked_effect_along_path(void *, s32, void *);
extern s32 func_80024ED0(void *, void *, void *);
extern u8 D_800265C8[];
extern u8 D_800269C8[];

typedef struct ParticleNode {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 * unk_10;
} ParticleNode;   



typedef struct ParticleState {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u8 pad_1E[0x4];
    u16 unk_22;
} ParticleState;   

typedef struct TrailPosition {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} TrailPosition;   

typedef struct PairedTrailPosition {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} PairedTrailPosition;   

/* Create the moving particle with display color 0x40E020 and paired trail positions. */
void *create_moving_fading_particle(ObjectPosition *origin, s16 angle, s16 radius, s16 height_offset, ObjectNodeHeader **allocation_head) {
    s16 height;
    u16 slot_index;
    u16 origin_x;
    u16 origin_z;
    u16 origin_y;
    TrailPosition *position_slot;
    u8 *position_table;
    ObjectPosition *positions;
    ObjectNodeHeader *object;
    PairedTrailPosition *paired_slot;
    ParticleState *object_data;

    object = allocate_list_node(0x202, allocation_head);
    if (object != 0) {
        object->unk_10 = (void *)move_linked_effect_along_path;
        register_node(object, (s32)func_80024ED0);
        positions = object->position;
        positions->x.w.i = (s16) (*(u16 *)&origin->x.w.i + ((s32) (rcos(angle) * radius) >> 0xF));
        positions->y.w.i = (s16) (*(u16 *)&origin->y.w.i + ((s32) (rsin(angle) * radius) >> 0xF));
        height = *(u16 *)&origin->z.w.i + ((s32) (height_offset << 0x10) >> 0x13);
        positions->z.w.i = height;
        if ((*(s16 *)D_800269C8) < height) {
            positions->z.w.i = (*(s16 *)D_800269C8);
        }
        *((u16 *)&positions->velocity_x + 1) = (u16) *(u16 *)&origin->x.w.i;
        *((u16 *)&positions->velocity_y + 1) = (u16) *(u16 *)&origin->y.w.i;
        *((u16 *)&positions->velocity_z + 1) = (u16) *(u16 *)&origin->z.w.i;
        object_data = (void *) 0x40E020;
        (*(s32 *)((u8 *)(object->sprite) + 0xC)) = (s32) object_data;
        slot_index = (u16)D_80026476;
        object_data = ((void *)object) + 0x20;
        object_data->unk_16 = angle;
        object_data->unk_1C = height_offset;
        object_data->unk_18 = radius;
        object_data->unk_22 = slot_index;
        if ((s16) slot_index < 0x71) {
            position_table = D_800265C8;
            position_slot = &position_table[(s16) slot_index * 8];
            origin_x = *((u16 *)&positions->velocity_x + 1);
            paired_slot = &position_table[((s16) slot_index + 0x10) * 8];
            position_slot->unk_00 = origin_x;
            paired_slot->unk_00 = origin_x;
            origin_y = *((u16 *)&positions->velocity_y + 1);
            position_slot->unk_02 = origin_y;
            paired_slot->unk_02 = origin_y;
            origin_z = *((u16 *)&positions->velocity_z + 1);
            D_80026476 = slot_index + 1;
            position_slot->unk_04 = origin_z;
            paired_slot->unk_04 = origin_z;
        }
    }
    return object;
}
