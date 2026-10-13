#include "shared/entity.h"
#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_node.h"

extern s32 rand(void);
extern s32 func_80024124(PointRecord *, EntityRec *);
extern void func_80024374(void *);

/* Retail 8196ABC4 (func_800243C4): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..15 in x/y, 0..31 in z) and the given offsets (minus half the jitter range). */
void func_800243C4(ObjectNodeHeader *parent, s32 state_14_value, s32 state_08_value, s32 state_32_value,
                   s16 x_offset, s16 y_offset, s16 z_offset) {
    ObjectNodeHeader *spawned;
    EntityRec *position;
    PointRecord *state;
    s32 jitter;

    /* the parent's next slot is the list head the new node links behind */
    spawned = func_8003FD64(0x211, (ObjectNodeHeader **)parent);
    if (spawned != 0) {
        spawned->unk_10 = (void *)func_80024374;
        /* Retail uses unsigned high-half arithmetic; the u16 store also
         * preserves CDK combine/scheduling before the next rand call. */
        jitter = rand();
        *(u16 *)&((EntityRec *)spawned->unk_08)->x.w.i =
            *(u16 *)&((EntityRec *)parent->unk_08)->x.w.i +
            (jitter & 0xF) + (x_offset - 8);
        jitter = rand();
        *(u16 *)&((EntityRec *)spawned->unk_08)->y.w.i =
            *(u16 *)&((EntityRec *)parent->unk_08)->y.w.i +
            (jitter & 0xF) + (y_offset - 8);
        state = (PointRecord *)(spawned + 1);
        jitter = rand();
        position = spawned->unk_08;
        *(u16 *)&position->z.w.i =
            *(u16 *)&((EntityRec *)parent->unk_08)->z.w.i +
            (jitter & 0x1F) + (z_offset - 0x10);
        state->unk_14 = state_14_value;
        state->brightness = state_32_value;
        func_8004491C(spawned, (s32)func_80024124);
        state->color = state_08_value;
    }
}
