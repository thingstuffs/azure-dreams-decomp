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

void func_8196096C(s32 arg0, Input *arg1, Input *arg2, s32 arg3) {
    Root *root = D_80083160;
    Record *record;
    Record *tail_arg;
    Input *input = arg2;
    Globals *globals;
    TableEntry *table;
    Scratch *scratch;
    register void *call_a0;
    register void *call_a1;
    register s32 *mmio ASM_REG("$1");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 saved_arg0 ASM_REG("$21") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *config;
    u16 tail_value14;
    s32 tail_color;
    s32 shade;
    register s32 coord ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    do { record = root->record; } while (0);
    globals = (Globals *)&D_80083160;
    mmio = (s32 *)0x1F800000;
    mmio[8] = arg3;
    table = globals->table;
    func_800649A0();
    ASM_KEEP_NV(globals);   /* MATCH pin: keeps a statement from moving across a call/branch */
    call_a0 = (void *)0x1F800028;
    call_a1 = (void *)0x1F800050;
    ASM_KEEP_NV(call_a0);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_KEEP_NV(call_a1);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_SET(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = (Scratch *)0x1F800000;
    scratch->w6C = 0;
    scratch->w68 = 0;
    scratch->w64 = 0;
    scratch->h2C = 0;
    scratch->h2A = 0;
    scratch->h28 = 0;
    func_80065820(call_a0, call_a1);
    func_80064D80(&scratch->w50);
    func_80064CF0(&scratch->w50);
    scratch->h8C = 0x800;
    scratch->h84 = 0x800;
    scratch->h7C = 0x800;
    scratch->h74 = 0x800;
    if (input != 0) {
        scratch->w70 = table[input->index0].value;
        scratch->w78 = table[input->index1].value;
        scratch->w80 = table[input->index2].value;
        scratch->w88 = table[input->index3].value;
        record->fC.w = input->value8;
        record->f14.w = input->valueC;
        record->f1C.h[0] = input->value12;
        tail_color = 0x808080;
        tail_value14 = input->value14;
        ASM_KEEP_DEP_NV(record, tail_value14);   /* MATCH pin: retail keeps a computation the compiler would drop */
        tail_arg = record;
        ASM_KEEP_NV(record);   /* MATCH pin: retail register colouring depends on it */
        record->f4.w = tail_color;
        record->f24.h[0] = tail_value14;
        func_8002638C(tail_arg);
    }

    scratch->w78 = 0x40;
    scratch->w70 = 0;
    scratch->w80 = 0x400000;
    scratch->w88 = 0x400040;
    config = D_80027374;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    record->f14.h[1] = *(u16 *)(config + 4);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    record->fC.h[1] = *(u16 *)(config + 6);
    record->f1C.b[0] = config[8];
    record->fC.b[0] = record->f1C.b[0];
    record->f24.b[0] = config[8] + config[10];
    record->f14.b[0] = record->f24.b[0];
    record->f14.b[1] = config[9];
    record->fC.b[1] = record->f14.b[1];
    record->f24.b[1] = config[9] + config[11];
    record->f1C.b[1] = record->f24.b[1];
    shade = (D_800273A8 << 7) / 240;
    *(volatile u8 *)&record->f4.b[0] = shade;
    *(volatile u8 *)&record->f4.b[2] = shade;
    *(volatile u8 *)&record->f4.b[1] = shade;
    ASM_KEEP_NV(scratch);   /* MATCH pin: retail immediate-load split depends on it */
    func_800666F4(record);
    func_800654B0((void *)((u32)scratch | 0x70),
                  (void *)((u32)scratch | 0x78),
                  (void *)((u32)scratch | 0x80),
                  (void *)((u32)scratch | 0x88),
                  &record->f8.h[0], &record->f10.h[0],
                  &record->f18.h[0], &record->f20.h[0],
                  &scratch->w90, &scratch->w94);

    coord = record->f8.h[0];
    coord -= 0xA0;
    record->f8.h[0] = arg1->index0 + coord;
    coord = record->f18.h[0];
    coord -= 0xA0;
    record->f18.h[0] = arg1->index0 + coord;
    coord = record->f10.h[0];
    coord -= 0xA0;
    record->f10.h[0] = arg1->index0 + coord;
    coord = record->f20.h[0];
    coord -= 0xA0;
    record->f20.h[0] = arg1->index0 + coord;
    {
        s32 coord_y;
        ASM_SET(coord_y);   /* MATCH pin: load-bearing for the whole function shape */
        coord_y = record->f8.h[1];
        coord_y -= 0x78;
        coord_y += arg1->index1 + saved_arg0;
        record->f8.h[1] = coord_y;
        coord_y = record->f10.h[1];
        coord_y -= 0x78;
        coord_y += arg1->index1 + saved_arg0;
        record->f10.h[1] = coord_y;
        coord_y = record->f18.h[1];
        coord_y -= 0x78;
        coord_y += arg1->index1 + saved_arg0;
        record->f18.h[1] = coord_y;
        coord_y = record->f20.h[1];
        coord_y -= 0x78;
        coord_y += arg1->index1 + saved_arg0;
        record->f20.h[1] = coord_y;
    }
    func_8006658C(scratch->arg3, record);
    func_80064A40();
    record = (Record *)((u8 *)record + 0x28);
    globals->root->record = record;
}
