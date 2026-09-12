#include "common.h"

extern void func_80035208();
extern void func_800478B8();
extern void func_8008B620();

extern u8 D_80072210[];
extern u8 D_80072214[];
extern s32 D_80082ABC;
extern u8 D_80083160[];
extern u8 D_80083780[];
extern u8 D_8008BED8[];
extern u8 D_800FC418;
extern u8 D_800D2EA4;

/* Handle input and update the object display position for its current state. */
void func_8008BC58(u8 *object, void *transform, void *context) {
    u8 *input = D_80083160;
    u8 *entries = *(u8 **)(object + 0x7C);
    s16 state;
    register void *context_copy ASM_REG("$4"); /* MATCH: retain retail's unused a2-to-a0 move in the entry branch delay slot. */

    context_copy = context;
    if (D_800FC418 != 0) {
        ASM_USE2_NV(context_copy, context);
        *(void **)(object + 0x68) = D_8008BED8;
        return;
    }

    state = *(s16 *)(object + 0x66);
    if (state == 0) {
        u16 timer = *(u16 *)(object + 0x64) - 1;

        *(u16 *)(object + 0x64) = timer;
        if ((timer << 16) <= 0) {
            s32 buttons;

            *(u16 *)(object + 0x64) = 0;
            if (*(s32 *)(input + 0x10) & 0x10000000) {
                *(u16 *)((u8 *)transform + 0xA) += 0x10;
            }
            if (*(s32 *)(input + 0x10) & 0x40000000) {
                *(u16 *)((u8 *)transform + 0xA) -= 0x10;
            }

            buttons = *(s32 *)(input + 0x10);
            if (buttons & 0x40) {
                D_800FC418 = 1;
                func_80035208(D_80072214);
                return;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                func_80035208(D_80072210, transform);
                return;
            }
        }
    } else if (state == 9) {
        s16 *position;

        func_800478B8();
        position = (s16 *)D_80083780;
        *(s32 *)(*(u8 **)object + 0x30) = position[1] / 64 - 0x18;
        *(s32 *)(*(u8 **)object + 0x34) = position[3] / 64 - 0x40;
        return;
    } else if (state == 10) {
        s32 buttons;
        s32 entry_index;
        u8 entry_id;
        u8 *positions;

        func_800478B8();
        buttons = *(s32 *)(input + 0x10);
        if (buttons & 0x6000) {
            if (++*(s32 *)(object + 0x74) >= *(s32 *)(object + 0x78)) {
                *(s32 *)(object + 0x74) = 0;
            }
        } else if (buttons & 0x9000) {
            if (--*(s32 *)(object + 0x74) < 0) {
                *(s32 *)(object + 0x74) = *(s32 *)(object + 0x78) - 1;
            }
        } else {
            goto update_position;
        }
        func_8008B620(entries[*(s32 *)(object + 0x74)]);
    update_position:
        entry_index = *(s32 *)(object + 0x74);
           /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        positions = (u8 *)&D_800D2EA4;
        entry_id = entries[entry_index];
        *(s32 *)(*(u8 **)object + 0x30) = positions[entry_id * 8] - 0x18;

        entry_index = *(s32 *)(object + 0x74);
        entry_id = entries[entry_index];
        *(s32 *)(*(u8 **)object + 0x34) = positions[entry_id * 8 + 1] - 0x40;

        entry_index = *(s32 *)(object + 0x74);
        D_80082ABC = entries[entry_index];
    }
}
