#include "common.h"

#define F(base, type, off) (*(type *)((char *)(base) + (off)))

extern void *D_800DF364[];
extern void *D_800E3D7C[];
extern s32 D_800814A0[];
extern s32 D_8008346C[];

extern void func_800A56E0(s32);
extern void func_800478B8(void *, void *, void *);

/* Updates a target marker's position, scale, color, and rotation. */
void func_800B96C4(void *state, void *position_arg, void *marker_arg) {
    void *target;
    void *target_pos;

    if (F(state, s16, 0xC) == 0) {
        void *tracked_target = F(F(state, void *, 0), void *, 0);
        if (tracked_target != 0) {
            if (D_800DF364[0] != tracked_target) {
                func_800A56E0(0x507);
                F(state, s16, 0xE) = 4;
                D_800DF364[0] = F(F(state, void *, 0), void *, 0);
            }
        } else {
            void *fallback_target;
            u16 phase;
            F(state, s16, 0xE) = 4;
            fallback_target = D_800E3D7C[0];
            phase = F(state, u16, 0xC);
            D_800DF364[0] = fallback_target;
            F(state, u16, 0xC) = phase + 1;
        }
        if (F(marker_arg, u16, 0x1C) < 0x1000) {
            u16 next_scale = F(marker_arg, u16, 0x1E) + 0x200;
            F(marker_arg, u16, 0x1E) = next_scale;
            F(marker_arg, u16, 0x1C) = next_scale;
            if (next_scale >= 0x1001) {
                F(marker_arg, u16, 0x1E) = 0x1000;
                F(marker_arg, u16, 0x1C) = 0x1000;
            }
        }
    } else {
        s16 frames_left = F(state, s16, 0xE);
        if (frames_left != 0) {
            u16 scale = F(marker_arg, u16, 0x1E);
            u16 next_scale = (u16)((s32)scale - (s32)scale / frames_left);
            F(marker_arg, u16, 0x1E) = next_scale;
            F(marker_arg, u16, 0x1C) = next_scale;
        } else {
            F(marker_arg, u16, 0x1E) = 0;
            F(marker_arg, u16, 0x1C) = 0;
        }
    }

    {
        void *tracked_target = F(F(state, void *, 0), void *, 0);
        if (tracked_target == 0) {
            F(marker_arg, s32, 0xC) = 0x808080;
        } else if (tracked_target == F(D_800E3D7C[0], void *, 0xAC)) {
            F(marker_arg, s32, 0xC) = 0x101080;
        } else {
            F(marker_arg, s32, 0xC) = 0x801010;
        }
    }
    target = D_800DF364[0];
    target_pos = F((char *)target - 0x18, void *, 0);
    if (F(state, s16, 0xE) != 0) {
        F(((void *)(position_arg)), s32, 0) = F(((void *)(position_arg)), s32, 0) + (F(target_pos, s32, 0) - F(((void *)(position_arg)), s32, 0)) / F(state, s16, 0xE);
        F(((void *)(position_arg)), s32, 4) = F(((void *)(position_arg)), s32, 4) + (F(target_pos, s32, 4) - F(((void *)(position_arg)), s32, 4)) / F(state, s16, 0xE);
        F(((void *)(position_arg)), s32, 8) = F(((void *)(position_arg)), s32, 8) + (((s32)(F(target, s16, 0x88) - F(((void *)(position_arg)), s16, 0xA))) << 16) / F(state, s16, 0xE);
        {
            s16 frames_left = F(state, u16, 0xE) - 1;
            F(state, u16, 0xE) = frames_left;
            if (frames_left == 0) {
                if (F(state, s16, 0xC) == 0) {
                    F(((void *)(position_arg)), u16, 2) = F(target_pos, u16, 2);
                    F(((void *)(position_arg)), u16, 6) = F(target_pos, u16, 6);
                    F(((void *)(position_arg)), u16, 0xA) = F(target, u16, 0x88);
                } else {
                    F(state, u16, -2) = F(state, u16, -2) | 0x8000;
                    D_8008346C[0] = 0;
                    D_800814A0[0] = D_800814A0[0] | 0x8000;
                }
            }
        }
    }
    F(marker_arg, u16, 0x1A) = F(marker_arg, u16, 0x1A) + 0x40;
    func_800478B8(marker_arg, target_pos, target);
}
