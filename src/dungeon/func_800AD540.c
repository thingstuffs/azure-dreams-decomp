#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct {
    u8 pad0[0x8c];
    void *next;
    u8 pad90[6];
    s16 delay;
    u8 pad98[3];
    u8 state;
} StateObj;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[4];
    s32 dx;
    s32 dy;
    s32 unk14;
} Motion;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xe];
    u8 x;
    u8 y;
} Params;

typedef struct {
    u8 pad0[0x1c];
    s32 flags;
    u8 pad20[8];
    u8 byte28;
    u8 pad29[0x41];
    u16 key6a;
} Entity;

typedef struct {
    u8 pad0[0xa];
    u16 count;
    u8 padc[4];
    s32 value;
} Global83460;

extern u8 D_800B2A60[];

extern void func_8009A028(Entity *);
extern void func_800A2B04(Motion *, u8, u8);
extern void func_800AD4D0(Entity *);

/* Initializes and slows entity motion, then stops it or moves it to the target tile. */
void func_800B2CA0(StateObj *motion_state, Motion *motion, Params *params, Entity *entity) {
    s32 state;
    s16 initial_delay;
    s32 velocity_x;
    s32 velocity_y;
    s32 biased_dx;
    s32 biased_dy;

    state = motion_state->state;
    switch (state) {
    case 0:
        func_800AD4D0(entity);
        motion->dx = (-*(s16 *)(((u8 *)dirStepX) + ((entity->key6a >> 8) & 0xe))) << 0xf;
        motion->dy = (-*(s16 *)(((u8 *)dirStepY) + ((entity->key6a >> 8) & 0xe))) << 0xf;
        motion_state->state++;
        if (params->flags & 0x8000) {
            if (entity->byte28 != 0) {
                motion_state->state = 2;
                return;
            }
        {
            DungeonGlobalStatus *shared_state = &dungeonStatus;
            motion->unk14 = 0;
            motion->dy = 0;
            motion->dx = 0;
            if (((s32)shared_state->unk_10) == (s32)((u8 *)entity - 0x20)) {
                *(s32 *)&shared_state->unk_10 &= 0x7fffffff;
            }
            shared_state->unk_0A++;
            func_8009A028(entity);
            ((u16 *)motion_state)[-1] |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        return;
        }
        initial_delay = -1;
        if (entity->flags & 0x228) {
            initial_delay = 8;
        }
        motion_state->delay = initial_delay;
                /* fallthrough */
    case 1:
        velocity_x = motion->dx;
        biased_dx = velocity_x;
        if (velocity_x < 0) {
            biased_dx = velocity_x + 3;
        }
        velocity_y = motion->dy;
        motion->dx = velocity_x - (biased_dx >> 2);
        biased_dy = velocity_y;
        if (velocity_y < 0) {
            biased_dy = velocity_y + 3;
        }
        motion->dy = velocity_y - (biased_dy >> 2);
        if (motion_state->delay > 0) {
            u16 delay = motion_state->delay;
            motion_state->delay = delay - 1;
        } else if (params->flags & 0x6000) {
            motion_state->delay = 0;
        }
        if (motion_state->delay != 0) {
            return;
        }
        if (entity->byte28 == 0) {
        {
            DungeonGlobalStatus *shared_state = &dungeonStatus;
            motion->unk14 = 0;
            motion->dy = 0;
            motion->dx = 0;
            if (((s32)shared_state->unk_10) == (s32)((u8 *)entity - 0x20)) {
                *(s32 *)&shared_state->unk_10 &= 0x7fffffff;
            }
            shared_state->unk_0A++;
            func_8009A028(entity);
            ((u16 *)motion_state)[-1] |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        return;
        }
        motion_state->delay = 8;
        motion_state->state++;
        return;
    case 2:
    {
        s16 frames_left = motion_state->delay;
        if (frames_left != 0) {
            s32 target_x = (s32)params->x << 6;
            s32 pos_x = motion->x - 0x20;
            motion->dx = ((target_x - pos_x) << 0xf) / frames_left;
            {
                s32 pos_y = motion->y - 0x20;
                s32 target_y = (s32)params->y << 6;
                motion->dy = ((target_y - pos_y) << 0xf) / motion_state->delay;
            }
        }
        {
            u16 delay = motion_state->delay;
            delay -= 1;
            motion_state->delay = delay;
            if ((delay << 0x10) > 0) {
                return;
            }
        }
    }

        motion->unk14 = 0;
        motion->dy = 0;
        motion->dx = 0;
        func_800A2B04(motion, params->x, params->y);
        {
            if (((s32)dungeonStatus.unk_10) == (s32)((u8 *)entity - 0x20)) {
                *(s32 *)&dungeonStatus.unk_10 &= 0x7fffffff;
            }
            motion_state->next = D_800B2A60;
        }
        return;
    default:
        return;
    }
}
