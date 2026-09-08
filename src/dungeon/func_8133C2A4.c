#include "common.h"

#ifdef NON_MATCHING
#define SEQUENCE_INDEX_ADVANCE(index, base) ((void)0)
#define SEQUENCE_INDEX_BYTE(index, base) ((base)[(index)])
#else
#define SEQUENCE_INDEX_ADVANCE(index, base) ((index) += (s32)(base))
#define SEQUENCE_INDEX_BYTE(index, base) (*(u8 *)(index))
#endif

typedef struct Entity Entity;
typedef struct Aux Aux;

struct Entity {
    u8 pad00[0x2A];
    s16 angle;
    u8 pad2C[0x1A];
    u16 flags46;
    u8 pad48[0x4E];
    u16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[0xE];
    s8 direction;
    u8 padAB;
    u8 animation;
    u8 padAD[2];
    s8 fieldAF;
    s8 fieldB0;
};

struct Aux {
    u8 pad00[4];
    s8 field04;
    u8 pad05[0xF];
    u16 flags14;
    u8 pad16[0xE];
    u8 x24;
    u8 y25;
    u8 pad26[6];
    u8 *sequence;
};

extern s32 func_80047784(Aux *, u8, s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A56E0(s32);
extern void func_800A9A0C(Entity *);
extern void func_8016B230(Entity *, s32, Aux *, Entity *);
extern void func_8016D6F8(Entity *, s32, Aux *, Entity *);
extern void func_8016DAC0(Entity *, s32, Aux *, Entity *);
extern void func_8016EB68(void);
extern void func_80170510(void);
extern void func_80170838(void);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern u8 D_80173A60[];
extern u8 D_80173A88[];
extern u8 D_80173AF8;
extern u8 *D_80175DC4;
extern s16 D_80175DC8;

s32 func_801732A4(Entity *arg0, s32 arg1, Aux *arg2)
{
    s32 angle_out[2];
    Entity *ent;
    register s32 saved_arg1 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Aux *aux;
    register Entity *ent_arg3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *script;
    s32 code;
    register s32 raw_kind ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 selector;
    s32 next_state;
    s32 kind;
    s32 index;
    u8 *sequence;
    u8 *f8_sequence;
    u8 *old_sequence;
    u8 *jump_script;
    s32 script_current;
    s32 current;
    u16 timer;
    s32 saved_state;
    u16 old_flags;
    s32 dispatch_d8;

    ent = arg0;
    saved_arg1 = arg1;
    aux = arg2;
    ent_arg3 = ent;
    ASM_KEEP(ent);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
top:
    if (aux->flags14 & 0x40) {
        goto return_zero;
    }
    script = D_80175DC4;
    code = script[1];
    ASM_KEEP(code);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    raw_kind = code & 0xFF;
    ASM_KEEP(raw_kind);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if (raw_kind == 0) {
        ent->fieldAF = 0;
        goto common;
    }
    script_current = script[0];
    timer = (u16)(D_80175DC8 + 1);
    D_80175DC8 = (s16)timer;
    if (script_current < (s16)timer) {
        D_80175DC4 = script + 2;
        D_80175DC8 = 0;
    }
    ASM_KEEP(script);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    old_flags = ent_arg3->flags46;
    ent_arg3->angle = (s16)((code & 7) << 9);
    dispatch_d8 = 0xD8;
    ent_arg3->flags46 = (u16)(old_flags | 0x8000);
    kind = raw_kind & 0xF8;
    ASM_KEEP(raw_kind);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if (kind == dispatch_d8) {
        goto case_D8;
    }
    if (kind >= 0xD9) {
        goto dispatch_hi;
    }
    if (kind == 0x10) {
        goto case_10;
    }
    if (kind >= 0x11) {
        goto dispatch_mid;
    }
    if (kind == 8) {
        goto case_08;
    }
    goto common;

dispatch_mid:
    if (kind == 0xC8) {
        goto case_C8;
    }
    if (kind == 0xD0) {
        goto case_D0;
    }
    goto common;

dispatch_hi:
    if (kind == 0xE8) {
        goto case_E8;
    }
    if (kind >= 0xE9) {
        goto dispatch_higher;
    }
    if (kind == 0xE0) {
        goto case_E0;
    }
    goto common;

dispatch_higher:
    if (kind == 0xF0) {
        goto case_F0;
    }
    if (kind == 0xF8) {
        goto case_F8;
    }
    goto common;

case_D0:
    jump_script = D_80175DC4;
    D_80175DC8 = 0;
    jump_script += *(s8 *)jump_script * 2;
    D_80175DC4 = jump_script;
    goto top;

case_08:
    func_8016B230(ent, saved_arg1, aux, ent_arg3);
    return 0;

case_F0:
    func_8016DAC0(ent, saved_arg1, aux, ent_arg3);
    return 0;

case_E8:
    ent_arg3->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);
    func_8016D6F8(ent, saved_arg1, aux, ent_arg3);
    return 0;

case_10:
    selector = ent->animation;
    if (selector == 1) {
        goto sequence_1;
    }
    if (selector >= 2) {
        goto sequence_ge_2;
    }
    if (selector == 0) {
        goto sequence_0;
    }
    goto common;

sequence_ge_2:
    if (selector == 2) {
        goto sequence_2;
    }
    if (selector == 3) {
        goto sequence_3;
    }
    goto common;

sequence_0:
    old_sequence = aux->sequence;
    sequence = D_801739A0;
    goto sequence_join;

sequence_1:
    old_sequence = aux->sequence;
    sequence = D_801739A8;
    goto sequence_join;

sequence_2:
    old_sequence = aux->sequence;
    sequence = D_801739B0;
    goto sequence_join;

sequence_3:
    old_sequence = aux->sequence;
    sequence = D_801739B8;

sequence_join:
    {
        s16 *angle_base;

        if (old_sequence == sequence) {
            goto common;
        }
        angle_base = &D_80083228;
        aux->sequence = sequence;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = ((*angle_base + ent_arg3->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(index, sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(index, sequence), 0);
        goto common;
    }

case_F8:
    current = ent->state;
    if (current == 0) {
        goto case_F8_state0;
    }
    if (current == 1) {
        goto case_F8_state1;
    }
    goto common;

case_F8_state0:
    {
        s16 *angle_base;

        if (ent->animation != 0) {
            goto common;
        }
        old_sequence = aux->sequence;
        f8_sequence = D_80173A88;
        if (old_sequence == f8_sequence) {
            goto common;
        }
        angle_base = &D_80083228;
        aux->sequence = f8_sequence;
        ASM_KEEP(f8_sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = ((*angle_base + ent_arg3->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(index, f8_sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(index, f8_sequence), aux->field04);
        ent->state++;
        ent->timer = 0;
        goto common;
    }
case_F8_state1:
    {
        s16 *angle_base;

        timer = (u16)(ent->timer + 1);
        ent->timer = timer;
        if ((s16)timer < 0x28) {
            goto common;
        }
        next_state = 2;
        sequence = D_801739B0;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_base = &D_80083228;
        ent->animation = next_state;
        aux->sequence = sequence;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = ((*angle_base + ent_arg3->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(index, sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(index, sequence), 0);
        ent->state++;
        goto common;
    }

case_E0:
    saved_state = ent->state;
    if (saved_state == 0) {
        goto case_E0_state0;
    }
    if (saved_state == 1) {
        goto case_E0_state1;
    }
    goto common;

case_E0_state0:
    {
        s16 *angle_base;
        u8 *e0_sequence;

        if (ent->animation != 2) {
            goto common;
        }
        e0_sequence = D_80173A60;
        if (aux->sequence == e0_sequence) {
            goto common;
        }
        angle_base = &D_80083228;
        aux->sequence = e0_sequence;
        ASM_KEEP(e0_sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = ((*angle_base + ent_arg3->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(index, e0_sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(index, e0_sequence), aux->field04);
        ent->state++;
        ent->timer = 0;
        goto common;
    }
case_E0_state1:
    {
        s16 *angle_base;

        timer = (u16)(ent->timer + 1);
        ent->timer = timer;
        if ((s16)timer == 0x1A) {
            func_80170510();
            func_8016EB68();
            D_80173AF8 = saved_state;
            func_80170838();
        }
        if ((s16)ent->timer == 0x24) {
            func_800A56E0(0x819);
        }
        if ((s16)ent->timer < 0x2C) {
            goto common;
        }
        next_state = 3;
        sequence = D_801739B8;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_base = &D_80083228;
        ent->animation = next_state;
        aux->sequence = sequence;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        index = ((*angle_base + ent_arg3->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(index, sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(index, sequence), 0);
        ent->state++;
        goto common;
    }

case_D8:
    current = ent->state;
    next_state = 1;
    if (current == 0) {
        goto case_D8_state0;
    }
    if (current == next_state) {
        goto case_D8_state1;
    }
    goto common;

case_D8_state0:
    {
        ent->state = next_state;
        ent->timer = 0;
        ent->direction = 0;
    }
case_D8_state1:
    ent_arg3->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);
    timer = (u16)(ent->timer + 1);
    ent->timer = timer;
    if (timer & 1) {
        ent->direction = -1;
    } else {
        ent->direction = 1;
    }
    goto common;

case_C8:
    current = ent->state;
    if (current == 1) {
        goto case_C8_state1;
    }
    if ((s32)current >= 2) {
        goto case_C8_ge2;
    }
    if (current == 0) {
        goto case_C8_state0;
    }
    goto common;

case_C8_ge2:
    if (current == 2) {
        goto update_angle;
    }
    goto common;

case_C8_state0:
    ent_arg3->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);
    ent->state++;
    ent->timer = 0;
    ent->direction = 0;
    ent->fieldB0 = 2;
    goto common;

case_C8_state1:
    {
        s16 *angle_base;
        u8 *c8_sequence;

        timer = (u16)(ent->timer + 1);
        ent->timer = timer;
        if ((s16)timer < 4) {
            goto update_angle;
        }
        ent->timer = 0;
        ent->state = (u8)(ent->state + 1);
        ent_arg3->angle = func_800A0818(aux->x24, aux->y25,
            D_80082E80[0x24], D_80082E80[0x25], angle_out);
        c8_sequence = D_801739A0;
        ASM_KEEP(c8_sequence);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        angle_base = &D_80083228;
        ent->animation = 0;
        aux->sequence = c8_sequence;
        ASM_KEEP(c8_sequence);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        index = ((*angle_base + ent_arg3->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(index, c8_sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(index, c8_sequence), 0);
    }

update_angle:
    ent_arg3->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);

common:
    func_800A9A0C(ent_arg3);
return_zero:
    return 0;
}
