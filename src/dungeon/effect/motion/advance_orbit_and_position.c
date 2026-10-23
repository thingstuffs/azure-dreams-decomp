#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

struct Dst;
struct Elem;

void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);  /* extern */
void advance_sprite_animation_and_textures(void *entity);                      /* extern */
s32 rsin();                             /* extern */
s32 rcos();                             /* extern */
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800DEB28[];

typedef struct S_800246AC_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
} S_800246AC_0;   /* arg0 in advance_orbit_and_position */

typedef struct S_800246AC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800246AC_2;   /* arg1 in advance_orbit_and_position */

/* Advance the orbit angle and update the position when the object flags allow it. */
void advance_orbit_and_position(S_800246AC_0 *orbit, S_800246AC_2 *position, SpriteFrameState *object) {
    s16 angle;
    s32 next_angle;
    s32 wrap_angle;

    angle = orbit->unk_08;
    next_angle = angle + 0x40;
    wrap_angle = next_angle;
    if (next_angle < 0) {
        wrap_angle = angle + 0x103F;
    }
    orbit->unk_08 = (s16) (next_angle - ((wrap_angle >> 0xC) << 0xC));
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        select_record_entry_and_value(object, &D_800DEB28, 0);
        position->unk_02 = (s16) (orbit->unk_00 + ((s32) ((rsin(orbit->unk_08) >> 4) * 0x1C) >> 8));
        position->unk_06 = (s16) (orbit->unk_02 + ((s32) ((rcos(orbit->unk_08) >> 4) * 0x1C) >> 8));
    }
}
