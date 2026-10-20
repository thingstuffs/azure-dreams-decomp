#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *func_800373DC(s32);
extern void func_8003BC18();
extern void func_8006E8B8();
extern void func_8023FA58();

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

/* Build the town HUD: the frame object, its three child slots, the gauge sprite and the five icons. */
void create_town_hud(void) {
    void *object;
    s8 *parent;
    s8 *slot;
    s8 *primitive;
    s32 i;
    s32 case_value;
    s16 rect[4];
    u8 *common_value;
    u8 *child_handler;

    parent = NULL;
    object = func_800373DC(0x32);
    common_value = D_80526704;
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
    i = 2;
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
        /* Codegen-matching initializer (owner trade 10-12, cleanup candidate): at 2.6.3 only a NON-constant
         * initializer emits the CLOBBER that makes rgb a global allocno; the value is overwritten below. */
        union { s32 v; } rgb = { i };

        func_8003BC18(object, D_8003D588);
        primitive = *(s8 **)((s8 *)object + 8);
        {
            union { s8 *v; } state = { *(s8 **)((s8 *)object + 0xC) };

            *(u8 **)((s8 *)object + 0x10) = D_8052DE94;
            *(s8 **)((s8 *)object + 0x20) = parent;
            *(s16 *)(state.v + 0x1C) = 0x1000;
            *(s16 *)(state.v + 0x1E) = 0x1000;
            *(s16 *)(state.v + 0x20) = 0x1000;
            *(s32 *)(state.v + 8) = 0x2B;
            *(s16 *)(state.v + 0x12) = 0;
            *(s16 *)(state.v + 0x14) = 0;
            *(s16 *)(state.v + 0x10) = 0;
            *(s16 *)(state.v + 0x16) = 0;
            *(s16 *)(state.v + 0x18) = 0;
            *(s16 *)(state.v + 0x1A) = 0;
            *(s32 *)(state.v + 0) = 0;
            *(u8 *)(state.v + 4) = 0;
            *(u8 *)(state.v + 5) = 0;
            rgb.v = 0x00808080;
            *(s32 *)(state.v + 0xC) = rgb.v;
            *(s32 *)(primitive + 0) = 0x04400000;
            *(s32 *)(primitive + 4) = 0x02C00000;
            *(s32 *)(primitive + 8) = 0;
            *(u8 **)((s8 *)object + 0x70) = common_value;
            func_8023FA58((s8 *)object + 0x28,
                          *(s8 **)((s8 *)object + 8), D_80530184, primitive);
        }
    }

    do {
        object = func_800373DC(0x100);
        if (object != NULL) {
            func_8003BC18(object, D_8052E1E0);
            *(s8 **)((s8 *)object + 0x20) = parent;
            *(u8 **)((s8 *)object + 0x10) = D_8052DF68;
            *(s16 *)((s8 *)object + 0x42) = (s16)i;
            object = (s8 *)object + 0x20;
            switch (i) {
            case 0:
                case_value = 1;
                *(s16 *)((s8 *)object + 0x20) = (s16)case_value;
                break;
            case 1:
            case 2:
                case_value = 2;
                *(s16 *)((s8 *)object + 0x20) = (s16)case_value;
                break;
            case 3:
            case 4:
                case_value = 3;
                *(s16 *)((s8 *)object + 0x20) = (s16)case_value;
                break;
            default:
                break;
            }
            i--;
        } else {
            i--;
        }
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
