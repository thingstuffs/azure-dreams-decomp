#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    Vec3 first;
    Vec3 second;
} Pair;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused_0C;
    s32 unused_10;
} Work;

extern s32 func_800374F4();
extern void func_80097AD0();
extern void func_800A895C();
extern Pair D_80089128;
extern void *memcpy();

/* Process a position and its raised copy using a local vector pair. */
void func_800A8ADC(s32 unused_arg, s32 *position) {
    Pair pair;
    Work raised_pos;
    u8 *data_page;
    Pair *pair_source;
    s32 x_or_result;
    s32 second_z;
    register s32 second_y ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *call_data = position;
    void *input_pos;

#ifdef NON_MATCHING
    data_page = (u8 *)&D_80089128 + 0x6ED8;
#else
    data_page = (u8 *)0x80090000;
#endif
    ASM_KEEP_NV(data_page);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    pair_source = (Pair *)(data_page - 0x6ED8);
    ASM_KEEP_NV(pair_source);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    memcpy(&pair.first, &pair_source->first, sizeof(Vec3));
    x_or_result = pair_source->second.x;
    ASM_USE2_NV(data_page, x_or_result);   /* MATCH pin: load-bearing for the whole function shape */
    second_y = pair_source->second.y;
    second_z = pair_source->second.z;
    pair.second.x = x_or_result;
    pair.second.y = second_y;
    pair.second.z = second_z;
    ASM_USE_NV(second_y);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_USE_NV(call_data);   /* MATCH pin: load-bearing for the whole function shape */
    raised_pos.x = ((s32 *)call_data)[0];
    raised_pos.y = ((s32 *)call_data)[1];
    raised_pos.z = ((s32 *)call_data)[2] + 0x100000;
    x_or_result = func_800374F4(2, second_z, pair_source);
    input_pos = call_data;
    call_data = &pair;
    func_800A895C(input_pos, call_data, (x_or_result & 0xFFFF) + 2);
    func_80097AD0(&raised_pos, call_data, (func_800374F4(2) & 0xFFFF) + 2);
}
