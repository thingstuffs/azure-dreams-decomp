#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern u8 D_8002012C[];
extern u8 D_80020134[];
extern u8 D_8002013C[];
extern u8 D_80020140[];
extern u8 D_80020144[];
extern u8 D_80020148[];
extern u8 D_8002582C[];
extern u8 D_80025BC8[];
extern u8 D_80026B78[];
extern u8 D_80026BC4[];
extern u8 D_80026C54[];
extern u8 D_80026F50[];
extern u8 D_80045340[];
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_80083498[];
extern u8 D_800F7968[];

extern void func_80026CE4(s32);
extern void func_8003DB94(void *, void *, s32, void *);
extern void func_8003E188(s32, s32);
extern void *func_8003FC64(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void func_8008F074(void *, void *, void *);
extern void func_800C15C0(s32, s32);

s32 func_800254A4(void)
{
    void *first[2];
    void *second[2];
    register u8 *root ASM_REG("$21") = NULL;
    void *obj;
    void *part1;
    void *part2;
    void *part3;
    register void *final_part ASM_REG("$2");
    void *draw;
    void *packet;
    register void *link ASM_REG("$2");
    void *stack_value;
    void *first_callback;
    void *callback;
    void *aux;
    void **slot;
    u8 *source;
    register u8 *indexed_source ASM_REG("$2");
    register u8 *dst0 ASM_REG("$4");
    register u8 *dst1 ASM_REG("$3");
    u8 byte;
    s32 i;
    s32 final_color;
    register s32 final_extent ASM_REG("$4");
    s16 coord;

    ASM_KEEP(root);
    first[0] = D_8002012C;
    first[1] = D_80020134;
    ASM_SCHED_BARRIER();
    second[0] = D_8002013C;
    second[1] = D_80020140;
    source = D_80020144;

    func_800C15C0(0x24, 0x200);
    func_80026CE4(0x5A);
    func_8003E188(0x3C, (s32)root);

    obj = func_8003FC64(2);
    if (obj != NULL) {
        root = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_80025BC8;
        FIELD(root, s16, 0x18) = rand() & 1;
    }

    i = 2;
    first_callback = D_8002582C;
    aux = D_80020148;
    slot = (void **)(root + 8);
first_loop:
    obj = func_8003FC64(0x136);
    *slot = obj;
    if (obj != NULL) {
        FIELD(obj, void *, 0x10) = first_callback;
        func_8004491C(obj, D_80045340);
        part1 = (u8 *)obj + 0x20;
        draw = FIELD(obj, void *, 0xC);
        packet = FIELD(obj, void *, 8);
        FIELD(packet, s32, 0) = 0x05600000;
        FIELD(packet, s32, 4) = (i << 0x16) + 0x03E00000;
        FIELD(packet, s32, 8) = 0x00800000;
        FIELD(packet, s32, 0x14) = 0xFFFC0000;
        FIELD(obj, void *, 0x20) = root;
        FIELD(part1, s16, 0x56) = i;
        FIELD(draw, s16, 0x1E) = 0x1000;
        FIELD(draw, s16, 0x1C) = 0x1000;
        func_8003DB94(draw, D_800F7968, 0, packet);
        FIELD(draw, s32, 0xC) = 0x00808080;
        FIELD(part1, void *, 0x4C) = aux;
        func_8008F074((u8 *)obj + 0x24, FIELD(obj, void *, 8), D_80026F50);
    }
    i--;
    slot--;
    if (i >= 0) {
        goto first_loop;
    }

    i = 1;
    callback = D_80026B78;
    coord = 0x2C;
    do {
        obj = func_8003FD64(1, D_80083498);
        part2 = (u8 *)obj + 0x20;
        if (obj != NULL) {
            FIELD(obj, void *, 0x10) = callback;
            func_8004491C(obj, D_80053858);
            FIELD(part2, s16, 0x14) = 0x20;
            FIELD(part2, s16, 0x18) = 3;
            FIELD(part2, s16, 0x1A) = 0x7C80;
            FIELD(part2, s16, 0x16) = coord;
            FIELD(part2, s32, 0x10) = 0x00808080;
            stack_value = first[i];
            FIELD(part2, void *, 0xC) = root;
            FIELD(part2, void *, 4) = stack_value;
        }
        i--;
        coord -= 0xC;
    } while (i >= 0);

    i = 1;
    do {
        indexed_source = source + i;
        ASM_KEEP(indexed_source);
        dst0 = (u8 *)second[0] + i;
        dst1 = (u8 *)second[1] + i;
        byte = *indexed_source;
        ASM_KEEP(dst0);
        ASM_KEEP(dst1);
        i--;
        *dst1 = byte;
        *dst0 = byte;
    } while (i >= 0);

    i = 1;
    callback = D_80026BC4;
    coord = 0x2C;
    do {
        obj = func_8003FD64(1, D_80083498);
        part3 = (u8 *)obj + 0x20;
        if (obj != NULL) {
            FIELD(obj, void *, 0x10) = callback;
            func_8004491C(obj, D_80053858);
            FIELD(part3, s16, 0x14) = 0x50;
            FIELD(part3, s16, 0x18) = 3;
            FIELD(part3, s16, 0x1A) = 0x7C80;
            FIELD(part3, s16, 0x16) = coord;
            FIELD(part3, s32, 0x10) = 0x00808080;
            FIELD(part3, void *, 4) = second[i];
            if (i != 0) {
                if (i == 1) {
                    goto third_nonzero_link;
                }
                FIELD(part3, void *, 0xC) = root;
                goto third_continue;
            } else {
                link = root + 0x12;
                goto third_store_link;
            }
third_nonzero_link:
            link = root + 0x14;
third_store_link:
            ASM_KEEP(link);
            FIELD(part3, void *, 8) = link;
            FIELD(part3, void *, 0xC) = root;
        }
third_continue:
        i--;
        coord -= 0xC;
    } while (i >= 0);

    obj = func_8003FD64(1, D_80083498);
    if (obj != NULL) {
        FIELD(obj, void *, 0x10) = D_80026C54;
        func_8004491C(obj, &D_80053A88);
        final_color = 0x00404040;
        final_part = (u8 *)obj + 0x20;
        ASM_KEEP(final_part);
        final_extent = 0x1C;
        ASM_KEEP(final_extent);
        FIELD(final_part, volatile s16, 0xC) = final_extent;
        FIELD(final_part, volatile s16, 0xE) = final_extent;
        FIELD(final_part, volatile s16, 0x12) = final_extent;
        FIELD(final_part, volatile u16, 0x16) |= 1;
        FIELD(final_part, s16, 0x10) = 0x48;
        FIELD(final_part, s16, 0x14) = 2;
        FIELD(final_part, s32, 8) = final_color;
        FIELD(final_part, void *, 4) = root;
    }

    return 0;
}

/* MECHANISM: Sibling pointer arrays force the 0x48 frame; split first-loop callback
   liveness yields the retail s7/s6/s4 held-base roles. A prefix scheduling fence
   plus short-lived copy/link/final pins reproduce the call and join lifetimes.
   Volatile final stores retain the retail store-before-RMW emission order. */
