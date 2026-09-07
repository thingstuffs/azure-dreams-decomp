#include "common.h"

typedef struct S_800C8150_0 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x3C];
    u32 unk_54;
} S_800C8150_0;   /* arg0 in func_800C8150 */

typedef struct S_800C8150_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8150_1;   /* entry in func_800C8150 */

typedef struct S_800C8150_2 {
    u8 pad_00[0x54];
    u32 unk_54;
} S_800C8150_2;   /* object in func_800C8150 */



typedef struct TablePage {
    u8 pad[0x2098];
    s16 entries[1];
} TablePage;

extern void func_80099844(void *, void *);
extern s16 func_800A1BD0(void *);
extern s16 func_800C8900();

extern u8 D_800E18F5[];
extern u8 D_800E195C[];
extern u8 *D_800E3D7C;

/* Checks status flags, advances eligible actor state, or performs the requested action. */
u32 func_800C8150(S_800C8150_0 *actor, s16 action_arg_1, s16 action_arg_2, s32 status_mask)
{
    s32 slot;
    u8 *slot_entry;
    void *message_target;
    u8 *message;
    S_800C8150_2 *linked_object;
    s32 state_index;
    s32 raw_state_index;
    s32 state_offset;
    s32 state;
    s32 next_state;
    register s32 shifted_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register TablePage *table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    slot = 1;
    if (actor->unk_14 & 0x4000) {
        u8 *object_page;

        object_page = (u8 *)0x800E0000;
        slot_entry = *(u8 **)(object_page + 0x3D7C) + 4;
        status_mask = 0x40000;
loop:
        linked_object = ((S_800C8150_1 *)slot_entry)->unk_AC;
        if ((linked_object != 0) && (linked_object->unk_54 & status_mask)) {
            goto marked_move;
        }
        slot--;
        slot_entry -= 4;
        if (slot >= 0) {
            goto loop;
        }
        goto common;
    } else if (actor->unk_54 & 0x40000) {
        message_target = actor;
        goto marked_ready;
    }

common:
    if (actor->unk_14 & 0x4000) {
        state = actor->unk_12;
        if ((state != 4) && (actor->unk_13 != 0)) {
            actor->unk_12 = state + 1;
            raw_state_index = func_800A1BD0(actor);
            shifted_index = raw_state_index << 16;
            state_index = shifted_index >> 16;
            table_page = (TablePage *)0x80010000;
            if (state_index >= 0) {
                state_offset = state_index * 2;
                next_state = actor->unk_12;
                table_page->entries[state_index] = next_state;
            }
            func_80099844(actor, D_800E195C);
            return 1;
        }
        func_800C8900(actor, action_arg_1, action_arg_2);
        return 1;
    }

    goto unmarked;

marked_move:
    message_target = actor;
marked_ready:
    message = D_800E18F5;
    func_80099844(message_target, message);
    return 0;

unmarked:
    return (u32)~func_800C8900(actor, action_arg_1, action_arg_2) >> 31;
}
