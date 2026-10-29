#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"
#include "town/map.h"

typedef struct S_800A8440_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_800A8440_1;   /* arg0 in fade_timed_primitive; pointer addresses record offset 0x2 */

/* Fades the primitive and sets completion flags when the countdown expires. */
void fade_timed_primitive(void *record_fields, void *unused, SpriteFrameState *primitive) {
    u16 ticks_left;
    u8 brightness;
    u8 unused_byte;

    advance_sprite_animation_and_textures(primitive);
    brightness = primitive->color.c.r;
    if (brightness != 0) {
        primitive->color.c.r = (brightness - 0x10);
        primitive->color.c.b = (brightness - 0x10);
        primitive->color.c.g = (brightness - 0x10);
    }
    ticks_left = ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_04 - 1;
    ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800A8440_1 *)((u8 *)record_fields - 0x2))->unk_00 = (u16) (((S_800A8440_1 *)((u8 *)record_fields
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
