#include "common.h"
#include "records/Rec_func_80173D78_arg0.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;


typedef struct S_80173D78_1 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { u32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; struct { u8 pad[0x3]; volatile u8 v; } at03u; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173D78_1;   /* arg2 in func_80173D78 */

typedef struct S_80173D78_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1A];
    s16 unk_88;
} S_80173D78_2;   /* arg3 in func_80173D78 */

typedef struct S_80173D78_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80173D78_3;   /* found in func_80173D78 */

typedef struct S_80173D78_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173D78_4;   /* counter_base in func_80173D78 */

typedef struct S_80173D78_5 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_80173D78_5;   /* base in func_80173D78 */


extern void *D_801708A0[];
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern M2C_UNK D_800C6AEC;
extern M2C_UNK D_8017086C;
extern M2C_UNK D_80170898;
extern M2C_UNK D_80170EE4;
extern M2C_UNK D_8017398C;

void func_8004491C();
void func_80044A50();
s32 func_800990FC();
s32 func_80099194();
void func_80099290();
s32 func_8009929C();
s32 func_80099734();
void func_8009A028();
void func_8009A21C();
void func_8009A3D0();
void *func_8009B25C();
void func_800A56E0();
void func_800A5720();
s16 func_800A70E4();
void func_800A9A0C();
void func_800BC318();
void func_80175DD0();
void *func_8017618C();

/* Updates target selection, effect creation, and the sprite fade-out sequence. */
void func_80173D78(void *action, void *context, S_80173D78_1 *sprite, S_80173D78_2 *actor)
{
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    S_80173D78_3 *target;
    void *effect;
    S_80173D78_5 *object;
    s32 target_x;
    s32 target_y;
    s32 direction_offset;
    s32 saved_random;
    s32 random_value;
    void *source_actor;
    register s32 random_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been target */
    s32 result_chain;
    s32 tile_mask;
    s32 map_flags;
    u32 sound_x;
    u32 sound_y;
    s16 tile_index;
    u16 sprite_flags;
    u16 ticks_left;
    u8 state;

    state = ((Rec_func_80173D78_arg0 *)action)->unk_9B;
    if (state >= 5U) {
        return;
    }
    (void)state_labels;
    goto *D_801708A0[(u32)state];

jt_c0:
    sprite_flags = sprite->unk_14;
    if (!(sprite_flags & 0xE000)) {
        return;
    }
    if (!(sprite_flags & 0x8000)) {
        func_800A56E0(0x80D);
    }
    ((Rec_func_80173D78_arg0 *)action)->unk_9B = ((Rec_func_80173D78_arg0 *)action)->unk_9B + 1;
    if (sprite->unk_14 & 0x8000) {
        ((Rec_func_80173D78_arg0 *)action)->unk_96 = 0;
        goto jt_c4;
    }
    ((Rec_func_80173D78_arg0 *)action)->unk_96 = 0x10;
    goto jt_c4;

jt_c1:
    if (!(((Rec_func_80173D78_arg0 *)action)->unk_96 & 3)) {
        if (!(sprite->unk_14 & 0x8000)) {
            func_80175DD0(action, context, sprite, 0);
            func_80175DD0(action, context, sprite, 1);
        }
    }
    ticks_left = ((Rec_func_80173D78_arg0 *)action)->unk_96 - 1;
    ((Rec_func_80173D78_arg0 *)action)->unk_96 = ticks_left;
    if ((s16)ticks_left > 0) {
        return;
    }

    direction_offset = ((u16)actor->unk_2A >> 8) & 0xE;
    target_x = sprite->unk_24 + *(u16 *)((s8 *)&D_8006CCD8 + direction_offset);
    target_y = sprite->unk_25 + *(u16 *)((s8 *)&D_8006CCE8 + direction_offset);
    actor->unk_60.i = 0;

    if (((Rec_func_80173D78_arg0 *)action)->unk_AC == 0) {
        target = func_8009B25C(actor, target_x & 0xFFFF, target_y & 0xFFFF,
                             actor->unk_88);
        actor->unk_60.p = target;
        if (target != 0) {
            state = target->unk_13;
            if (((u32)(state - 1) >= 0x2DU) || (state == 0x1E)) {
                random_value = func_800990FC();
                source_actor = actor;
                ASM_KEEP(source_actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been target */
                random_arg = random_value;
                ASM_KEEP(random_arg);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been target */
                result_chain = func_80099734(source_actor, saved_random = random_arg);
                func_80099290(
                    func_80099194(&D_80170898,
                        func_80099734(target,
                            func_8009929C(0xA,
                                func_80099194(&D_8017086C, result_chain)))));
                func_800A5720(saved_random);
                func_800A56E0(0x506);
                actor->unk_60.i = 0;
            }
        }
    }

    if (((Rec_func_80173D78_arg0 *)action)->unk_AC < 2U) {
        if (actor->unk_60.i == 0) {
            tile_index = func_800A70E4((s16)target_x, (s16)target_y,
                                 actor->unk_88);
            if (tile_index >= 0) {
                actor->unk_60.i = tile_index + 1;
            }
        }
    }

    if (actor->unk_60.i == 0) {
        void *counter_base;

        func_800A9A0C(actor);
        ((Rec_func_80173D78_arg0 *)action)->unk_8C = &D_80170EE4;
        counter_base = &D_80083460;
        ((S_80173D78_4 *)counter_base)->unk_0A =
            ((S_80173D78_4 *)counter_base)->unk_0A - 1;
        actor->unk_1C &= 0xEFFFFFFF;
        goto jt_c4;
    }

    ((Rec_func_80173D78_arg0 *)action)->unk_9B = ((Rec_func_80173D78_arg0 *)action)->unk_9B + 1;
    map_flags = actor->unk_14;
    sound_x = sprite->unk_24;
    sound_y = sprite->unk_25;
    tile_mask = 0x3000;
    if (map_flags & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(sound_x, sound_y, tile_mask);

    actor->unk_1C |= 0x10000;
    effect = func_8017618C(action, context, sprite, actor);
    ((Rec_func_80173D78_arg0 *)action)->unk_A4 = effect;
    if (effect != 0) {
        object = (s8 *)action - 0x20;
        func_80044A50(object);
        func_8004491C(object, &D_800C6AEC);
        sprite->unk_0C.at03.v = 0;
        sprite->unk_12 = sprite->unk_12 - 0x80;
        sprite->unk_14 |= 0xC;
        func_8009A028(actor);
        object->unk_10 |= 0x80000000;
        goto advance_state;
    }

    map_flags = actor->unk_14;
    sound_x = sprite->unk_24;
    sound_y = sprite->unk_25;
    tile_mask = 0x3000;
    if (map_flags & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A21C(sound_x, sound_y, tile_mask);
    actor->unk_1C &= 0xFFFEFFFF;
    goto jt_c4;

jt_c2:
    state = sprite->unk_0C.at03.v;
    if (state < 7U) {
        sprite->unk_0C.at03.v = state + 1;
        sprite->unk_0C.at00.v =
            sprite->unk_0C.at00.v +
            (-(s32)sprite->unk_0C.at00.v /
             (8 - sprite->unk_0C.at03u.v));
        sprite->unk_0C.at01.v =
            sprite->unk_0C.at01.v +
            (-(s32)sprite->unk_0C.at01.v /
             (8 - sprite->unk_0C.at03.v));
        sprite->unk_0C.at02.v =
            sprite->unk_0C.at02.v +
            (-(s32)sprite->unk_0C.at02.v /
             (8 - sprite->unk_0C.at03.v));
        goto jt_c4;
    }

    object = (s8 *)action - 0x20;
    func_80044A50(object);
    func_800BC318(object);
    sprite->unk_0C.at03.v = 0;
    sprite->unk_0C.at00u.v = 0x00808080;
    sprite->unk_14 |= 0x800;
    sprite->unk_12 = sprite->unk_12 + 0x80;
    sprite->unk_14 &= 0xFFF3;
advance_state:
    ((Rec_func_80173D78_arg0 *)action)->unk_9B = ((Rec_func_80173D78_arg0 *)action)->unk_9B + 1;
    goto jt_c4;

jt_c3:
{
    void *counter_base;

    ((Rec_func_80173D78_arg0 *)action)->unk_9A = 0x18;
    ((Rec_func_80173D78_arg0 *)action)->unk_9B = 0;
    ((Rec_func_80173D78_arg0 *)action)->unk_8C = &D_8017398C;
    counter_base = &D_80083460;
    ((S_80173D78_4 *)counter_base)->unk_0A =
        ((S_80173D78_4 *)counter_base)->unk_0A - 1;
    actor->unk_6D = 0;
    actor->unk_1C &= 0xEFFFFFFF;
    actor->unk_46 &= 0x7FFF;
}
jt_c4:
    return;
}
