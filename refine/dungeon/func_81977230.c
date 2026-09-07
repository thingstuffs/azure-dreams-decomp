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

/* Builds and projects a textured, vertex-colored quad and links it into the ordering table. */
s32 func_81977230(s32 color0, s32 color1, s32 color2, s32 color3) {
    Poly *quad;
    Context *context;
    s16 texture_page;
    register s32 tex_or_link ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 u_or_addr_mask;
    s32 u_right;
    OffsetGlobal *offset_global;
    Scratch *scratch;
    register s32 *ot_entry ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 *offsets;
    u16 *screen0;
    u16 *screen1;
    u16 *screen2;
    register u16 *screen3 ASM_REG("$11");   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *depth_cue;
    void *transform_flags;
    void *vertex0;
    void *vertex1;
    void *vertex2;
    void *vertex3;
    register u32 depth_or_tag_mask ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */

    vertex0 = (void *)0;
    vertex1 = (void *)3;
    context = D_80083160.context;
    vertex2 = (void *)0x300;
    scratch = (Scratch *)0x1F800000;
    scratch->ordering_table = (u8 *)context + 0xB0;
    quad = context->poly;
    context->poly = (Poly *)((u8 *)quad + 0x34);
    quad->bytes[3] = 0xC;
    quad->bytes[7] = 0x3E;
    vertex3 = (void *)0x100;
    texture_page = func_80066460(vertex0, vertex1, vertex2, vertex3);
    screen0 = (u16 *)scratch;
    screen0 = (u16 *)((u32)screen0 | 0x70U);
    screen1 = (u16 *)scratch;
    screen1 = (u16 *)((u32)screen1 | 0x74U);
    screen2 = (u16 *)scratch;
    screen2 = (u16 *)((u32)screen2 | 0x78U);
    screen3 = (u16 *)scratch;
    screen3 = (u16 *)((u32)screen3 | 0x7CU);
    quad->halfwords[0x1A / 2] = texture_page;
    tex_or_link = 0x7DCF;
    ASM_KEEP(tex_or_link);   /* MATCH pin: keeps a statement from moving across a call/branch */
    u_or_addr_mask = 0xC0;
    ASM_KEEP(u_or_addr_mask);   /* MATCH pin: keeps a statement from moving across a call/branch */
    quad->halfwords[0xE / 2] = tex_or_link;
    tex_or_link = 0x40;
    ASM_KEEP(tex_or_link);   /* MATCH pin: keeps a statement from moving across a call/branch */
    u_right = 0xFF;
    ASM_KEEP(u_right);   /* MATCH pin: keeps a statement from moving across a call/branch */
    quad->bytes[0xD] = tex_or_link;
    quad->bytes[0x19] = tex_or_link;
    quad->bytes[0x25] = 0x7F;
    quad->bytes[0x31] = 0x7F;
    quad->bytes[4] = (u8)(color0 >> 0x10);
    quad->bytes[5] = (u8)(color0 >> 8);
    quad->bytes[0x10] = (u8)(color1 >> 0x10);
    quad->bytes[0x11] = (u8)(color1 >> 8);
    quad->bytes[0x1C] = (u8)(color2 >> 0x10);
    quad->bytes[0x1D] = (u8)(color2 >> 8);
    quad->bytes[0x28] = (u8)(color3 >> 0x10);
    quad->bytes[0x29] = (u8)(color3 >> 8);
    quad->bytes[0xC] = (u8)u_or_addr_mask;
    quad->bytes[0x18] = (u8)u_right;
    quad->bytes[0x24] = (u8)u_or_addr_mask;
    quad->bytes[0x30] = (u8)u_right;
    offset_global = &D_80026208;
    quad->bytes[6] = (u8)color0;
    quad->bytes[0x12] = (u8)color1;
    quad->bytes[0x1E] = (u8)color2;
    quad->bytes[0x2A] = (u8)color3;
    offsets = offset_global->values;
    scratch->input[4] = (s16)((scratch->values[0] + offsets[0]) >> 0x10);
    depth_cue = scratch;
    scratch->input[8] = (s16)((scratch->values[4] + offsets[0]) >> 0x10);
    depth_cue = (void *)((u32)depth_cue | 8U);
    scratch->input[12] = (s16)((scratch->values[8] + offsets[0]) >> 0x10);
    transform_flags = scratch;
    scratch->input[16] = (s16)((scratch->values[12] + offsets[0]) >> 0x10);
    transform_flags = (void *)((u32)transform_flags | 0xCU);
    scratch->input[5] = (s16)((scratch->values[1] + offsets[1]) >> 0x10);
    vertex0 = scratch;
    scratch->input[9] = (s16)((scratch->values[5] + offsets[1]) >> 0x10);
    vertex0 = (void *)((u32)vertex0 | 0x10U);
    scratch->input[13] = (s16)((scratch->values[9] + offsets[1]) >> 0x10);
    vertex1 = scratch;
    scratch->input[17] = (s16)((scratch->values[13] + offsets[1]) >> 0x10);
    vertex1 = (void *)((u32)vertex1 | 0x18U);
    scratch->input[6] = (s16)((scratch->values[2] + offsets[2]) >> 0x10);
    vertex2 = scratch;
    scratch->input[10] = (s16)((scratch->values[6] + offsets[2]) >> 0x10);
    vertex2 = (void *)((u32)vertex2 | 0x20U);
    scratch->input[14] = (s16)((scratch->values[10] + offsets[2]) >> 0x10);
    vertex3 = scratch;
    scratch->input[18] = (s16)((scratch->values[14] + offsets[2]) >> 0x10);
    vertex3 = (void *)((u32)vertex3 | 0x28U);
    scratch->ordering_index = func_80065590(vertex0, vertex1, vertex2, vertex3, screen0, screen1, screen2, screen3, depth_cue, transform_flags);
    quad->halfwords[8 / 2] = scratch->output[0];
    quad->halfwords[0xA / 2] = scratch->output[1];
    quad->halfwords[0x14 / 2] = scratch->output[2];
    quad->halfwords[0x16 / 2] = scratch->output[3];
    quad->halfwords[0x20 / 2] = scratch->output[4];
    quad->halfwords[0x22 / 2] = scratch->output[5];
    quad->halfwords[0x2C / 2] = scratch->output[6];
    quad->halfwords[0x2E / 2] = scratch->output[7];
    depth_or_tag_mask = scratch->ordering_index;
    if (depth_or_tag_mask < 0x1E0U) {
        u_or_addr_mask = 0xFFFFFF;
        tex_or_link = depth_or_tag_mask << 2;
        ot_entry = (s32 *)(u32)scratch->ordering_table;
        depth_or_tag_mask = 0xFF000000;
        tex_or_link = tex_or_link + (u32)ot_entry;
        quad->words[0] = (s32)((quad->words[0] & depth_or_tag_mask) | (*(u32 *)tex_or_link & u_or_addr_mask));
        ot_entry = (s32 *)(u32)scratch->ordering_index;
        ot_entry = (s32 *)((u32)ot_entry << 2);
        ot_entry = (s32 *)((u32)ot_entry + (u32)scratch->ordering_table);
        *ot_entry = (*ot_entry & depth_or_tag_mask) | ((s32) quad & u_or_addr_mask);
    }
    return 0;
}
