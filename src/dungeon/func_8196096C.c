#include "common.h"

typedef union {
    s32 w;
    u16 h[2];
    u8 b[4];
} Word;

typedef struct {
    Word f0;
    Word f4;
    Word f8;
    Word fC;
    Word f10;
    Word f14;
    Word f18;
    Word f1C;
    Word f20;
    Word f24;
} Record;

typedef struct {
    u16 index0;
    u16 index1;
    u16 index2;
    u16 index3;
    s32 value8;
    s32 valueC;
    u16 value10;
    u16 value12;
    u16 value14;
} Input;

typedef struct {
    u8 pad0[0x20];
    s32 arg3;
    u8 pad24[4];
    u16 h28;
    u16 h2A;
    u16 h2C;
    u8 pad2E[0x22];
    s32 w50;
    u8 pad54[0x10];
    s32 w64;
    s32 w68;
    s32 w6C;
    s32 w70;
    u16 h74;
    u16 pad76;
    s32 w78;
    u16 h7C;
    u16 pad7E;
    s32 w80;
    u16 h84;
    u16 pad86;
    s32 w88;
    u16 h8C;
    u16 pad8E;
    s32 w90;
    s32 w94;
} Scratch;

typedef struct {
    u8 pad0[0x8D0];
    Record *record;
} Root;

typedef struct {
    Root *root;
    u8 pad4[0x1E0];
    struct TableEntry *table;
} Globals;

typedef struct TableEntry {
    s32 value;
    s32 pad;
} TableEntry;

extern Root *D_80083160;
extern u8 D_80027374[12];
extern u8 D_800273A8;

extern void func_8002638C() __attribute__((noreturn));
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064CF0(void *arg0);
extern void func_80064D80(void *arg0);
extern void func_800654B0(void *arg0, void *arg1, void *arg2, void *arg3,
                           u16 *arg4, u16 *arg5, u16 *arg6, u16 *arg7,
                           s32 *arg8, s32 *arg9);
extern void func_80065820(void *arg0, void *arg1);
extern void func_8006658C(s32 arg0, Record *record);
extern void func_800666F4(Record *record);

/* Builds and submits a shaded textured quad at the requested screen position. */
void func_8196096C(s32 y_offset, Input *origin, Input *quad_data, s32 draw_depth) {
    Root *root = D_80083160;
    Record *record;
    Record *quad_packet;
    Input *quad_input = quad_data;
    Globals *globals;
    TableEntry *vertex_table;
    Scratch *scratch;
    register void *rotation;
    register void *matrix;
    register s32 *scratch_words ASM_REG("$1");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 saved_y_offset ASM_REG("$21") = y_offset;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *texture_config;
    u16 corner_uv;
    s32 neutral_color;
    s32 shade;
    register s32 coord_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    do { record = root->record; } while (0);
    globals = (Globals *)&D_80083160;
    scratch_words = (s32 *)0x1F800000;
    scratch_words[8] = draw_depth;
    vertex_table = globals->table;
    func_800649A0();
    ASM_KEEP_NV(globals);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    rotation = (void *)0x1F800028;
    matrix = (void *)0x1F800050;
    ASM_KEEP_NV(rotation);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(matrix);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_SET(scratch);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch = (Scratch *)0x1F800000;
    scratch->w6C = 0;
    scratch->w68 = 0;
    scratch->w64 = 0;
    scratch->h2C = 0;
    scratch->h2A = 0;
    scratch->h28 = 0;
    func_80065820(rotation, matrix);
    func_80064D80(&scratch->w50);
    func_80064CF0(&scratch->w50);
    scratch->h8C = 0x800;
    scratch->h84 = 0x800;
    scratch->h7C = 0x800;
    scratch->h74 = 0x800;
    if (quad_input != 0) {
        scratch->w70 = vertex_table[quad_input->index0].value;
        scratch->w78 = vertex_table[quad_input->index1].value;
        scratch->w80 = vertex_table[quad_input->index2].value;
        scratch->w88 = vertex_table[quad_input->index3].value;
        record->fC.w = quad_input->value8;
        record->f14.w = quad_input->valueC;
        record->f1C.h[0] = quad_input->value12;
        neutral_color = 0x808080;
        corner_uv = quad_input->value14;
        ASM_KEEP_DEP_NV(record, corner_uv);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        quad_packet = record;
        ASM_KEEP_NV(record);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        record->f4.w = neutral_color;
        record->f24.h[0] = corner_uv;
        func_8002638C(quad_packet);
    }

    scratch->w78 = 0x40;
    scratch->w70 = 0;
    scratch->w80 = 0x400000;
    scratch->w88 = 0x400040;
    texture_config = D_80027374;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    record->f14.h[1] = *(u16 *)(texture_config + 4);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    record->fC.h[1] = *(u16 *)(texture_config + 6);
    record->f1C.b[0] = texture_config[8];
    record->fC.b[0] = record->f1C.b[0];
    record->f24.b[0] = texture_config[8] + texture_config[10];
    record->f14.b[0] = record->f24.b[0];
    record->f14.b[1] = texture_config[9];
    record->fC.b[1] = record->f14.b[1];
    record->f24.b[1] = texture_config[9] + texture_config[11];
    record->f1C.b[1] = record->f24.b[1];
    shade = (D_800273A8 << 7) / 240;
    *(volatile u8 *)&record->f4.b[0] = shade;
    *(volatile u8 *)&record->f4.b[2] = shade;
    *(volatile u8 *)&record->f4.b[1] = shade;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    func_800666F4(record);
    func_800654B0((void *)((u32)scratch | 0x70),
                  (void *)((u32)scratch | 0x78),
                  (void *)((u32)scratch | 0x80),
                  (void *)((u32)scratch | 0x88),
                  &record->f8.h[0], &record->f10.h[0],
                  &record->f18.h[0], &record->f20.h[0],
                  &scratch->w90, &scratch->w94);

    coord_x = record->f8.h[0];
    coord_x -= 0xA0;
    record->f8.h[0] = origin->index0 + coord_x;
    coord_x = record->f18.h[0];
    coord_x -= 0xA0;
    record->f18.h[0] = origin->index0 + coord_x;
    coord_x = record->f10.h[0];
    coord_x -= 0xA0;
    record->f10.h[0] = origin->index0 + coord_x;
    coord_x = record->f20.h[0];
    coord_x -= 0xA0;
    record->f20.h[0] = origin->index0 + coord_x;
    {
        s32 coord_y;
        ASM_SET(coord_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coord_y = record->f8.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f8.h[1] = coord_y;
        coord_y = record->f10.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f10.h[1] = coord_y;
        coord_y = record->f18.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f18.h[1] = coord_y;
        coord_y = record->f20.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f20.h[1] = coord_y;
    }
    func_8006658C(scratch->arg3, record);
    func_80064A40();
    record = (Record *)((u8 *)record + 0x28);
    globals->root->record = record;
}
