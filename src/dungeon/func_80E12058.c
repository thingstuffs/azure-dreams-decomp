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

void *func_80175858(void *arg0, Copy24 *arg1, void *arg2) {
    void *temp_a0;
    void *temp_a2;
    void *temp_v0;
    void *temp_v1;
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *arg0_hold = arg0;
    Copy24 *arg1_hold = arg1;
    void *arg2_hold = arg2;

    ASM_KEEP_NV(arg0_hold);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg1_hold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg2_hold);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_v0 = func_8003FC64(0x312);
    if (temp_v0 != NULL) {
        goto allocated;
    }
    result = NULL;
    goto done;
allocated:
    ((S_80175858_0 *)temp_v0)->unk_10 = &D_8017573C;
    func_8004491C(temp_v0, &D_80045340);
    temp_a2 = temp_v0 + 0x20;
    ASM_KEEP_NV(temp_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80175858_1 *)temp_a2)->unk_04.s =
        (u16)((S_80175858_2 *)arg0_hold)->unk_2A;
    temp_a0 = ((S_80175858_0 *)temp_v0)->unk_0C;
    ((S_80175858_3 *)temp_a0)->unk_28 =
        ((S_80175858_4 *)arg2_hold)->unk_28;
    temp_a1 = ((S_80175858_4 *)arg2_hold)->unk_12;
    ((S_80175858_3 *)temp_a0)->unk_1E = 0x800;
    ((S_80175858_3 *)temp_a0)->unk_1C = 0x800;
    ((S_80175858_3 *)temp_a0)->unk_0C = 0x808080;
    (*(u16 *)((u8 *)temp_a0 + 0x12)) = temp_a1;
    func_80047784(
        temp_a0,
        D_80176498[
            ((D_80083228 + ((S_80175858_1 *)temp_a2)->unk_04.u + 0x100) >> 9) &
            7],
        0);
    temp_v1 = ((S_80175858_0 *)temp_v0)->unk_08;
    result = temp_v0;
    *(Copy24 *)temp_v1 = *arg1_hold;
done:
    return result;
}

/* MECHANISM: True-space CFG plus one v0 result carrier preserves bnez/local-j/zero-delay.
   Guarded s1/s3/s2 argument holds reproduce the 0x28 frame and exact save scatter.
   Byte-table typing and an early a1 halfword lifetime remove scaling and load-delay drift.
   Holding the copy destination in v1 before v0 yields retail's packed 24-byte copy order. */
