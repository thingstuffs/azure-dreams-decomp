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

/* Advances the entity action script and updates its animation, facing, and timed events. */
s32 func_801732A4(Entity *input_entity, s32 action_param, Aux *input_aux)
{
    s32 angle_out[2];
    Entity *entity;
    register s32 action_value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Aux *aux;
    register Entity *actor ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *script;
    s32 command;
    register s32 command_byte ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 animation;
    s32 next_phase;
    s32 opcode;
    s32 sequence_index;
    u8 *sequence;
    u8 *start_sequence;
    u8 *old_sequence;
    u8 *jump_script;
    s32 duration;
    s32 state;
    u16 timer;
    s32 event_state;
    u16 old_flags;
    s32 turn_opcode;

    entity = input_entity;
    action_value = action_param;
    aux = input_aux;
    actor = entity;
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
top:
    if (aux->flags14 & 0x40) {
        goto return_zero;
    }
    script = D_80175DC4;
    command = script[1];
    ASM_KEEP(command);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    command_byte = (u8) command;
    if (command_byte == 0) {
        entity->fieldAF = 0;
        goto common;
    }
    duration = script[0];
    timer = (u16)(D_80175DC8 + 1);
    D_80175DC8 = (s16)timer;
    if (duration < (s16)timer) {
        D_80175DC4 = script + 2;
        D_80175DC8 = 0;
    }
    ASM_KEEP(script);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    old_flags = actor->flags46;
    actor->angle = (s16)((command & 7) << 9);
    turn_opcode = 0xD8;
    actor->flags46 = (u16)(old_flags | 0x8000);
    opcode = command_byte & 0xF8;
    ASM_KEEP(command_byte);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (opcode == turn_opcode) {
        goto case_D8;
    }
    if (opcode >= 0xD9) {
        goto dispatch_hi;
    }
    if (opcode == 0x10) {
        goto case_10;
    }
    if (opcode >= 0x11) {
        goto dispatch_mid;
    }
    if (opcode == 8) {
        goto case_08;
    }
    goto common;

dispatch_mid:
    if (opcode == 0xC8) {
        goto case_C8;
    }
    if (opcode == 0xD0) {
        goto case_D0;
    }
    goto common;

dispatch_hi:
    if (opcode == 0xE8) {
        goto case_E8;
    }
    if (opcode >= 0xE9) {
        goto dispatch_higher;
    }
    if (opcode == 0xE0) {
        goto case_E0;
    }
    goto common;

dispatch_higher:
    if (opcode == 0xF0) {
        goto case_F0;
    }
    if (opcode == 0xF8) {
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
    func_8016B230(entity, action_value, aux, actor);
    return 0;

case_F0:
    func_8016DAC0(entity, action_value, aux, actor);
    return 0;

case_E8:
    actor->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);
    func_8016D6F8(entity, action_value, aux, actor);
    return 0;

case_10:
    animation = entity->animation;
    if (animation == 1) {
        goto sequence_1;
    }
    if (animation >= 2) {
        goto sequence_ge_2;
    }
    if (animation == 0) {
        goto sequence_0;
    }
    goto common;

sequence_ge_2:
    if (animation == 2) {
        goto sequence_2;
    }
    if (animation == 3) {
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
        sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
        goto common;
    }

case_F8:
    state = entity->state;
    if (state == 0) {
        goto case_F8_state0;
    }
    if (state == 1) {
        goto case_F8_state1;
    }
    goto common;

case_F8_state0:
    {
        s16 *angle_base;

        if (entity->animation != 0) {
            goto common;
        }
        old_sequence = aux->sequence;
        start_sequence = D_80173A88;
        if (old_sequence == start_sequence) {
            goto common;
        }
        angle_base = &D_80083228;
        aux->sequence = start_sequence;
        ASM_KEEP(start_sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(sequence_index, start_sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, start_sequence), aux->field04);
        entity->state++;
        entity->timer = 0;
        goto common;
    }
case_F8_state1:
    {
        s16 *angle_base;

        timer = (u16)(entity->timer + 1);
        entity->timer = timer;
        if ((s16)timer < 0x28) {
            goto common;
        }
        next_phase = 2;
        sequence = D_801739B0;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_base = &D_80083228;
        entity->animation = next_phase;
        aux->sequence = sequence;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
        entity->state++;
        goto common;
    }

case_E0:
    event_state = entity->state;
    if (event_state == 0) {
        goto case_E0_state0;
    }
    if (event_state == 1) {
        goto case_E0_state1;
    }
    goto common;

case_E0_state0:
    {
        s16 *angle_base;
        u8 *event_sequence;

        if (entity->animation != 2) {
            goto common;
        }
        event_sequence = D_80173A60;
        if (aux->sequence == event_sequence) {
            goto common;
        }
        angle_base = &D_80083228;
        aux->sequence = event_sequence;
        ASM_KEEP(event_sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(sequence_index, event_sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, event_sequence), aux->field04);
        entity->state++;
        entity->timer = 0;
        goto common;
    }
case_E0_state1:
    {
        s16 *angle_base;

        timer = (u16)(entity->timer + 1);
        entity->timer = timer;
        if ((s16)timer == 0x1A) {
            func_80170510();
            func_8016EB68();
            D_80173AF8 = event_state;
            func_80170838();
        }
        if ((s16)entity->timer == 0x24) {
            func_800A56E0(0x819);
        }
        if ((s16)entity->timer < 0x2C) {
            goto common;
        }
        next_phase = 3;
        sequence = D_801739B8;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_base = &D_80083228;
        entity->animation = next_phase;
        aux->sequence = sequence;
        ASM_KEEP(sequence);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
        entity->state++;
        goto common;
    }

case_D8:
    state = entity->state;
    next_phase = 1;
    if (state == 0) {
        goto case_D8_state0;
    }
    if (state == next_phase) {
        goto case_D8_state1;
    }
    goto common;

case_D8_state0:
    {
        entity->state = next_phase;
        entity->timer = 0;
        entity->direction = 0;
    }
case_D8_state1:
    actor->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);
    timer = (u16)(entity->timer + 1);
    entity->timer = timer;
    if (timer & 1) {
        entity->direction = -1;
    } else {
        entity->direction = 1;
    }
    goto common;

case_C8:
    state = entity->state;
    if (state == 1) {
        goto case_C8_state1;
    }
    if ((s32)state >= 2) {
        goto case_C8_ge2;
    }
    if (state == 0) {
        goto case_C8_state0;
    }
    goto common;

case_C8_ge2:
    if (state == 2) {
        goto update_angle;
    }
    goto common;

case_C8_state0:
    actor->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);
    entity->state++;
    entity->timer = 0;
    entity->direction = 0;
    entity->fieldB0 = 2;
    goto common;

case_C8_state1:
    {
        s16 *angle_base;
        u8 *idle_sequence;

        timer = (u16)(entity->timer + 1);
        entity->timer = timer;
        if ((s16)timer < 4) {
            goto update_angle;
        }
        entity->timer = 0;
        entity->state = (u8)(entity->state + 1);
        actor->angle = func_800A0818(aux->x24, aux->y25,
            D_80082E80[0x24], D_80082E80[0x25], angle_out);
        idle_sequence = D_801739A0;
        ASM_KEEP(idle_sequence);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        angle_base = &D_80083228;
        entity->animation = 0;
        aux->sequence = idle_sequence;
        ASM_KEEP(idle_sequence);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
        SEQUENCE_INDEX_ADVANCE(sequence_index, idle_sequence);
        func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, idle_sequence), 0);
    }

update_angle:
    actor->angle = func_800A0818(aux->x24, aux->y25,
        D_80082E80[0x24], D_80082E80[0x25], angle_out);

common:
    func_800A9A0C(actor);
return_zero:
    return 0;
}
