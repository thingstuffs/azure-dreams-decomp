#include "common.h"


extern volatile s32 D_801379A8;
extern volatile s32 D_801379B0;

extern s32 func_80058FF0(s32 value, s32 direction, s32 amount);
extern void func_80063FF8(s32 sound);
extern s32 func_804016D0(void);
extern void func_804018FC(void);
extern void func_804067BC(void *object);
extern void func_80406CFC(void *object);
extern void func_804070C4(void *object);
extern void func_804083FC(s32 field20, s32 field24);


typedef struct S_80406DA0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
} S_80406DA0_0;   /* object in func_80406DA0 */

void func_80406DA0(void *object)
{
    s32 input;
    s32 flags;
    s32 direction;
    s32 index;
    s32 held_input;

    input = D_801379A8;
    direction = 0;
    if (input != 0) {
        object = (u8 *)object + 1;
        object = (u8 *)object - 1;
        flags = D_801379B0;
        if (flags & 0x40) {
            func_80063FF8(0x515);
            goto forced_tail;
        }
        if (flags & 0x20) {
            func_80063FF8(0x514);
            func_80406CFC(object);
            goto direction_check;
        }
        if (!(input & 0x5000)) {
            goto direction_check;
        }
        if (!(flags & 0x5000)) {
            goto held_counter;
        }
        (*(s32 *)((u8 *)object + (0x30))) = 0;
        flags = D_801379B0;
        if (flags & 0x1000) {
            direction = -1;
            goto direction_check;
        }
        if (flags & 0x4000) {
            direction = 1;
        }
        goto direction_check;

held_counter:
        index = ((S_80406DA0_0 *)object)->unk_30;
        if (index < 13) {
            goto store_next;
        }
        (*(s32 *)((u8 *)object + (0x30))) = index - 4;
        held_input = D_801379A8;
        if (held_input & 0x1000) {
            direction = -1;
            goto direction_check;
        }
        if (held_input & 0x4000) {
            direction = 1;
        }
        goto direction_check;

store_next:
        ((S_80406DA0_0 *)object)->unk_30 = index + 1;

direction_check:
        if (direction != 0) {
            func_80063FF8(0x502);
            ((S_80406DA0_0 *)object)->unk_2C =
                func_80058FF0(((S_80406DA0_0 *)object)->unk_2C, direction, 5);
            func_804067BC(object);
        }
    }

    direction = func_804016D0();
    func_804018FC();
    if (direction == 0) {
        return;
    }
    if (direction == 1) {
        return;
    }

forced_tail:
    func_804070C4((u8 *)object - 0x20);
    func_804083FC(((S_80406DA0_0 *)object)->unk_20, ((S_80406DA0_0 *)object)->unk_24);
}
