#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct S_800C4030_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C4030_1;   /* state in func_800C4030 */


extern s32 func_8004A658(s32, s32);
extern void func_8008D344(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099368(s32, s32);
extern s32 func_80099734(void *record, u8 *out);
extern s32 func_800999B0(s32);
extern void func_8009BF7C(s32 flag, s8 value);
extern void func_800A56E0(s32);
extern void func_800A5720(s8 *text);
extern void func_800A5F38(void *, s32);
extern s8 func_800A6DA4(s32, s32);
extern s32 func_800AD6FC(void *, s32, s32);

extern u8 D_800893DC[];
extern u8 D_800E187C[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

/* Handles a target or active-slot update and decrements the shared count on completion. */
s32 func_800C4030(EntityRec *target, s32 action, s16 action_type, s32 action_param)
{
    s32 result;
    s32 slot_index;
    u8 *slot_data;
    u8 *slot_state;
    u8 *table_base;
    u8 *table_base_2;
    s32 first_arg;
    s32 second_arg;
    s32 second_arg_2;
    s32 scratch_value;
    s32 saved_context;

    if (action_type == 0xD) {
        return func_80098864(action, action_param);
    }

    if (target == D_800E3D7C) {
        target->unk_110 = action;
        func_8008D344(target, &D_80083780.x.v, &D_80082E80.unk_000, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        result = func_800990FC();
        first_arg = action;
        second_arg_2 = result;
        saved_context = second_arg_2;
        result = func_80099368(first_arg, second_arg_2);
        result = func_80099194(D_800E187C, result);
        result = func_80099734(target, result);
        result = func_80099194(D_800893DC, result);
        result = func_800999B0(result);
        func_80099290(result);
        func_800A5720(saved_context);

        table_base = (u8 *)0x800E0000;
        scratch_value = (*(u8 *)((u8 *)&target->unk_10 + 3));
        table_base_2 = (u8 *)D_800DDE84;
        second_arg = ((u16 *)table_base_2)[scratch_value];
        first_arg = second_arg & 3;
        if (func_800AD6FC(target, first_arg, action) == 0) {
            func_800A5F38(target, action);
            return 1;
        }
        table_base = (u8 *)0x80080000;
    } else {
        func_8009BF7C(1, 8);
        func_800A56E0(0x80F);
        slot_index = 0;
        slot_data = D_800E36C8;
        slot_state = D_800E3548;
    loop:
        if (slot_state[1] != 0) {
            slot_state[1] = 0xE;
            slot_state[0] = 3;
            *(s32 *)(slot_data + 8) = func_8004A658(0xE, 3);
            slot_state[2] = func_800A6DA4(0x10, 0x18);
            slot_state[3] = 1;
        }
        slot_data += 0xC;
        slot_index++;
        slot_state += 4;
        if (slot_index < 0x40) goto loop;
        table_base = (u8 *)0x80080000;
    }
    table_base += 0x3460;
    result = ((S_800C4030_1 *)table_base)->unk_0A;
    first_arg = action;
    result--;
    ((S_800C4030_1 *)table_base)->unk_0A = result;
    func_80098B38(first_arg);
    return 1;

}

