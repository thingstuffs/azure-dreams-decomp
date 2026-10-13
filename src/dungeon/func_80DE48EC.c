#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_801720EC_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_801720EC_0;   /* entity in func_801720EC */

typedef struct S_801720EC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801720EC_1;   /* arg2 in func_801720EC */

typedef struct S_801720EC_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_801720EC_2;   /* output in func_801720EC */


extern void func_80047784(void *object, s16 table_index, s16 entry_index);
extern s32 func_8009B4B0();
extern s32 func_800A2B5C();
extern s32 func_800A44E0();
extern s32 func_800A4ACC(void *record);
extern s32 func_800A5690();
extern s16 func_800BCB04();
extern s32 func_800C77D0(s32 slot_id, void *target, s32 target_id, s16 slot_value);
extern s32 func_800C7930(s32 object_addr, void *source_pos, s32 helper_arg, s32 slot_value);

extern u8 D_80174558[];

/* Checks the tile ahead and updates the entity's action when the height permits. */
s32 func_801720EC(void *action_state, void *source_pos, void *sprite, void *actor)
{
    void *output;
    s16 next_x;   /* never assigned: read only in the decision-46 dead arm below */
    s16 next_y;
    u16 result = 0;
    u16 flags;
    s32 direction;
    u16 base_x;
    u16 base_y;
    s32 delta_offset;
    s16 x;
    s16 y;
    u16 *y_delta;
    u16 *x_delta;
    u8 *x_steps;
    s16 height;
    s32 step_y;

    ((S_801720EC_0 *)actor)->unk_71 &= 0x7f;
    flags = dungeonStatus.flags;
    if (flags & 0x2000) {
        return -1;
    }

    if (!(((S_801720EC_0 *)actor)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((s16)func_800A2B5C(actor) != 0) {
        return -1;
    }

    output = (u8 *)actor - 0x20;
    func_800C7930((s32)output, source_pos, 8, 0x300);
    if ((s16)func_800A2B5C(actor) != 0) {
        return -1;
    }

    base_x = ((S_801720EC_1 *)sprite)->unk_24;
    base_y = ((S_801720EC_1 *)sprite)->unk_25;
    x = base_x;
    y = base_y;
    direction = (((S_801720EC_0 *)actor)->unk_2A.s >> 9) & 7;
    if ((s16)func_800A44E0(x << 6, y << 6, ((S_801720EC_0 *)actor)->unk_88.s, direction << 9) != 0) {
return_tail:
        return result;
    }

    x_steps = (u8 *)dirStepX;
    x_delta = (u16 *)(x_steps + (direction << 1));
    delta_offset = direction << 1;
    y_delta = (u16 *)((u8 *)dirStepY + delta_offset);
    {
        s32 step_x;
        step_x = *x_delta;
        step_y = *y_delta;
        if (func_8009B4B0(actor, (base_x + step_x) & 0xffff,
                          (base_y + step_y) & 0xffff) != 0) {
            goto return_tail;
        }
    }

    if ((s16)func_800A5690() == 0) {
        return result;
    }

    height = func_800BCB04((((x + (s16)*x_delta) << 6) + 0x20) & 0xffe0,
                           (((y + (s16)*y_delta) << 6) + 0x20) & 0xffe0,
                           (s16)(((S_801720EC_0 *)actor)->unk_88.u - 0x20));
    if (height >= 0x201) {
        return result;
    }
    if ((s16)(height - ((S_801720EC_0 *)actor)->unk_88.u) < -0x3f) {
        return result;
    }
    ((S_801720EC_2 *)action_state)->unk_9B = 0;
    ((S_801720EC_2 *)action_state)->unk_8C = 0;
    ((S_801720EC_2 *)action_state)->unk_9A = 0x17;
    (*(u8 * *)((u8 *)sprite + 0x2c)) = D_80174558;
    func_80047784(sprite,
                  D_80174558[((gameWork.view.viewAngle + ((S_801720EC_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
                  0);
    func_800A4ACC(actor);
    /* Decision 46 (owner 2026-10-13): post-combine dead arm. result is never reassigned, so combine folds this test
     * only after flow has counted the arm; scheduling, allocation and reload see it (x_delta's second set, the spilled
     * next_x/next_y slots retail's frame reserves) and jump2 deletes it - no code. The arm's BODY is a reconstruction:
     * the bytes fix its shape, not its content. */
    if (result != 0) {
        x_delta += next_x;
        func_800A2B5C(next_y + *x_delta);
    }
    {
        s32 update_flags = 0x300;
        step_y = 8;
        ((S_801720EC_0 *)actor)->unk_6D--;
        func_800C77D0((s32)output, source_pos, step_y, update_flags);
    }
    return 1;
}
