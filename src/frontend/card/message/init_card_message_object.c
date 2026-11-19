#include "frontend/card/message.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "shared/object_node.h"
#include "frontend/card/message_display.h"

s32 forward_target(MenuDisplayNode **entries);
void init_menu_entry_pointers(CardDevDialogDisplay *, s32);
void func_80402EBC(CardDevDialogDisplay *, struct ObjectNodeHeader *, s32, s32, s32);
s32 process_global(s32, u8 *);

typedef struct S_8001BF84_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8001BF84_0;   /* root in func_8001BF84 */

/* Initializes or retrieves the memory card message object. */
u8 *init_card_message_object(struct ObjectNodeHeader *message_param_1, s32 message_param_2, s32 message_param_3, s32 message_param_4)
{
    s32 result;
    CardDevDialogDisplay *store_base;
    u8 *root = card_message_object;
    CardDevDialogDisplay *child = NODE_BODY(card_message_object);

    if (func_80047FD8(root) == 0) {
        root = func_8003C714(0, root, 0x1E1);
        if (root == 0) {
            func_8007C040(D_80400548, D_80400570, 0x299);
            func_8007BEF0(1);
        }
        func_80040560((s32)root, card_status_query_address);
    } else {
        process_global(*(s32 *)0x80409534 != 2, root);
        D_80409526 &= 0x7FFF;
        func_8007BFE0(child, 0x764);
    }

    init_menu_entry_pointers(child, 6);
    ((S_8001BF84_0 *)root)->unk_0C = (s32)&child->template_node;
    result = forward_target(child->entries);
    store_base = child;
    store_base->template_node.unk_0C = result;
    func_80402EBC(store_base, message_param_1, message_param_2, message_param_3, message_param_4);
    ((S_8001BF84_0 *)root)->unk_10 = (s32)D_80402F04;
    return root;
}
