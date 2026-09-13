#include "common.h"

typedef void (*EntryCallback)(void *);

extern void func_8001941C(void *, void *, s32);

typedef union PackedWord {
    u32 word;
    struct {
        u16 lo;
        u16 hi;
    } half;
} PackedWord;

typedef struct DataRecord {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    PackedWord unkC;
    u32 unk10;
} DataRecord;

/* Populate records from entries, pack their flags and tag, and invoke entry callbacks. */
void *func_8001976C(void *records, void *entries, s32 flags, s32 tag)
{
    DataRecord *record;
    u8 *entry;
    s32 record_flags;
    u32 tag_bits;
    u32 flag_bits;
    s32 header_word;
    register u32 packed_word ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 half_bits;
    u32 header_or_addr;

    do {
        record = records;
    } while (0);
    entry = entries;
    record_flags = flags;
    half_bits = record_flags >> 8;
    packed_word = record_flags & 0x3FFF0000;
    header_or_addr = 0xC0000010;
    header_word = packed_word | header_or_addr;
    half_bits &= 0x3F;
    flag_bits = half_bits << 24;
    tag_bits = (tag & 0xFF) << 16;
    header_or_addr = (u32)record;
    loop_0: {
        func_8001941C((void *)header_or_addr, entry, 5);
        packed_word = 0xC0000000;
        if (record_flags != 0) {
            record->unk8 = header_word;
            packed_word = tag_bits | packed_word;
        } else {
            packed_word = tag_bits | packed_word;
        }
        packed_word = flag_bits | packed_word;
        half_bits = record->unkC.half.lo;
        record->unkC.word = packed_word | half_bits;
        if (*entry != 0) {
            (*(EntryCallback *)(entry + 8))(record);
            entry += 0x14;
        } else {
            record++;
            entry += 0x14;
        }
        header_or_addr = (u32)record;
    } if (*(entry - 0x13) != 0x80) goto loop_0;
    return record;
}

/* MECHANISM: Guarded pins encode s0-s5 and v0/v1/a0; a seam fence preserves
   the second OR before the lhu, including its required load-delay nop.
   The callback arm rejoins the bottom-tested loop instead of tail-calling. */
