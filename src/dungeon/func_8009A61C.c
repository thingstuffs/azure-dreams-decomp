#include "common.h"

extern s32 func_8009FB34();
extern s32 func_800A0818(s32, s32, s32, s32, s16 *);

/* Tests whether distinct neighboring positions share a lookup value or pass the relation check. */
s32 func_8009FD7C(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y) {
    u16 src_x_bits = src_x;
    u16 src_y_bits = src_y;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 dst_x_bits = dst_x;
    u16 dst_y_bits = dst_y;
    s16 relation_detail;
    s32 src_value;
    register s32 query_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 query_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 saved_src_value;
    s32 dst_value;
    s16 *detail_out;
    s32 query_dst_x;
    s32 query_dst_y;
    s32 delta_x;
    register s32 y_work ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 signed_src_x;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 signed_src_y;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 signed_dst_x;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 signed_dst_y ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 relation_flags;
    s32 distance_x;
    s32 allowed;
    s32 distance_y;
    s32 distance;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    signed_dst_x = (s16) dst_x;
    signed_src_x = (s16) src_x;
    delta_x = signed_dst_x - signed_src_x;
    distance_x = __builtin_abs(delta_x);
    if (distance_x < 2) {
        y_work = dst_y << 0x10;
        signed_dst_y = y_work >> 0x10;
        y_work = src_y << 0x10;
        signed_src_y = y_work >> 0x10;
        y_work = signed_dst_y - signed_src_y;
        distance_y = y_work;
        if (y_work < 0) {
            distance_y = -distance_y;
        }
        if (distance_y < 2) {
            distance = distance_x + distance_y;
               /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
               /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            if (distance != 0) {
                query_x = src_x_bits & 0xFFFF;
                query_y = src_y_bits & 0xFFFF;
                src_value = func_8009FB34(query_x, query_y, dst_x << 0x10);
                   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                query_x = dst_x_bits & 0xFFFF;
                query_y = dst_y_bits & 0xFFFF;
                saved_src_value = src_value;
                dst_value = func_8009FB34(query_x, query_y);
                if ((saved_src_value << 0x10) == (dst_value << 0x10)) {
                    return 1;
                }
                query_x = signed_src_x;
                query_y = signed_src_y;
                detail_out = &relation_detail;
                ASM_KEEP(detail_out);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                query_dst_x = signed_dst_x;
                query_dst_y = signed_dst_y;
                relation_flags = (s32) (func_800A0818(query_x, query_y, query_dst_x, query_dst_y, detail_out) << 0x10) >> 0x19;
                relation_detail = (s16) relation_flags;
                allowed = 1;
                if (relation_flags & 1) {
                    goto reject;
                }
                return allowed;
            }
        }
        goto reject;
    }
reject:
    allowed = 0;
    return allowed;
}
