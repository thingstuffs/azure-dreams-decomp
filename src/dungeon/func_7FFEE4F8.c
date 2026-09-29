#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

typedef struct S_8008BC58_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    s16 unk_66;
    void * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
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
extern u8 D_8008BED8[];
extern u8 D_800D2EA4[];
extern u8 D_800FC418;

/* Handles input, selection changes, and display positioning for the current state. */
void func_8008BC58(u8 *object, S_8008BC58_2 *view_params, void *update_context)
{
    GameWork *input = &gameWork;
    u8 *selection_ids = ((S_8008BC58_0 *)object)->unk_7C;
    u8 *display_record;
    s16 state;

    if (D_800FC418 != 0) {
        ((S_8008BC58_0 *)object)->unk_68 = D_8008BED8;
        return;
    }

    state = ((S_8008BC58_0 *)object)->unk_66;
    if (state == 0) {
        u16 input_delay;
        s32 buttons;

        input_delay = ((S_8008BC58_0 *)object)->unk_64 - 1;
        ((S_8008BC58_0 *)object)->unk_64 = input_delay;
        if ((input_delay << 16) <= 0) {
            ((S_8008BC58_0 *)object)->unk_64 = 0;
            if (((s32)input->unk_010) & 0x10000000) {
                view_params->unk_0A += 0x10;
            }
            if (((s32)input->unk_010) & 0x40000000) {
                view_params->unk_0A -= 0x10;
            }
            buttons = ((s32)input->unk_010);
            if (buttons & 0x40) {
                D_800FC418 = 1;
                func_80035208(D_80072214);
                return;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                func_80035208(D_80072210);
                return;
            }
        } else {
            return;
        }
    } else if (state == 9) {
        s32 x;
        s32 y;

        func_800478B8(update_context);
        display_record = *(u8 **)object;
        x = D_80083780.x.w.i / 64 - 0x18;
        ((S_8008BC58_3 *)display_record)->unk_30 = x;
        display_record = *(u8 **)object;
        y = D_80083780.y.w.i / 64 - 0x40;
        ((S_8008BC58_3 *)display_record)->unk_34 = y;
        return;
    } else if (state == 10) {
        s32 selection_index;
        s32 selection_index_2;
        s32 selection_index_3;
        s32 selection_index_4;
        s32 selection_index_5;
        s32 selection_index_6;
        u8 selection_id;
        u8 *selection_positions;
        s32 buttons;

        func_800478B8(update_context);
        buttons = ((s32)input->unk_010);
        if (buttons & 0x6000) {
            selection_index = ((S_8008BC58_0 *)object)->unk_74 + 1;
            ((S_8008BC58_0 *)object)->unk_74 = selection_index;
            if (selection_index >= ((S_8008BC58_0 *)object)->unk_78) {
                ((S_8008BC58_0 *)object)->unk_74 = 0;
            }
            func_8008B620(selection_ids[((S_8008BC58_0 *)object)->unk_74]);
        } else if (buttons & 0x9000) {
            selection_index_2 = ((S_8008BC58_0 *)object)->unk_74 - 1;
            ((S_8008BC58_0 *)object)->unk_74 = selection_index_2;
            if (selection_index_2 < 0) {
                selection_index_3 = ((S_8008BC58_0 *)object)->unk_78 - 1;
                ((S_8008BC58_0 *)object)->unk_74 = selection_index_3;
            }
            func_8008B620(selection_ids[((S_8008BC58_0 *)object)->unk_74]);
        }

        selection_index_4 = ((S_8008BC58_0 *)object)->unk_74;
        selection_positions = D_800D2EA4;
        selection_id = selection_ids[selection_index_4];
        ((S_8008BC58_3 *)(*(u8 **)object))->unk_30 = selection_positions[selection_id * 8] - 0x18;

        selection_index_5 = ((S_8008BC58_0 *)object)->unk_74;
        selection_id = selection_ids[selection_index_5];
        display_record = *(u8 **)object;
        ((S_8008BC58_3 *)display_record)->unk_34 = selection_positions[selection_id * 8 + 1] - 0x40;

        selection_index_6 = ((S_8008BC58_0 *)object)->unk_74;
        selection_id = selection_ids[selection_index_6];
        D_80082ABC = selection_id;
    }

    return;
}
