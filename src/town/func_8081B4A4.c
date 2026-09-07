#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800254A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800254A4_0;   /* obj in func_800254A4 */

typedef struct S_800254A4_1 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800254A4_1;   /* root in func_800254A4 */

typedef struct S_800254A4_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800254A4_2;   /* packet in func_800254A4 */

typedef struct S_800254A4_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
    u8 pad_50[0x6];
    s16 unk_56;
} S_800254A4_3;   /* part1 in func_800254A4 */

typedef struct S_800254A4_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800254A4_4;   /* draw in func_800254A4 */

typedef struct S_800254A4_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800254A4_5;   /* part2 in func_800254A4 */

typedef struct S_800254A4_6 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800254A4_6;   /* part3 in func_800254A4 */

typedef struct S_800254A4_7 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    volatile s16 unk_0C;
    volatile s16 unk_0E;
    s16 unk_10;
    volatile s16 unk_12;
    s16 unk_14;
    volatile u16 unk_16;
} S_800254A4_7;   /* final_part in func_800254A4 */



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
    register u8 *root ASM_REG("$21") = NULL;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *obj;
    S_800254A4_3 *part1;
    S_800254A4_5 *part2;
    S_800254A4_6 *part3;
    S_800254A4_7 *final_part;
    S_800254A4_4 *draw;
    S_800254A4_2 *packet;
    void *link;
    void *stack_value;
    void *first_callback;
    void *callback;
    void *aux;
    void **slot;
    u8 *source;
    u8 *indexed_source;
    u8 *dst0;
    u8 *dst1;
    u8 byte;
    s32 i;
    s32 final_color;
    register s32 final_extent ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s16 coord;

    ASM_KEEP(root);   /* MATCH pin: retail schedule: same instructions, different order without it */
    first[0] = D_8002012C;
    first[1] = D_80020134;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    second[0] = D_8002013C;
    second[1] = D_80020140;
    source = D_80020144;

    func_800C15C0(0x24, 0x200);
    func_80026CE4(0x5A);
    func_8003E188(0x3C, (s32)root);

    obj = func_8003FC64(2);
    if (obj != NULL) {
        root = (u8 *)obj + 0x20;
        ((S_800254A4_0 *)obj)->unk_10 = D_80025BC8;
        ((S_800254A4_1 *)root)->unk_18 = rand() & 1;
    }

    i = 2;
    first_callback = D_8002582C;
    aux = D_80020148;
    slot = (void **)(root + 8);
first_loop:
    obj = func_8003FC64(0x136);
    *slot = obj;
    if (obj != NULL) {
        ((S_800254A4_0 *)obj)->unk_10 = first_callback;
        func_8004491C(obj, D_80045340);
        part1 = (u8 *)obj + 0x20;
        draw = ((S_800254A4_0 *)obj)->unk_0C;
        packet = ((S_800254A4_0 *)obj)->unk_08;
        packet->unk_00 = 0x05600000;
        packet->unk_04 = (i << 0x16) + 0x03E00000;
        packet->unk_08 = 0x00800000;
        packet->unk_14 = 0xFFFC0000;
        ((S_800254A4_0 *)obj)->unk_20 = root;
        part1->unk_56 = i;
        draw->unk_1E = 0x1000;
        draw->unk_1C = 0x1000;
        func_8003DB94(draw, D_800F7968, 0, packet);
        draw->unk_0C = 0x00808080;
        part1->unk_4C = aux;
        func_8008F074((u8 *)obj + 0x24, ((S_800254A4_0 *)obj)->unk_08, D_80026F50);
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
            ((S_800254A4_0 *)obj)->unk_10 = callback;
            func_8004491C(obj, D_80053858);
            part2->unk_14 = 0x20;
            part2->unk_18 = 3;
            part2->unk_1A = 0x7C80;
            part2->unk_16 = coord;
            part2->unk_10 = 0x00808080;
            stack_value = first[i];
            part2->unk_0C = root;
            part2->unk_04 = stack_value;
        }
        i--;
        coord -= 0xC;
    } while (i >= 0);

    i = 1;
    do {
        indexed_source = source + i;
        dst0 = (u8 *)second[0] + i;
        dst1 = (u8 *)second[1] + i;
        byte = *indexed_source;
        ASM_KEEP(dst0);   /* MATCH pin: load-bearing for the whole function shape */
        ASM_KEEP(dst1);   /* MATCH pin: retail register colouring depends on it */
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
            ((S_800254A4_0 *)obj)->unk_10 = callback;
            func_8004491C(obj, D_80053858);
            part3->unk_14 = 0x50;
            part3->unk_18 = 3;
            part3->unk_1A = 0x7C80;
            part3->unk_16 = coord;
            part3->unk_10 = 0x00808080;
            part3->unk_04 = second[i];
            if (i != 0) {
                if (i == 1) {
                    goto third_nonzero_link;
                }
                part3->unk_0C = root;
                goto third_continue;
            } else {
                link = root + 0x12;
                goto third_store_link;
            }
third_nonzero_link:
            link = root + 0x14;
third_store_link:
            part3->unk_08 = link;
            part3->unk_0C = root;
        }
third_continue:
        i--;
        coord -= 0xC;
    } while (i >= 0);

    obj = func_8003FD64(1, D_80083498);
    if (obj != NULL) {
        ((S_800254A4_0 *)obj)->unk_10 = D_80026C54;
        func_8004491C(obj, &D_80053A88);
        final_color = 0x00404040;
        final_part = (u8 *)obj + 0x20;
        ASM_KEEP(final_part);   /* MATCH pin: retail schedule: same instructions, different order without it */
        final_extent = 0x1C;
        final_part->unk_0C = final_extent;
        final_part->unk_0E = final_extent;
        final_part->unk_12 = final_extent;
        final_part->unk_16 |= 1;
        final_part->unk_10 = 0x48;
        final_part->unk_14 = 2;
        final_part->unk_08 = final_color;
        final_part->unk_04 = root;
    }

    return 0;
}

/* MECHANISM: Sibling pointer arrays force the 0x48 frame; split first-loop callback
   liveness yields the retail s7/s6/s4 held-base roles. A prefix scheduling fence
   plus short-lived copy/link/final pins reproduce the call and join lifetimes.
   Volatile final stores retain the retail store-before-RMW emission order. */
