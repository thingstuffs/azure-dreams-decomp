#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"

#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void update_flickering_layer_sprite(void *effect_data, void *unused, Rec_D_80082E80 *effect);
extern u8 D_800DEAE0[];
extern s32 func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

typedef struct S_801676CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801676CC_0;

typedef struct S_801676CC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_801676CC_1;

typedef struct S_801676CC_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801676CC_2;

typedef struct S_801676CC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801676CC_3;


typedef struct S_801676CC_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801676CC_5;

/* Creates sixteen effects at the given position with increasing sprite scales. */
void create_layered_sprite_pulse(EntityRec *origin) {
    s16 scale_x;
    s16 scale_y;
    s32 effect_index;
    s16 initial_ticks;
    void *effect_data;
    S_801676CC_2 *render_params;
    S_801676CC_3 *position;
    S_801676CC_5 *sprite;
    void *effect;
    S_801676CC_0 *effect_state;

    effect_index = 0;
    initial_ticks = 0xE;
    effect_data = &update_flickering_layer_sprite;
    scale_y = 0x1000;
    scale_x = 0x1400;
    do {
        effect = func_8003FC64(0x212);
        if (effect != NULL) {
            effect_state = effect + 0x20;
            effect_state->unk_18 = initial_ticks;
            effect_state->unk_1A = initial_ticks;
            ((S_801676CC_1 *)effect)->unk_10 = effect_data;
            func_8004491C(effect, func_80045340);
            render_params = ((S_801676CC_1 *)effect)->unk_0C;
            render_params->unk_10 = 0x60;
            render_params->unk_14 = (u16) (render_params->unk_14 | 0xC);
            position = ((S_801676CC_1 *)effect)->unk_08;
            position->unk_00 = (s32) origin->x.v;
            position->unk_04 = (s32) origin->y.v;
            position->unk_08 = (s32) (origin->z.v + 0xFFC00000);
            sprite = ((S_801676CC_1 *)effect)->unk_0C;
            sprite->unk_1C = scale_x;
            sprite->unk_1E = scale_y;
            sprite->unk_0E = 0;
            sprite->unk_0D = 0;
            sprite->unk_0C = 0;
            sprite->unk_06 = 0;
            sprite->unk_12 = 0x7DCF;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
            func_8003DB94(sprite, D_800DEAE0, 0);
        }
        scale_y += 0x200;
        effect_index += 1;
        scale_x += 0x200;
    } while (effect_index < 0x10);
}
