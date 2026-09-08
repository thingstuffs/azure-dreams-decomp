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

void *func_801748FC(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 *current;
    u8 *result;
    s32 coordinate;
    register u8 *sentinel ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 lower;
    s32 filter2;
    register s32 filter1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 scratch;
    u8 *object;
    s16 height;

    current = arg0;
    sentinel = current;
    ASM_KEEP_NV(sentinel);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    filter1 = arg1;
    scratch = ((S_801748FC_0 *)current)->unk_5C;
    current = (u8 *)scratch + 0x20;
    if (current != sentinel) {
        filter2 = arg2;
        scratch = arg3 << 0x10;
        coordinate = scratch >> 0x10;
        lower = coordinate - 0x20;
        do {
            object = ((S_801748FC_0_pre *)current)[-1].unk_00;
            result = current - 0x20;
            if ((((S_801748FC_1 *)object)->unk_24 == (filter1 & 0xFFFF)) &&
                (((S_801748FC_1 *)object)->unk_25 == (filter2 & 0xFFFF)) &&
                (height = ((S_801748FC_0 *)current)->unk_88,
                 height <= coordinate + 0x20) &&
                (height >= lower) &&
                ((u32)(((S_801748FC_0 *)current)->unk_13 - 0x33) >= 4U)) {
                scratch = func_800A41F0(current);
                scratch <<= 0x10;
                if (scratch != 0) {
                    return result;
                }
            }
            scratch = ((S_801748FC_0 *)current)->unk_5C;
            ASM_KEEP_NV(filter1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            current = (u8 *)scratch + 0x20;
        } while (current != sentinel);
    }

    return 0;
}

/* MECHANISM: A current/sentinel copy split plus nonempty-arm filter and coordinate lifetimes
   reproduce the 0x30 frame, s0-s6 save set, and do/while CFG. A shared pinned v0 scratch
   preserves link-load/cast roles; destructive <<= keeps the call-result shift in v0. */
