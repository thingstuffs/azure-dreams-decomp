#include "common.h"

typedef struct S_801748FC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801748FC_0_pre;   /* the 0x14 bytes before current in func_801748FC, addressed as current[-1] */

typedef struct S_801748FC_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x48];
    s32 unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_801748FC_0;   /* current in func_801748FC */

typedef struct S_801748FC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801748FC_1;   /* object in func_801748FC */



extern s32 func_800A41F0(void *);

/* Find the first eligible entry matching both object filters within 32 units of the target height. */
void *func_801748FC(void *list_head, s32 wanted_24, s32 wanted_25, s32 height_center)
{
    u8 *current;
    u8 *entry;
    s32 target_height;
    register u8 *sentinel ASM_REG("$19");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 min_height;
    s32 filter_25;
    register s32 filter_24 ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 scratch;
    u8 *object;
    s16 height;

    current = list_head;
    sentinel = current;
    ASM_KEEP_NV(sentinel);   /* MATCH pin: keeps a statement from moving across a call/branch */
    filter_24 = wanted_24;
    scratch = ((S_801748FC_0 *)current)->unk_5C;
    current = (u8 *)scratch + 0x20;
    if (current != sentinel) {
        filter_25 = wanted_25;
        scratch = height_center << 0x10;
        target_height = scratch >> 0x10;
        min_height = target_height - 0x20;
        do {
            object = ((S_801748FC_0_pre *)current)[-1].unk_00;
            entry = current - 0x20;
            if ((((S_801748FC_1 *)object)->unk_24 == (filter_24 & 0xFFFF)) &&
                (((S_801748FC_1 *)object)->unk_25 == (filter_25 & 0xFFFF)) &&
                (height = ((S_801748FC_0 *)current)->unk_88,
                 height <= target_height + 0x20) &&
                (height >= min_height) &&
                ((u32)(((S_801748FC_0 *)current)->unk_13 - 0x33) >= 4U)) {
                scratch = func_800A41F0(current);
                scratch <<= 0x10;
                if (scratch != 0) {
                    return entry;
                }
            }
            scratch = ((S_801748FC_0 *)current)->unk_5C;
            ASM_KEEP_NV(filter_24);   /* MATCH pin: load-bearing for the whole function shape */
            current = (u8 *)scratch + 0x20;
        } while (current != sentinel);
    }

    return 0;
}
