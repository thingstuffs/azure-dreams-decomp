#include "common.h"

#include "common.h"

/* Decompress an LZ stream with LSB-first flags and return the end of the output. */
u8 *func_8004068C(u8 *src, u8 *dst) {
    u32 flags;
    register s32 bits_left ASM_REG("$8");
    u32 offset;
    s32 copy_count;
    u8 *copy_src;

    flags = 0;
    bits_left = 1;

loop:
    bits_left = bits_left - 1;
next:
    if (bits_left != 0) {

    } else {
        flags = *src;
        src = src + 1;
        bits_left = 8;
    }
    if ((flags & 1) != 0) {
        goto match;
    }

    flags = flags >> 1;
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
    goto loop;

match:
    bits_left = bits_left - 1;
    flags = flags >> 1;
    if (bits_left == 0) {
        flags = *src;
        src = src + 1;
        bits_left = 8;
    }
    if ((flags & 1) != 0) {
        goto short_match;
    }

    offset = (*src << 8) | src[1];
    flags = flags >> 1;
    if (offset == 0) {
        goto done;
    }
    copy_count = (s32)(offset & 0xF);
    src = src + 2;
    if (copy_count != 0) {
        copy_count = copy_count + 2;
        goto copy_setup;
    }
    copy_count = (s32)(*src) + 1;
    src = src + 1;
copy_setup:
    offset = offset >> 4;
    goto do_copy;

short_match:
    bits_left = bits_left - 1;
    flags = flags >> 1;
    if (bits_left == 0) {
        flags = *src;
        src = src + 1;
        bits_left = 8;
    }
    copy_count = (s32)((flags & 1) << 1);
    bits_left = bits_left - 1;
    flags = flags >> 1;
    if (bits_left == 0) {
        flags = *src;
        src = src + 1;
        bits_left = 8;
    }
    copy_count = copy_count + 2;
    copy_count = copy_count + (s32)(flags & 1);
    flags = flags >> 1;
    offset = *src;
    src = src + 1;
    if (offset == 0) {
        offset = 0x100;
    }

do_copy:
    copy_src = dst - offset;
    if (copy_count == 0) {
        goto loop;
    }
    do {
        *dst = *copy_src;
        copy_src = copy_src + 1;
        copy_count = copy_count - 1;
        dst = dst + 1;
    } while (copy_count != 0);
    bits_left = bits_left - 1;
    goto next;

done:
    return dst;
}
