#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C5214_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA8];
    s32 unk_BC;
} S_800C5214_0;   /* object in func_800C5214 */

typedef struct S_800C5214_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C5214_1;   /* part in func_800C5214 */



extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800C52B8(s32);
extern u8 D_800345B8[];
extern u8 D_800C52D0[];
extern u8 D_800F148C[];

void *func_800C5214(s32 arg0)
{
    S_800C5214_1 *part;
    S_800C5214_0 *object;

    object = func_8003FC64(0x136);
    if (object == NULL) {
        return NULL;
    }

    {
        register void *result ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
        register u16 flags ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 value ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

        object->unk_10 = D_800C52D0;
        object->unk_BC = arg0;
        part = object->unk_0C;
        part->unk_1E = 0x1800;
        part->unk_1C = 0x1800;
        part->unk_0E = 0x4C;
        part->unk_0D = 0x4C;
        part->unk_0C = 0x4C;
        part->unk_08 = D_800F148C;
        part->unk_00 = 0;
        part->unk_04 = 0;
        part->unk_05 = 0;
        part->unk_06 = -0x10;
        func_8004491C(object, D_800345B8);
        result = object;
        ASM_KEEP(result);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        flags = part->unk_14;
        value = 0x20;
        part->unk_10 = value;
        part->unk_14 = flags | 0x1C;
        return func_800C52B8(value);
    }
}

/* MECHANISM: The NULL guard preserves retail's beqz into a trailing literal-zero return.
   Returning the s32 func_800C52B8 result exposes LEAD-22's tail shape, converting jal to j
   while retaining the flags store in its delay slot; v0/v1/a0 pins preserve the live roles. */
