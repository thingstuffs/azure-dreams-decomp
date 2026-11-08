#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"

#include "common.h"
#include "engine/node.h"
#include "shared/sprite_frame_state.h"
#include "engine/effect.h"

typedef struct {
    u8 unk_00[0x0C];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F[0x0D];
    u16 unk_1C;
} Func8003C520Data;

extern u32 D_800814A0;

/* Decreases intensity and marks the object finished when its countdown expires. */
void fade_manager_step_out(void *object, ObjectPosition *unused, SpriteFrameState *data) {
    s32 intensity = data->color.c.b;
    s32 countdown = data->scale_x;

    intensity -= 0x10;
    countdown -= 0x200;
    data->scale_x = countdown;
    if (intensity < 0) {
        intensity = 0;
    }

    data->color.c.b = intensity;
    data->color.c.g = intensity;
    data->color.c.r = intensity;
    if (((s16)(data->scale_x)) > 0) {
        return;
    }

    unlink_node_if_registered(object);
    *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
    D_800814A0 |= OBJECT_REMOVE_PENDING;
}
