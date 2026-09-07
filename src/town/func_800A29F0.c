#include "common.h"

typedef struct {
    s32 words[21];
} TownRecord;

typedef struct {
    s32 words[4];
} CopyChunk;

extern u8 D_80010A80[];

void func_800A0150(s32 arg0, u8 *arg1, TownRecord *arg2, s8 arg3)
{
    u8 *flags;
    u8 *flags_after;
    u8 *page_after;
    u8 *record_after;
    s32 *src;
    s32 *dst;
    s32 *end;
    s32 flag_bits;
    s32 tail_offset;
    register s32 index ASM_REG("$10");   /* MATCH pin: retail register colouring depends on it */

    index = arg0;
    ASM_KEEP(index);   /* MATCH pin: load-bearing for the whole function shape */
    flags = (u8 *)0x80010000;
    arg0 = index * 4;
    flags += arg0;
    flags[0x980] = arg1[0];
    flags[0x981] = arg1[1];
    flags[0x982] = arg1[2];
    flags[0x983] = arg1[3];

    if (arg1[1] == 0x13) {
        src = (s32 *)arg2;
        dst = (s32 *)((u8 *)0x80010A80 + (index * 0x54));
        end = src + 20;
        do {
            *(CopyChunk *)dst = *(CopyChunk *)src;
            src += 4;
            dst += 4;
        } while (src != end);
        *dst = *src;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        tail_offset = index * 4;
        page_after = (u8 *)0x80010000;
        flags_after = page_after + tail_offset;
        record_after = page_after + (index * 0x54);
        flag_bits = flags_after[0x983];
        flag_bits &= 0xC0;
        flag_bits |= index;
        flags_after[0x983] = flag_bits;
        record_after[0xAC4] = arg3;
    }
}

/* MECHANISM: The retail leaf is frameless and holds the runtime index in $t2 across both regions.
   Explicit destination/end live ranges wrap a 16-byte chunk assignment, exposing $t0/$t1
   while retaining GCC's load-four/store-four lowering; the post-copy page base is scope-split. */
