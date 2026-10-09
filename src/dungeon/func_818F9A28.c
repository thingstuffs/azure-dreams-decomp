#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* The spawned effect's record (the object header precedes it). */
typedef struct SpawnedRecord {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} SpawnedRecord;

extern s32 rand(void);
extern s32 func_80024EDC(void *, void *);
extern void func_8002515C();

/* Retail 818F9A28 (func_80025228): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void func_80025228(
    ObjectNodeHeader *parent,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    ObjectNodeHeader *source_obj = parent;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *spawned;
    SpawnedRecord *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    void *init_data;
    EntityRec *dest_x;
    EntityRec *dest_y;
    EntityRec *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = func_8003FD64(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->unk_10 = (void *)func_8002515C;
        jitter_x = rand() & 0x1F;
        position_x = ((EntityRec *)source_obj->unk_08)->x.w.i;
        dest_x = spawned->unk_08;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((EntityRec *)source_obj->unk_08)->y.w.i;
        dest_y = spawned->unk_08;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        init_data = func_80024EDC;
        jitter_z &= 0x1F;
        position_z = ((EntityRec *)source_obj->unk_08)->z.w.i;
        fields = (SpawnedRecord *)(spawned + 1);
        dest_z = spawned->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        func_8004491C(spawned, (s32)init_data);
        fields->unk_08 = saved_field_28;
    }
}
