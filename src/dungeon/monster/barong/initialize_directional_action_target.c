#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad00[0x1E];
    s16 field1E;
    u8 pad20[0x0C];
    u8 *field2C;
} Obj;

typedef struct {
    u8 pad00[0x2A];
    s16 field2A;
} Other;

typedef struct {
    u8 pad00[0x9A];
    s8 field9A;
    s8 field9B;
    u8 pad9C[2];
    s16 field9E;
} First;

extern u8 D_8017556C[];
struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);

/* Initialize state and configure the object using the direction lookup table. */
void initialize_directional_action_target(First *state, s32 unused, SpriteFrameState *object, Other *angle_source)
{
    state->field9A = 0x10;
    state->field9B = 0;
    state->field9E = 2;
    object->frameTable = D_8017556C;
    select_sprite_entry(object,
                  D_8017556C[((g_game_work.view.camera_rotation.parts.viewAngle + angle_source->field2A + 0x100) >> 9) & 7],
                  0);
    object->scale_y = 0xC00;
}
