#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

extern PackedWord D_80018880;
extern s32 func_80018594(s32);

void func_8067F5C4(u8 *arg0) {
    s32 index;
    s32 marker;
    s32 tail_offset;
    u8 *copy_page;
    register u8 *copy_source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    u8 *entry;
    u8 *tail_base;
    register u8 *tail ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    copy_page = (u8 *)0x80020000;
    ASM_KEEP(copy_page);   /* MATCH pin: retail immediate-load split depends on it */
    copy_source = copy_page - 0x7780;
    ASM_KEEP(copy_source);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    *(PackedWord *)arg0 = *(PackedWord *)copy_source;
    ASM_KEEP(copy_page);   /* MATCH pin: retail immediate-load split depends on it */
    index = 1;
    marker = 0x18;
    entry = arg0 + 4;
    do {
        entry[1] = marker;
        entry[0] = index;
        if (func_80018594(index + 0x1497) != 0) {
            entry[3] |= 0x80;
        }
        index++;
        entry += 4;
    } while (index < 0x21);
    tail_base = arg0;
    ASM_KEEP(tail_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    tail_offset = index * 4;
    tail = (u8 *)((u32)tail_offset + (u32)tail_base);
    ASM_KEEP(tail);   /* MATCH pin: retail register colouring depends on it */
    tail[1] = 0;
    tail[0] = 0;
}

/* MECHANISM: A packed four-byte aggregate forces the retail lwl/lwr then swl/swr copy.
   Seam keeps hold page v0 across source a2 and payload v1 without leaking into the loop.
   Named marker/walker and guarded tail pins preserve the s3/s0 and v0/v1 live ranges. */
