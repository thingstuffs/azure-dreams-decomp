#include "common.h"
#include "dungeon/actor.h"
#include "records/Rec_func_8008D024_arg0.h"


extern void *familiar_record_slots[];
extern u8 D_800E0B18[16];
extern u8 D_800E0B2B[16];
extern u8 D_800E202D[16];

extern s16 find_entity_slot_by_field_ac(void *target_value);
extern s32 find_entity_slot_by_field_e4(void *target_value);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(const u8 *source, u8 *buffer);
extern u8 *clear_byte_and_advance(u8 *byte_ptr);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_800E05E1[];
extern u8 D_800E05F0[];


typedef struct S_800956B8_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800956B8_0;   /* arg3 in resolve_familiar_deployment_request */

typedef struct S_800956B8_1_pre {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x10];
} S_800956B8_1_pre;   /* the 0x18 bytes before object in resolve_familiar_deployment_request, addressed as object[-1] */

typedef struct S_800956B8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_800956B8_1;   /* object in resolve_familiar_deployment_request */

typedef struct S_800956B8_2 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800956B8_2;   /* (u8 *)arg0 + index * 4 in resolve_familiar_deployment_request */


typedef struct S_800956B8_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_800956B8_4;   /* st in resolve_familiar_deployment_request */

/* Reports unavailable familiar requests or resets the selected action state and saves the familiar
   selection. */
void resolve_familiar_deployment_request(void *context_ptr, s32 unused_one, void *unused_two, void *selection_ptr)
{
    void *object;
    s32 index;
    void *tail_result;
    s16 result;
    s32 value;

    object = familiar_record_slots[((S_800956B8_0 *)selection_ptr)->unk_03 & 0x1F];
    if (!(((S_800956B8_1 *)object)->unk_1C & 0x20000)) {
        result = find_entity_slot_by_field_ac(object);
                /* Retail callee sets a3 = 10 at 0x80099114 before reading it; no incoming argument. */
        context_ptr = get_unused_text_buffer();
        {
            u8 *msg3;
            if (result >= 0) {
                u8 *msg;
                value = expand_text_control_codes(D_800E0B18, (s32)context_ptr);
                if (result != 0) {

                    msg = D_800E05F0;
                } else {

                    msg = D_800E05E1;
                }
                tail_result = expand_text_control_codes(msg, value);
                msg3 = D_800E0B2B;
                value = tail_result - 3;
                value = expand_text_control_codes(msg3, value);
            } else {
                msg3 = D_800E202D;

                value = (s32)context_ptr;
                value = expand_text_control_codes(msg3, value);
            }
            clear_byte_and_advance(value);
        }
        display_text_with_fullwidth_adjustment((s32)context_ptr);
        return;
    }

    index = (s16)find_entity_slot_by_field_e4(object);
    if (index >= 0) {
        object = ((S_800956B8_2 *)((u8 *)context_ptr + index * 4))->unk_AC;
        if (((S_800956B8_1 *)object)->unk_14 & 0x20000000) {
            ((S_800956B8_1 *)object)->unk_1C |= 0x10000;
            begin_actor_flagged_action(object, ((S_800956B8_1_pre *)object)[-1].unk_00,
                          ((S_800956B8_1_pre *)object)[-1].unk_04, object);
            return;
        }
    }

    index = find_entity_slot_by_field_ac(object);
    {
        S_800956B8_4 *st;

        if (index >= 0) {
            void *tail_selected;
            tail_selected = ((S_800956B8_2 *)((u8 *)context_ptr + index * 4))->unk_AC;
            st = tail_selected;
            st->unk_9A = 2;
        } else {
            st = ((Rec_func_8008D024_arg0 *)context_ptr)->unk_60;
            st->unk_9A = 2;
        }
        st->unk_9B = 0;
        st->unk_8C = 0;
        ((Rec_func_8008D024_arg0 *)context_ptr)->unk_110 = selection_ptr;
    }
}

/* MECHANISM: frame is 4 saves (s2,ra,s1,s0 at 0x18/0x1c/0x14/0x10) with arg3->s2
   and arg0->s1. Retail leaves both expand_text_control_codes call delay slots empty. */
