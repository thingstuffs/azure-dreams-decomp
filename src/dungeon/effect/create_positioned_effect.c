#include "common.h"
#include "shared/sprite_frame_state.h"

typedef struct {
    u8 before_sprite[8];
    void *sprite;
    void *render;
    void *callback;
    u8 before_work[0xC];
    u8 work[0x3E];
} Effect;
typedef struct { u8 pad[2]; u16 x; u8 pad2[2]; u16 y; u8 pad3[2]; u16 z; } Position;
extern Effect *allocate_list_node(s32, void *);
extern void register_node(Effect *, void *);
extern u8 D_800CEEFC[], D_80024784[];

/* Create a positioned effect and set its animation and lifetime parameters. */
Effect *create_positioned(void *source, s32 x, s32 y, s32 z, Position *position, s32 texture, s16 frame, s32 lifetime, s32 timer) {
    Effect *effect;
    u8 *sprite;
    u8 *work;
    u8 *render;
    effect = allocate_list_node(0x212, source);
    if (effect != 0) {
        effect->callback = D_80024784;
        register_node(effect, D_800CEEFC);
        sprite = effect->sprite;
        *(u16 *)(sprite + 2) = position->x;
        *(u16 *)(sprite + 6) = position->y;
        *(u16 *)(sprite + 0xA) = position->z;
        work = effect->work;
        *(s16 *)(sprite + 0xE) = x;
        *(s16 *)(work + 0x18) = x;
        *(s16 *)(sprite + 0x12) = y;
        *(s16 *)(work + 0x1A) = y;
        *(s16 *)(sprite + 0x16) = z;
        *(s16 *)(work + 0x1C) = z;
        render = effect->render;
        ((SpriteFrameState *)render)->source = texture;
        ((SpriteFrameState *)render)->scale_y = 0x1000;
        ((SpriteFrameState *)render)->scale_x = 0x1000;
        ((SpriteFrameState *)render)->color.word = 0x808080;
        {
        s32 index = frame;
        if (index != 0) {
            ((SpriteFrameState *)render)->tpage_abr = (index - 1) << 5;
            ((SpriteFrameState *)render)->flags |= 0xC;
        }
        }
        *(s16 *)(work + 0x2E) = 8;
        *(s16 *)(work + 0x3C) = 0x80;
        *(s32 *)(work + 0x14) = lifetime;
        *(s16 *)(work + 0x32) = timer;
    }
    return effect;
}
