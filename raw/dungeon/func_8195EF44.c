#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_8002488C() __attribute__((noreturn));
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 D_80024648;
extern s32 D_80046398;
extern s32 D_800814A0;
extern u8 D_8008333C[32];

void *func_8195EF44(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    register s16 hold0 ASM_REG("$18") = arg0;
    register s16 hold1 ASM_REG("$19") = arg1;
    register s16 hold2 ASM_REG("$20") = arg2;
    register s16 hold3 ASM_REG("$23") = arg3;
    register void *obj ASM_REG("$17");
    register void *work ASM_REG("$16");
    register u8 *map ASM_REG("$21");
    register u8 *page ASM_REG("$22");
    register void *field_addr ASM_REG("$2");
    register void *call_addr ASM_REG("$5");
    register void *call_obj ASM_REG("$4");
    register void *render ASM_REG("$2");
    register u8 *coord ASM_REG("$3");
    register s32 color ASM_REG("$4");
    u16 *cells;
    u16 cell;
    register s32 flags ASM_REG("$4");
    register s32 global_flags ASM_REG("$5");
    register void *zero_return ASM_REG("$2");
    register u8 *global_page ASM_REG("$3");
    register s32 x ASM_REG("$4");
    register s32 y ASM_REG("$3");
    register s32 sign ASM_REG("$2");

    obj = func_8003FC64(2);
    page = (u8 *)0x80080000;
    ASM_KEEP(page);
    map = page + 0x333C;
    if (obj == NULL) {
        goto done;
    }

    ASM_KEEP(map);
    work = FIELD(obj, void *, 0xC);
    sign = (s32)((u32)(u16)hold0 << 16);
    ASM_KEEP_NV(sign);
    x = sign >> 16;
    if (x < 0) {
        x += 0x3F;
    }
    sign = (s32)((u32)(u16)hold1 << 16);
    ASM_KEEP_NV(sign);
    y = sign >> 16;
    x >>= 6;
    if (y < 0) {
        y += 0x3F;
    }
    y >>= 6;
    y <<= FIELD(map, s16, 0x14);
    y = x + y;
    cells = FIELD(page, u16 *, 0x333C);
    cell = cells[y * 3];
    FIELD(work, s32, 8) = cell;

    if (cell != 0) {
        goto nonzero;
    }

    zero_return = NULL;
    ASM_KEEP(zero_return);
    global_page = (u8 *)0x80080000;
    ASM_KEEP(global_page);
    flags = FIELD(obj, u16, 0x1E);
    global_flags = FIELD(global_page, s32, 0x14A0);
    flags |= 0x8000;
    global_flags |= 0x8000;
    FIELD(obj, u16, 0x1E) = flags;
    FIELD(global_page, s32, 0x14A0) = global_flags;
    func_8002488C(flags, global_flags);

nonzero:
    call_obj = obj;
    ASM_KEEP(call_obj);
    field_addr = &D_80024648;
    ASM_KEEP(field_addr);
    call_addr = &D_80046398;
    FIELD(obj, void *, 0x10) = field_addr;
    func_8004491C(call_obj, call_addr);

    color = 0x808080;
    render = FIELD(obj, void * volatile, 8);
    ASM_CLOBBER("$3");
    coord = (u8 *)obj + 0x20;
    ASM_KEEP_NV(coord);
    FIELD(render, s16, 2) = hold0;
    FIELD(coord, s16, 0x38) = hold0;
    FIELD(render, s16, 6) = hold1;
    FIELD(coord, s16, 0x3A) = hold1;
    FIELD(render, s16, 0xA) = hold2;
    FIELD(coord, s16, 0x3C) = hold2;
    FIELD(work, s16, 0x20) = 0x1000;
    FIELD(work, s16, 0x1E) = 0x1000;
    FIELD(work, s16, 0x1C) = 0x1000;
    FIELD(work, s16, 0x10) = 0x20;
    FIELD(work, s32, 0xC) = color;
    FIELD(work, s16, 0x14) = 0xC;
    FIELD(coord, s16, 0x4C) = 0xC;
    FIELD(coord, s16, 0x60) = hold3;
    FIELD(coord, s16, 0x62) = hold2;
    ASM_KEEP(hold0);
    ASM_KEEP(hold1);
    ASM_KEEP(hold2);
    ASM_KEEP(hold3);
done:
    return obj;
}

/* MECHANISM: Pinned s2/s3/s4/s7 args, s1 obj/s0 work, and split s6/s5 map bases
   reproduce the 0x38 frame; a v1 clobber schedules coord in the render-load slot.
   The old-style () noreturn declaration self-serves the arg-carrying jal-to-j tail. */
