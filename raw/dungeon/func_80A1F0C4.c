#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80170858[];
extern u8 D_8006DE24[20];
extern u8 *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[16];
extern s32 D_8008346C[3];
extern u8 D_80083498[16];
extern u8 D_80170E84[];
extern u8 D_80174820[];
extern u8 D_80174850[];

extern s32 func_8003F270();
extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80045340(void);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800DA840(void *, s32);
extern void func_801740FC(void);

void func_801728C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_1, &&jt_2, &&jt_3, &&jt_4, &&jt_5, &&jt_6, &&jt_7
    };
    u16 pos[3];
    u16 delta[3];
    s32 state;
    u32 kind;
    register u32 dispatch_raw ASM_REG("$2");
    register u32 dispatch_kind ASM_REG("$3");
    s32 normal_kind;
    s32 mode;
    register s32 mode_test ASM_REG("$2");
    s32 count;
    register s32 next_state ASM_REG("$2");
    u8 *anim;
    u16 timer;
    void *entity;
    void *part;
    void *parent;
    register u32 callback_page ASM_REG("$2");
    void (*callback)(void);
    void *global;
    register void *mode_global ASM_REG("$2");
    u8 *global_state;
    s32 x;
    s32 y;
    u16 flags;

    mode = 0;
    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    if (!(FIELD(arg3, s32, 0x1C) & 0x2000)) {
        goto no_special;
    }
    dispatch_raw = FIELD(arg3, u16, 0x46) & 0x3FFF;
    ASM_KEEP_NV(dispatch_raw);
    dispatch_kind = dispatch_raw - 1;
    ASM_KEEP_NV(dispatch_kind);
    if (dispatch_kind >= 7) {
        goto jt_4;
    }
    (void)jt_keep;
    goto *D_80170858[dispatch_kind];

jt_7:
    mode = 1;
    goto no_3;
jt_6:
    mode = 1;
    goto no_2;
jt_5:
    mode = 1;
    goto no_1;

no_special:
    normal_kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (normal_kind == 2) {
        goto no_2;
    }
    if (normal_kind < 3) {
        if (normal_kind == 1) {
            goto no_1;
        }
        anim = 0;
        goto selected;
    }
    if (normal_kind != 3) {
        anim = 0;
        goto selected;
    }
no_3:
jt_3:
    anim = (u8 *)arg3 + 0xE;
    goto selected;
no_2:
jt_2:
    anim = (u8 *)arg3 + 0xB;
    goto selected;
no_1:
jt_1:
    anim = (u8 *)arg3 + 8;
    goto selected;
jt_4:
    anim = 0;

selected:
    if (*anim == 0) {
        goto empty_anim;
    }
    FIELD(arg0, volatile u16, 0x98) &= 0xFF7F;
    ASM_SCHED_BARRIER();
    mode_test = mode;
    ASM_KEEP_NV(mode_test);
    if (mode_test != 0) {
        mode_global = D_800814A8;
        ASM_KEEP_NV(mode_global);
        FIELD(arg3, void *, 0x60) = mode_global;
        parent = FIELD(mode_global, void *, -0x14);
        goto copy_parent;
    }

    kind = *anim;
    if (D_8006DE24[kind * 0x14 + 0x12] == 2) {
        parent = FIELD(arg3, void *, 0x60);
        if (parent != 0) {
            parent = FIELD(parent, void *, -0x14);
copy_parent:
            FIELD(arg3, u8, 0x72) = FIELD(parent, u8, 0x24);
            FIELD(arg3, u8, 0x73) = FIELD(parent, u8, 0x25);
            goto object_ready;
        }
    } else {
        FIELD(arg3, void *, 0x60) = func_800A05A4(
            arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A), 0x10);
        ASM_MEM_BARRIER();
        x = FIELD(arg3, s8, 0x72);
        y = FIELD(arg3, s8, 0x73);
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        FIELD(arg3, u8, 0x72) = x;
        FIELD(arg3, u8, 0x73) = y;
    }

object_ready:
    pos[0] = FIELD(arg1, u16, 2);
    pos[1] = FIELD(arg1, u16, 6);
    pos[2] = FIELD(arg1, u16, 0xA);
    if (func_800A94A0(arg3, anim, mode, (u8 *)arg0 + 0x98) != 0) {
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(pos, (s16)((*anim - 1) % 3));
        next_state = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, u16, 0x96) = 30000;
        goto increment_state;
    }
    goto done;

empty_anim:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    global = D_800814A8;
    D_8008346C[0] = 0;
    FIELD(global, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_80170E84;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto done;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_2:
    if (func_8003DE58(FIELD(arg2, void *, 8), arg2, delta, 0) == 0) {
        delta[0] = delta[1] = delta[2] = 0;
    }
    if ((FIELD(arg2, s8, 4) == 3 && (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 6;
        FIELD(arg0, u16, 0x98) |= 0x80;
        if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
            flags = FIELD(arg0, volatile u16, 0x98);
            FIELD(arg0, u16, 0x98) = flags | 0x8000;
            entity = func_8003FD64(0x112, D_80083498);
            if (entity != 0) {
                func_8004491C(entity, func_80045340);
                part = (u8 *)entity + 0x20;
                FIELD(entity, void *, 0x10) = func_801740FC;
                FIELD(FIELD(entity, void *, 8), u16, 2) =
                    FIELD(arg1, u16, 2) + delta[0];
                FIELD(FIELD(entity, void *, 8), u16, 6) =
                    FIELD(arg1, u16, 6) + delta[1];
                FIELD(FIELD(entity, void *, 8), u16, 0xA) =
                    FIELD(arg1, u16, 0xA) + delta[2];
                FIELD(part, s32, 0xA4) = 0;
                FIELD(part, u16, 0x96) = 4;
                parent = FIELD(entity, void *, 0xC);
                FIELD(parent, s32, 0x28) = FIELD(arg2, s32, 0x28);
                FIELD(parent, u16, 0x1E) = 0x1000;
                FIELD(parent, u16, 0x1C) = 0x1000;
                FIELD(parent, u16, 0x14) = FIELD(arg2, u16, 0x14);
                FIELD(parent, u16, 0x12) = FIELD(arg2, u16, 0x12);
                FIELD(parent, void *, 0xC) = FIELD(arg2, void *, 0xC);
                func_80047784(parent, 0x2D, 0);
            }
        }
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((s32)(timer << 16) <= 0) {
        FIELD(arg0, u16, 0x98) &= 0x7FFF;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }

    if (FIELD(arg0, u16, 0x98) & 0x8000) {
        callback_page = 0x80170000;
        ASM_KEEP(callback_page);
        count = 7;
        callback = (void *)(callback_page + 0x40FC);
        do {
            entity = func_8003FD64(0x112, D_80083498);
            if (entity != 0) {
                func_8004491C(entity, func_80045340);
                FIELD(entity, void *, 0x10) = callback;
                FIELD(FIELD(entity, void *, 8), u16, 2) =
                    FIELD(arg1, u16, 2) + delta[0] + (func_80069EF8() & 0xF) - 8;
                FIELD(FIELD(entity, void *, 8), u16, 6) =
                    FIELD(arg1, u16, 6) + delta[1] + (func_80069EF8() & 0xF) - 8;
                FIELD(FIELD(entity, void *, 8), u16, 0xA) =
                    FIELD(arg1, u16, 0xA) + delta[2] + (func_80069EF8() & 0xF) - 8;
                FIELD(FIELD(entity, void *, 8), s32, 0xC) =
                    ((func_80069EF8() & 0xFF) - 0x80) << 11;
                FIELD(FIELD(entity, void *, 8), s32, 0x10) =
                    ((func_80069EF8() & 0xFF) - 0x80) << 11;
                FIELD(FIELD(entity, void *, 8), s32, 0x14) =
                    -(func_80069EF8() & 0xFF) << 12;
                part = (u8 *)entity + 0x20;
                FIELD(part, s32, 0xA4) = 0;
                FIELD(part, u16, 0x96) = 7;
                parent = FIELD(entity, void *, 0xC);
                FIELD(parent, s32, 0x28) = FIELD(arg2, s32, 0x28);
                FIELD(parent, u16, 0x1E) = 0x1000;
                FIELD(parent, u16, 0x1C) = 0x1000;
                FIELD(parent, u16, 0x14) = FIELD(arg2, u16, 0x14);
                FIELD(parent, u16, 0x12) = FIELD(arg2, u16, 0x12) - 0x80;
                FIELD(parent, u16, 0x10) = 0x60;
                FIELD(parent, s32, 0xC) = 0x00808080;
                FIELD(parent, u16, 0x14) |= 0xC;
                func_80047784(parent, 0x2F, 0);
            }
            count--;
        } while (count >= 0);
    }

    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg2, void *, 0x2C) = D_80174850;
        func_80047784(
            arg2,
            D_80174850[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        next_state = FIELD(arg0, u8, 0x9B);
increment_state:
        ASM_KEEP_NV(next_state);
        FIELD(arg0, u8, 0x9B) = next_state + 1;
        goto done;
    }
    goto done;

state_3:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, void *, 0x2C) != D_80174820) {
        FIELD(arg2, void *, 0x2C) = D_80174820;
        func_80047784(
            arg2,
            D_80174820[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    global_state = D_80083460;
    if (FIELD(global_state, s32, 0xC) == 0) {
        FIELD(global_state, u16, 0xA)--;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, void *, 0x8C) = D_80170E84;
        func_800A4ACC(arg3);
        if (FIELD(arg3, s8, 0x6D) > 0) {
            FIELD(arg3, u8, 0x6D)--;
        }
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

done:
    return;
}
