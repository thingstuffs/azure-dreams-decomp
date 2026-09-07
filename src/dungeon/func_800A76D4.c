#include "common.h"

typedef struct {
    u8 pad[0x9B];
    u8 unk9B;
} StructArg0;

typedef struct {
    u8 pad[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 pad10[2];
    u16 unk12;
    u16 unk14;
} StructArg2;

typedef struct {
    u8 pad[0xA];
    u16 unk0A;
    u8 pad2[4];
} StructD80083460;

extern u8 D_80045340[0x10];
extern StructD80083460 D_80083460;

void func_80044A50(void *);
void func_8004491C(void *, void *);

s32 func_800ACE34(StructArg0 *arg0, s32 arg1, StructArg2 *arg2) {
    register StructArg0 *s0 ASM_REG("$16") = arg0;   /* MATCH pin: load-bearing for the whole function shape */
    StructArg2 *s1 = arg2;
    u8 v1 = s0->unk9B;
    u8 t0;
    register s32 a1 ASM_REG("$5");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 a3;
    register s32 a0 ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u8 a2;
    s32 q_v1;
    u16 d_v1;

    if (v1 == 0) goto block1;
    if (v1 == 1) goto block2;
    return 0;

block1:
    t0 = s1->unk0C;
    s1->unk0F++;
    a1 = 0x80 - t0;
    a1 = a1 / *(volatile u8 *)&s1->unk0F;
    a3 = s1->unk0D;
    a0 = 0x80 - a3;
    a0 = a0 / *(volatile u8 *)&s1->unk0F;
    a2 = s1->unk0E;
    q_v1 = 0x80 - a2;
    q_v1 = q_v1 / *(volatile u8 *)&s1->unk0F;
    t0 += a1;
    s1->unk0C = t0;
    a3 += a0;
    s1->unk0D = a3;
    a2 += q_v1;
    s1->unk0E = a2;
    if (*(volatile u8 *)&s1->unk0F >= 8) {
        s1->unk0E = 0x80;
        s1->unk0D = 0x80;
        s1->unk0C = 0x80;
        s0->unk9B++;
    }
    return 0;

block2:
    s1->unk0F--;
    if (s1->unk0F != 0) {
        return 0;
    }
    s0 = (StructArg0 *)((u8 *)s0 - 0x20);
    func_80044A50(s0);
    s1->unk12 += 0x80;
    s1->unk14 &= 0xFFF3;
    func_8004491C(s0, D_80045340);
    d_v1 = D_80083460.unk0A;
    d_v1--;
    D_80083460.unk0A = d_v1;
    return 1;
}
