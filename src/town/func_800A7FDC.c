#include "common.h"
#include "shared/game_work.h"

extern s32 D_800A5A98;
extern s16 D_800D01F8[];
extern u8 D_80100D98[];

extern void textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern s16 townStepAngle12Toward(s32, s32, s32);
extern s32 townViewRelativeAngleSector(s16);
extern void townClearMotionAlongBlockedDirectionsUpdateAffectedAxes(void *);
extern void townCopyEntityRecordFields(void *, void *);

/* Turn the entity toward its target angle and update its directional sprite. */
void townTurnEntityTowardTarget(void *entity, void *transform, void *sprite) {
    GameWork *input_state;
    void *transform_arg;
    s32 direction;
    s32 current_angle;
    s32 target_angle;

    transform_arg = transform;
    input_state = &gameWork;
    townClearMotionAlongBlockedDirectionsUpdateAffectedAxes(transform_arg);
    {
        void *entity_type;

        entity_type = *(void **)entity;
        if (entity_type == (u8 *)&D_800A5A98 && (input_state->buttons & 0x2000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle -= 0x200;
            *(s16 *)((u8 *)entity + 0x18) = townStepAngle12Toward(current_angle, target_angle, 0x200);
        } else if (entity_type == (u8 *)&D_800A5A98 && (input_state->buttons & 0x8000)) {
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle += 0x200;
            *(s16 *)((u8 *)entity + 0x18) = townStepAngle12Toward(current_angle, target_angle, 0x200);
        } else {
            current_angle = *(s16 *)((u8 *)entity + 0x18);
            target_angle = *(s16 *)((u8 *)entity + 0x10);
            *(s16 *)((u8 *)entity + 0x18) = townStepAngle12Toward(current_angle, target_angle, 0x200);
        }
    }
    direction = townViewRelativeAngleSector(*(s16 *)((u8 *)entity + 0x18));
    if (*(s16 *)((u8 *)entity + 0x12) != direction) {
        textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(sprite,
                      *(u8 *)(*(u8 **)((u8 *)entity + 0x1C) + direction),
                      *(s8 *)((u8 *)sprite + 4), 0);
        *(s16 *)((u8 *)entity + 0x12) = direction;
    }
    {
        s16 *flip_table = D_800D01F8;
        u16 sprite_flags;

        if (flip_table[direction] != 0) {
            *(u16 *)((u8 *)sprite + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)sprite + 0x14) &= 0xFFFE;
        }
    }
    func_80048AC8(sprite, 0);
    {
        u8 *render_state = D_80100D98;

        townCopyEntityRecordFields(render_state, transform);
        *(s32 *)(render_state + 8) = 0;
    }
}
