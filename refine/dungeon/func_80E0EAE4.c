#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_801722E4_4 {
    u8 pad_00[0x60];
    void * unk_60;
} S_801722E4_4;   /* arg3 in func_801722E4 */

typedef struct S_801722E4_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801722E4_5_pre;   /* the 0x14 bytes before ((S_801722E4_4 *)arg3)->unk_60 in func_801722E4, addressed as ((S_801722E4_4 *)arg3)->unk_60[-1] */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80047784();
extern s16 func_800A0818();
extern s32 func_800A2B5C();
extern M2C_UNK func_800A4ACC();
extern M2C_UNK func_800C77D0();
extern M2C_UNK func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801764A0[];

typedef struct S_801722E4_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801722E4_0;   /* arg3 in func_801722E4 */

typedef struct S_801722E4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801722E4_1;   /* arg2 in func_801722E4 */

typedef struct S_801722E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801722E4_2;   /* temp_v0 in func_801722E4 */

typedef struct S_801722E4_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_801722E4_3;   /* arg0 in func_801722E4 */

/* Face the target and initialize the actor action when status checks allow it. */
void func_801722E4(S_801722E4_3 *action_state, M2C_UNK event_context, S_801722E4_1 *sprite, void *actor) {
    M2C_UNK distance;
    void *actor_base;
    S_801722E4_2 *target;
    u8 *direction_frames;
    s8 *angle_page;

    ((S_801722E4_0 *)actor)->unk_71 =
        (u8)(((S_801722E4_0 *)actor)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2008)) {
        actor_base = (s8 *)actor - 0x20;
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            func_800C7930(actor_base, event_context, 8, 0x300);
            if ((func_800A2B5C(actor) << 0x10) == 0) {
                target = ((S_801722E4_5_pre *)(((S_801722E4_4 *)actor)->unk_60))[-1].unk_00;
                ((S_801722E4_0 *)actor)->unk_2A = func_800A0818(
                    sprite->unk_24,
                    sprite->unk_25,
                    target->unk_24,
                    target->unk_25,
                    &distance);
                direction_frames = D_801764A0;
                action_state->unk_9A = 0x17;
                ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
                angle_page = (s8 *)0x80080000;
                ASM_KEEP(angle_page);   /* MATCH pin: retail schedule: same instructions, different order without it */
                action_state->unk_9B = 0;
                action_state->unk_8C = 0;
                sprite->unk_2C = direction_frames;
                func_80047784(
                    sprite,
                    direction_frames[((s32)(*(s16 *)(angle_page + 0x3228) +
                                    ((S_801722E4_0 *)actor)->unk_2A + 0x100) >> 9) &
                             7],
                    0);
                func_800A4ACC(actor);
                ((S_801722E4_0 *)actor)->unk_6D =
                    (u8)(((S_801722E4_0 *)actor)->unk_6D - 1);
                action_state->unk_98 =
                    (u16)(action_state->unk_98 | 8);
                func_800C77D0(actor_base, event_context, 8, 0x300);
            }
        }
    }
}

/* MECHANISM: Keep the natural 56-byte frame, sibling scalar stack local, and five
   saved value roles. Materialize the table base before the 0x9A store, then fence
   and pin the 0x8008 page in v0 after it; this produces retail's la/sb/lui order. */
