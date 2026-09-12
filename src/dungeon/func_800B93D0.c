#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800BEB30_0 {
    u8 pad_00[0x4C];
    u8 * unk_4C;
    u8 pad_50[0xC0];
    u8 * unk_110;
    s32 unk_114;
} S_800BEB30_0;   /* global in func_800BEB30 */


typedef struct S_800BEB30_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BEB30_2;   /* decrement_base in func_800BEB30 */



extern s32 func_8008D344();
extern s32 func_8008D368();
extern s32 func_80098864();
extern s32 func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099368();
extern s32 func_8009955C();
extern s32 func_800997FC();
extern s32 func_800998C0();
extern s32 func_80099978();
extern s32 func_800A5720();
extern s32 func_800A5F38();
extern s32 func_800A6480();
extern s32 func_800AD6FC();

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern u8 D_80089364[];
extern u8 D_80089368[];
extern u8 D_800DD148[];
extern u16 D_800DDE84[];
extern u8 D_800E110B[];
extern u8 D_800E112A[];
extern u8 D_800E1156[];
extern u8 D_800E116E[];
extern u8 *D_800E3D7C[];

/* Applies an action to a target or held item and updates the action counter. */
s32 func_800BEB30(u32 target, u8 *action, s16 action_kind, s32 context) {
    u8 *state;
    u8 *item;
    s32 action_value;
    register s32 value;
    u32 choice_index;
    s32 call_context = context;
    s32 value_arg;
    register u8 *data_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *counter_base;
    s32 result_value;
    u8 item_type;

    if (action_kind == 0xD) {
        return func_80098864(action, call_context);
    }

    state = D_800E3D7C[0];
    if (target == (u32)state) {
        ((S_800BEB30_0 *)state)->unk_110 = action;
        func_8008D344(state, D_80083780, D_80082E80, state);
        action[3] &= (u8)~0x20;
        return 0;
    }

    if (target <= 0x9FFFFFFF) {
        func_800A6480(target, action, action_kind);
        if (func_800AD6FC(target, D_800DDE84[((Rec_D_800E3D7C *)target)->unk_10.at03_u8.v] & 3, 0) == 0) {
            func_800A5F38(target, action);
            return 1;
        }
        goto decrement;
    }

    item = ((S_800BEB30_0 *)state)->unk_4C;
    if (item != 0) {
        if (!(action[3] & 0x20)) {
            ((S_800BEB30_0 *)state)->unk_114 = 0x202080;
            func_8008D368(state, D_80083780, D_80082E80, D_800DD148, 2);
            action[3] |= 0x20;
            return 0;
        }

        action_value = func_800990FC(state, call_context, action_kind);
        value = action_value;
        item_type = item[1];
        if (item_type != 0xF) {
            data_arg = item;
            if (item_type != 0x10) {
                goto other;
            }
            if (item[0] != 2) {
                goto other;
            }
        }
        {
            if (!(item[3] & 0x40)) {
                value = func_8009955C(item, action_value);
                if ((s8)item[2] < 0x63) {
                    item[2] = (u8)(item[2] + 1);
                }
                value = func_80099978(func_80099194(D_800E110B, value));
                choice_index = value - 2;
                value = func_80099194(D_80089364, value);
                result_value = func_80099368(item, value);
                value_arg = value;
                value = result_value;
                func_800998C0(choice_index, value_arg);
                data_arg = D_80089368;
                value_arg = value;
                goto message;
            }
            result_value = func_80099368(item, action_value);
            data_arg = D_800E112A;
            goto result;
        }

other:
        value_arg = value;
        result_value = func_80099368(data_arg, value_arg);
        data_arg = D_800E1156;
result:
        value_arg = result_value;
message:
        value = func_80099194(data_arg, value_arg);
        func_80099290(value);
        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800A5720(action_value);
        goto decrement;
    }

    func_800997FC(D_800E116E, call_context, action_kind);

decrement:
    counter_base = (u8 *)&D_80083460;
    ((S_800BEB30_2 *)counter_base)->unk_0A--;
    func_80098B38(action);
    return 1;
}
