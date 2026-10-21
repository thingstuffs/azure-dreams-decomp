#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x8C];
    u8 *field_8C;
    u8 pad_90[0x6];
    union {
        s16 s16;
        u16 u16;
    } field_96;
} SequenceFieldView_81336BB4;

typedef struct {
    u8 pad_00[0x14];
    u16 field_14;
    u8 pad_16[0x16];
    u8 *field_2C;
} SpriteFieldView_81336BB4;

typedef struct {
    u8 pad_00[0xC];
    s32 field_0C;
    s32 field_10;
    s32 field_14;
} TransformFieldView_81336BB4;

typedef struct {
    u8 pad_00[0x2A];
    s16 field_2A;
    u8 pad_2C[0x1A];
    u16 field_46;
} ActorFieldView_81336BB4;


extern u8 D_8016A36C[];
extern s16 D_801760D8[];
extern u8 D_801739A0[];

extern void func_800419EC(s32, s32, void *);
extern void select_sprite_entry(void *, u8, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void create_layered_sprite_pulse(void *);
extern void create_eight_part_textured_ribbon(void *, void *, void *, void *);
extern void create_player_centered_sequence_effect(void *, void *, void *);

/* Advances a timed actor sequence, updating effects and directional animation before clearing completion flags. */
void advance_timed_actor_effect_sequence(u8 *sequence, u8 *transform, u8 *sprite_arg, u8 *actor_arg) {
    u8 state;
    s32 anim_mode;
    u8 *anim_table;
    u8 *current_anim_table;
    ActorRecord *effect_actor;
    u16 timer;
    u16 next_timer;
    s16 old_timer;
    s32 direction;
    u8 *sprite = sprite_arg;
    u8 *actor = actor_arg;
    state = sequence[0x9B];
    switch (state) {
    case 0:
        create_layered_sprite_pulse(transform);
        ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = 5;
        sequence[0x9B] = sequence[0x9B] + 1;
        play_sound_if_enabled(0x703);
        D_801760D8[0] = 0;
        return;

    case 1:
        timer = ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 - 1;
        ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = timer;
        if ((timer << 0x10) > 0 && !( ((SpriteFieldView_81336BB4 *)sprite)->field_14 & 0xE000)) {
            return;
        }
        state = sequence[0x9B];
        ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = 0;
        sequence[0x9B] = state + 1;
        return;

    case 2:
        timer = ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 + 1;
        ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = timer;
        if ((s16)timer == 1) {
            create_eight_part_textured_ribbon(sequence, transform, sprite, ((u8 *)(&D_80083780)));
        }
        if (((SequenceFieldView_81336BB4 *)sequence)->field_96.s16 == 2) {
            effect_actor = D_800814A8;
            ((PlayerRecord *)effect_actor)->unk_10C |= 1;
            effect_actor->movement_facing = ((u16)effect_actor->facing) + 0x800;
            func_800419EC(6, 0xC, effect_actor);
            play_sound_if_enabled(0x601);
            create_player_centered_sequence_effect(sequence, transform, sprite);
        }
        if (((SequenceFieldView_81336BB4 *)sequence)->field_96.s16 == 0xB) {
            state = sequence[0x9B];
            ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = 0;
            sequence[0x9B] = state + 1;
            return;
        }
        return;

    case 3:
        if (!( ((SpriteFieldView_81336BB4 *)sprite)->field_14 & 0xE000)) {
            return;
        }
        ((TransformFieldView_81336BB4 *)transform)->field_14 = 0;
        ((TransformFieldView_81336BB4 *)transform)->field_10 = 0;
        ((TransformFieldView_81336BB4 *)transform)->field_0C = 0;
        set_record_integer_tile_center(transform, sprite[0x24], sprite[0x25]);
        anim_mode = sequence[0xAC];
        switch (anim_mode) {
        case 0:
            current_anim_table = ((SpriteFieldView_81336BB4 *)sprite)->field_2C;
            anim_table = D_801739A0;
            break;
        case 1:
            current_anim_table = ((SpriteFieldView_81336BB4 *)sprite)->field_2C;
            anim_table = D_801739A0 + 0x8;
            break;
        case 2:
            current_anim_table = ((SpriteFieldView_81336BB4 *)sprite)->field_2C;
            anim_table = D_801739A0 + 0x10;
            break;
        case 3:
            current_anim_table = ((SpriteFieldView_81336BB4 *)sprite)->field_2C;
            anim_table = D_801739A0 + 0x18;
            break;
        default:
            state = sequence[0x9B];
            ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = 0;
            sequence[0x9B] = state + 1;
            return;
        }
        if (current_anim_table != anim_table) {
            ((SpriteFieldView_81336BB4 *)sprite)->field_2C = anim_table;
            direction = ((s32)(g_game_work.view.camera_rotation.parts.viewAngle + ((ActorFieldView_81336BB4 *)actor)->field_2A + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, *(u8 *)((u32)direction + (u32)anim_table), 0);
        }
        goto advance;

    case 4:
        old_timer = ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16;
        next_timer = old_timer + 1;
        ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = next_timer;
        if (old_timer < 0x50) {
            return;
        }
advance:
        state = sequence[0x9B];
        ((SequenceFieldView_81336BB4 *)sequence)->field_96.u16 = 0;
        sequence[0x9B] = state + 1;
        return;

    case 5:
        actor[0x73] = 0;
        actor[0x72] = 0;
        ((SequenceFieldView_81336BB4 *)sequence)->field_8C = D_8016A36C;
        g_dungeon_status.active_actor = 0;
        ((ActorFieldView_81336BB4 *)actor)->field_46 &= 0x7FFF;

        return;
    default:
        return;
    }
}
