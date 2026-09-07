#include "common.h"

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
} Motion;

typedef struct Owner {
    u8 pad0[6];
    u16 count6;
    u16 count8;
    s16 kindA;
    u16 flagsC;
} Owner;

typedef struct Actor {
    u8 pad0[0x48];
    void *callback48;
    u8 pad4C[0x68 - 0x4C];
    s16 state68;
    u8 pad6A[0x98 - 0x6A];
    u8 *ptr98;
    u8 pad9C[0xA0 - 0x9C];
    s16 typeA0;
    s16 timerA2;
    u16 flagsA4;
    s16 initialA6;
    u8 padA8[0xAC - 0xA8];
    Owner *ownerAC;
} Actor;

typedef struct Anim {
    void *data0;
    u8 frame4;
    u8 frame5;
    s16 value6;
    void *data8;
    u8 padC[0x14 - 0xC];
    u16 flags14;
    u8 pad16[0x1C - 0x16];
    u16 scale1C;
    u16 scale1E;
} Anim;

typedef struct HalfTable {
    u16 value[6];
} HalfTable;

typedef struct AnimData {
    u8 pad0[4];
    void *data4;
    u32 pad8;
} AnimData;

extern s32 rand(void);
extern void func_8003DB94(Anim *, void *, s32);
extern void func_8008F074(Actor *, Motion *, void *);
extern void func_8008F134(Actor *);
extern void func_80033D08(Actor *);
extern void func_80053DA8(s32);
extern void func_800478B8(Anim *);
extern s32 func_800A2A18(void *, Motion *);

extern u8 D_800F7DD4[];
extern u8 D_800F7D64[];
extern u8 D_800F7D3C[];
extern u8 D_80026F38[];
extern u8 D_800200FC[];
extern void *D_80020104[];
extern HalfTable D_800200E4;
extern HalfTable D_800200F0;
extern s32 D_800814A0[3];

void func_80024B48(Actor *actor, Motion *motion, Anim *anim)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9
    };
    Owner *owner = actor->ownerAC;
    HalfTable scale_x = D_800200E4;
    HalfTable scale_y = D_800200F0;

    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;
    actor->timerA2--;
    owner->flagsC |= 1;

    {
        s32 state = actor->state68;
        if ((u32)state >= 10U) {
            goto switch_end;
        }
        (void)jt_keep;
        goto *D_80020104[state];
    }

jt_c0: {
        register s32 r ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 value ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        r = rand() & 0xF;
        if (owner->kindA >= 25) {
            r = rand() & 7;
        } else if (owner->kindA >= 19) {
            if (r < 3) {
                r = -rand() & 3;
            } else if (r < 5) {
                r = (rand() % 23) + 44;
            }
        } else if (owner->kindA >= 7) {
            if (r < 4) {
                r = -rand() & 3;
            } else if (r < 8) {
                r = (rand() % 23) + 44;
            }
        } else if (r < 6) {
            r = -rand() & 3;
        } else if (r < 7) {
            r = (rand() % 23) + 44;
        }
        value = r + 14;
        actor->timerA2 = value;
        actor->initialA6 = value;
        motion->vy = -0x400000 / actor->timerA2;
        if (actor->typeA0 < 2) {
            anim->flags14 |= 1;
        }
        if (actor->typeA0 & 1) {
            anim->value6 = -0x100;
            motion->vy = -motion->vy;
        } else {
            anim->value6 = -0x40;
            func_8003DB94(anim, D_800F7DD4, 0);
        }
        actor->state68 = 1;
        goto switch_end;
    }

jt_c1: {
        s32 value;
        if (actor->timerA2 <= 0) {
            motion->vy = 0;
            value = actor->initialA6;
            actor->timerA2 = value * 2;
            motion->vx = 0x800000 / (s16)(value * 2);
            if (actor->typeA0 < 2) {
                motion->vx = -motion->vx;
            }
            func_8003DB94(anim, D_800F7D64, 0);
            actor->state68 = 2;
        }
        goto switch_end;
    }

jt_c2: {
        if (actor->timerA2 <= 0) {
            s32 raw;
            u16 type;
            s32 value;
            raw = (u16)actor->initialA6;
            type = actor->typeA0;
            actor->timerA2 = raw;
            {
                register s32 sx ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
                sx = actor->timerA2;
                value = -0x400000 / sx;
            }
            {
                register s32 flag ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
                flag = type & 1;
                if (flag) {
                s32 out;
                if ((s16)type == 1) {
                    out = value;
                } else {
                    out = -value;
                }
                motion->vx = out;
                motion->vy = 0;
                } else {
                    ASM_UNDEF(flag);   /* MATCH pin: retail register colouring depends on it */
                    motion->vx = 0;
                    motion->vy = value;
                }
            }
            actor->state68 = 3;
        }
        goto switch_end;
    }

jt_c3:
        if (actor->timerA2 <= 0) {
            motion->vy = 0;
            motion->vx = 0;
            motion->y += -0x40000;
            anim->data0 = D_800F7D3C;
            anim->data8 = ((AnimData *)D_800F7D3C)->data4;
            anim->frame4 = 0;
            anim->frame5 = 0;
            if (rand() & 7) {
                actor->timerA2 = 16;
                actor->timerA2 = actor->initialA6;
                motion->vz = (-0x700000 - motion->z) / actor->timerA2;
                actor->state68 = 4;
            } else {
                s32 shot;
                s32 floor;
                actor->timerA2 = 12;
                shot = (rand() & 0xFF) << 12;
                floor = motion->z + 0x580000;
                motion->vz = (shot - floor) / actor->timerA2;
                actor->state68 = 5;
            }
        }
        goto switch_end;

jt_c4:
        if (motion->z <= -0x580000 && !(actor->flagsA4 & 2)) {
            anim->value6 = 0;
            actor->callback48 = D_800200FC;
            actor->flagsA4 |= 2;
            func_8008F074(actor, motion, D_80026F38);
            owner->count8++;
        }
        if (actor->timerA2 == 3) {
            anim->data0 = D_800F7D3C;
            anim->data8 = ((AnimData *)D_800F7D3C)->data4;
            anim->frame4 = 0;
            anim->frame5 = 0;
        }
        if (actor->timerA2 <= 0) {
            motion->vz = 0;
            actor->state68 = 7;
            actor->timerA2 = actor->initialA6 * 2 + 20;
        }
        goto switch_end;

jt_c5:
        if (actor->timerA2 <= 0) {
            actor->timerA2 = 6;
            motion->vz = (-0x280000 - motion->z) / actor->timerA2;
            actor->state68 = 6;
        }
        goto switch_end;

jt_c6:
        if (actor->timerA2 <= 0) {
            actor->timerA2 = 8;
            motion->vz = (-0x700000 - motion->z) / actor->timerA2;
            actor->state68 = 4;
        }
        goto switch_end;

jt_c7:
        if (actor->timerA2 <= 0) {
            if (actor->typeA0 & 1) {
                func_8003DB94(anim, D_800F7D64, 0);
            } else {
                anim->value6 = 0x40;
                func_8003DB94(anim, D_800F7DD4, 0);
            }
            actor->flagsA4 &= ~2;
            owner->flagsC &= ~4;
            actor->timerA2 = 8;
            {
                register s32 back ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
                u16 type = actor->typeA0;
                back = -0x80000;
                if (type & 1) {
                    s32 out;
                    if ((s16)type != 1) {
                        out = 0x80000;
                    } else {
                        out = back;
                    }
                    motion->vx = out;
                    motion->vy = 0;
                } else {
                    motion->vx = 0;
                    motion->vy = back;
                }
            }
            actor->state68 = 8;
        }
        goto switch_end;

jt_c8:
        if (actor->timerA2 <= 0) {
            func_8008F134(actor);
            if (actor->ptr98 != 0) {
                *actor->ptr98 = 0;
            }
            func_80033D08(actor);
            *(u16 *)((u8 *)actor - 2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        goto switch_end;

jt_c9:
        if (actor->timerA2 == 1) {
            func_80053DA8(0x511);
        }
        if (actor->timerA2 < 6) {
            anim->scale1C = scale_x.value[actor->timerA2];
            anim->scale1E = scale_y.value[actor->timerA2];
        }
        if (actor->timerA2 <= 0) {
            actor->state68 = 8;
        }
        goto switch_end;

switch_end:
    func_800478B8(anim);
    if ((actor->flagsA4 & 2) && func_800A2A18(D_80026F38, motion)) {
        motion->vz = 0;
        motion->vy = 0;
        motion->vx = 0;
        actor->ownerAC->count6++;
        actor->flagsA4 &= ~2;
        anim->data0 = D_800F7D3C;
        anim->data8 = ((AnimData *)D_800F7D3C)->data4;
        anim->frame4 = 0;
        anim->frame5 = 0;
        actor->timerA2 = 14;
        actor->state68 = 9;
    }
}
