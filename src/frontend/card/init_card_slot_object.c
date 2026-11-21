#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/slot_assert_bytes.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"





extern s32 func_804075D0(void *object, s32 value);
extern u32 func_80407688(void *object, s32 option);
extern void assert_card_slot_and_set_high_bit(void *card_slot);


typedef struct S_800206C8_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800206C8_0;   /* base in func_800206C8 */

typedef struct S_800206C8_1 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    struct CardDevSlotEntry **entry_table;
} S_800206C8_1;   /* slot_state in func_800206C8 */

/* Initializes the memory card slot object and its working state. */
void *init_card_slot_object(s32 init_option)
{
    S_800206C8_0 *base;
    S_800206C8_1 *slot_state;

    base = (S_800206C8_0 *)D_8040C318;
    slot_state = NODE_BODY(D_8040C318);
    if (func_80047FD8(base) == 0) {
        base = func_8003C714(0, base, 0x42);
        if (base == 0) {
            printf_8007C040(card_slot_assert_format, card_slot_filename, 0x136);
            exit_8007BEF0(1);
        }
        func_80040560(base, card_dev_render_panel_hierarchy);
    } else {
        assert_card_slot_and_set_high_bit(base);
        D_8040C336 &= 0x7FFF;
        bzero_8007BFE0(slot_state, 0xE4);
    }
    func_804075D0(slot_state, 4);
    base->unk_0C = (s32)(unsigned long)((u8 *)slot_state + 0x50);
    slot_state->unk_5C = card_dev_bind_slot_rows_template(slot_state->entry_table);
    func_80407688(slot_state, init_option);
    base->unk_10 = (s32)(unsigned long)card_dev_advance_slot_stream_pair;
    return base;
}
