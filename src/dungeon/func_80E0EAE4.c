#include "common.h"
#include "records/Rec_D_800E3D7C.h"



typedef s32 M2C_UNK;


typedef struct S_801722E4_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801722E4_5_pre;   /* the 0x14 bytes before ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_801722E4, addressed as ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv[-1] */


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

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 =
        (u8)(((Rec_D_800E3D7C *)actor)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2008)) {
        actor_base = (s8 *)actor - 0x20;
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            func_800C7930(actor_base, event_context, 8, 0x300);
            if ((func_800A2B5C(actor) << 0x10) == 0) {
                target = ((S_801722E4_5_pre *)(((Rec_D_800E3D7C *)actor)->unk_60.as_pv))[-1].unk_00;
                ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
                    sprite->unk_24,
                    sprite->unk_25,
                    target->unk_24,
                    target->unk_25,
                    &distance);
                direction_frames = D_801764A0;
                action_state->unk_9A = 0x17;
                do {
                    angle_page = (s8 *)0x80080000;
                } while (0);
                ASM_KEEP(angle_page);
                action_state->unk_9B = 0;
                action_state->unk_8C = 0;
                sprite->unk_2C = direction_frames;
                func_80047784(
                    sprite,
                    direction_frames[((s32)(*(s16 *)(angle_page + 0x3228) +
                                    ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) &
                             7],
                    0);
                func_800A4ACC(actor);
                ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 =
                    (u8)(((Rec_D_800E3D7C *)actor)->unk_6D.as_u8 - 1);
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
