#include "common.h"

typedef struct S_800BF478_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800BF478_0;   /* arg0 in func_800BF478 */



typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1258[];
extern s32 D_800E296C;
extern u8 *D_800E3D7C;

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *, s32, s16);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);

/* Handles item use on a target and consumes the item when the action completes. */
s32 func_800BF478(S_800BF478_0 *target, s32 item, s16 use_type, s32 use_context)
{
    if (use_type == 13) {
        return func_80098864(item, use_context);
    }

    if (target == D_800E3D7C) {
        target->unk_110 = item;
        func_8008D344(target, D_80083780, D_80082E80, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, item, use_type);
        if (func_800AD6FC(target,
                         D_800DDE84[target->unk_13] & 3,
                         item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    } else {
        func_800997FC(D_800E1258, use_context, use_type);
        D_800E296C |= 0x800;
    }

    D_80083460.field_A--;
    func_80098B38(item);
    return 1;
}
