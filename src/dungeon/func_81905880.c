#include "modules/dungeon_ovl_1924800.h"

/* Three 4-byte slots; only the second halfword of each is used. */

/* The spawned effect's record (the object header precedes it). */

/* Retail 81905880 (func_80025080): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void func_80025080(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
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
        spawned->unk_10 = (void *)func_80024FB4;
        jitter_x = rand() & 0x1F;
        position_x = ((EffectPosition *)source_obj->unk_08)->spawn.x;
        dest_x = spawned->unk_08;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->spawn.x = position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((EffectPosition *)source_obj->unk_08)->spawn.y;
        dest_y = spawned->unk_08;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->spawn.y = position_y;

        jitter_z = rand();
        jitter_z &= 0x1F;
        position_z = ((EffectPosition *)source_obj->unk_08)->spawn.z;
        fields = (SpawnedRecord *)(spawned + 1);
        dest_z = spawned->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->spawn.z = position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        func_8004491C(spawned, (s32)func_80024D64);
        fields->unk_08 = saved_field_28;
    }
}
