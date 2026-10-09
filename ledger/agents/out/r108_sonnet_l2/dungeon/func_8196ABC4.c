#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_node.h"

/* Three 4-byte slots; only the second halfword of each is used. */
typedef struct EffectPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    u16 pad_08;
    u16 z;
} EffectPosition;

/* The spawned effect's record (the object header precedes it). */
typedef struct SpawnedRecord {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0C[8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} SpawnedRecord;

extern s32 rand(void);
extern s32 func_80024124(void *, void *);
extern void func_80024374(void *);

/* Retail 8196ABC4 (func_800243C4): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..15 in x/y, 0..31 in z) and the given offsets (minus half the jitter range). */
void func_800243C4(ObjectNodeHeader *parent, s32 state_14_value, s32 state_08_value, s32 state_32_value,
                   s16 x_offset, s16 y_offset, s16 z_offset) {
    ObjectNodeHeader *spawned;
    EffectPosition *position;
    SpawnedRecord *state;
    s32 jitter;

    /* the parent's next slot is the list head the new node links behind */
    spawned = func_8003FD64(0x211, (ObjectNodeHeader **)parent);
    if (spawned != 0) {
        spawned->unk_10 = (void *)func_80024374;
        jitter = rand();
        ((EffectPosition *)spawned->unk_08)->x =
            ((EffectPosition *)parent->unk_08)->x +
            (jitter & 0xF) + (x_offset - 8);
        jitter = rand();
        ((EffectPosition *)spawned->unk_08)->y =
            ((EffectPosition *)parent->unk_08)->y +
            (jitter & 0xF) + (y_offset - 8);
        state = (SpawnedRecord *)(spawned + 1);
        jitter = rand();
        position = spawned->unk_08;
        position->z =
            ((EffectPosition *)parent->unk_08)->z +
            (jitter & 0x1F) + (z_offset - 0x10);
        state->unk_14 = state_14_value;
        state->unk_32 = state_32_value;
        func_8004491C(spawned, (s32)func_80024124);
        state->unk_08 = state_08_value;
    }
}
