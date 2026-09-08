#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_8004B248();                      /* extern */
s32 func_800B677C();                             /* extern */
M2C_UNK func_800B691C(); /* extern */
s32 func_800B6990();                 /* extern */
extern M2C_UNK D_8004CAA0;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_800B6754;


typedef struct S_800B6A0C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800B6A0C_0;   /* var_s0 in func_800B6A0C */

typedef struct S_800B6A0C_1 {
    u8 pad_00[0x94];
    s32 unk_94;
    s32 unk_98;
} S_800B6A0C_1;   /* temp_s1 in func_800B6A0C */

/* Allocate and initialize an object, marking it for cleanup if setup fails. */
void *func_800B6A0C(s32 resource_id, M2C_UNK slot_index, M2C_UNK x, s32 y, s32 z) {
    S_800B6A0C_1 *state;
    void *object;

    object = func_8003FC64(0);
    state = object + 0x20;
    if (object != NULL) {
        if (func_800B6990(state, 0x18) != 0) {
            ((S_800B6A0C_0 *)object)->unk_0C = (void *) (object + 0xA8);
            state->unk_94 = func_800B677C(state->unk_98);
            func_800B691C(state, resource_id, slot_index, x, y, z);
            ((S_800B6A0C_0 *)object)->unk_10 = &D_800B6754;
            func_8004491C(object, &D_8004CAA0);
            return object;
        }
        func_8004B248(object + 0xBC);
        ((S_800B6A0C_0 *)object)->unk_1E = (u16) (((S_800B6A0C_0 *)object)->unk_1E | 0x8000);
        object = NULL;
        D_800814A0 = (s32) (D_800814A0 | 0x8000);
    }
    return object;
}
