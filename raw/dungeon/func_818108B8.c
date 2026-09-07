#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 value;
    u8 pad10[4];
} ItemRecord;

typedef struct {
    u8 pad0[0xC];
    ItemRecord *records;
    u8 pad10[4];
} ItemCategory;

typedef struct {
    u8 pad0[8];
    s32 value;
    u8 padC[0x10];
    s32 index;
} Subobject;

typedef struct {
    u8 pad0[0xC];
    s32 category;
    u8 pad10[4];
    void *subobject_base;
    u8 pad18[0x60];
    u8 fallback_arg[0x10];
    s32 fallback_value;
} Object;

extern ItemCategory D_80073414[];
extern void func_8004A7D8();
extern void func_8002594C(void) __attribute__((noreturn));
extern void strcpy();

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

void func_800258B8(void *arg0)
{
    s32 category;
    s32 subobject_base;
    void *object = arg0;
    void *subobject;

    subobject_base = FIELD(object, s32, 0x14);
    category = FIELD(object, s32, 0xC);
    subobject = (void *)(subobject_base + 0x20);
    ASM_USE(subobject_base);
    if (category != 0x13) {
        ASM_SCHED_BARRIER();
        if (FIELD(subobject, s32, 8) != 0) {
            ASM_SCHED_BARRIER();
            func_8004A7D8(category, FIELD(subobject, s32, 0x1C));
            ASM_SCHED_BARRIER();
            D_80073414[FIELD(object, s32, 0xC)]
                .records[FIELD(subobject, s32, 0x1C)].value =
                FIELD(subobject, s32, 8);
            func_8002594C();
        }
    }
    strcpy(FIELD(object, s32, 0x88), (u8 *)object + 0x78);
}

/* MECHANISM: Pin object/subobject to s0/s1 for the retail frame saves and held-base roles.
   Keep the raw +0x14 base live through pointer formation to force lw v0; addiu s1.
   Scheduling fences preserve the retail nop slots at both guards and the first call. */
