#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Copy24 {
    s32 words[6];
} Copy24;

extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_8002420C;
extern s32 D_80045340;
extern s32 D_800E2178;

typedef struct S_81892AF0_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81892AF0_0;   /* temp_v0 in func_81892AF0 */

typedef struct S_81892AF0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_81892AF0_1;   /* temp_v0_2 in func_81892AF0 */

typedef struct S_81892AF0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_81892AF0_2;   /* temp_s0 in func_81892AF0 */

typedef struct S_81892AF0_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_81892AF0_3;   /* temp_a1 in func_81892AF0 */

/* Creates a sprite object with initialized state and a copied, adjusted transform. */
void *func_81892AF0(s32 state_value, Copy24 *source_transform, s16 variant) {
    Copy24 *transform;
    S_81892AF0_2 *sprite;
    void *object;
    S_81892AF0_1 *state;
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    object = func_8003FC64(0x212);
    result = NULL;
    if (object != NULL) {
        ((S_81892AF0_0 *)object)->unk_10 = &D_8002420C;
        state = object + 0x20;
        ((S_81892AF0_0 *)object)->unk_20 = state_value;
        state->unk_04 = 0;
        state->unk_06 = variant;
        sprite = ((S_81892AF0_0 *)object)->unk_0C;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        func_8003DB94(sprite, &D_800E2178, 0);
        sprite->unk_1E = 0x1800;
        sprite->unk_1C = 0x1800;
        func_8004491C(object, &D_80045340);
        transform = ((S_81892AF0_0 *)object)->unk_08;
        result = object;
        *transform = *source_transform;
        ((S_81892AF0_3 *)transform)->unk_14 = 0x10000;
        ((S_81892AF0_3 *)transform)->unk_08 += 0xFD010000;
    }
    return result;
}
