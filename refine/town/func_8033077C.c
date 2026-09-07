#include "common.h"

typedef struct {
    u8 bytes[8];
} ByteBlock8;

extern void *D_80016000;
extern ByteBlock8 D_80016164;

/* Sum the weights selected by type flags for enabled records. */
s32 func_8001AF7C(void) {
    ByteBlock8 weights;
    s32 record_index;
    register s32 total_weight ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    u8 flags;
    u8 *record_data;
    register u8 *type_table ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    register ByteBlock8 *weight_source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    u8 *data_page;
    u8 *record;

    total_weight = 0;
    ASM_KEEP(total_weight);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    type_table = **(u8 ***)((u8 *)D_80016000 + 0x30);
    ASM_KEEP(type_table);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    data_page = (u8 *)0x80010000;
    ASM_KEEP(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    weight_source = (ByteBlock8 *)(data_page + 0x6164);
    ASM_KEEP(weight_source);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    weights = *weight_source;
    ASM_KEEP(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    record_index = total_weight;
    ASM_KEEP(record_index);   /* MATCH pin: retail schedule: same instructions, different order without it */
    record_data = *(u8 **)((u8 *)D_80016000 + 0x38);
    do {
        record = record_data + (record_index * 2);
        flags = type_table[(record[0x33A4] << 5) + 2];
        if (flags & 1) {
            total_weight += weights.bytes[(flags >> 3) & 7];
        }
        record_index++;
    } while (record_index < 0x22);
    return total_weight;
}

/* MECHANISM: The eight-byte local is copied through a2 while a 0x80010000 page
   stays live in v0, forcing the unaligned copy temporaries into v1/a0.
   Runtime-role pins preserve a3/a0/t0/a1; a named entry keeps base+index order. */
