#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonTile;

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170858[];
void func_80047784(void *arg0, u8 arg1, s32 arg2);
s32 func_8009A180(void *arg0, s32 arg1);
s8 func_8009FB34(u8 arg0, u8 arg1);
s32 func_8009FD7C(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
s16 func_800A0818(u8 arg0, u8 arg1, u8 arg2, u8 arg3, void *arg4);
s32 func_800A1C58(void *arg0);
void func_800A9A0C(void *arg0);
void func_800AA258(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
s32 func_800AA6B4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
void func_800AA79C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
void func_800AA888(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
s32 func_800AA924(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
void func_800AAB10(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
void func_80173720(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
void func_8017405C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);
void func_80174924(void);
s32 func_80175C94(void *arg0, M2C_UNK arg1, void *arg2, s32 arg3);
s32 func_80175E6C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3);

extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonTile D_800E2970[];
extern u8 D_80176320[];
extern M2C_UNK D_80176358;
extern M2C_UNK D_80176360;
extern M2C_UNK D_80176370;

static __inline__ void set_map(void *arg2, void *arg3, u8 *ptr) {
    M2C_FIELD(arg2, void **, 0x2C) = (void *)ptr;
    func_80047784(arg2, ptr[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
}

void func_80173B98(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    M2C_UNK sp18;
    s32 temp_a1;
    s32 temp_v0_3;
    s8 temp_v0;
    u8 *map;
    u16 temp_v0_2;

    if (D_80083462 & 0x1000) {
        M2C_FIELD(arg0, u8 *, 0x9A) = 14;
        func_80174924();
        return;
    }
    if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (M2C_FIELD(arg2, void **, 0x2C) == &D_80176360) {
            return;
        }
        set_map(arg2, arg3, (u8 *)&D_80176358);
        return;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200) {
        if (M2C_FIELD(arg2, void **, 0x2C) == &D_80176360) {
            M2C_FIELD(arg0, u8 *, 0x9A) = 13;
            M2C_FIELD(arg0, s8 *, 0x9B) = 1;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg3, s32 *, 0x1C) &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, &D_80176358) != 0) {
            return;
        }
    }
    if (!(D_80083462 & 0x2000)) {
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }
        ASM_SCHED_BARRIER();
        if (M2C_FIELD(arg0, u8 *, 0x9A) != 14) {
            if (M2C_FIELD(arg2, void **, 0x2C) != (void *)D_80176320) {
                set_map(arg2, arg3, D_80176320);
            }
            M2C_FIELD(arg0, u8 *, 0x9A) = 14;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
        if (M2C_FIELD(arg3, s16 *, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, &D_80176370) != 0) {
                return;
            }
        }
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173720(arg0, arg1, arg2, arg3);
            return;
        }
        if ((func_800A1C58(arg3) << 0x10) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }
    temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
    if (M2C_FIELD(arg3, s8 *, 0x6D) > 0) {
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
            func_800A9A0C(arg3);
            return;
        }
        if (M2C_FIELD(arg2, u16 *, 0x24) == D_80082EA4) {
            func_8017405C(arg0, arg1, arg2, arg3);
            return;
        }
        if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((func_80175C94(arg0, arg1, arg2, 0) << 0x10) == 0) {
                return;
            }
            temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
            M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
            if (!(temp_v0_2 & 0x8000)) {
                func_8017405C(arg0, arg1, arg2, arg3);
                return;
            }
        }
        temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
        if ((u32) (temp_v0_3 - 1) >= 0xCU) {
            func_8017405C(arg0, arg1, arg2, arg3);
            return;
        }
        (void)jt_keep; goto *D_80170858[(u32)((temp_v0_3) - 1)];
jt_c9:
        if (func_80175E6C(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_8017405C(arg0, arg1, arg2, arg3);
        return;
jt_c1:
jt_c2:
jt_c3:
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c12:
        func_800A9A0C(arg3);
        return;
jt_c4:
jt_c10:
jt_c11:
        func_8017405C(arg0, arg1, arg2, arg3);
        return;
    }
    temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (!(temp_a1 & 0x2000)) {
        if (temp_v0 >= 0 && (D_800E2970[temp_v0].flags & 2)) {
            // skip
        } else if (!(temp_a1 & 0x430)) {
            map = (u8 *)&D_80082E80;
            if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(map, u8 *, 0x24), M2C_FIELD(map, u8 *, 0x25)) << 0x10) != 0) {
                M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(map, u8 *, 0x24), M2C_FIELD(map, u8 *, 0x25), &sp18);
            }
        }
    }
    if (D_80083462 & 0x2000) {
        return;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x40) {
        return;
    }
    if (M2C_FIELD(arg2, void **, 0x2C) == (void *)D_80176320) {
        return;
    }
    set_map(arg2, arg3, D_80176320);
}
