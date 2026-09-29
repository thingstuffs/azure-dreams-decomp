#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80024398_0_pre {
    u16 unk_00;
} S_80024398_0_pre;   /* the 0x2 bytes before arg0 in func_80024398, addressed as arg0[-1] */

typedef struct S_80024398_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4];
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
} S_80024398_0;   /* arg0 in func_80024398 */

typedef struct S_80024398_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80024398_1;   /* parent in func_80024398 */

typedef struct S_80024398_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80024398_2;   /* node in func_80024398 */

extern s16 D_8002992E[5];

/* Adjusts node scale by countdown phase, restoring unity and setting completion flags at the end. */
void func_80024398(void *effect)
{
    u32 scale_x;
    u32 scale_y;
    s32 ticks_left;
    s16 next_ticks;
    u16 old_scale;
    u16 new_scale;
    S_80024398_2 *node;

    ticks_left = ((S_80024398_0 *)effect)->unk_28.s;
    D_8002992E[0] = 1;

    {
        S_80024398_1 *parent;

        parent = ((S_80024398_0 *)effect)->unk_20;
        node = parent->unk_0C;
    }

    if (ticks_left >= 0x1F) {
        scale_x = node->unk_1C;
        scale_y = node->unk_1E;
        scale_x += 0x88;
        scale_y += 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else if (ticks_left >= 0x19) {
        scale_x = node->unk_1C - 0x88;
        scale_y = node->unk_1E - 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else if (ticks_left >= 0x10) {
        scale_x = node->unk_1C + 0x88;
        scale_y = node->unk_1E + 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else if (ticks_left >= 0xA) {
        scale_x = node->unk_1C - 0x88;
        scale_y = node->unk_1E - 0x88;
        node->unk_1C = scale_x;
        node->unk_1E = scale_y;
    } else {
        old_scale = node->unk_1C;
        if (old_scale < 0x1000U) {
            new_scale = old_scale + 0x88;
            node->unk_1C = new_scale;
            if ((u16)new_scale >= 0x1001U) {
                node->unk_1C = 0x1000U;
            }
        }

        old_scale = node->unk_1E;
        if (old_scale < 0x1000U) {
            new_scale = old_scale + 0x88;
            node->unk_1E = new_scale;
            if ((u16)new_scale >= 0x1001U) {
                node->unk_1E = 0x1000U;
            }
        }
    }

    next_ticks = ((S_80024398_0 *)effect)->unk_28.u - 1;
    ((S_80024398_0 *)effect)->unk_28.s = next_ticks;
    if ((next_ticks << 16) <= 0) {
        node->unk_1E = 0x1000U;
        node->unk_1C = 0x1000U;
        ((S_80024398_0_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
