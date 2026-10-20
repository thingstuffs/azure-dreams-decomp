#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"

typedef struct S_80172F44_0 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x40];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_80172F44_0;   /* state in create_boss_randomized_effect */

typedef struct S_80172F44_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172F44_1;   /* object in create_boss_randomized_effect */

typedef struct S_80172F44_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80172F44_3;   /* transform in create_boss_randomized_effect */

typedef struct S_80172F44_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172F44_4;   /* arg0 in create_boss_randomized_effect */

extern void register_node(void *entry, void *registration_id);
extern s32 rand(void);
extern void func_8003DB94(void *ptr, void *ptr1, s32 value);
extern void project_sprite_chain(void);
extern void update_accelerating_growing_particle(void);

/* Creates a visual effect at an offset position with randomized state. */
void create_boss_randomized_effect(S_80172F44_4 *position, s32 x_offset, s32 y_offset, s32 z_offset)
{
    void *object;
    S_80172F44_3 *transform;
    SpriteFrameState *display;
    u8 *state;
    s32 random_value;
    s32 z_fixed;
    u16 x_integer;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = (u8 *)object + 0x20;
        ((S_80172F44_0 *)state)->unk_16 = 0x1A;
        ((S_80172F44_1 *)object)->unk_10 = update_accelerating_growing_particle;
        register_node(object, project_sprite_chain);

        display = ((S_80172F44_1 *)object)->unk_0C;
        display->tpage_abr = 0x40;
        display->unk_06 = 6;
        display->flags |= 0xC;

        transform = ((S_80172F44_1 *)object)->unk_08;
        transform->unk_00.at00.v = position->unk_00;
        transform->unk_04.at00.v = position->unk_04;

        x_integer = transform->unk_00.at02.v;
        z_fixed = position->unk_08;
        transform->unk_00.at02.v = x_integer + x_offset;
        transform->unk_08.at00.v = z_fixed;
        transform->unk_04.at02.v += y_offset;
        transform->unk_08.at02.v += z_offset;

        random_value = rand();
        ((S_80172F44_0 *)state)->unk_58 = random_value - 0x8000;
        random_value = rand();
        ((S_80172F44_0 *)state)->unk_5C = random_value - 0x8000;
        random_value = rand();
        ((S_80172F44_0 *)state)->unk_60 = random_value - 0x40000;

        display = ((S_80172F44_1 *)object)->unk_0C;
        display->scale_y = 0x400;
        display->scale_x = 0x400;
        display->color.c.b = 0x16;
        display->color.c.g = 0x16;
        display->color.c.r = 0x16;
        display->clut = 0x7DCF;
        display->flags |= 0x100;
        func_8003DB94(display, D_800DE870, 0);
    }
}
