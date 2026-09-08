#include "common.h"

#include "common.h"

typedef struct {
    u8 bytes[0x60];
} Template96;

typedef struct {
    u32 words[4];
} Copy16;

typedef struct {
    u32 words[4];
} __attribute__((packed)) UnalignedCopy16;

extern Template96 D_8007136C;

/* Copies the default template and fills five byte pairs with the value and its negated half. */
void func_8004A170(void *unused_ptr, Template96 *dst, u32 value, u32 unused_word) {
    Template96 *base = dst;
    u8 *src_bytes;
    u8 *dst_bytes;
    u8 *src_end;
    u32 half_value;

    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    src_bytes = D_8007136C.bytes;
    dst_bytes = base->bytes;
    if (((u32)base | (u32)src_bytes) & 3) {
        src_end = src_bytes + sizeof(D_8007136C);
        do {
            *(UnalignedCopy16 *)dst_bytes = *(UnalignedCopy16 *)src_bytes;
            src_bytes += sizeof(UnalignedCopy16);
            dst_bytes += sizeof(UnalignedCopy16);
        } while (src_bytes != src_end);
    } else {
        src_end = src_bytes + sizeof(D_8007136C);
        do {
            *(Copy16 *)dst_bytes = *(Copy16 *)src_bytes;
            src_bytes += sizeof(Copy16);
            dst_bytes += sizeof(Copy16);
        } while (src_bytes != src_end);
    }

    half_value = (value & 0xFFFF) >> 1;

    base->bytes[0x0A] = value;
    base->bytes[0x16] = value;
    base->bytes[0x22] = value;
    base->bytes[0x3A] = value;
    base->bytes[0x46] = value;

    value = -half_value;
    base->bytes[0x02] = value;
    base->bytes[0x0E] = value;
    base->bytes[0x1A] = value;
    base->bytes[0x32] = value;
    base->bytes[0x3E] = value;
}
