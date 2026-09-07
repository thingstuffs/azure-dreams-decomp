#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct StatePair {
    s32 first;
    s32 second;
} StatePair;

extern s32 D_801379A8;
extern s32 D_801379B0;
extern s8 D_8008CA34;
extern s32 D_804090F8[];
extern s32 D_80400854;
extern s32 D_80400860;

extern void func_8003FA78(void *arg0, s32 arg1);
extern void func_8003FD58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80063FF8(s32 arg0);
extern void func_804008A0(s32 arg0);
extern void func_80400EF8(void);
extern StatePair *func_804017EC(void);
extern void func_804018FC(void);
extern void func_80407830(s32 arg0, s32 arg1);
extern void func_8040787C(s32 arg0, StatePair *arg1, s32 *arg2);
extern void func_804080A4(void);
extern void func_804084DC(void *arg0);

void func_804081AC(void *arg0)
{
    s32 changed[2];
    StatePair *state;
    StatePair *state_arg;
    s32 input;
    s32 flags;
    s32 status;
    s32 value;

    input = D_801379A8;
    status = 0;
    if (input != 0) {
        flags = D_801379B0;
        if (flags & 0x40) {
            s32 *object;

            func_80063FF8(0x515);
            func_804084DC((u8 *)arg0 - 0x20);
            D_8008CA34 = 2;
            func_80400EF8();
            func_8003FD58(0, 0xF, 0, 0);
            object = FIELD(arg0, s32 *, 0x14);
            FIELD(object, u16, 0x1E) |= 0x2000;
            goto status_check;
        } else if (flags & 0x20) {
            func_80063FF8(0x514);
            func_804008A0(FIELD(arg0, s32, 0xC));
            FIELD(arg0, s32, 0x34) = 0;
            FIELD(arg0, void *, -0x10) = func_804080A4;
            goto function_return;
        } else if (input & 0xA000) {
            if (input & 0x8000) {
                value = FIELD(arg0, s32, 0xC);
                FIELD(arg0, s32, 0xC) = 0;
                if (value != 0) {
                    status = 1;
                }
            } else {
                value = FIELD(arg0, s32, 0xC);
                if (value == 0) {
                    status = 1;
                }
                FIELD(arg0, s32, 0xC) = 1;
            }
        }

status_check:
        if (status != 0) {
            func_80063FF8(0x502);
            func_80407830(FIELD(arg0, s32, 0x24), FIELD(arg0, s32, 0xC));
        }
    }

    state = func_804017EC();
    changed[0] = state->first != FIELD(arg0, s32, 0x18);
    changed[1] = state->second != FIELD(arg0, s32, 0x1C);
    state_arg = state;
    FIELD(arg0, StatePair, 0x18) = *state;
    func_8040787C(FIELD(arg0, s32, 0x24), state_arg, changed);
    func_8003FA78(&D_80400854, D_804090F8[state->first]);
    func_8003FA78(&D_80400860, D_804090F8[state->second]);
    func_804018FC();

function_return:
    return;
}
