#include "common.h"

extern s32 func_800251F4();
extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s16 func_800BCB04();

/* Applies a coordinate update and triggers effects when the queried value is within bounds. */
void func_80025648(s32 object, s32 raw_x, s32 raw_y, s32 raw_upper, s32 lower_bound) {
    s32 x = raw_x;
    s32 y = raw_y;
    register s32 call_x ASM_REG("$3") = x;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call_y ASM_REG("$5") = y;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 object_data ASM_REG("$20") = object + 0x20;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 upper = (s16)raw_upper;
    register s32 raw_lower ASM_REG("$6") = lower_bound;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 shifted_lower ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 lower ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs object_data+offset) depends on it */
    s32 query_x;
    s32 query_y;
    s16 query_value;

    if (upper < 0x200) {
        ASM_KEEP(call_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        query_x = call_x & 0xFFFF;
        query_y = call_y & 0xFFFF;
        ASM_KEEP(raw_lower);   /* MATCH pin: retail schedule: same instructions, different order without it */
        shifted_lower = raw_lower << 16;
        lower = shifted_lower >> 16;
        query_value = func_800BCB04(query_x, query_y, lower, raw_upper << 16);
        if (query_value < upper && query_value >= lower) {
            func_800251F4(object_data, (s16)x, (s16)y, upper);
            ASM_KEEP(lower);   /* MATCH pin: load-bearing for the whole function shape */
            func_800419EC(6, 12);
            func_800A56E0(0x50B);
        }
    }
}
