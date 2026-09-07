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

void func_8004A170(void *arg0, Template96 *dst, u32 value, u32 arg3) {
    Template96 *base = dst;
    u8 *src;
    u8 *out;
    u8 *end;
    u32 half;

    ASM_KEEP(base);   /* MATCH pin: slus-diff */
    src = D_8007136C.bytes;
    out = base->bytes;
    if (((u32)base | (u32)src) & 3) {
        end = src + sizeof(D_8007136C);
        do {
            *(UnalignedCopy16 *)out = *(UnalignedCopy16 *)src;
            src += sizeof(UnalignedCopy16);
            out += sizeof(UnalignedCopy16);
        } while (src != end);
    } else {
        end = src + sizeof(D_8007136C);
        do {
            *(Copy16 *)out = *(Copy16 *)src;
            src += sizeof(Copy16);
            out += sizeof(Copy16);
        } while (src != end);
    }

    half = (value & 0xFFFF) >> 1;

    base->bytes[0x0A] = value;
    base->bytes[0x16] = value;
    base->bytes[0x22] = value;
    base->bytes[0x3A] = value;
    base->bytes[0x46] = value;

    value = -half;
    base->bytes[0x02] = value;
    base->bytes[0x0E] = value;
    base->bytes[0x1A] = value;
    base->bytes[0x32] = value;
    base->bytes[0x3E] = value;
}
