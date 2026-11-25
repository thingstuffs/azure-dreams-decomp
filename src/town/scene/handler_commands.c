/* Handler state and command requests
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/ll34_5db800_80016000:80018340, PD:town/ll34_5db800_80016000:800183D0.
 * PD:town/ll34_5db800_80016000:80018340
 * PD:town/ll34_5db800_80016000:800183D0
 */
#include "town/scene.h"

/* Private declarations retained from the member sources. */
/* Handler state and command requests */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/ll34_5db800_80016000:80018340, PD:town/ll34_5db800_80016000:800183D0. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/data.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

typedef struct S_func_8065C34C_1 {
    u8 pad_00[0x50];
    s32 (*unk_50)(PackedWord *);
} S_func_8065C34C_1;

extern PackedWord D_80016020;

/* Set the state to 9 and cache the callback result using a copy of the global arguments. */
void request_handler_state_9(void) {
    extern s32 D_800183D0;
    PackedWord callback_args;
    Rec_D_80016000 *context;
    S_func_8065C34C_1 *callback_table;

    callback_args = D_80016020;
    context = town_scene_root;
    callback_table = context->services;
    D_800183D0 = 9;
    scene_command_result = callback_table->unk_50(&callback_args);
}

/* Submit the global value and command 0x17, and save the callback result. */
void request_handler_command_17(void) {
    extern s32 D_800183D0;
    s8 command_args[2];
    void *state_word = &D_800183D0;
    u8 *state_byte = state_word;

    command_args[1] = 0x17;
    command_args[0] = *state_byte;
    scene_command_result = town_scene_root->services->get_item_buy_money(command_args);
}
