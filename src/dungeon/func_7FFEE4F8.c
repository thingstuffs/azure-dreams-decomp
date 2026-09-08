#include "common.h"

typedef struct S_8008BC58_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    s16 unk_66;
    void * unk_68;
    u8 pad_6C[0x8];
    union { s32 s; volatile s32 u; } unk_74;   /* accessed as both */
    s32 unk_78;
    u8 * unk_7C;
} S_8008BC58_0;   /* object in func_8008BC58 */

typedef struct S_8008BC58_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8008BC58_1;   /* input in func_8008BC58 */

typedef struct S_8008BC58_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BC58_2;   /* arg1 in func_8008BC58 */

typedef struct S_8008BC58_3 {
    u8 pad_00[0x30];
    s32 unk_30;
    s32 unk_34;
} S_8008BC58_3;   /* record in func_8008BC58 */



extern void func_80035208();
extern void func_800478B8();
extern void func_8008B620();

extern u8 D_80072210[];
extern u8 D_80072214[];
extern s32 D_80082ABC;
extern u8 D_80083160[];
extern u8 D_80083780[];
extern u8 D_8008BED8[];
extern u8 D_800D2EA4[];
extern u8 D_800FC418;

/* Handles input, selection changes, and display positioning for the current state. */
void func_8008BC58(u8 *object, S_8008BC58_2 *view_params, void *update_context)
{
    u8 *input = D_80083160;
    u8 *selection_ids = ((S_8008BC58_0 *)object)->unk_7C;
    u8 *display_record;
    s16 state;

    if (D_800FC418 != 0) {
        ((S_8008BC58_0 *)object)->unk_68 = D_8008BED8;
        goto done;
    }

    state = ((S_8008BC58_0 *)object)->unk_66;
    if (state == 0) {
        u16 input_delay;
        s32 buttons;

        input_delay = ((S_8008BC58_0 *)object)->unk_64 - 1;
        ((S_8008BC58_0 *)object)->unk_64 = input_delay;
        if ((input_delay << 16) <= 0) {
            ((S_8008BC58_0 *)object)->unk_64 = 0;
            if (((S_8008BC58_1 *)input)->unk_10 & 0x10000000) {
                view_params->unk_0A += 0x10;
            }
            if (((S_8008BC58_1 *)input)->unk_10 & 0x40000000) {
                view_params->unk_0A -= 0x10;
            }
            buttons = ((S_8008BC58_1 *)input)->unk_10;
            if (buttons & 0x40) {
                D_800FC418 = 1;
                func_80035208(D_80072214);
                goto done;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                func_80035208(D_80072210);
                goto done;
            }
        } else {
            goto done;
        }
    } else if (state == 9) {
        s16 *fixed_position;
        s32 x;
        s32 y;

        func_800478B8(update_context);
        fixed_position = (s16 *)D_80083780;
        display_record = *(u8 **)object;
        x = fixed_position[1] / 64 - 0x18;
        ((S_8008BC58_3 *)display_record)->unk_30 = x;
        display_record = *(u8 **)object;
        y = fixed_position[3] / 64 - 0x40;
        ((S_8008BC58_3 *)display_record)->unk_34 = y;
        goto done;
    } else if (state == 10) {
        register s32 selection_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        u8 selection_id;
        register u8 *selection_positions ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 buttons;

        func_800478B8(update_context);
        buttons = ((S_8008BC58_1 *)input)->unk_10;
        if (buttons & 0x6000) {
            selection_index = ((S_8008BC58_0 *)object)->unk_74.s + 1;
            ((S_8008BC58_0 *)object)->unk_74.s = selection_index;
            if (selection_index >= ((S_8008BC58_0 *)object)->unk_78) {
                ((S_8008BC58_0 *)object)->unk_74.s = 0;
            }
        } else if (buttons & 0x9000) {
            selection_index = ((S_8008BC58_0 *)object)->unk_74.s - 1;
            ((S_8008BC58_0 *)object)->unk_74.s = selection_index;
            if (selection_index < 0) {
                selection_index = ((S_8008BC58_0 *)object)->unk_78 - 1;
                ((S_8008BC58_0 *)object)->unk_74.s = selection_index;
            }
        } else {
            goto update;
        }

        func_8008B620(selection_ids[((S_8008BC58_0 *)object)->unk_74.u]);

update:
        selection_index = ((S_8008BC58_0 *)object)->unk_74.s;
        selection_positions = D_800D2EA4;
        selection_id = selection_ids[selection_index];
        display_record = *(u8 **)object;
        ((S_8008BC58_3 *)display_record)->unk_30 = selection_positions[selection_id * 8] - 0x18;

        selection_index = ((S_8008BC58_0 *)object)->unk_74.s;
        selection_id = selection_ids[selection_index];
        display_record = *(u8 **)object;
        ((S_8008BC58_3 *)display_record)->unk_34 = selection_positions[selection_id * 8 + 1] - 0x40;

        selection_index = ((S_8008BC58_0 *)object)->unk_74.s;
        selection_id = selection_ids[selection_index];
        D_80082ABC = selection_id;
    }

done:
    return;
}
