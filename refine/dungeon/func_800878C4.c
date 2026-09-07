#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s8 pad_00[0x2A];
    s16 field_2A;
} Arg0;

extern s32 D_800E296C[3];
extern u8 D_800DD0B8[8];
extern u8 D_800DCFB0[8];
extern s16 D_80083228[5];

extern void func_800B0F50(void *, s32, void *, void *);
extern void func_800B1768(s32, s32, s32, s32, s32, s32);
extern void func_80048A44(void *, u8, s32, s32);

typedef struct S_8008D024_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8008D024_0;   /* temp_a3 in func_8008D024 */

typedef struct S_8008D024_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008D024_1;   /* temp_a0 in func_8008D024 */

typedef struct S_8008D024_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x6C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x68];
    void * unk_104;
    u8 pad_108[0x18];
    s16 unk_120;
} S_8008D024_2;   /* arg0 in func_8008D024 */

typedef struct S_8008D024_3 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008D024_3;   /* arg2 in func_8008D024 */

/* Selects an eligible linked target and initializes the actor's action and directional display. */
s32 func_8008D024(S_8008D024_2 *actor, s32 context, S_8008D024_3 *display, s32 target_index, s32 action_mode) {
    s32 target_flags;
    s32 slot_offset;
    S_8008D024_1 *target;
    Arg0 *actor_heading;
    s8 *slot_base;
    u8 *direction_frames;
    s16 saved_mode;

    slot_offset = (s32)(target_index << 0x10) >> 0xE;
    slot_base = (s8 *)((s32)slot_offset + (s32)actor);
    actor_heading = actor;
    target = ((S_8008D024_0 *)slot_base)->unk_AC;
    saved_mode = action_mode;
    if (target != 0) {
        target_flags = target->unk_1C;
        if (target_flags & 0x20000) {
            if (!(target_flags & 0x80000)) {
                actor->unk_104 = target;
                actor->unk_9A = 0x27;
                actor->unk_9B = 0;
                actor->unk_8C = 0;
                func_800B0F50(target, context, display, slot_base);
                if ((action_mode << 0x10) == 0) {
                    func_800B1768(0x21, 0xE0, 0x84, 0, 0, 0);
                    func_800B1768(0x22, 0xF2, 0x98, 1, 0, 2);
                    func_800B1768(0x24, 0xCE, 0x98, 2, 1, 4);
                    func_800B1768(0x23, 0xE0, 0xAC, 3, 1, 6);
                    D_800E296C[0] |= 0x2000;
                }
                if (actor->unk_1C & 0x100000) {
                    direction_frames = D_800DD0B8;
                } else {
                    direction_frames = D_800DCFB0;
                }
                display->unk_2C = direction_frames;
                func_80048A44(display, direction_frames[((s32)(D_80083228[0] + ((Arg0 *)actor_heading)->field_2A + 0x100) >> 9) & 7], 0, 1);
                actor->unk_120 = saved_mode;
                return 1;
            }
        }
    }
    return 0;
}
