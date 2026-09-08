#include "common.h"

/* Copies raw bytes or decodes nibble RLE in linear or column order. */
u8 *func_800407C0(u8 *src_start, u8 *dst_start)
{
    register u8 *dst ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *column_start;
    u8 *first_row_end;
    u8 *dst_end;
    register u8 *dst_byte ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 header ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    s32 stride;
    s32 size;
    s32 remaining;
    s32 dst_high;
    s32 src_low;
    s32 nibble;
    s32 high_nibble;
    register s32 repeat_nibble ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 saved_byte;
    s32 column_byte;
    u32 packed;
    u8 *src;

    src = src_start;
    ASM_KEEP_NV(src);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    dst = dst_start;
    dst_high = 0;
    column_start = dst;
    header = *src++;
    if (header & 1) {
        for (;;) {
            packed = *src++;
            if ((packed & 0xF0) == 0) {
                remaining = (packed & 0xFF) * 2;
                if ((packed & 0xFF) == 0) {
                    goto return_linear_end;
                }
                src_low = 0;
                while (remaining > 0) {
                    if (src_low == 0) {
                        packed = *src++;
                    }
                    dst_byte = dst;
                    if (dst_high == 0) {
                        if (src_low != 0) {
                            *dst = packed & 0xF;
                        } else {
                            *dst = packed >> 4;
                        }
                    } else {
                        saved_byte = *dst;
                        dst++;
                        if (src_low != 0) {
                            high_nibble = (packed << 4) & 0xF0;
                        } else {
                            high_nibble = packed & 0xF0;
                        }
                        *dst_byte = saved_byte | high_nibble;
                    }
                    src_low ^= 1;
                    remaining--;
                    dst_high ^= 1;
                }
            } else {
                remaining = packed >> 4;
                nibble = packed & 0xF;
                repeat_nibble = nibble;
                while (remaining >= 0) {
                    if (dst_high == 0) {
                        *dst = repeat_nibble;
                    } else {
                        *dst |= nibble << 4;
                        dst++;
                    }
                    remaining--;
                    dst_high ^= 1;
                }
            }
        }
    return_linear_end:
        return dst + 1;
    }
    if (header != 0) {
        stride = header >> 1;
        size = src[0] + (src[1] << 8);
        src += 2;
        first_row_end = dst + stride;
        dst_end = dst + size;
        do {
            packed = *src++;
            if ((packed & 0xF0) == 0) {
                remaining = packed * 2;
                src_low = 0;
                while (remaining > 0) {
                    if (src_low == 0) {
                        packed = *src++;
                    }
                    if (dst_high == 0) {
                        nibble = packed & 0xF;
                        if (src_low == 0) {
                            nibble = packed >> 4;
                        }
                        *dst = nibble;
                    } else {
                        column_byte = *dst;
                        if (src_low != 0) {
                            nibble = (packed << 4) & 0xF0;
                        } else {
                            nibble = packed & 0xF0;
                        }
                        *dst = column_byte | nibble;
                    }
                    dst += stride;
                    src_low ^= 1;
                    if (dst >= dst_end) {
                        dst_high ^= 1;
                        if (dst_high == 0) {
                            column_start++;
                            if (column_start >= first_row_end) {
                                return dst_end;
                            }
                        }
                        dst = column_start;
                    }
                    remaining--;
                }
            } else {
                remaining = packed >> 4;
                nibble = packed & 0xF;
                repeat_nibble = nibble;
                while (remaining >= 0) {
                    if (dst_high == 0) {
                        *dst = repeat_nibble;
                    } else {
                        *dst |= nibble << 4;
                    }
                    dst += stride;
                    if (dst >= dst_end) {
                        dst_high ^= 1;
                        if (dst_high == 0) {
                            column_start++;
                            if (column_start >= first_row_end) {
                                return dst_end;
                            }
                        }
                        dst = column_start;
                    }
                    remaining--;
                }
            }
        } while (dst + stride < dst_end || dst_high == 0 || column_start + 1 < first_row_end);
        return dst_end;
    }
    size = src[0] + (src[1] << 8);
    memcpy(dst, src + 2, size);
    return dst + size;
}
