/* Relink of matched dungeon/func_80C004EC; every changed retail word is a paired relocation. */
#define dungeonUpdateActorSequenceVariant func_8015BCEC
#define D_801616AC D_8015B6AC
#define D_80161B94 D_8015BB94
#define D_801622CC D_8015C2CC
#define D_801622D4 D_8015C2D4
#define D_801622E0 D_8015C2E0
#define D_801622E4 D_8015C2E4
#define D_801622E5 D_8015C2E5
#define D_801622E8 D_8015C2E8
#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_801732A4_arg0.h"

typedef struct EffectPositionObjectView {
    u8 pad_00[0x8];
    void * position;
} EffectPositionObjectView;

typedef struct EffectGroundPositionView {
    s32 x;
    s32 y;
} EffectGroundPositionView;

typedef struct ColorChannels {
    u8 red;
    u8 green;
    u8 blue;
} ColorChannels;

typedef struct EffectObjectView {
    u8 pad_00[0x8];
    void * position;
    void * sprite;
    s32 * update;
} EffectObjectView;

typedef struct EffectHeightView {
    u8 pad_00[0x8];
    s32 z;
} EffectHeightView;

typedef struct EffectSpriteView {
    u8 pad_00[0xC];
    union { s32 color; void *pointer; } colorOrPointer;
    s32 flags;
    u16 animationFlags;
    u8 pad_16[0x6];
    s16 scaleX;
    s16 scaleY;
} EffectSpriteView;

void func_8003DB94();
s32 Control_CD();
void soundSetCdCueParameters();
void func_80041588();
int func_800445E0();
s32 func_8004491C();
s32 lookupMaskedByteTable();
s32 func_80069EF8();
void func_8009A028();
void func_8009A3D0();
void dungeonDecrementMonsterEntryCount();
s32 dungeonAdvanceStagedEntityLoad();
s32 func_800A56E0();
s32 dungeonCreateStatusLinkedRenderEffect();
s32 dungeonSelectNearbyTargetAndInitializeSlot();
extern void func_8015B904(s32, void *, s32, s32, s16, u16);
extern s32 D_8003E140;
extern s32 D_8006CD58;
extern ColorChannels *D_800DCEEC[];
extern s32 D_800DCF5C;
extern s32 D_8014A000;
extern s32 D_8015B6AC;
extern s32 D_8015BB94;
extern s32 D_8015C2CC;
extern s32 D_8015C2D4[];
extern s16 D_8015C2E0;
extern s32 D_8015C2E4;
extern u8 D_8015C2E5;
extern s32 D_8015C2E8;

void func_8015BCEC(Rec_func_801732A4_arg0 *state, EntityRec *position, Rec_D_80082E80 *actor, void *model) {
    s16 next_spawn;
    s16 next_trail;
    s16 spawn_count;
    s16 trail_count;
    s32 direction;
    s32 color;
    s32 variant_index;
    s16 effect_variant;
    s32 effect_height;
    u16 fade_left;
    u16 elapsed;
    u16 fade_timer;
    s32 event_done;
    u8 phase;
    void *effect_model;
    ColorChannels *target_color;
    EffectHeightView *effect_position;
    EffectSpriteView *effect_sprite;
    GameWork *scene_color;
    EffectObjectView *effect;

    scene_color = &gameWork;
    phase = state->unk_9B;
    switch (phase) {
    case 0:
        state->unk_9B = (u8) (state->unk_9B + 1);
        return;
    case 1:
        func_80041588(&D_8015C2CC, &D_8015C2E4, 0);
        state->unk_A6 = 0;
        state->unk_9B = (u8) (state->unk_9B + 1);
        ((Rec_D_80082E80 *)model)->unk_8A = (u16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v;
        ((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v =
            (s32) (((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v & 0xFFFBFFFF);
    case 2:
        direction = ((s32) (gameWork.view.viewAngle + (s16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if ((*(u8 *)&D_8015C2E4) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x200);
            return;
        }
        func_80041588(&D_8015C2CC, &D_8015C2E4, 1);
        soundSetCdCueParameters(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), NULL);
        D_8015C2E5 = 0;
        Control_CD(0xFF, &D_8003E140, &D_8015C2E5);
        dungeonSelectNearbyTargetAndInitializeSlot(model - 0x20, position, 8, 0x300);
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 3:
        fade_timer = state->unk_96;
        fade_left = fade_timer - 1;
        state->unk_96 = fade_left;
        if ((fade_left << 0x10) <= 0) {
            event_done = D_8015C2E5;
            state->unk_96 = fade_timer;
            if (event_done == 0) {
                return;
            }
            state->unk_9B = (u8) (state->unk_9B + 1);
            func_800A56E0(0x300);
            return;
        }
        target_color = D_800DCEEC[lookupMaskedByteTable(model)];
        scene_color->view.unk_090 = (u8) (scene_color->view.unk_090 + ((s32) (target_color->red
            - scene_color->view.unk_090) / (s16) state->unk_96));
        scene_color->view.unk_091 = (u8) (scene_color->view.unk_091 + ((s32) (target_color->green
            - scene_color->view.unk_091) / (s16) state->unk_96));
        scene_color->view.unk_092 = (u8) (scene_color->view.unk_092 + ((s32) (target_color->blue
            - scene_color->view.unk_092) / (s16) state->unk_96));
        return;
    case 4:
        effect = func_8003FC64(0x12);
        if (effect == NULL) {
            return;
        }
        effect->update = &D_8015BB94;
        func_8004491C(effect, &D_8015B6AC);
        color = 0x808080;
        state->unk_AC = effect;
        effect_model = model;
        ((EffectGroundPositionView *)(((EffectPositionObjectView *)effect)->position))->x = (s32) position->x.v;
        ((EffectGroundPositionView *)(((EffectPositionObjectView *)effect)->position))->y = (s32) position->y.v;
        effect_position = effect->position;
        effect_height = position->z.v;
        D_8015C2E0 = -8;
        effect_position->z = effect_height;
        effect_sprite = effect->sprite;
        effect_sprite->scaleY = 0x1000;
        effect_sprite->scaleX = 0x1000;
        effect_sprite->colorOrPointer.color = color;
        variant_index = lookupMaskedByteTable(effect_model) - 1;
        effect_variant = variant_index;
        if ((variant_index << 0x10) < 0) {
            effect_variant = func_80069EF8() % 3;
        }
        func_8003DB94(effect_sprite, D_8015C2D4[(s16) effect_variant] + (s8 *) &D_8014A000, 0);
        actor->unk_14.at00_u16.v = (u16) (actor->unk_14.at00_u16.v | 0x80);
        spawn_count = 0;
        state->unk_96 = 0U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        do {
            func_8015B904(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
            next_spawn = spawn_count + 1;
            spawn_count = next_spawn;
        } while (next_spawn < 8);
        return;
    case 5:
        elapsed = state->unk_96;
        state->unk_96 = (u16) (elapsed + 1);
        if ((s16) elapsed < 0x1E) {
            trail_count = 0;
            do {
                func_8015B904(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
                next_trail = trail_count + 1;
                trail_count = next_trail;
            } while (next_trail < 8);
        }
        effect_sprite = state->unk_AC;
        effect_sprite = effect_sprite->colorOrPointer.pointer;
        if (effect_sprite->animationFlags & 0xE000) {
            state->unk_9B = (u8) (state->unk_9B + 1);
        }
    case 6:
        if (state->unk_9B != 6) {
            return;
        }
        if (dungeonCreateStatusLinkedRenderEffect(position, D_8015C2E8, D_8015C2E0, &D_800DCF5C) == 0) {
            return;
        }
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        dungeonDecrementMonsterEntryCount(((Rec_D_80082E80 *)model)->unk_12.at01_u8.v, 3);
        func_8009A3D0(actor->unk_24, actor->unk_25, 0x300);
        func_8009A028(model);
        effect_sprite = model - 0x20;
        effect_sprite->flags = (s32) (effect_sprite->flags | 0x80000000);
        return;
    case 7:
        ((Rec_D_80082E80 *)model)->unk_60.as_s32 = dungeonAdvanceStagedEntityLoad(actor, model);
        return;
    }
}
