#include "common.h"

#ifndef NULL
#define NULL 0
#endif


extern void func_8002488C() __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 D_80024648;
extern s32 D_80046398;
extern s32 D_800814A0;
extern u8 D_8008333C[32];


typedef struct S_8195EF44_0 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8195EF44_0;   /* map in func_8195EF44 */

typedef struct S_8195EF44_1 {
    u8 pad_00[0x333C];
    u16 * unk_333C;
} S_8195EF44_1;   /* page in func_8195EF44 */

typedef struct S_8195EF44_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_8195EF44_2;   /* work in func_8195EF44 */

typedef struct S_8195EF44_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8195EF44_3;   /* global_page in func_8195EF44 */

typedef struct S_8195EF44_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195EF44_4;   /* render in func_8195EF44 */

typedef struct S_8195EF44_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    u8 pad_3E[0xE];
    s16 unk_4C;
    u8 pad_4E[0x12];
    s16 unk_60;
    s16 unk_62;
} S_8195EF44_5;   /* coord in func_8195EF44 */

/* Allocate and initialize an object using the map cell at the supplied position. */
void *func_8195EF44(s16 world_x, s16 world_y, s16 world_z, s16 coord_60)
{
    s16 saved_x = world_x;
    s16 saved_y = world_y;
    s16 saved_z = world_z;
    s16 saved_coord_60 = coord_60;
    void *obj;
    S_8195EF44_2 *work;
    register u8 *map ASM_REG("$21");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u8 *page ASM_REG("$22");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *field_addr;
    void *call_addr;
    void *call_obj;
    void *render;
    u8 *coord;
    s32 color;
    u16 *cells;
    u16 cell;
    s32 obj_flags;
    s32 global_flags;
    register void *zero_return ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
    register u8 *global_page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 cell_x;
    register s32 cell_index ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 shifted_coord ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */

    obj = func_8003FC64(2);
    page = (u8 *)0x80080000;
    ASM_KEEP(page);   /* MATCH pin: retail immediate-load split depends on it */
    map = page + 0x333C;
    if (obj == NULL) {
        goto done;
    }

    ASM_KEEP(map);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    work = (*(void * *)((u8 *)obj + 0xC));
    shifted_coord = (s32)((u32)(u16)saved_x << 16);
    cell_x = shifted_coord >> 16;
    if (cell_x < 0) {
        cell_x += 0x3F;
    }
    shifted_coord = (s32)((u32)(u16)saved_y << 16);
    cell_index = shifted_coord >> 16;
    cell_x >>= 6;
    if (cell_index < 0) {
        cell_index += 0x3F;
    }
    cell_index >>= 6;
    cell_index <<= ((S_8195EF44_0 *)map)->unk_14;
    cell_index = cell_x + cell_index;
    cells = ((S_8195EF44_1 *)page)->unk_333C;
    cell = cells[cell_index * 3];
    work->unk_08 = cell;

    if (cell != 0) {
        goto nonzero;
    }

    zero_return = NULL;
    ASM_KEEP(zero_return);   /* MATCH pin: retail basic-block layout depends on it */
    global_page = (u8 *)0x80080000;
    ASM_KEEP(global_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    obj_flags = (*(u16 *)((u8 *)obj + 0x1E));
    global_flags = ((S_8195EF44_3 *)global_page)->unk_14A0;
    obj_flags |= 0x8000;
    global_flags |= 0x8000;
    (*(u16 *)((u8 *)obj + 0x1E)) = obj_flags;
    ((S_8195EF44_3 *)global_page)->unk_14A0 = global_flags;
    func_8002488C(obj_flags, global_flags);

nonzero:
    call_obj = obj;
    ASM_KEEP(call_obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    field_addr = &D_80024648;
    ASM_KEEP(field_addr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_addr = &D_80046398;
    (*(void * *)((u8 *)obj + 0x10)) = field_addr;
    func_8004491C(call_obj, call_addr);

    color = 0x808080;
    render = (*(void * volatile *)((u8 *)obj + 8));
    ASM_CLOBBER("$3");   /* MATCH pin: retail basic-block layout depends on it */
    coord = (u8 *)obj + 0x20;
    ASM_KEEP_NV(coord);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ((S_8195EF44_4 *)render)->unk_02 = saved_x;
    ((S_8195EF44_5 *)coord)->unk_38 = saved_x;
    ((S_8195EF44_4 *)render)->unk_06 = saved_y;
    ((S_8195EF44_5 *)coord)->unk_3A = saved_y;
    ((S_8195EF44_4 *)render)->unk_0A = saved_z;
    ((S_8195EF44_5 *)coord)->unk_3C = saved_z;
    work->unk_20 = 0x1000;
    work->unk_1E = 0x1000;
    work->unk_1C = 0x1000;
    work->unk_10 = 0x20;
    work->unk_0C = color;
    work->unk_14 = 0xC;
    ((S_8195EF44_5 *)coord)->unk_4C = 0xC;
    ((S_8195EF44_5 *)coord)->unk_60 = saved_coord_60;
    ((S_8195EF44_5 *)coord)->unk_62 = saved_z;
done:
    return obj;
}

/* MECHANISM: Pinned s2/s3/s4/s7 args, s1 obj/s0 work, and split s6/s5 map bases
   reproduce the 0x38 frame; a v1 clobber schedules coord in the render-load slot.
   The old-style () noreturn declaration self-serves the arg-carrying jal-to-j tail. */
