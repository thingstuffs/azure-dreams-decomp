#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024370;
extern M2C_UNK D_80024E40;
extern M2C_UNK D_80045340;

typedef struct S_8002441C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_8002441C_0;   /* temp_v0 in func_8002441C */

typedef struct S_8002441C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002441C_1;   /* temp_s0 in func_8002441C */

typedef struct S_8002441C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002441C_2;   /* temp_v1 in func_8002441C */

typedef struct S_8002441C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002441C_3;   /* arg1 in func_8002441C */

/* Creates an object with initialized display settings and a copy of the supplied state. */
void *func_8002441C(s32 object_id, S_8002441C_3 *initial_state) {
    S_8002441C_1 *display;
    S_8002441C_0 *object;
    S_8002441C_2 *state;
    register void *result ASM_REG("$2");

    object = func_8003FC64(0x212);
    if (object == 0) {
        result = 0;
    } else {
        object->unk_10 = &D_80024370;
        display = object->unk_0C;
        object->unk_20 = object_id;
        object->unk_24 = 0;
        display->unk_0E = 0x80;
        display->unk_0D = 0x80;
        display->unk_0C = 0x80;
        display->unk_0E = 0xC0;
        func_8003DB94(display, &D_80024E40, 0);
        display->unk_1C = 0x2000;
        display->unk_1E = 0x1000;
        display->unk_12 = 0x7DCF;
        display->unk_14 = (u16)(display->unk_14 | 0xC);
        display->unk_10 = (u16)(display->unk_10 | 0x20);
        display->unk_14 = (u16)(display->unk_14 | 0x100);
        func_8004491C(object, &D_80045340);
        state = object->unk_08;
        state->unk_00 = initial_state->unk_00;
        state->unk_04 = initial_state->unk_04;
        state->unk_08 = initial_state->unk_08;
        state->unk_0C = initial_state->unk_0C;
        state->unk_10 = initial_state->unk_10;
        state->unk_14 = initial_state->unk_14;
        result = object;
    }
    return result;
}
