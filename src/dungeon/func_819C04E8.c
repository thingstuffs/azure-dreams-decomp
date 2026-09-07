#include "common.h"


typedef unsigned long uptr;

typedef struct {
    u8 bytes[12];
} __attribute__((packed)) Copy12;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) Copy8;

typedef struct {
    Copy12 first;
    Copy12 second;
    Copy8 third;
} __attribute__((packed)) Copy32;

typedef struct {
    u8 pad0[8];
    void *part8;
    void *partC;
    void *part10;
} Object;

extern Object *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern Copy32 D_80024028[];
extern u8 D_80025800[];
extern void *D_80028630;
extern u8 D_80028664[];
extern s32 D_800814A0;
extern u8 D_800C9034[];


typedef struct S_80025CE8_0 {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x1C];
    Object * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    u8 pad_32[0x4];
    u16 unk_36;
    s16 unk_38;
    s16 unk_3A;
} S_80025CE8_0;   /* entry in func_80025CE8 */

typedef struct S_80025CE8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80025CE8_1;   /* part8 in func_80025CE8 */

typedef struct S_80025CE8_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_80025CE8_2;   /* partC in func_80025CE8 */

typedef struct S_80025CE8_3_pre {
    void * unk_00;
    u8 pad_04[0x79CC];
} S_80025CE8_3_pre;   /* the 0x79D0 bytes before alloc_page in func_80025CE8, addressed as alloc_page[-1] */

typedef struct S_80025CE8_4 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80025CE8_4;   /* cleanup in func_80025CE8 */

s32 func_80025CE8(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    Object *objects[21];
    Copy32 copy;
    u8 *copy_page;
    register Copy32 *copy_source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 i;
    Object **slot;
    register Object *allocated ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    Object *cleanup;
    Object *object_after;
    S_80025CE8_1 *part8;
    S_80025CE8_2 *partC;
    s32 entry_x;
    u16 entry_y;
    register u8 *entry ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 next ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 slot_offset ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 asset_offset ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u16 part_flags ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 cleanup_flags;
    s32 color;
    Object *dispatch_arg;
    u8 *alloc_page;

    copy_page = (u8 *)0x80020000;
    ASM_KEEP(copy_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    copy_source = (Copy32 *)(copy_page + 0x4028);
    ASM_KEEP(copy_source);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    copy.first = copy_source->first;
    copy.second = copy_source->second;
    copy.third = copy_source->third;
    ASM_KEEP(copy_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    i = 0;
    do {
        if (((u32)(u16)i << 16) != 0) {
            alloc_page = (u8 *)0x80080000;
            dispatch_arg = objects[0];
            goto call_alloc;
        }
        alloc_page = (u8 *)0x80080000;
        ASM_KEEP(alloc_page);   /* MATCH pin: load-bearing for the whole function shape */
        dispatch_arg = (Object *)(alloc_page + 0x3498);
    call_alloc:
        allocated = func_8003FD64(0x12, dispatch_arg);
        slot_offset = ((s32)(s16)i) << 2;
        slot = (Object **)((uptr)slot_offset + (uptr)objects);
        *slot = allocated;
        if (allocated != 0) {
            color = 0x800000;
            ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
            allocated->part10 = D_80025800;
            entry = (u8 *)&copy + ((arg3 >> 7) & 0x1C);
            color |= 0x8080;
            entry_x = ((S_80025CE8_0 *)entry)->unk_00;
            part8 = (*slot)->part8;
            part8->unk_02 = arg0 + (entry_x << 7);
            entry_y = ((S_80025CE8_0 *)entry)->unk_02;
            part8->unk_0A = arg2 - 0x90;
            part8->unk_06 = arg1 + (((s32)entry_y << 16) >> 9);

            partC = (*slot)->partC;
            asset_offset = (s32)(s16)i * 0x10;
            partC->unk_1A = arg3 - 0x400;
            partC->unk_16 = 0x400;
            partC->unk_20 = 0x1000;
            partC->unk_1E = 0x1000;
            partC->unk_1C = 0x1000;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
            entry = D_80028664 + asset_offset;
            partC->unk_08 = entry;
            part_flags = partC->unk_14;
            entry_x = 0x20;
            partC->unk_10 = entry_x;
            partC->unk_0C = color;
#ifndef NON_MATCHING
            color = 0x800D0000;
            ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
#endif
            part_flags |= 0xC;
            partC->unk_14 = part_flags;
#ifndef NON_MATCHING
            func_8004491C(*slot, (void *)(color - 0x6FCC));
#else
            func_8004491C(*slot, D_800C9034);
#endif

            object_after = *slot;
            if ((s16)i != 0) {
                entry = (u8 *)object_after + 0x20;
                ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */
                ((S_80025CE8_0 *)entry)->unk_20 = objects[0];
                goto shared_tail;
            }
            entry = (u8 *)object_after + 0x20;
            alloc_page = (u8 *)0x80030000;
            ASM_KEEP(alloc_page);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_80025CE8_3_pre *)alloc_page)[-1].unk_00 = part8;
        shared_tail:
            partC->unk_1E = 0;
            partC->unk_1C = 0;
            partC->unk_20 = 0;
            ((S_80025CE8_0 *)entry)->unk_30 = 0x3C;
            ((S_80025CE8_0 *)entry)->unk_36 = arg3;
            ((S_80025CE8_0 *)entry)->unk_3A = 0;
            ((S_80025CE8_0 *)entry)->unk_38 = 0xF;
            goto continue_loop;
        }
            slot_offset = i - 1;
            i = slot_offset;
            ASM_KEEP(slot_offset);   /* MATCH pin: retail register colouring depends on it */
            if ((s32)((u32)slot_offset << 16) >= 0) {
                do {
                    slot_offset = (s32)((u32)i << 16);
                    next = i - 1;
                    i = next;
                    slot_offset >>= 14;
                    alloc_page = (u8 *)((uptr)slot_offset + (uptr)objects);
                    next = (s32)((u32)next << 16);
                    cleanup = *(Object **)alloc_page;
                    cleanup_flags = ((S_80025CE8_4 *)cleanup)->unk_1E;
                    slot_offset = D_800814A0;
                    slot_offset |= 0x8000;
                    D_800814A0 = slot_offset;
                    cleanup_flags |= 0x8000;
                    ((S_80025CE8_4 *)cleanup)->unk_1E = cleanup_flags;
                } while (next >= 0);
                return 0;
            } else {
                return 0;
            }
        continue_loop:
        slot_offset = i + 1;
        i = slot_offset;
        ASM_KEEP(i);   /* MATCH pin: retail register colouring depends on it */
    } while ((s16)slot_offset < 21);
    return (s32)objects[0];
}
