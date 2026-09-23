#include "common.h"

extern s32 func_8009FB34();
extern s32 func_800A0818(s32, s32, s32, s32, s16 *);

/* Tests whether distinct neighboring positions share a lookup value or pass the relation check. */
s32 func_8009FD7C(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y) {
    u16 src_x_bits = src_x;
    u16 src_y_bits = src_y;
    u16 dst_x_bits = dst_x;
    u16 dst_y_bits = dst_y;
    s16 relation_detail;
    s32 src_value;
    s32 query_x;
    s32 query_y;
    s32 saved_src_value;
    s32 dst_value;
    s32 query_dst_x;
    s32 query_dst_y;
    s32 delta_x;
    register s32 detail_out;
    s32 signed_dst_y;
    s32 signed_src_x;
    s32 signed_src_y;
    s32 signed_dst_x;
    s32 relation_flags;
    s32 distance_x;
    s32 allowed;
    s32 distance_y;

    signed_dst_x = (s16) dst_x;
    signed_src_x = (s16) src_x;
    delta_x = signed_dst_x - signed_src_x;
    distance_x = __builtin_abs(delta_x);
    if (distance_x < 2) {
        signed_dst_y = (s16)dst_y;
        signed_src_y = (s16)src_y;
        detail_out = signed_dst_y - signed_src_y;
        distance_y = __builtin_abs(detail_out);
        if (distance_y < 2) {
            detail_out = distance_x + distance_y;
            if (detail_out != 0) {
                query_x = src_x_bits & 0xFFFF;
                query_y = src_y_bits & 0xFFFF;
                src_value = func_8009FB34(query_x, query_y);
                query_x = dst_x_bits & 0xFFFF;
                query_y = dst_y_bits & 0xFFFF;
                saved_src_value = src_value;
                dst_value = func_8009FB34(query_x, query_y);
                if ((saved_src_value << 0x10) == (dst_value << 0x10)) {
                    return 1;
                }
                query_x = signed_src_x;
                query_y = signed_src_y;
                query_dst_x = signed_dst_x;
                query_dst_y = signed_dst_y;
                relation_flags = (s32) (func_800A0818(query_x, query_y, query_dst_x, query_dst_y, &relation_detail) << 0x10) >> 0x19;
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
