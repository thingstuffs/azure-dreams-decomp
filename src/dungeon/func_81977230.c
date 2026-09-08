/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s16 func_80066460();

typedef struct {
    u8 *ordering_table;
    s32 ordering_index;
    s16 input[20];
    s32 values[16];
    u16 output[8];
} Scratch;

typedef union {
    u8 bytes[0x40];
    u16 halfwords[0x20];
    u32 words[0x10];
} Poly;

typedef struct {
    u8 pad[0x8D0];
    Poly *poly;
} Context;

typedef struct {
    s32 *values;
    u8 pad[8];
} OffsetGlobal;

typedef struct {
    Context *context;
    u8 pad[8];
} RootGlobal;

extern OffsetGlobal D_80026208;
extern RootGlobal D_80083160;

s32 func_81977230(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Poly *temp_s4;
    Context *context;
    s16 temp_v0;
    register s32 temp_k ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_c0;
    s32 temp_ff;
    OffsetGlobal *offset_global;
    Scratch *scratch;
    register s32 *temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 *temp_t0;
    u16 *out0;
    u16 *out1;
    u16 *out2;
    register u16 *out3 ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *arg_t2;
    void *arg_t1;
    void *arg_a0;
    void *arg_a1;
    void *arg_a2;
    void *arg_a3;
    register u32 temp_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    arg_a0 = (void *)0;
    arg_a1 = (void *)3;
    context = D_80083160.context;
    arg_a2 = (void *)0x300;
    scratch = (Scratch *)0x1F800000;
    scratch->ordering_table = (u8 *)context + 0xB0;
    temp_s4 = context->poly;
    context->poly = (Poly *)((u8 *)temp_s4 + 0x34);
    temp_s4->bytes[3] = 0xC;
    temp_s4->bytes[7] = 0x3E;
    arg_a3 = (void *)0x100;
    temp_v0 = func_80066460(arg_a0, arg_a1, arg_a2, arg_a3);
    out0 = (u16 *)scratch;
    out0 = (u16 *)((u32)out0 | 0x70U);
    out1 = (u16 *)scratch;
    out1 = (u16 *)((u32)out1 | 0x74U);
    out2 = (u16 *)scratch;
    out2 = (u16 *)((u32)out2 | 0x78U);
    out3 = (u16 *)scratch;
    out3 = (u16 *)((u32)out3 | 0x7CU);
    temp_s4->halfwords[0x1A / 2] = temp_v0;
    temp_k = 0x7DCF;
    ASM_KEEP(temp_k);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_c0 = 0xC0;
    ASM_KEEP(temp_c0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_s4->halfwords[0xE / 2] = temp_k;
    temp_k = 0x40;
    ASM_KEEP(temp_k);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_ff = 0xFF;
    ASM_KEEP(temp_ff);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_s4->bytes[0xD] = temp_k;
    temp_s4->bytes[0x19] = temp_k;
    temp_s4->bytes[0x25] = 0x7F;
    temp_s4->bytes[0x31] = 0x7F;
    temp_s4->bytes[4] = (u8)(arg0 >> 0x10);
    temp_s4->bytes[5] = (u8)(arg0 >> 8);
    temp_s4->bytes[0x10] = (u8)(arg1 >> 0x10);
    temp_s4->bytes[0x11] = (u8)(arg1 >> 8);
    temp_s4->bytes[0x1C] = (u8)(arg2 >> 0x10);
    temp_s4->bytes[0x1D] = (u8)(arg2 >> 8);
    temp_s4->bytes[0x28] = (u8)(arg3 >> 0x10);
    temp_s4->bytes[0x29] = (u8)(arg3 >> 8);
    temp_s4->bytes[0xC] = (u8)temp_c0;
    temp_s4->bytes[0x18] = (u8)temp_ff;
    temp_s4->bytes[0x24] = (u8)temp_c0;
    temp_s4->bytes[0x30] = (u8)temp_ff;
    offset_global = &D_80026208;
    temp_s4->bytes[6] = (u8)arg0;
    temp_s4->bytes[0x12] = (u8)arg1;
    temp_s4->bytes[0x1E] = (u8)arg2;
    temp_s4->bytes[0x2A] = (u8)arg3;
    temp_t0 = offset_global->values;
    scratch->input[4] = (s16)((scratch->values[0] + temp_t0[0]) >> 0x10);
    arg_t2 = scratch;
    scratch->input[8] = (s16)((scratch->values[4] + temp_t0[0]) >> 0x10);
    arg_t2 = (void *)((u32)arg_t2 | 8U);
    scratch->input[12] = (s16)((scratch->values[8] + temp_t0[0]) >> 0x10);
    arg_t1 = scratch;
    scratch->input[16] = (s16)((scratch->values[12] + temp_t0[0]) >> 0x10);
    arg_t1 = (void *)((u32)arg_t1 | 0xCU);
    scratch->input[5] = (s16)((scratch->values[1] + temp_t0[1]) >> 0x10);
    arg_a0 = scratch;
    scratch->input[9] = (s16)((scratch->values[5] + temp_t0[1]) >> 0x10);
    arg_a0 = (void *)((u32)arg_a0 | 0x10U);
    scratch->input[13] = (s16)((scratch->values[9] + temp_t0[1]) >> 0x10);
    arg_a1 = scratch;
    scratch->input[17] = (s16)((scratch->values[13] + temp_t0[1]) >> 0x10);
    arg_a1 = (void *)((u32)arg_a1 | 0x18U);
    scratch->input[6] = (s16)((scratch->values[2] + temp_t0[2]) >> 0x10);
    arg_a2 = scratch;
    scratch->input[10] = (s16)((scratch->values[6] + temp_t0[2]) >> 0x10);
    arg_a2 = (void *)((u32)arg_a2 | 0x20U);
    scratch->input[14] = (s16)((scratch->values[10] + temp_t0[2]) >> 0x10);
    arg_a3 = scratch;
    scratch->input[18] = (s16)((scratch->values[14] + temp_t0[2]) >> 0x10);
    arg_a3 = (void *)((u32)arg_a3 | 0x28U);
    scratch->ordering_index = func_80065590(arg_a0, arg_a1, arg_a2, arg_a3, out0, out1, out2, out3, arg_t2, arg_t1);
    temp_s4->halfwords[8 / 2] = scratch->output[0];
    temp_s4->halfwords[0xA / 2] = scratch->output[1];
    temp_s4->halfwords[0x14 / 2] = scratch->output[2];
    temp_s4->halfwords[0x16 / 2] = scratch->output[3];
    temp_s4->halfwords[0x20 / 2] = scratch->output[4];
    temp_s4->halfwords[0x22 / 2] = scratch->output[5];
    temp_s4->halfwords[0x2C / 2] = scratch->output[6];
    temp_s4->halfwords[0x2E / 2] = scratch->output[7];
    temp_a1 = scratch->ordering_index;
    if (temp_a1 < 0x1E0U) {
        temp_c0 = 0xFFFFFF;
        temp_k = temp_a1 << 2;
        temp_v1 = (s32 *)(u32)scratch->ordering_table;
        temp_a1 = 0xFF000000;
        temp_k = temp_k + (u32)temp_v1;
        temp_s4->words[0] = (s32)((temp_s4->words[0] & temp_a1) | (*(u32 *)temp_k & temp_c0));
        temp_v1 = (s32 *)(u32)scratch->ordering_index;
        temp_v1 = (s32 *)((u32)temp_v1 << 2);
        temp_v1 = (s32 *)((u32)temp_v1 + (u32)scratch->ordering_table);
        *temp_v1 = (*temp_v1 & temp_a1) | ((s32) temp_s4 & temp_c0);
    }
    return 0;
}
