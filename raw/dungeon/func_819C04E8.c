#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

extern void func_80025DD8(void) __attribute__((noreturn));
extern void func_80025EE0(void) __attribute__((noreturn));
extern void func_80025F5C(void);
extern void func_80025F7C(void);
#if 0
extern void func_80025F5C(void) __attribute__((noreturn));
extern void func_80025F7C(void) __attribute__((noreturn));
#endif
extern Object *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern Copy32 D_80024028[];
extern u8 D_80025800[];
extern void *D_80028630;
extern u8 D_80028664[];
extern s32 D_800814A0;
extern s32 D_80083498;
extern u8 D_800C9034[];

s32 func_80025CE8(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    Object *objects[21];
    Copy32 copy;
    register u8 *copy_page ASM_REG("$2");
    register Copy32 *copy_source ASM_REG("$6");
    register s32 i ASM_REG("$17");
    register Object **slot ASM_REG("$19");
    Object *allocated;
    register Object *cleanup ASM_REG("$4");
    register Object *object_after ASM_REG("$2");
    void *part8;
    void *partC;
    register s32 entry_x ASM_REG("$2");
    register u16 entry_y ASM_REG("$2");
    register u8 *entry ASM_REG("$3");
    register s32 next ASM_REG("$5");
    register s32 slot_offset ASM_REG("$2");
    register s32 asset_offset ASM_REG("$3");
    register u16 part_flags ASM_REG("$3");
    register u16 cleanup_flags ASM_REG("$3");
    register s32 *global_flags;
    register s32 color ASM_REG("$5");
    register Object *dispatch_arg ASM_REG("$5");
    register u8 *alloc_page ASM_REG("$2");
    register void *alloc_arg ASM_REG("$5");

    copy_page = (u8 *)0x80020000;
    ASM_KEEP(copy_page);
    copy_source = (Copy32 *)(copy_page + 0x4028);
    ASM_KEEP(copy_source);
    copy.first = copy_source->first;
    copy.second = copy_source->second;
    copy.third = copy_source->third;
    ASM_KEEP(copy_page);
    i = 0;
    global_flags = (s32 *)0x80080000;
    do {
        if (((u32)(u16)i << 16) != 0) {
            alloc_page = (u8 *)0x80080000;
            ASM_KEEP(alloc_page);
            dispatch_arg = objects[0];
            ASM_KEEP(dispatch_arg);
            func_80025DD8();
        }
        alloc_page = (u8 *)0x80080000;
        ASM_KEEP(alloc_page);
        alloc_arg = alloc_page + 0x3498;
        ASM_KEEP(alloc_arg);
        allocated = func_8003FD64(0x12, alloc_arg);
        slot_offset = ((s32)(s16)i) << 2;
        ASM_KEEP(slot_offset);
        slot = (Object **)((uptr)slot_offset + (uptr)objects);
        ASM_KEEP(slot);
        *slot = allocated;
        if (allocated != 0) {
            color = 0x800000;
            ASM_KEEP(color);
            allocated->part10 = D_80025800;
            entry = (u8 *)&copy + ((arg3 >> 7) & 0x1C);
            color |= 0x8080;
            ASM_KEEP(color);
            entry_x = FIELD(entry, s16, 0);
            part8 = (*slot)->part8;
            FIELD(part8, s16, 2) = arg0 + (entry_x << 7);
            entry_y = FIELD(entry, u16, 2);
            FIELD(part8, s16, 0xA) = arg2 - 0x90;
            FIELD(part8, s16, 6) = arg1 + (((s32)entry_y << 16) >> 9);

            partC = (*slot)->partC;
            asset_offset = (s32)(s16)i * 0x10;
            ASM_KEEP(asset_offset);
            FIELD(partC, s16, 0x1A) = arg3 - 0x400;
            FIELD(partC, s16, 0x16) = 0x400;
            FIELD(partC, s16, 0x20) = 0x1000;
            FIELD(partC, s16, 0x1E) = 0x1000;
            FIELD(partC, s16, 0x1C) = 0x1000;
            FIELD(partC, void *, 8) = D_80028664 + asset_offset;
            part_flags = FIELD(partC, u16, 0x14);
            ASM_KEEP(part_flags);
            FIELD(partC, s16, 0x10) = 0x20;
            FIELD(partC, s32, 0xC) = color;
#ifndef NON_MATCHING
            color = 0x800D0000;
            ASM_KEEP(color);
#endif
            part_flags |= 0xC;
            ASM_KEEP(part_flags);
            FIELD(partC, u16, 0x14) = part_flags;
            ASM_SCHED_BARRIER();
#ifndef NON_MATCHING
            func_8004491C(*slot, (void *)(color - 0x6FCC));
#else
            func_8004491C(*slot, D_800C9034);
#endif

            object_after = *slot;
            if ((s16)i != 0) {
                entry = (u8 *)object_after + 0x20;
                ASM_KEEP(entry);
                FIELD(entry, Object *, 0x20) = objects[0];
                func_80025EE0();
            }
            entry = (u8 *)object_after + 0x20;
            alloc_page = (u8 *)0x80030000;
            ASM_KEEP(alloc_page);
            FIELD(alloc_page, void *, -0x79D0) = part8;
            FIELD(partC, s16, 0x1E) = 0;
            FIELD(partC, s16, 0x1C) = 0;
            FIELD(partC, s16, 0x20) = 0;
            FIELD(entry, s16, 0x30) = 0x3C;
            FIELD(entry, u16, 0x36) = arg3;
            FIELD(entry, s16, 0x3A) = 0;
            FIELD(entry, s16, 0x38) = 0xF;
            func_80025F5C();
        }
            slot_offset = i - 1;
            i = slot_offset;
            ASM_KEEP(slot_offset);
            if ((s32)((u32)slot_offset << 16) >= 0) {
                do {
                    slot_offset = (s32)((u32)i << 16);
                    ASM_KEEP(slot_offset);
                    next = i - 1;
                    ASM_KEEP(next);
                    i = next;
                    ASM_KEEP(i);
                    slot_offset >>= 14;
                    alloc_page = (u8 *)((uptr)slot_offset + (uptr)objects);
                    ASM_KEEP(alloc_page);
                    next = (s32)((u32)next << 16);
                    ASM_KEEP(next);
                    cleanup = *(Object **)alloc_page;
                    ASM_KEEP(cleanup);
                    cleanup_flags = FIELD(cleanup, u16, 0x1E);
                    slot_offset = global_flags[0x528];
                    slot_offset |= 0x8000;
                    global_flags[0x528] = slot_offset;
                    ASM_SCHED_BARRIER();
                    cleanup_flags |= 0x8000;
                    FIELD(cleanup, u16, 0x1E) = cleanup_flags;
                } while (next >= 0);
                slot_offset = 0;
                ASM_TAILSLOT_PIN_TIED(slot_offset);
                func_80025F7C();
            } else {
                return 0;
            }
        ASM_SCHED_BARRIER();
        slot_offset = i + 1;
        ASM_KEEP(slot_offset);
        i = slot_offset;
        ASM_KEEP(i);
    } while ((s16)slot_offset < 21);
    return (s32)objects[0];
}
