#include "common.h"
#include "m2c_compat.h"
extern s32 func_80069EF8(void);
/* The 0x54-byte ring ends at the adjacent weights-table address.
 * Name the bounded ring without guessing the following table's extent. */
typedef struct { u8 packets[0x54]; } PacketRing;
extern s8 D_80024AE0[];

extern u16 D_80024A70;
#include "shared/object_flags.h"

typedef union { u16 bits; s16 value; } JitterHalf;
typedef struct { u16 fraction; JitterHalf whole; } JitterAxis;
typedef struct { JitterAxis axes[6]; } JitterMotion;
typedef struct {
    u8 reserved_00[0x14];
    void *anchor;
    u16 base_position[3];
    u8 reserved_1e[0x14];
    s16 phase;
    u8 reserved_34[8];
    JitterHalf fade;
} JitterEffect;
typedef struct {
    u8 reserved_00[8];
    u32 packet;
    u8 red, green, blue;
    u8 reserved_0f[0xD];
    u16 scale_x, scale_y;
} JitterSprite;
typedef struct { u16 flags; } JitterHeader;

/* Jitters the sprite around its base coordinates, cycles its packets, and shrinks and fades it until
   removal. */
void jitter_effect_position_and_fade(void *effect, void *position, void *sprite) {
    s32 axes_left;
    u16 *base_coord;
    s32 jitter;
    s32 fade;
    u16 base_value;
    u16 next_scale;
    u32 next_packet;
    u8 brightness;
    void *anchor;
    JitterAxis *motion_axis;

    anchor = (((JitterEffect *)effect)->anchor);
    D_80024A70 += 1;
    if (anchor != NULL) {
        (((JitterMotion *)(position))->axes[3].whole.bits) = (u16) (((JitterMotion *)(anchor))->axes[0].whole.bits);
        (((JitterMotion *)(position))->axes[4].whole.bits) = (u16) (((JitterMotion *)((((JitterEffect *)effect)->anchor)))->axes[1].whole.bits);
        (((JitterMotion *)(position))->axes[5].whole.bits) = (u16) (((JitterMotion *)((((JitterEffect *)effect)->anchor)))->axes[2].whole.bits);
    }
    motion_axis = position;
    base_coord = ((JitterEffect *)effect)->base_position;
    axes_left = 3;
    do {
        axes_left -= 1;
        jitter = (func_80069EF8() & 0xF) - 8;
        base_value = *base_coord;
        base_coord += 1;
        (((JitterAxis *)motion_axis)->whole.value) = (s16) (base_value + (jitter * D_80024AE0[(((JitterEffect *)effect)->phase)]));
        motion_axis++;
    } while (axes_left > 0);
    next_packet = (((JitterSprite *)sprite)->packet) + 0xC;
    (((JitterSprite *)sprite)->packet) = next_packet;
    if (next_packet >= (u32)D_80024AE0) {
        (((JitterSprite *)sprite)->packet) = (u32)((PacketRing *)((u8 *)D_80024AE0 - sizeof(PacketRing)))->packets;
    }
    next_scale = (((JitterSprite *)sprite)->scale_y) - ((((JitterSprite *)sprite)->scale_y) / 24);
    (((JitterSprite *)sprite)->scale_y) = next_scale;
    (((JitterSprite *)sprite)->scale_x) = next_scale;
    fade = (((JitterEffect *)effect)->fade.bits);
    fade -= 8;
    (((JitterEffect *)effect)->fade.bits) = fade + ((s16) (u16) (((JitterEffect *)effect)->phase) / 2);
    brightness = (u8) (((JitterEffect *)effect)->fade.bits);
    (((JitterSprite *)sprite)->blue) = brightness;
    (((JitterSprite *)sprite)->green) = brightness;
    (((JitterSprite *)sprite)->red) = brightness;
    if ((s16) (((JitterEffect *)effect)->fade.bits) <= 0) {
        (((JitterHeader *)effect)[-1].flags) = (u16) ((((JitterHeader *)effect)[-1].flags) | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
