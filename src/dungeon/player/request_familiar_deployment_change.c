#include "dungeon/item/message.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "dungeon/player.h"

typedef struct S_80094270_3 {
    u8 pad_00[0xFA];
    u8 unk_FA;
} S_80094270_3;   /* (actor + (s16) slot) in request_familiar_deployment_change */

typedef struct S_80094270_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80094270_4;   /* entry in request_familiar_deployment_change */

   /* ((S_80094270_4 *)entry)->unk_AC in request_familiar_deployment_change */

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *familiar_record_slots[];
s16 check_familiar_deployment_placement(); /* extern */
void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */                          /* extern */
void display_formatted_context_message(void *context);                   /* extern */
s32 play_sound_if_enabled(s32 query_value);                     /* extern */
s32 display_text_with_fullwidth_adjustment(s8 *text);                         /* extern */
extern u8 D_800E05E1[15];
extern u8 D_800E05F0[16];
extern u8 D_800E0633[];
extern u8 D_800E0726[19];
extern u8 D_800E0739[14];
extern u8 D_800E0747[31];
extern u8 D_800E0766[3];
extern u8 D_800E0769[19];
extern u8 D_800E077C[14];
extern u8 D_800E078A[54];

   /* entry in request_familiar_deployment_change */

typedef struct S_80094270_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80094270_2;   /* item in request_familiar_deployment_change */

/* Use or equip the item in the given slot: build the result message for the outcome, or fall through to the failure path. */
s32 request_familiar_deployment_change(void *actor, s32 param_a, void *param_b, S_80094270_2 *item, s32 slot) {
    s16 out_a;
    s16 out_b;
    s16 kind;
    void *text;
    u8 bits;
    void *msg;
    void *call_result;
    FamiliarItemSlotView *entry;
    void *hdr;
    void *hdr3;

    ((Rec_func_8008ACDC_arg0 *)actor)->unk_8A = (s16) slot;
    if (reject_forbidden_familiar_recall(0) == 0) {
        if (((S_80094270_3 *)((actor + (s16) slot)))->unk_FA == 2) {
            display_formatted_context_message(&D_800E0633);
            return 1;
        }
        entry = (void *) ((((Rec_func_8008ACDC_arg0 *)actor)->unk_8A * 4) + (u32) actor);
        if (entry->item_address == item) {
            if (!(((ActorRecord *)(((S_80094270_4 *)entry)->unk_AC))->flags1C & 0x20000)) {
                /* Format the selected outcome, then terminate the message. */
                msg = get_unused_text_buffer();
                text = expand_text_control_codes(D_800E0726, msg);
                if (((Rec_func_8008ACDC_arg0 *)actor)->unk_8A != 0) {
                    hdr = D_800E05F0;
                } else {
                    hdr = D_800E05E1;
                }
                text = expand_text_control_codes(hdr, text);
                call_result = expand_text_control_codes(D_800E0739, text - 3);
                clear_byte_and_advance(call_result);
                goto finish;
            } else {
                clear_player_linked_action_flags();
                reference_tile_object.selected_item = 0;
                begin_familiar_deployment_change(actor, param_a, param_b, 0, 0);
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_60 = 0;
            }
        } else {
            kind = check_familiar_deployment_placement(actor, param_a, param_b, &out_a, &out_b, item);
            hdr3 = actor;
            if (kind != 0) {
                msg = get_unused_text_buffer();
                if (kind == 1) {
                    kind = item->unk_03 & 0x1F;
                    text = expand_text_control_codes(D_800E0747, msg);
                    text = write_text_byte_and_advance(0xA, text);
                    call_result = append_entity_display_text(familiar_record_slots[kind], text);
                    text = expand_text_control_codes(D_800E0766, call_result);
                } else if (kind == 2) {
                    text = expand_text_control_codes(D_800E0769, msg);
                    if ((s16)slot != 0)
                        hdr = D_800E05F0;
                    else
                        hdr = D_800E05E1;
                    text = expand_text_control_codes(hdr, text);
                    text = expand_text_control_codes(D_800E077C, text - 3);
                } else {
                    bits = item->unk_03 & 0x1F;
                    call_result = append_entity_display_text(familiar_record_slots[bits], msg);
                    text = expand_text_control_codes(D_800E078A, call_result);
                }

                /* The three outcomes share the termination and display tail. */
                clear_byte_and_advance(text);
finish:
                display_text_with_fullwidth_adjustment(msg);
                play_sound_if_enabled(0x506);
                return 1;
            }
            ((Rec_func_8008ACDC_arg0 *)hdr3)->unk_C8 = 0;
            reference_tile_object.selected_item = (s32) item;
            begin_familiar_deployment_change(actor, param_a, param_b, out_a, (s32) out_b);
            clear_player_linked_action_flags();
        }
        return 0;
    }
    return 1;
}
