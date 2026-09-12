#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_80175858_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80175858_0;   /* temp_v0 in func_80175858 */

typedef struct S_80175858_1 {
    u8 pad_00[0x4];
    union { u16 s; s16 u; } unk_04;   /* accessed as both */
} S_80175858_1;   /* temp_a2 in func_80175858 */

typedef struct S_80175858_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80175858_2;   /* arg0_hold in func_80175858 */

typedef struct S_80175858_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80175858_3;   /* temp_a0 in func_80175858 */

typedef struct S_80175858_4 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80175858_4;   /* arg2_hold in func_80175858 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 words[6];
} Copy24;

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
void func_80047784(void *, u8, s32);
extern u8 D_80045340;
extern s16 D_80083228;
extern u8 D_8017573C;
extern u8 D_80176498[];

/* Allocate and initialize an object with source direction, render properties, and copied data. */
void *func_80175858(void *direction_src, Copy24 *initial_data, void *render_src) {
    void *render_data;
    void *object_state;
    void *object;
    void *data_dst;
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 render_attr ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *direction_ref = direction_src;
    Copy24 *data_src = initial_data;
    void *render_ref = render_src;

    object = func_8003FC64(0x312);
    if (object != NULL) {
        goto allocated;
    }
    result = NULL;
    goto done;
allocated:
    ((S_80175858_0 *)object)->unk_10 = &D_8017573C;
    func_8004491C(object, &D_80045340);
    object_state = object + 0x20;
    ASM_KEEP_NV(object_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80175858_1 *)object_state)->unk_04.s =
        (u16)((S_80175858_2 *)direction_ref)->unk_2A;
    render_data = ((S_80175858_0 *)object)->unk_0C;
    ((S_80175858_3 *)render_data)->unk_28 =
        ((S_80175858_4 *)render_ref)->unk_28;
    render_attr = ((S_80175858_4 *)render_ref)->unk_12;
    ((S_80175858_3 *)render_data)->unk_1E = 0x800;
    ((S_80175858_3 *)render_data)->unk_1C = 0x800;
    ((S_80175858_3 *)render_data)->unk_0C = 0x808080;
    (*(u16 *)((u8 *)render_data + 0x12)) = render_attr;
    func_80047784(
        render_data,
        D_80176498[
            ((D_80083228 + ((S_80175858_1 *)object_state)->unk_04.u + 0x100) >> 9) &
            7],
        0);
    data_dst = ((S_80175858_0 *)object)->unk_08;
    result = object;
    *(Copy24 *)data_dst = *data_src;
done:
    return result;
}
