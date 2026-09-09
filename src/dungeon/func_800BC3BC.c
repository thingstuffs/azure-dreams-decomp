#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern s32 D_80082EB0[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E14D8[];
extern u8 D_800E14EB[];
extern u8 D_800E1514[];
extern u8 *D_800E3D7C;

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_800992E8(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);



typedef struct S_800C1B1C_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800C1B1C_1;   /* base in func_800C1B1C */

typedef struct S_800C1B1C_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    union { s8 s; u8 u; } unk_02;   /* accessed as both */
} S_800C1B1C_2;   /* ((S_800C1B1C_1 *)base)->unk_04 in func_800C1B1C */

/* Apply a target action or update the current item and display its result message. */
s32 func_800C1B1C(Rec_D_800E3D7C *target, s32 action, s16 action_type, s32 action_arg)
{
    s32 *item_state;
    s32 message;
    s32 message_end;

    if (action_type == 13) {
        return func_80098864(action, action_arg);
    }

    if (target == D_800E3D7C) {
        target->unk_110 = action;
        func_8008D344(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, action, action_type);
        if (func_800AD6FC(
                target, D_800DDE84[target->unk_10.at03_u8.v] & 3, 0) == 0) {
            func_800A5F38(target, action);
            return 1;
        }
    } else {
        message = func_800990FC();
        item_state = D_80082EB0;
        if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_01 == 4) {
            message_end = func_80099194(
                D_800E14EB,
                func_800992E8(
                    ((S_800C1B1C_1 *)item_state)->unk_04,
                    func_80099194(D_800E14D8, message)));
            func_800A56E0(0x80F);
            if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_02.s < 99) {
                ((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_02.u++;
            }
        } else {
            message_end = func_80099194(D_800E1514, message);
        }
        func_80099290(message_end);
        func_800A5720(message);
    }

    D_80083460.field_A--;
    func_80098B38(action);
    return 1;
}
