#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s16 func_8009FD40(void *, void *);
extern u8 D_80082E80[];
extern s8 D_80082EA6;
extern u8 D_80080000[];

/* Updates and returns the state flag using a source index and two thresholds. */
s32 func_800A19E4(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result) {
    u32 flags = F(state, u32, 0x1C);
    s8 source_index;

    if (flags & 0x20000) {
        if (flags & 0x10) {
            F(state, u32, 0x1C) = flags & ~0x20000;
            F(state, s8, 0x73) = 0;
            F(state, s8, 0x72) = 0;
            *result = -1;
            goto done;
        }
        source_index = F(source, s8, 0x26);
        if (source_index >= 0) {
            if (source_index == F(D_80080000, s8, 0x2EA6)) goto done;
        }
        if ((func_8009FD40(D_80082E80, source) << 16) >= (upper_limit << 16)) {
            F(state, s8, 0x73) = 0;
            F(state, s8, 0x72) = 0;
            F(state, u32, 0x1C) &= ~0x20000;
            *result = -1;
            goto done;
        }
        goto done;
    }
    if (!(flags & 0x10)) {
        source_index = F(source, s8, 0x26);
        if (source_index >= 0) {
            if (source_index == F(D_80080000, s8, 0x2EA6)) goto set_flag;
        }
        if ((func_8009FD40(D_80082E80, source) << 16) >= (lower_limit << 16)) goto done;
set_flag:
        F(state, u32, 0x1C) |= 0x20000;
    }
done:
    return (F(state, u32, 0x1C) >> 17) & 1;
}
