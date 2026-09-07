#include "common.h"

typedef struct {
    u8 bytes[8];
} ByteBlock8;

extern void *D_80016000;
extern ByteBlock8 D_80016164;

s32 func_8001AF7C(void) {
    ByteBlock8 local;
    s32 index;
    register s32 sum ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    u8 value;
    u8 *records;
    register u8 *table ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register ByteBlock8 *source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    u8 *page;
    u8 *entry;

    sum = 0;
    ASM_KEEP(sum);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    table = **(u8 ***)((u8 *)D_80016000 + 0x30);
    ASM_KEEP(table);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    page = (u8 *)0x80010000;
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    source = (ByteBlock8 *)(page + 0x6164);
    ASM_KEEP(source);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    local = *source;
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    index = sum;
    ASM_KEEP(index);   /* MATCH pin: retail schedule: same instructions, different order without it */
    records = *(u8 **)((u8 *)D_80016000 + 0x38);
    do {
        entry = records + (index * 2);
        value = table[(entry[0x33A4] << 5) + 2];
        if (value & 1) {
            sum += local.bytes[(value >> 3) & 7];
        }
        index++;
    } while (index < 0x22);
    return sum;
}

/* MECHANISM: The eight-byte local is copied through a2 while a 0x80010000 page
   stays live in v0, forcing the unaligned copy temporaries into v1/a0.
   Runtime-role pins preserve a3/a0/t0/a1; a named entry keeps base+index order. */
