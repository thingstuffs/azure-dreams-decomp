#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80048A44();
extern M2C_UNK func_80099844();
extern s32 func_8009B5AC();
extern M2C_UNK func_8009F644();
extern M2C_UNK func_800A56E0();
extern s32 D_80012090[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_80081484[];
extern s32 D_80083170[];
extern s16 D_80083228[];
extern u8 D_8008ACDC[];
extern u8 D_800DCFC8[];
extern u8 D_800E0495[];



typedef struct S_8008C5C4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008C5C4_1;   /* arg2 in func_8008C5C4 */

typedef struct S_8008C5C4_2 {
    u8 pad_00[0x8C];
    union { void * p; u8 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x80];
    s32 unk_11C;
    u8 pad_120[0x4];
    s32 unk_124;
} S_8008C5C4_2;   /* arg0 in func_8008C5C4 */

typedef struct S_8008C5C4_3 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
} S_8008C5C4_3;   /* temp_v0 in func_8008C5C4 */

typedef struct S_8008C5C4_4 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008C5C4_4;   /* (void *)tail_page in func_8008C5C4 */

typedef struct S_8008C5C4_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008C5C4_5;   /* temp_a3 in func_8008C5C4 */

typedef struct S_8008C5C4_6 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8008C5C4_6;   /* ((S_8008C5C4_2 *)arg0)->unk_124 in func_8008C5C4 */

/* Find a target ahead of the actor and initialize the interaction state. */
s32 func_8008C5C4(S_8008C5C4_2 *action, void *unused, S_8008C5C4_1 *position, Rec_D_800E3D7C *actor) {
    s32 target;
    s32 target_result;
    s32 direction_offset;
    s32 result;
    register u32 tail_page ASM_REG("$3");
    s32 tail_result;
    s32 mode;
    register s32 target_kind;

    direction_offset = ((u16)actor->unk_2A.as_u16 >> 8) & 0xE;
    target_result = func_8009B5AC(
        actor,
        (s16)(position->unk_24 + *(u16 *)(D_8006CCD8 + direction_offset)),
        (s16)(position->unk_25 + *(u16 *)(D_8006CCE8 + direction_offset)));
    action->unk_124 = target_result;
    if (target_result != 0) {
        result = -1;
        if (target_result <= 0) {
            if (!(((S_8008C5C4_3 *)target_result)->unk_14 & 0x80000)) {
                action->unk_11C = target_result;
                action->unk_124 = 0;
            } else {
                mode = *(s32 *)0x80012090;
                if (mode == 1) {
                    target_kind = ((S_8008C5C4_3 *)target_result)->unk_13;
                    if ((target_kind == 0x39) || (target_kind == 2)) {
                        if (D_80083170[0] & 0x40) {
                            func_800A56E0(0x506);
                            func_80099844(action->unk_124, &D_800E0495);
                            tail_result = 0;
                        } else {
                            tail_result = 0;
                        }
                        ASM_KEEP(tail_result);
                        tail_page = 0x80080000;
                        ASM_KEEP(tail_page);
                        ((S_8008C5C4_4 *)((void *)tail_page))->unk_1484 = 0;
                        tail_page = 0x80090000;
                        ASM_KEEP(tail_page);
                        tail_page -= 0x5324;
                        action->unk_124 = 0;
                        action->unk_8C.p = (void *)tail_page;
                        return;
                    }
                }
                target = action->unk_124;
                ((S_8008C5C4_5 *)target)->unk_1C |= 0x80000;
                actor->unk_1C.as_s32 |= 0x100000;
                ((S_8008C5C4_6 *)(action->unk_124))->unk_60 = actor;
                func_8009F644(actor, 0x20, 0, 0);
                func_800A56E0(0x511);
            }
            action->unk_9A = 0x1B;
            action->unk_9B = 0;
            action->unk_8C.p = 0;
            position->unk_2C = D_800DCFC8;
            func_80048A44(
                position,
                D_800DCFC8[((s32)(D_80083228[0] +
                                 (s16)actor->unk_2A.as_u16 + 0x100) >> 9) & 7],
                0, 1);
            tail_result = 1;
            return tail_result;
        }
        return result;
    }
    action->unk_8C.p2 = D_8008ACDC;
    result = 0;
    return result;
}
