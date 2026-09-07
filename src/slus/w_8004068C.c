#include "common.h"

#include "common.h"

/* Bitstream LZ decompressor: LSB-first flag bits, returns end of dst. */
u8 *func_8004068C(u8 *src, u8 *dst) {
    u32 flags; /* a3 */
    register s32 bitcnt ASM_REG("$8"); /* t0 */
    u32 offset;
    s32 count;
    u8 *from;

    flags = 0;
    bitcnt = 1;

loop:
    bitcnt = bitcnt - 1;
next:
    if (bitcnt != 0) {
        /* fall through with existing flags */
    } else {
        flags = *src;
        src = src + 1;
        bitcnt = 8;
    }
    if ((flags & 1) != 0) {
        goto match;
    }
    /* literal */
    flags = flags >> 1;
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
    goto loop;

match:
    bitcnt = bitcnt - 1;
    flags = flags >> 1;
    if (bitcnt == 0) {
        flags = *src;
        src = src + 1;
        bitcnt = 8;
    }
    if ((flags & 1) != 0) {
        goto short_match;
    }
    /* long match: BE u16 */
    offset = (*src << 8) | src[1];
    flags = flags >> 1;
    if (offset == 0) {
        goto done;
    }
    count = (s32)(offset & 0xF);
    src = src + 2;
    if (count != 0) {
        count = count + 2;
        goto copy_setup;
    }
    count = (s32)(*src) + 1;
    src = src + 1;
copy_setup:
    offset = offset >> 4;
    goto do_copy;

short_match:
    bitcnt = bitcnt - 1;
    flags = flags >> 1;
    if (bitcnt == 0) {
        flags = *src;
        src = src + 1;
        bitcnt = 8;
    }
    count = (s32)((flags & 1) << 1);
    bitcnt = bitcnt - 1;
    flags = flags >> 1;
    if (bitcnt == 0) {
        flags = *src;
        src = src + 1;
        bitcnt = 8;
    }
    count = count + 2;
    count = count + (s32)(flags & 1);
    flags = flags >> 1;
    offset = *src;
    src = src + 1;
    if (offset == 0) {
        offset = 0x100;
    }

do_copy:
    from = dst - offset;
    if (count == 0) {
        goto loop;
    }
    do {
        *dst = *from;
        from = from + 1;
        count = count - 1;
        dst = dst + 1;
    } while (count != 0);
    bitcnt = bitcnt - 1;
    goto next;

done:
    return dst;
}
