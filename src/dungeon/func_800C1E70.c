#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern u8 D_800DF63C[];
extern u8 D_800E3D20[];
extern u16 D_800E58F8[];

/* Update target tracking and smoothly approach its position and transition value. */
void func_800C75D0(void *tracker) {
    struct S_80083178 *state = &D_80083178;
    s16 frames_left;
    s16 next_frames;
    s16 target_height;
    u16 *target_pos;
    void *tracked_object;

    tracked_object = *(void **)((char *)tracker + 0x34);
    if ((tracked_object != 0) && (*(u16 *)((char *)tracked_object + 0x1E) & 0x8000)) {
        u16 *saved_pos = D_800E58F8;
        *(void **)((char *)tracker + 0x34) = 0;
        saved_pos[1] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 2);
        saved_pos[3] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 6);
        saved_pos[5] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 0xA);
        *(void **)((char *)tracker + 0xC) = saved_pos;
    }
    frames_left = *(s16 *)((char *)tracker + 0x24);
    if (frames_left > 0) {
        *(u16 *)((char *)state + 0x98) = (u16)*(s16 *)((char *)state + 0x98) +
            (*(s16 *)((char *)tracker + 0x26) - *(s16 *)((char *)state + 0x98)) / frames_left;
    } else {
        D_800E3D20[0] = 0;
    }
    next_frames = *(s16 *)((char *)tracker + 0x24) - 1;
    *(s16 *)((char *)tracker + 0x24) = next_frames;
    if (next_frames < -0x80) {
        *(s16 *)((char *)tracker + 0x24) = -0x80;
    }
    *(u16 *)((char *)tracker + 4) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 2);
    *(u16 *)((char *)tracker + 6) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 6);
    target_pos = *(u16 **)((char *)tracker + 0xC);
    target_height = func_800BCB04(target_pos[1], target_pos[3], (s16)(target_pos[5] - 0x20));
    *(s16 *)((char *)tracker + 8) = target_height;
    if (target_height >= 0x201) {
        *(s16 *)((char *)tracker + 8) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 0xA);
    }
    *(s16 *)((char *)state + 0xA4) = (u16)*(s16 *)((char *)state + 0xA4) + ((s32)((s16)*(u16 *)((char *)tracker + 4) - *(s16 *)((char *)state + 0xA4)) >> 2);
    *(s16 *)((char *)state + 0xA6) = (u16)*(s16 *)((char *)state + 0xA6) + ((s32)((s16)*(u16 *)((char *)tracker + 6) - *(s16 *)((char *)state + 0xA6)) >> 2);
    if (D_800DF63C[0] != 0) {
        *(s16 *)((char *)state + 0xA8) = (u16)*(s16 *)((char *)state + 0xA8) + ((s32)(*(s16 *)((char *)tracker + 8) - *(s16 *)((char *)state + 0xA8)) >> 2);
    }
    D_800DF63C[0] = (s8)(*(s16 *)((char *)state + 0xA8) != *(s16 *)((char *)tracker + 8));
    *(u16 *)((char *)state + 0x94) = (s32)(*(u16 *)((char *)state + 0x94) << 0x10) >> 0x12;
    *(u16 *)((char *)state + 0x96) = (s32)(*(u16 *)((char *)state + 0x96) << 0x10) >> 0x12;
}
