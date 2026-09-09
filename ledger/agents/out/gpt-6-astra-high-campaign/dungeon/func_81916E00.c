#include "common.h"



typedef s32 M2C_UNK;
typedef struct Copy24 {
    s32 words[6];
} Copy24;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003DB94();
void *func_8003FD64();
M2C_UNK func_8004491C();
extern M2C_UNK D_8002457C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC50;

typedef struct S_80024600_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_80024600_0;   /* temp_v0 in func_80024600 */

typedef struct S_80024600_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024600_1;   /* temp_s0 in func_80024600 */

/* Creates an object with default rendering settings and copies its initial data. */
void *func_80024600(s32 *owner_data, Copy24 *initial_data) {
    s32 owner_value;
    S_80024600_1 *render_state;
    S_80024600_0 *object;
    Copy24 *object_data;
    register void *result ASM_REG("$2");

    object = func_8003FD64(0x212, (s8 *) owner_data - 0x20);
    if (object == NULL) {
        result = NULL;
    } else {
        object->unk_10 = &D_8002457C;
        owner_value = *owner_data;
        render_state = object->unk_0C;
        object->unk_24 = 0;
        object->unk_20 = owner_value;
        render_state->unk_0C = 0x808080;
        render_state->unk_12 = 0x7DCF;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x100);
        func_8003DB94(render_state, &D_800DEC50, 0);
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        func_8004491C(object, &D_80045340);
        object_data = object->unk_08;
        *object_data = *initial_data;
        result = object;
    }
    return result;
}
