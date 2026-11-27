#include "frontend/card.h"
#include "frontend/card/message.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "shared/object_node.h"
#include "frontend/card/message_display.h"
#include "frontend/libcard.h"

s32 forward_target(MenuDisplayNode **entries);
void func_80402EBC(CardDevDialogDisplay *, struct ObjectNodeHeader *, s32, s32, s32 *);
/* The initializer branch loads the dialog root into a1 before this call. */
s32 process_global();

typedef struct S_8001BF84_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8001BF84_0;   /* root in func_8001BF84 */

/* Initializes or retrieves the memory card message object. */
u8 *init_card_message_object(struct ObjectNodeHeader *message_param_1, s32 message_param_2, s32 message_param_3, s32 *result_slot)
{
    s32 result;
    CardDevDialogDisplay *store_base;
    u8 *root = card_message_object;
    CardDevDialogDisplay *child = NODE_BODY(card_message_object);

    if (func_80047FD8(root) == 0) {
        root = func_8003C714(0, root, 0x1E1);
        if (root == 0) {
            printf_8007C040(card_message_assert_format, card_message_assert_filename, 0x299);
            exit_8007BEF0(1);
        }
        func_80040560(root, card_dev_render_panel_hierarchy);
    } else {
        process_global(*(s32 *)0x80409534 != 2, root);
        D_80409526 &= 0x7FFF;
        bzero_8007BFE0(child, 0x764);
    }

    init_menu_entry_pointers(child, 6);
    ((S_8001BF84_0 *)root)->unk_0C = (s32)&child->template_node;
    result = forward_target(child->entries);
    store_base = child;
    store_base->template_node.unk_0C = result;
    func_80402EBC(store_base, message_param_1, message_param_2, message_param_3, result_slot);
    ((S_8001BF84_0 *)root)->unk_10 = (s32)D_80402F04;
    return root;
}
