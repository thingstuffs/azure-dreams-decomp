#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *func_800373DC(s32);
extern void func_8003BC18();
extern void func_8006E8B8();
extern void func_8023FA58();
extern void func_8052C7C0(void) __attribute__((noreturn));

extern u8 D_8003D588[];
extern u8 D_80526704[];
extern u8 D_8052C854[];
extern u8 D_8052D4B8[];
extern u8 D_8052DE94[];
extern u8 D_8052DF68[];
extern u8 D_8052E1E0[];
extern u8 D_80530154[];
extern u8 D_80530184[];
extern u8 D_805305B8[];
extern u8 D_805305F8[];
#ifndef NON_MATCHING
extern void *D_8052671C[];
#endif

void func_808119EC(void) {
    void *object;
    s8 *parent;
    register s8 *slot ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 *primitive;
    register s8 *state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 i;
    s32 case_value;
    s16 rect[4];
    u8 *common_value;
    u8 *child_handler;
#ifndef NON_MATCHING
    static void *const keepalive[3] = {
        &&case_0, &&case_1_2, &&case_3_4
    };
#endif

    parent = NULL;
    object = func_800373DC(0x32);
    common_value = D_80526704;
    i = 2;
    if (object != NULL) {
        parent = (s8 *)object + 0x20;
        primitive = *(s8 **)((s8 *)object + 8);
        *(u8 **)((s8 *)object + 0x10) = D_8052C854;
        *(s32 *)(primitive + 0) = 0x04600000;
        *(s32 *)(primitive + 4) = 0x03600000;
        *(u8 **)((s8 *)object + 0x68) = common_value;
        func_8023FA58(parent, primitive, D_80530154, primitive);
    }

    child_handler = D_8052D4B8;
    slot = parent + 8;
    do {
        object = func_800373DC(2);
        *(void **)(slot + 0x4C) = object;
        if (object != NULL) {
            *(u8 **)((s8 *)object + 0x10) = child_handler;
            *(s16 *)((s8 *)object + 0x28) = (s16)i;
            *(s8 **)((s8 *)object + 0x20) = parent;
        }
        i--;
        slot -= 4;
    } while (i >= 0);

    object = func_800373DC(0x136);
    i = 4;
    if (object != NULL) {
        func_8003BC18(object, D_8003D588);
        primitive = *(s8 **)((s8 *)object + 8);
        state = *(s8 **)((s8 *)object + 0xC);
        *(u8 **)((s8 *)object + 0x10) = D_8052DE94;
        *(s8 **)((s8 *)object + 0x20) = parent;
        *(s16 *)(state + 0x1C) = 0x1000;
        *(s16 *)(state + 0x1E) = 0x1000;
        *(s16 *)(state + 0x20) = 0x1000;
        *(s32 *)(state + 8) = 0x2B;
        *(s16 *)(state + 0x12) = 0;
        *(s16 *)(state + 0x14) = 0;
        *(s16 *)(state + 0x10) = 0;
        *(s16 *)(state + 0x16) = 0;
        *(s16 *)(state + 0x18) = 0;
        *(s16 *)(state + 0x1A) = 0;
        *(s32 *)(state + 0) = 0;
        *(u8 *)(state + 4) = 0;
        *(u8 *)(state + 5) = 0;
        *(s32 *)(state + 0xC) = 0x00808080;
        *(s32 *)(primitive + 0) = 0x04400000;
        *(s32 *)(primitive + 4) = 0x02C00000;
        *(s32 *)(primitive + 8) = 0;
        *(u8 **)((s8 *)object + 0x70) = common_value;
        func_8023FA58((s8 *)object + 0x28,
                      *(s8 **)((s8 *)object + 8), D_80530184, primitive);
    }

    slot = (s8 *)D_8052671C;
    do {
        object = func_800373DC(0x100);
        if (object != NULL) {
            func_8003BC18(object, D_8052E1E0);
            *(s8 **)((s8 *)object + 0x20) = parent;
            *(u8 **)((s8 *)object + 0x10) = D_8052DF68;
            *(s16 *)((s8 *)object + 0x42) = (s16)i;
            object = (s8 *)object + 0x20;
#ifndef NON_MATCHING
            if ((u32)i >= 5) {
                goto switch_done;
            }
            goto **(void **)slot;
case_0:
            case_value = 1;
            ASM_TAILSLOT_PIN_TIED(case_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8052C7C0();
case_1_2:
            case_value = 2;
            ASM_TAILSLOT_PIN_TIED(case_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8052C7C0();
case_3_4:
            case_value = 3;
            *(s16 *)((s8 *)object + 0x20) = (s16)case_value;
switch_done:
#else
            switch (i) {
            case 0:
                *(s16 *)((s8 *)object + 0x20) = 1;
                break;
            case 1:
            case 2:
                *(s16 *)((s8 *)object + 0x20) = 2;
                break;
            case 3:
            case 4:
                *(s16 *)((s8 *)object + 0x20) = 3;
                break;
            }
#endif
        }
        i--;
        slot -= 4;
    } while (i >= 0);
    rect[0] = 0x40;
    rect[1] = 0x1D0;
    rect[2] = 0x20;
    rect[3] = 1;
    func_8006E8B8(rect, D_805305B8);
    rect[0] = 0xC0;
    rect[1] = 0x1F8;
    rect[2] = 0x30;
    rect[3] = 1;
    func_8006E8B8(rect, D_805305F8);
}
/* MECHANISM: Preserve the seed's exact 0x38 frame, saved-register roles, and computed-goto layout.
   Cases 0/1 pin constants in $v0 and call the zero-argument noreturn shared target.
   ASM_TAILSLOT_PIN_TIED lets LEAD 28b sink each li into the converted j delay slot. */
