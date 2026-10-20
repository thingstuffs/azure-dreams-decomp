#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/dungeon_delay_views.h"
#include "shared/position_views.h"

#ifndef NULL
#define NULL 0
#endif

   /* effect in create_random_color_offset_effect */

typedef struct S_80171498_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80171498_1;   /* arg0 in create_random_color_offset_effect */

   /* source in create_random_color_offset_effect */

typedef struct S_80171498_3 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x1E];
    s16 unk_5A;
    u8 pad_5C[0x2];
    s16 unk_5E;
    u8 pad_60[0x2];
    s16 unk_62;
} S_80171498_3;   /* base in create_random_color_offset_effect */

   /* ((S_80171498_0 *)effect)->unk_08 in create_random_color_offset_effect */

   /* ((S_80171498_1 *)arg0)->unk_08 in create_random_color_offset_effect */


void *allocate_list_node();
s32 resolve_record_orientation_or_fallback();
s32 register_node();
s32 rand();
s32 steer_effect_toward_target();

extern u8 D_80170ED8[];
extern u8 D_801712C4[];

/* Creates an offset effect, advances it ten steps, and assigns a random color. */
void create_random_color_offset_effect(
    void *parent, s16 initial_14, s32 unused, s16 initial_32,
    s16 offset_x, s16 offset_y, s16 offset_z)
{
    s16 held_offset_x = offset_x;
    s16 held_offset_y = offset_y;
    s16 held_offset_z = offset_z;
    struct { u16 x; u16 y; u16 z; } source_offset;
    s16 step;
    s32 color_high;
    s32 color_mid;
    void *source_data;
    void *effect;
    void *effect_data;

    effect = allocate_list_node(0x211, parent);
    if (effect != NULL) {
        ((ProjectileObject *)effect)->unk_10 = D_801712C4;

        ((SignedPositionView *)(((ProjectileObject *)effect)->unk_08))->unk_02 =
            ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_02 + held_offset_x;
        ((SignedPositionView *)(((ProjectileObject *)effect)->unk_08))->unk_06 =
            ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_06 + held_offset_y;
        ((SignedPositionView *)(((ProjectileObject *)effect)->unk_08))->unk_0A =
            ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_0A + held_offset_z;

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (resolve_record_orientation_or_fallback(((DelayMotionZ *)source_data)->unk_08, source_data, &source_offset, 0) != 0) {
            ((SignedPositionView *)(((ProjectileObject *)effect)->unk_08))->unk_02 += source_offset.x;
            ((SignedPositionView *)(((ProjectileObject *)effect)->unk_08))->unk_06 += source_offset.y;
            ((SignedPositionView *)(((ProjectileObject *)effect)->unk_08))->unk_0A += source_offset.z;
        }

        effect_data = (u8 *)effect + 0x20;
        ((S_80171498_3 *)effect_data)->unk_5A = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_02;
        ((S_80171498_3 *)effect_data)->unk_5E = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_06;
        ((S_80171498_3 *)effect_data)->unk_62 = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_0A;

        source_data = ((S_80171498_1 *)parent)->unk_0C;
        if (resolve_record_orientation_or_fallback(((DelayMotionZ *)source_data)->unk_08, source_data, &source_offset, 0) != 0) {
            (*(s16 *)((u8 *)effect_data + 0x5A)) += source_offset.x;
            (*(s16 *)((u8 *)effect_data + 0x5E)) += source_offset.y;
            ((S_80171498_3 *)effect_data)->unk_62 += source_offset.z;
        }

        ((S_80171498_3 *)effect_data)->unk_36 = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_02;
        ((S_80171498_3 *)effect_data)->unk_38 = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_06;
        ((S_80171498_3 *)effect_data)->unk_3A = ((MovingPosition *)(((S_80171498_1 *)parent)->unk_08))->unk_0A;

        step = 0;
        do {
            steer_effect_toward_target(effect_data, ((ProjectileObject *)effect)->unk_08, ((ProjectileObject *)effect)->unk_0C);
            step++;
        } while (step < 10);

        ((S_80171498_3 *)effect_data)->unk_14 = initial_14;
        ((S_80171498_3 *)effect_data)->unk_32 = initial_32;
        register_node(effect, D_80170ED8);

        color_high = rand();
        color_mid = rand();
        ((S_80171498_3 *)effect_data)->unk_00 =
            ((color_high & 0xFF) << 16) |
            ((color_mid & 0xFF) << 8) |
            (rand() & 0xFF);
        ((S_80171498_3 *)effect_data)->unk_08 = ((S_80171498_3 *)effect_data)->unk_00;
    }
}
