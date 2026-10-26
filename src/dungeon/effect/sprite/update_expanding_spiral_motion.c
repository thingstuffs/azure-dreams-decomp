#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"

struct Dst;
struct Elem;

extern void func_8002421C();
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void advance_sprite_animation_and_textures(void *entity);
extern s32 rsin();
extern s32 rcos();
extern u8 ribbon_sprite_entries[];

typedef struct S_8185CB30_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x10];
    u16 unk_1C;
    s16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    s16 unk_24;
} S_8185CB30_0;   /* arg0 in update_expanding_spiral_motion */

typedef struct S_8185CB30_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8185CB30_1;

typedef struct S_8185CB30_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8185CB30_2;   /* arg1 in update_expanding_spiral_motion */

/* Advance expanding spiral motion and update the moving object. */
void update_expanding_spiral_motion(S_8185CB30_0 *motion, S_8185CB30_2 *position, SpriteFrameState *object)
{
    s16 next_angle;
    u16 cycle_tick;
    u16 next_tick;
    GameWork *angle_table;
    S_8185CB30_1 *owner;

    owner = motion->unk_00;
    owner->unk_14 = (u16)(owner->unk_14 + 1);
    angle_table = &g_game_work;
    cycle_tick = motion->unk_22;
    next_tick = cycle_tick + 1;
    motion->unk_22 = next_tick;
    if ((s16)next_tick >= 8) {
        motion->unk_22 = (u16)(cycle_tick - 7);
    }
    if ((s16)motion->unk_22 == motion->unk_24) {
        func_8002421C(motion->unk_00, position);
    }
    if (motion->unk_1E < 0xC1) {
        motion->unk_1E = (s16)((u16)motion->unk_1E + 8);
    }
    next_angle = motion->unk_1C + (u16)motion->unk_1E;
    motion->unk_1C = (u16)next_angle;
    motion->unk_1C = (u16)(next_angle % 0x1000);
    motion->unk_20 = (u16)(motion->unk_20 + 4);
    position->unk_02 =
        (s16)(motion->unk_06 +
              ((s32)((rsin((s16)motion->unk_1C) >> 4) *
                     (s16)motion->unk_20) >> 8));
    position->unk_06 =
        (s16)(motion->unk_0A +
              ((s32)((rcos((s16)motion->unk_1C) >> 4) *
                     (s16)motion->unk_20) >> 8));
    object->angle_z =
        (s16)((s32)(0 - ((rcos((s16)motion->unk_1C -
                                        angle_table->view.camera_rotation.parts.viewAngle) >> 4) << 8)) >> 8);
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        select_record_entry_and_value(object, ribbon_sprite_entries, 0);
    }
}
