#include "common.h"

extern s32 func_800251F4();
extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s16 func_800BCB04();

/* Applies a coordinate update and triggers effects when the queried value is within bounds. */
void func_80025648(s32 object, s32 raw_x, s32 raw_y, s32 raw_upper, s32 lower_bound) {
    s32 x = raw_x;
    s32 y = raw_y;
    register s32 call_x ASM_REG("$3") = x;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 call_y ASM_REG("$5") = y;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 object_data ASM_REG("$20") = object + 0x20;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 upper = (s16)raw_upper;
    register s32 shifted_lower ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 lower ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 query_x;
    s32 query_y;
    s16 query_value;

    if (upper < 0x200) {
        ASM_KEEP(call_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        query_x = call_x & 0xFFFF;
        query_y = call_y & 0xFFFF;
        ASM_KEEP(lower_bound);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        shifted_lower = lower_bound << 16;
        lower = shifted_lower >> 16;
        query_value = func_800BCB04(query_x, query_y, lower, raw_upper << 16);
        if (query_value < upper && query_value >= lower) {
            func_800251F4(object_data, (s16)x, (s16)y, upper);
            ASM_KEEP(lower);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            func_800419EC(6, 12);
            func_800A56E0(0x50B);
        }
    }
}
