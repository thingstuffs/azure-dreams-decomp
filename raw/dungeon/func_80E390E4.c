#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef __SIZE_TYPE__ uptr;

typedef struct {
    u8 pad00[0x12];
    u8 field12;
    u8 field13;
} ItemInfo;

extern ItemInfo D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern u8 D_80083460[0x18];
extern void *D_80170838[5];
extern void *D_80170850[7];
extern u8 D_80170EE4[8];
extern u8 D_801765D8[8];
extern u8 D_80176648[8];
extern u8 D_80176668[8];

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, u16 *);
extern void func_800BB044(void *);

void func_801728E4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    register s32 special ASM_REG("$20");
    u16 flags;
    s32 kind;
    register u8 *table ASM_REG("$5");
    static void *const state_labels[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };
    static void *const kind_labels[] = {
        &&K8, &&KB, &&KE, &&KNone, &&K8Special, &&KBSpecial, &&KESpecial
    };

    state = FIELD(arg0, u8, 0x9B);
    special = 0;
    if ((u32)state >= 5) {
        return;
    }
    goto *D_80170838[state];

L0:
{
    register void *source ASM_REG("$2");

    arg1 = 0;
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        s32 index = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;

        if ((u32)index >= 7) {
            goto HaveSource;
        }
        goto *D_80170850[index];

KESpecial:
        special = 1;
        goto KE;
KBSpecial:
        special = 1;
        goto KB;
K8Special:
        special = 1;
        goto K8;
    }

    kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    switch (kind) {
    case 1:
        goto K8;
    case 2:
        goto KB;
    case 3:
        goto KE;
    default:
        goto HaveSource;
    }

KE:
    arg1 = (u8 *)arg3 + 0xE;
    goto HaveSource;
KB:
    arg1 = (u8 *)arg3 + 0xB;
    goto HaveSource;
K8:
    arg1 = (u8 *)arg3 + 8;
KNone:
HaveSource:
    if (FIELD(arg1, u8, 0) == 0) {
        return;
    }

    {
        register s32 special_test ASM_REG("$2");

        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        ASM_MEM_BARRIER();
        special_test = special;
        ASM_KEEP(special_test);
        if (special_test) {
            source = D_800814A8;
            FIELD(arg3, void *, 0x60) = source;
            goto CopyFacing;
        }
    }

    if (D_8006DE24[FIELD(arg1, u8, 0)].field12 != 2) {
        goto MakeSource;
    }

    source = FIELD(arg3, void *, 0x60);
    if (source == 0) {
        goto CallUpdate;
    }

CopyFacing:
    ASM_KEEP(arg3);
    {
        u8 *entry = *(u8 **)((u8 *)source - 0x14);
        ASM_KEEP(source);
        FIELD(arg3, u8, 0x72) = FIELD(entry, u8, 0x24);
        FIELD(arg3, u8, 0x73) = FIELD(entry, u8, 0x25);
    }
    goto Update;
}

MakeSource:
    {
        s32 x;
        s32 z;

        FIELD(arg3, void *, 0x60) =
            func_800A05A4(arg3,
                          FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25),
                          FIELD(arg3, s16, 0x2A),
                          0x10);
        ASM_MEM_BARRIER();
        x = FIELD(arg3, s8, 0x72);
        z = FIELD(arg3, s8, 0x73);
        if (x < 0) {
            ASM_SCHED_BARRIER();
            x = -x;
        }
        if (z < 0) {
            ASM_SCHED_BARRIER();
            z = -z;
        }
        FIELD(arg3, s8, 0x72) = x;
        FIELD(arg3, s8, 0x73) = z;
    }

Update:
CallUpdate:
    if (!func_800A94A0(arg3, arg1, special, (u16 *)((u8 *)arg0 + 0x98))) {
        return;
    }
    func_800BB044(arg3);
    goto AdvanceState;

L1:
    if (func_8003F270()) {
        FIELD(arg2, u16, 0x14) |= 0x0800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

L2:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    table = D_80176648;
    goto PlayEffect;

L3:
    if (FIELD(arg2, s8, 4) == 6 && (FIELD(arg2, u16, 0x14) & 0x1000)) {
        FIELD(arg0, u16, 0x98) |= 0x80;
    } else if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg0, u16, 0x98) |= 0x80;
    }
    if (!(FIELD(arg0, u16, 0x98) & 0x80)) {
        return;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    table = D_80176668;

PlayEffect:
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80047784(arg2,
        *(u8 *)((uptr)(((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) +
                (uptr)table),
        0);
AdvanceState:
    FIELD(arg0, u8, 0x9B)++;
    return;

L4:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        table = D_801765D8;
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    {
        u8 *global = D_80083460;

        if (FIELD(global, s32, 0x0C) != 0) {
            return;
        }
        FIELD(global, u16, 0x0A)--;
    }
    FIELD(arg0, u8 *, 0x8C) = D_80170EE4;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);
}
