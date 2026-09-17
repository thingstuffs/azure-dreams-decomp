#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

extern void func_8003DB94(void *, void *, s16);
extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, s32);
extern u8 D_80024230[];
extern u8 D_80045340[];
extern u8 D_800DEAE0[];

typedef struct S_818A4A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818A4A64_0;   /* temp_v0 in func_818A4A64 */

typedef struct S_818A4A64_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818A4A64_1;   /* temp_s0 in func_818A4A64 */

typedef struct S_818A4A64_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4A64_2;   /* arg1 in func_818A4A64 */

typedef struct S_818A4A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4A64_3;   /* temp_v1 in func_818A4A64 */

/* Creates an object, initializes its rendering state, and copies its position. */
void *func_818A4A64(s32 context_value, S_818A4A64_2 *initial_position) {
    S_818A4A64_1 *render_state;
    S_818A4A64_0 *object;
    S_818A4A64_3 *position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        render_state = object->unk_0C;
        object->unk_10 = (M2C_UNK *) D_80024230;
        object->unk_20 = context_value;
        render_state->unk_0E = 0;
        render_state->unk_0D = 0;
        render_state->unk_0C = 0;
        func_8003DB94(render_state, D_800DEAE0, 0);
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_14 |= 0xC;
        func_8004491C(object, (s32) D_80045340);
        position = object->unk_08;
        position->unk_02 = initial_position->unk_02;
        position->unk_06 = initial_position->unk_06;
        position->unk_0A = initial_position->unk_0A;
        return object;
    }
    return NULL;
}
