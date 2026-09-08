#include "common.h"

typedef struct {
    u8 bytes[8];
} ByteBlock8;

extern void *D_80016000;
extern ByteBlock8 D_80016164;

s32 func_8001AF7C(void) {
    ByteBlock8 local;
    s32 index;
    register s32 sum ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 value;
    u8 *records;
    register u8 *table ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register ByteBlock8 *source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *page;
    u8 *entry;

    sum = 0;
    ASM_KEEP(sum);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    table = **(u8 ***)((u8 *)D_80016000 + 0x30);
    ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    page = (u8 *)0x80010000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    source = (ByteBlock8 *)(page + 0x6164);
    ASM_KEEP(source);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    local = *source;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    index = sum;
    ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
