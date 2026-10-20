#include "shared/game_work.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void *allocate_list_node();
extern void register_node();
extern s32 rand(void);
extern u8 D_80025764[12];
extern u8 D_8002822C[12];
extern u8 D_800C95C0[12];
/* Spawn two pairs of effects at random offsets around the source. */
void spawn_paired_random_effects(void *source, s16 effect_param, s32 render_param)
{
    s32 remaining;
    void *effect;
    void *effect_data;
    SpriteFrameState *render_data;
    remaining = 2;
    do {
        effect = allocate_list_node(0x212, source);
        if (effect != 0) {
            *((void **) (((u8 *) effect) + 0x10)) = D_80025764;
            register_node(effect, project_sprite_chain);
            effect_data = ((u8 *) effect) + 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 2)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 6)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0xA)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA))) + (rand() & 0x3F)) - 0x20;
            render_data = *((void **) (((u8 *) effect) + 0xC));
            render_data->source = D_8002822C;
            render_data->scale_y = 0x1000;
            render_data->scale_x = 0x1000;
            render_data->color.word = render_param;
            render_data->unk_06 = 8;
            *((s16 *) (((u8 *) effect_data) + 0x36)) = effect_param;
            *((s16 *) (((u8 *) effect_data) + 0x30)) = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
    remaining = 2;
    do {
        effect = allocate_list_node(0x212, source);
        if (effect != 0) {
            *((void **) (((u8 *) effect) + 0x10)) = D_80025764;
            register_node(effect, D_800C95C0);
            effect_data = ((u8 *) effect) + 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 2)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 6)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0xA)) =
                ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA))) + (rand() & 0x3F)) - 0x20;
            *((s16 *) (((u8 *) effect) + 0x20)) = 0x20;
            *((s16 *) (((u8 *) effect_data) + 2)) = 0x20;
            *((s16 *) (((u8 *) effect_data) + 4)) = 1;
            *((s16 *) (((u8 *) effect_data) + 6)) = 0;
            *((s16 *) (((u8 *) effect_data) + 0x36)) = effect_param;
            *((s16 *) (((u8 *) effect_data) + 0x30)) = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
}
