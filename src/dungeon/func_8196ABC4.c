#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_node.h"

extern s32 rand(void);
extern s32 func_80024124(PointRecord *, PointPosition *);
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
