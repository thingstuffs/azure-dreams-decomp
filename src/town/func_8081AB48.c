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
extern void SD_Call(s32);
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

/* Updates actor movement, animation, and collision through its timed states. */
void func_80024B48(Actor *actor, Motion *motion, Anim *anim)
{
    static void *const state_labels[] = {
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
        (void)state_labels;
        goto *D_80020104[state];
    }

jt_c0: {
        register s32 duration_roll ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 duration ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        duration_roll = rand() & 0xF;
        if (owner->kindA >= 25) {
            duration_roll = rand() & 7;
        } else if (owner->kindA >= 19) {
            if (duration_roll < 3) {
                duration_roll = -rand() & 3;
            } else if (duration_roll < 5) {
                duration_roll = (rand() % 23) + 44;
            }
        } else if (owner->kindA >= 7) {
            if (duration_roll < 4) {
                duration_roll = -rand() & 3;
            } else if (duration_roll < 8) {
                duration_roll = (rand() % 23) + 44;
            }
        } else if (duration_roll < 6) {
            duration_roll = -rand() & 3;
        } else if (duration_roll < 7) {
            duration_roll = (rand() % 23) + 44;
        }
        duration = duration_roll + 14;
        actor->timerA2 = duration;
        actor->initialA6 = duration;
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
        s32 initial_duration;
        if (actor->timerA2 <= 0) {
            motion->vy = 0;
            initial_duration = actor->initialA6;
            actor->timerA2 = initial_duration * 2;
            motion->vx = 0x800000 / (s16)(initial_duration * 2);
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
            s32 initial_duration;
            u16 actor_type;
            s32 speed;
            initial_duration = (u16)actor->initialA6;
            actor_type = actor->typeA0;
            actor->timerA2 = initial_duration;
            {
                register s32 duration ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                duration = actor->timerA2;
                speed = -0x400000 / duration;
            }
            {
                register s32 moves_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                moves_x = actor_type & 1;
                if (moves_x) {
                    s32 x_speed;
                    if ((s16)actor_type == 1) {
                        x_speed = speed;
                    } else {
                        x_speed = -speed;
                    }
                    motion->vx = x_speed;
                    motion->vy = 0;
                } else {
                    ASM_UNDEF(moves_x);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    motion->vx = 0;
                    motion->vy = speed;
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
                s32 height_offset;
                s32 height_delta;
                actor->timerA2 = 12;
                height_offset = (rand() & 0xFF) << 12;
                height_delta = motion->z + 0x580000;
                motion->vz = (height_offset - height_delta) / actor->timerA2;
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
                register s32 exit_speed ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                u16 actor_type = actor->typeA0;
                exit_speed = -0x80000;
                if (actor_type & 1) {
                    s32 x_speed;
                    if ((s16)actor_type != 1) {
                        x_speed = 0x80000;
                    } else {
                        x_speed = exit_speed;
                    }
                    motion->vx = x_speed;
                    motion->vy = 0;
                } else {
                    motion->vx = 0;
                    motion->vy = exit_speed;
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
            SD_Call(0x511);
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
