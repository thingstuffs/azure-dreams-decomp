#include "frontend/card/choice_panel.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/slot_assert_bytes.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"





/* Initializes the memory card slot object and its working state. */
ObjectNodeHeader *init_card_slot_object(ObjectNodeHeader *owner)
{
    ObjectNodeHeader *base;
    CardDevSlotMenu *slot_state;

    base = (ObjectNodeHeader *)D_8040C318;
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
    card_dev_init_slot_entry_tables(slot_state, 4);
    base->sprite = (struct SpriteFrameState *)&slot_state->frame;
    slot_state->frame.unk_0C = card_dev_bind_slot_rows_template(slot_state->entry_table);
    func_80407688(slot_state, owner);
    base->update_callback = card_dev_advance_slot_stream_pair;
    return base;
}
