#include "common.h"

typedef struct S_80173CE0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173CE0_0;   /* arg0 in func_80173CE0 */

typedef struct S_80173CE0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173CE0_1;   /* arg2 in func_80173CE0 */



extern void func_800A2B04(s32, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174084(void *, s32, void *);
extern void func_801744B8(void *);
extern s32 D_8008346C;
extern s32 D_80170E5C;

/* Advance the action state and update the entity when action flags permit. */
void func_80173CE0(void *state_ctx, s32 entity_id, void *action, void *entity)
{
    s32 state;
    u16 flags;

    state = ((S_80173CE0_0 *)state_ctx)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto end;
    }
    if (state == 2) {
        goto state_two;
    }
    goto end;

state_zero:
    flags = ((S_80173CE0_1 *)action)->unk_14;
    if (flags & 0x8000) {
        ((S_80173CE0_1 *)action)->unk_14 = flags | 0x6000;
        ((S_80173CE0_0 *)state_ctx)->unk_9B = 2;
        goto end;
    }
    ((S_80173CE0_0 *)state_ctx)->unk_9B = 1;

state_one:
    if ((((S_80173CE0_1 *)action)->unk_04 == 8) &&
        (((S_80173CE0_1 *)action)->unk_14 & 0x1000)) {
        goto run_one;
    }
    if (!(((S_80173CE0_1 *)action)->unk_14 & 0xE000)) {
        goto end;
    }
run_one:
    func_801744B8(entity);
    func_800A56E0(0x80C);
    func_80174084(state_ctx, entity_id, action);
    ((S_80173CE0_0 *)state_ctx)->unk_9B++;
    goto end;

state_two:
    if (((S_80173CE0_1 *)action)->unk_14 & 0xE000) {
        func_800AD594(entity, 0x400);
        func_800A2B04(entity_id, ((S_80173CE0_1 *)action)->unk_24, ((S_80173CE0_1 *)action)->unk_25);
        ((S_80173CE0_0 *)state_ctx)->unk_8C = &D_80170E5C;
        D_8008346C = 0;
        (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
    }

end:
    return;
}
