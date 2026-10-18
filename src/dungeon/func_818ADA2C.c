#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct ParticleRenderOwner {
    u8 pad_00[0xC];
    void * unk_0C;
} ParticleRenderOwner;


s32 func_800644B8();
s32 func_80064584();
extern s16 D_80026476;
extern void move_linked_effect_along_path(void *, s32, void *);
extern s32 func_80024ED0(void *, void *, void *);
extern u8 D_800265C8[];
extern u8 D_800269C8[];

typedef struct ParticleNode {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} ParticleNode;   

typedef struct ParticlePositions {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} ParticlePositions;   

typedef struct ParticleOrigin {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} ParticleOrigin;

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
void *create_moving_fading_particle(ParticleOrigin *origin, s16 angle, s16 radius, s16 height_offset, ObjectNodeHeader **allocation_head) {
    s16 height;
    u16 slot_index;
    u16 origin_x;
    u16 origin_z;
    u16 origin_y;
    TrailPosition *position_slot;
    u8 *position_table;
    ParticlePositions *positions;
    void *object;
    PairedTrailPosition *paired_slot;
    ParticleState *object_data;

    object = func_8003FD64(0x202, allocation_head);
    if (object != NULL) {
        ((ParticleNode *)object)->unk_10 = (void *)move_linked_effect_along_path;
        func_8004491C(object, (s32)func_80024ED0);
        positions = ((ParticleNode *)object)->unk_08;
        positions->unk_02 = (s16) (origin->unk_02 + ((s32) (func_80064584(angle) * radius) >> 0xF));
        positions->unk_06 = (s16) (origin->unk_06 + ((s32) (func_800644B8(angle) * radius) >> 0xF));
        height = origin->unk_0A + ((s32) (height_offset << 0x10) >> 0x13);
        positions->unk_0A = height;
        if ((*(s16 *)D_800269C8) < height) {
            positions->unk_0A = (*(s16 *)D_800269C8);
        }
        positions->unk_0E = (u16) origin->unk_02;
        positions->unk_12 = (u16) origin->unk_06;
        positions->unk_16 = (u16) origin->unk_0A;
        object_data = (void *) 0x40E020;
        (*(s32 *)((u8 *)(((ParticleRenderOwner *)object)->unk_0C) + 0xC)) = (s32) object_data;
        slot_index = (u16)D_80026476;
        object_data = object + 0x20;
        object_data->unk_16 = angle;
        object_data->unk_1C = height_offset;
        object_data->unk_18 = radius;
        object_data->unk_22 = slot_index;
        if ((s16) slot_index < 0x71) {
            position_table = D_800265C8;
            position_slot = &position_table[(s16) slot_index * 8];
            origin_x = positions->unk_0E;
            paired_slot = &position_table[((s16) slot_index + 0x10) * 8];
            position_slot->unk_00 = origin_x;
            paired_slot->unk_00 = origin_x;
            origin_y = positions->unk_12;
            position_slot->unk_02 = origin_y;
            paired_slot->unk_02 = origin_y;
            origin_z = positions->unk_16;
            D_80026476 = slot_index + 1;
            position_slot->unk_04 = origin_z;
            paired_slot->unk_04 = origin_z;
        }
    }
    return object;
}
