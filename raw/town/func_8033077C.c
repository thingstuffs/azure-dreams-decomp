#include "common.h"

typedef struct {
    u8 bytes[8];
} ByteBlock8;

extern void *D_80016000;
extern ByteBlock8 D_80016164;

s32 func_8001AF7C(void) {
    ByteBlock8 local;
    register s32 index ASM_REG("$4");
    register s32 sum ASM_REG("$7");
    u8 value;
    register u8 *records ASM_REG("$5");
    register u8 *table ASM_REG("$8");
    register ByteBlock8 *source ASM_REG("$6");
    register u8 *page ASM_REG("$2");
    u8 *entry;

    sum = 0;
    ASM_KEEP(sum);
    table = **(u8 ***)((u8 *)D_80016000 + 0x30);
    ASM_KEEP(table);
    page = (u8 *)0x80010000;
    ASM_KEEP(page);
    source = (ByteBlock8 *)(page + 0x6164);
    ASM_KEEP(source);
    local = *source;
    ASM_KEEP(page);
    index = sum;
    ASM_KEEP(index);
    records = *(u8 **)((u8 *)D_80016000 + 0x38);
    ASM_KEEP(records);
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
