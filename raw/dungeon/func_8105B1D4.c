#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_80170F68;
extern u8 D_80173FB8[8];

extern s32 func_8003F270();
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_800DA840();
extern void func_80172AE0(void) __attribute__((noreturn));
extern void func_80172AE8(void) __attribute__((noreturn));
extern void func_80172AF0(void) __attribute__((noreturn));
extern void func_80172AFC(void) __attribute__((noreturn));
extern void func_80172B9C(void) __attribute__((noreturn));
extern void func_80172E64(void) __attribute__((noreturn));

void func_801729D4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_1, &&jt_2, &&jt_3, &&jt_4, &&jt_5, &&jt_6, &&jt_7
    };
    u16 pos[3];
    register u8 *anim ASM_REG("$16");
    register s32 mode ASM_REG("$20");
    register s32 mode_test ASM_REG("$2");
    s32 state;
    s32 kind;
    void *root;
    void *source;
    void *created;
    u8 *status;
    s32 x;
    s32 y;

    state = FIELD(arg0, u8, 0x9B);
    mode = 0;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_80172E64();
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_2;
    }
    func_80172E64();

state_0:
    if (!(FIELD(arg3, s32, 0x1C) & 0x2000)) {
        goto no_special;
    }
    kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
    if ((u32)kind >= 7U) {
        goto jt_4;
    }
    (void)jt_keep;
    goto *(((void **)D_80170838)[kind]);

jt_7:
    mode = 1;
    ASM_TAILSLOT_PIN(mode);
    func_80172AE0();
jt_6:
    mode = 1;
    ASM_TAILSLOT_PIN(mode);
    func_80172AE8();
jt_5:
    mode = 1;
    ASM_TAILSLOT_PIN(mode);
    func_80172AF0();

no_special:
    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (kind == 2) {
        goto no_2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto no_1;
        }
        anim = 0;
        ASM_KEEP(anim);
        func_80172AFC();
    }
    if (kind == 3) {
        goto no_3;
    }
    anim = 0;
    goto selected;

no_3:
jt_3:
    anim = (u8 *)arg3 + 0xE;
    ASM_TAILSLOT_PIN(anim);
    func_80172AFC();
no_2:
jt_2:
    anim = (u8 *)arg3 + 0xB;
    ASM_TAILSLOT_PIN(anim);
    func_80172AFC();
no_1:
jt_1:
    anim = (u8 *)arg3 + 8;
    ASM_TAILSLOT_PIN(anim);
    func_80172AFC();
jt_4:
    anim = 0;

selected:
    if (*anim == 0) {
        goto empty_anim;
    }
    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_KEEP(mode);
    mode_test = mode;
    ASM_KEEP(mode_test);
    if (mode_test != 0) {
        root = D_800814A8;
        FIELD(arg3, void *, 0x60) = root;
        source = FIELD(root, void *, -0x14);
        FIELD(arg3, u8, 0x72) = FIELD(source, u8, 0x24);
        FIELD(arg3, u8, 0x73) = FIELD(source, u8, 0x25);
        func_80172B9C();
    }

    ASM_SCHED_BARRIER();
    created = func_800A05A4(
        arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
        FIELD(arg3, s16, 0x2A), 0x10);
    FIELD(arg3, void *, 0x60) = created;
    ASM_SCHED_BARRIER();
    x = FIELD(arg3, s8, 0x72);
    y = FIELD(arg3, s8, 0x73);
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    ASM_SCHED_BARRIER();
    FIELD(arg3, u8, 0x72) = x;
    FIELD(arg3, u8, 0x73) = y;
    ASM_SCHED_BARRIER();

    pos[0] = FIELD(arg1, u16, 2);
    pos[1] = FIELD(arg1, u16, 6);
    pos[2] = FIELD(arg1, u16, 0xA);
    if (func_800A94A0(arg3, anim, mode, (u8 *)arg0 + 0x98) != 0) {
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(pos, (s16)((*anim - 1) % 3));
        FIELD(arg0, u8, 0x9B)++;
        func_80172E64();
    }
    goto done;

empty_anim:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = &D_80170F68;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_80172E64();

state_1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        func_80172E64();
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state_2:
    if ((FIELD(arg2, s8, 4) == 8 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 3;
        FIELD(arg0, u16, 0x98) |= 0x80;
    }
    FIELD(arg0, u16, 0x96)--;
    if ((s16)FIELD(arg0, u16, 0x96) <= 0) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        if (FIELD(arg2, void *, 0x2C) != D_80173FB8) {
            FIELD(arg2, void *, 0x2C) = D_80173FB8;
            func_80047784(
                arg2,
                D_80173FB8[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        status = (u8 *)&D_80083460;
        if (FIELD(status, s32, 0xC) == 0) {
            FIELD(status, u16, 0xA)--;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
            FIELD(arg0, void *, 0x8C) = &D_80170F68;
            func_800A4ACC(arg3);
            if (FIELD(arg3, s8, 0x6D) > 0) {
                FIELD(arg3, u8, 0x6D)--;
            }
            FIELD(arg3, u8, 0x73) = 0;
            FIELD(arg3, u8, 0x72) = 0;
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
            func_800A56E0(0xB4);
        }
    }

done:
    return;
}

/* MECHANISM: The s4 guard is delayed until its body use so the entry assignment
   can fill retail's state-dispatch branch slot without splitting the save block.
   Fences stop slot theft; distinct root/source/call ranges preserve v0/v1 roles. */
