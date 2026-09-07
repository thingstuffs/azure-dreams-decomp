#include "common.h"

typedef struct {
    s32 field_00;
    u8 unk04[8];
    s32 field_0C;
} Vec3;

typedef struct {
    u8 unk00[6];
    s16 field_06;
    u8 unk08[4];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 unk0F;
    s16 field_10;
    u8 unk12[2];
    u16 flags_14;
    u8 unk16[6];
    s16 field_1C;
    s16 field_1E;
    u8 unk20[12];
    u8 *field_2C;
} Sub;

typedef struct {
    u8 unk00[42];
    s16 field_2A;
    u8 unk2C[106];
    u16 field_96;
    u8 unk98[2];
    u8 field_9A;
    u8 unk9B[3];
    s16 field_9E;
} Extra;

typedef struct {
    u8 unk00[8];
    Vec3 *position;
    Sub *sub;
    void *callback;
} Node;

extern s16 D_80083228[5];
extern u8 D_80174B30[9];
extern Node *D_80174CDC;

extern void func_800419EC(s32, s32);
extern void func_80170DCC(void *, Vec3 *, Sub *);
extern void func_800A56E0(s32);
extern void func_80047784(Sub *, u8, s32);
extern void func_80170CE0(s32, s32, s32, s32);
extern void func_800478B8(Sub *);
extern void func_80171034(void) __attribute__((noreturn));

void func_80170EA0(void) {
    register Extra *s0 ASM_REG("$16");
    register Vec3 *s1 ASM_REG("$17");
    register Sub *s2 ASM_REG("$18");
    register Extra *s3 ASM_REG("$19");
    Node *node;
    s32 lo;
    u16 temp_v0;
    s32 state;

    node = D_80174CDC;
    s0 = (Extra *)((u8 *)node + 0x20);
    s1 = node->position;
    state = s0->field_9A;
    s2 = node->sub;
    s3 = s0;

    if (state == 1) {
        goto block_1;
    }
    if (state >= 2) {
        goto block_ge2;
    }
    if (state == 0) {
        goto block_0;
    }
    func_80171034();

block_ge2:
    if (state == 2) {
        goto block_2;
    }
    func_80171034();

block_0:
    s0->field_9A = 1;
    s0->field_96 = 0;

block_1:
    temp_v0 = s0->field_96++;
    if ((s16)temp_v0 >= 0x24) {
        s0->field_96 = 0x14;
        s0->field_9E = 0x14;
        s0->field_9A++;
        func_800419EC(6, 12);
        func_80170DCC(s0, s1, s2);
        func_800A56E0(0x601);
        s1->field_0C = -0x200000;
        s2->field_10 = 0x20;
        s2->field_2C = D_80174B30;
        s2->flags_14 |= 0xC;
        func_80047784(s2, D_80174B30[((D_80083228[0] + s3->field_2A + 0x100) >> 9) & 7], 0);
        func_80171034();
    }
    goto block_exit;

block_2: {
    register s32 a0 ASM_REG("$4") = s1->field_0C;
    register s32 v1 ASM_REG("$3") = s1->field_00;
    register s32 v0 ASM_REG("$2") = a0;
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x80170CE0` at 0x8017102C forwards $a3 untouched from this row's
     * entry; the row never reads it, so m2c had no name for it (section 22).
     * `need` is a positional SET, so the call carries positions 0..3
     * (section 21).  Position 0 is NOT a fresh uninitialised pin: an unset $4
     * pin stays live across the divide above and evicts retail's own a0 scratch
     * (`lh a0,158(s0)` / `div zero,v0,a0` became t0).  Retail leaves field_9E in
     * a0 at the call, so the existing $4 pin carries the divisor and is the
     * position-0 forwarder -- byte-neutral. */
    register s32 fa1 ASM_REG("$5");
    register s32 fa2 ASM_REG("$6");
    register s32 fa3 ASM_REG("$7");
    v1 += a0;
    s1->field_00 = v1;
    ASM_KEEP(v0);
    v0 /= 2;
    s1->field_0C = v0;
    a0 = s0->field_9E;
    lo = ((s32)(s16)(s0->field_96 - 1) << 7) / a0;
    s0->field_96--;
    s2->field_0E = (s8)lo;
    s2->field_0D = (s8)lo;
    s2->field_0C = (s8)lo;
    if ((s16)s0->field_96 <= 0) {
        func_80170CE0(a0, fa1, fa2, fa3);
    }
}

block_exit:
    func_800478B8(s2);
}
