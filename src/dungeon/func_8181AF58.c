#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_node.h"

/* Three 4-byte slots; only the second halfword of each is used. */
typedef struct EffectPosition {
    u16 pad_00;
    s16 x;
    u16 pad_04;
    s16 y;
    u16 pad_08;
    s16 z;
} EffectPosition;

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
extern s32 func_800241EC(void *, void *);
extern void func_80024604();

/* Retail 8181AF58 (func_80024758): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void func_80024758(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
                   s16 offset_y, s16 offset_z) {
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
    EffectPosition *dest_x;
    EffectPosition *dest_y;
    EffectPosition *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = func_8003FD64(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->unk_10 = (void *)func_80024604;
        jitter_x = rand() & 0x1F;
        position_x = ((EffectPosition *)source_obj->unk_08)->x;
        dest_x = spawned->unk_08;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x = position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((EffectPosition *)source_obj->unk_08)->y;
        dest_y = spawned->unk_08;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y = position_y;

        jitter_z = rand();
        jitter_z &= 0x1F;
        position_z = ((EffectPosition *)source_obj->unk_08)->z;
        fields = (SpawnedRecord *)(spawned + 1);
        dest_z = spawned->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z = position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        func_8004491C(spawned, (s32)func_800241EC);
        fields->unk_08 = saved_field_28;
    }
}
