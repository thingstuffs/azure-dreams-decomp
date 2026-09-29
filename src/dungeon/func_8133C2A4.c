#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"

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
s32 func_801732A4(Entity *entity, s32 action_value, Aux *aux)
{
    s32 angle_out[2];
    Entity *actor;
    u8 *script;
    s32 command;
    s32 command_byte;
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

    actor = entity;
top:
    if (aux->flags14 & 0x40) {
        return 0;
    }
    script = D_80175DC4;
    command = script[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        entity->fieldAF = 0;
    } else {
        duration = script[0];
        timer = (u16)(D_80175DC8 + 1);
        D_80175DC8 = (s16)timer;
        if (duration < (s16)timer) {
            D_80175DC4 = script + 2;
            D_80175DC8 = 0;
        }
        old_flags = actor->flags46;
        actor->angle = (s16)((command & 7) << 9);
        actor->flags46 = (u16)(old_flags | 0x8000);
        opcode = command_byte & 0xF8;
        switch (opcode) {
        case 0xD0:
            jump_script = D_80175DC4;
            D_80175DC8 = 0;
            jump_script += *(s8 *)jump_script * 2;
            D_80175DC4 = jump_script;
            goto top;

        case 0x08:
            func_8016B230(entity, action_value, aux, actor);
            return 0;

        case 0xF0:
            func_8016DAC0(entity, action_value, aux, actor);
            return 0;

        case 0xE8:
            actor->angle = func_800A0818(aux->x24, aux->y25,
                D_80082E80.tileX, D_80082E80.tileY, angle_out);
            func_8016D6F8(entity, action_value, aux, actor);
            return 0;

        case 0x10:
            animation = entity->animation;
            switch (animation) {
            case 0:
                old_sequence = aux->sequence;
                sequence = D_801739A0;
                break;
            case 1:
                old_sequence = aux->sequence;
                sequence = D_801739A8;
                break;
            case 2:
                old_sequence = aux->sequence;
                sequence = D_801739B0;
                break;
            case 3:
                old_sequence = aux->sequence;
                sequence = D_801739B8;
                break;
            default:
                func_800A9A0C(actor);
                return 0;
            }
            {
                s16 *angle_base;

                if (old_sequence == sequence) {
                    break;
                }
                angle_base = &gameWork.view.viewAngle;
                (*(u8 **)((u8 *)aux + 0x2C)) = sequence;
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
            }
            break;


        case 0xF8:
            state = entity->state;
            switch (state) {
            case 0:
            {
                s16 *angle_base;

                if (entity->animation != 0) {
                    break;
                }
                old_sequence = aux->sequence;
                start_sequence = D_80173A88;
                if (old_sequence == start_sequence) {
                    break;
                }
                angle_base = &gameWork.view.viewAngle;
                (*(u8 **)((u8 *)aux + 0x2C)) = start_sequence;
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, start_sequence);
                func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, start_sequence), aux->field04);
                entity->state++;
                entity->timer = 0;
                break;
            }
            case 1:
            {
                s16 *angle_base;

                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if ((s16)timer < 0x28) {
                    break;
                }
                entity->animation = 2;
                angle_base = &gameWork.view.viewAngle;
                sequence = ((*(u8 **)((u8 *)aux + 0x2C)) = D_801739B0);
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
                entity->state++;
                break;
            }
            }
            break;

        case 0xE0:
            event_state = entity->state;
            switch (event_state) {
            case 0:
            {
                s16 *angle_base;
                u8 *event_sequence;

                if (entity->animation != 2) {
                    break;
                }
                event_sequence = D_80173A60;
                if (aux->sequence == event_sequence) {
                    break;
                }
                angle_base = &gameWork.view.viewAngle;
                (*(u8 **)((u8 *)aux + 0x2C)) = event_sequence;
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, event_sequence);
                func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, event_sequence), aux->field04);
                entity->state++;
                entity->timer = 0;
                break;
            }
            case 1:
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
                    break;
                }
                entity->animation = 3;
                angle_base = &gameWork.view.viewAngle;
                sequence = ((*(u8 **)((u8 *)aux + 0x2C)) = D_801739B8);
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
                entity->state++;
                break;
            }
            }
            break;

        case 0xD8:
            state = entity->state;
            next_phase = 1;
            switch (state) {
            case 0:
                entity->state = next_phase;
                entity->timer = 0;
                entity->direction = 0;
            case 1:
                actor->angle = func_800A0818(aux->x24, aux->y25,
                    D_80082E80.tileX, D_80082E80.tileY, angle_out);
                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if (timer & 1) {
                    entity->direction = -1;
                } else {
                    entity->direction = 1;
                }
                break;
            }
            break;


        case 0xC8:
            state = entity->state;
            switch (state) {
            case 0:
                actor->angle = func_800A0818(aux->x24, aux->y25,
                    D_80082E80.tileX, D_80082E80.tileY, angle_out);
                entity->state++;
                entity->timer = 0;
                entity->direction = 0;
                entity->fieldB0 = 2;
                break;
            case 1:
            {
                s16 *angle_base;
                u8 *idle_sequence;

                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if ((s16)timer >= 4) {
                    entity->timer = 0;
                    entity->state = (u8)(entity->state + 1);
                    actor->angle = func_800A0818(aux->x24, aux->y25,
                        D_80082E80.tileX, D_80082E80.tileY, angle_out);
                    idle_sequence = D_801739A0;
                    angle_base = &gameWork.view.viewAngle;
                    entity->animation = 0;
                    (*(u8 **)((u8 *)aux + 0x2C)) = idle_sequence;
                    sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                    SEQUENCE_INDEX_ADVANCE(sequence_index, idle_sequence);
                    func_80047784(aux, SEQUENCE_INDEX_BYTE(sequence_index, idle_sequence), 0);
                }
            }
            case 2:
                actor->angle = func_800A0818(aux->x24, aux->y25,
                    D_80082E80.tileX, D_80082E80.tileY, angle_out);
                break;
            }
            break;
        }
    }

common:
    func_800A9A0C(actor);
    return 0;
}
