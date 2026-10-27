#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B34FC_1 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800B34FC_1;   /* arg0 in advance_five_step_fixed_point_ramp */

typedef struct S_800B34FC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800B34FC_2;   /* ((S_800B34FC_1 *)arg0)->unk_9C in advance_five_step_fixed_point_ramp */


typedef struct S_800B34FC_0 {
    void (*unk_00)();
    u8 pad_04[0x14];
    s32 unk_18;
} S_800B34FC_0;   /* arg0 in advance_five_step_fixed_point_ramp; pointer addresses record offset 0x10 */


extern void D_800B34A8(void *object);

/* Advance the five-step fixed-point ramp and switch callbacks after the final step. */
void advance_five_step_fixed_point_ramp(void *sub_object) {
    s32 next_step;

    ((S_800B34FC_2 *)(((S_800B34FC_1 *)sub_object)->unk_9C))->unk_06 =
        (s16) ((((S_800B34FC_0 *)((u8 *)sub_object - 0x10))->unk_18 << 0xC) / 5);
    next_step = ((S_800B34FC_0 *)((u8 *)sub_object - 0x10))->unk_18 + 1;
    ((S_800B34FC_0 *)((u8 *)sub_object - 0x10))->unk_18 = next_step;
    if (next_step >= 6) {
        ((S_800B34FC_0 *)((u8 *)sub_object - 0x10))->unk_00 = &D_800B34A8;
    }
}
