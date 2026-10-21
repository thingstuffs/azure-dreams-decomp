#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800F63D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800F63D0_0;

typedef struct S_800F63D0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F63D0_1;

extern s32 test_resident_bit();
extern void file_load_com(void *packed_data);
extern s32 register_node();
extern s16 get_surface_height_at_coordinates();
extern u8 D_80045C34[]; /* overlays/dungeon/first_pass_matched/func_80D403A8.c */
extern void update_pulsing_actor_color(void *state_data, s32 unused, void *actor_data);
extern M2C_UNK D_800F6F28;
extern M2C_UNK D_800F6F30;

/* Conditionally creates and initializes a type 0x12 object. */
void create_fixed_tile_effect_if_available(void) {
    S_800F63D0_1 *graphics;
    S_800F63D0_0 *object;
    SpriteFrameState *animation;

    if (test_resident_bit(0xA2) == 0) {
        file_load_com(&D_800F6F28);
        object = allocate_flagged_object_node(0x12);
        if (object != NULL) {
            object->unk_10 = &update_pulsing_actor_color;
            register_node(object, &D_80045C34);
            graphics = object->unk_08;
            graphics->unk_02 = 0x820;
            graphics->unk_06 = 0x820;
            graphics->unk_0A = get_surface_height_at_coordinates(graphics->unk_02, 0x820);
            animation = object->unk_0C;
            animation->scale_y = 0x1000;
            animation->scale_x = 0x1000;
            animation->source = &D_800F6F30;
            animation->tpage_abr = 0x20;
            animation->flags = 0xC;
            animation->unk_06 = 6;
        }
    }
}
