#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_particle_template.h"

typedef struct S_80045C34 S_80045C34;

typedef struct Copy12 {
    s32 word[3];
} __attribute__((packed)) Copy12;


extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 rand();
extern s32 func_80167088(s32 limit);
s32 draw_linked_sprites_clipped(u8 *first_data, s32 link_value, S_80045C34 *value_record);
void update_landing_particle_fade(u8 *object, u8 *motion, u8 *sprite);


typedef struct S_80165F00_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80165F00_0;   /* arg0 in create_jittered_landing_spark */

typedef struct S_80165F00_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80165F00_1;

typedef struct S_80165F00_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80165F00_2;

typedef struct S_80165F00_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80165F00_3;

typedef struct S_80165F00_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80165F00_4;   /* ((S_80165F00_0 *)arg0)->unk_08 in create_jittered_landing_spark */

typedef struct S_80165F00_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80165F00_5;

/* Spawns an effect near the source with randomized position and sprite scale. */
void create_jittered_landing_spark(S_80165F00_0 *source)
{
    s32 base_x;
    s32 base_y;
    s32 y_jitter;
    s32 x_jitter;
    s32 scale;
    S_80165F00_1 *source_pos;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;
    ObjectPosition *effect_transform;

    effect = allocate_flagged_object_node(0x12);
    if (effect != 0) {
        (effect->update_callback) = &update_landing_particle_fade;
        x_jitter = rand() & 0x3F;
        base_x =
            ((S_80165F00_4 *)(source->unk_08))->unk_02 - 0x20;
        ((S_80165F00_5 *)((effect->position)))->unk_02 =
            base_x + x_jitter;
        y_jitter = rand() & 0x3F;
        source_pos = source->unk_08;
        base_y = source_pos->unk_06 - 0x1A0;
        ((S_80165F00_5 *)((effect->position)))->unk_06 =
            base_y + y_jitter;
        ((S_80165F00_5 *)((effect->position)))->unk_0A =
            (s16)(((S_80165F00_4 *)(source->unk_08))->unk_0A -
                  0x100);
        effect_transform = effect->position;
        effect_transform->velocity_y = 0;
        effect_transform->velocity_x = 0;
        ((S_80165F00_5 *)((effect->position)))->unk_14 = 0x200000;
        register_node(effect, (void *)((s32)&draw_linked_sprites_clipped));
        sprite = effect->sprite;
        sprite->flags =
            (u16)(sprite->flags & 0xFFF3);
        scale = 0x1000 / (s32)(func_80167088(5) + 6);
        sprite->color.c.r = 0xFF;
        sprite->color.c.b = 0x20;
        sprite->color.c.g = 0x20;
        sprite->scale_y = (s16)scale;
        sprite->scale_x = (s16)scale;
        (*(Copy12 *)((u8 *)effect + 0x56)) =
            (*(Copy12 *)((u8 *)&particle_sprite_template + 0));
        sprite->source = (void *)(((void *)effect) + 0x56);
    }
}

/* MECHANISM: Dropping the cross-call destination cache gives the retail 0x20 frame and s0/s1 hold set.
   Split signed coordinate live ranges plus zero-arg RNG calls reproduce both addiu/store-delay
   sequences. U8 0xFF and packed Copy12 close G0. */
