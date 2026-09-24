#include "common.h"

typedef struct S_80172050_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172050_0;   /* actor in func_80172050 */

typedef struct S_80172050_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172050_1;   /* actor_info in func_80172050 */

typedef struct S_80172050_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172050_2;   /* out in func_80172050 */

typedef struct S_80172050_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
} S_80172050_3;   /* acting_actor in func_80172050 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, s32, s32, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80175F48;

/* Attempts an actor action and initializes its output and directional display on success. */
s32 func_80172050(void *action_out, s32 action_param, void *actor_info, void *acting_actor)
{
    volatile u8 frame_pad[8];
    u16 *global_state;
    u8 *direction_table;
    s32 computed_angle;
    s32 result;
    s32 action_code;
    u16 state_flags;

    ((S_80172050_0 *)acting_actor)->unk_71 &= 0x7F;
    global_state = (u16 *)&D_80083460;
    if (global_state[1] & 0x2000) {
        result = -1;
        goto done;
    }

    computed_angle = func_800A04F0(acting_actor, ((S_80172050_1 *)actor_info)->unk_24,
        ((S_80172050_1 *)actor_info)->unk_25, ((S_80172050_0 *)acting_actor)->unk_2A);
    if ((func_800A2CB8(((void *)(acting_actor)), computed_angle) << 16) == 0) {
        result = 0;
        goto done;
    }

    state_flags = global_state[1];
    if (state_flags & 0x2000) {
        result = -1;
        goto done;
    }
    if (!(((S_80172050_0 *)acting_actor)->unk_46 & 0x8000)) {
        if (state_flags & 8) {
            result = -1;
            goto done;
        }
    }

    if ((u16)(-func_800A0134(computed_angle, acting_actor) + 0x3F) >= 0x7F) {
        result = 0;
        goto done;
    }
    if ((func_800A2B5C(acting_actor) << 16) != 0) {
        result = -1;
        goto done;
    }

    func_800C7930((u8 *)acting_actor - 0x20, action_param, 8, 0x300);
    if ((func_800A2B5C(acting_actor) << 16) != 0) {
        result = -1;
        goto done;
    }
    ((S_80172050_2 *)action_out)->unk_9A = 0x11;
    action_code = 0x7C;
    ((S_80172050_2 *)action_out)->unk_9B = 0;
    ((S_80172050_2 *)action_out)->unk_8C = 0;
    ((S_80172050_0 *)acting_actor)->unk_84 = action_code;
    ((S_80172050_0 *)acting_actor)->unk_85 = 4;
    direction_table = &D_80175F48;
    (*(void * *)((u8 *)actor_info + 0x2C)) = direction_table;
    func_80047784(actor_info,
        direction_table[((D_80083228 + ((S_80172050_0 *)acting_actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172050_3 *)acting_actor)->unk_6D--;
    func_8009C93C(acting_actor, actor_info, ((S_80172050_3 *)acting_actor)->unk_2A, 1, 0);
    result = 1;

done:
    return result;
}

