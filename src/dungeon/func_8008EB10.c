#include "common.h"
#include "shared/tile_object.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_80094270_3 {
    u8 pad_00[0xFA];
    u8 unk_FA;
} S_80094270_3;   /* (actor + (s16) slot) in request_familiar_deployment_change */

typedef struct S_80094270_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80094270_4;   /* entry in request_familiar_deployment_change */

typedef struct S_80094270_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80094270_5;   /* ((S_80094270_4 *)entry)->unk_AC in request_familiar_deployment_change */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800E3DF0[];
s16 check_familiar_deployment_placement(); /* extern */
s32 reject_forbidden_familiar_recall();                         /* extern */
void clear_player_linked_action_flags();                      /* extern */
s32 get_unused_text_buffer();                          /* extern */
s32 expand_text_control_codes();                  /* extern */
void * func_80099290();                    /* extern */
s32 write_text_byte_and_advance();                    /* extern */
s32 append_entity_display_text();                        /* extern */
void display_formatted_context_message();                   /* extern */
s32 play_sound_if_enabled();                     /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E0633;
extern M2C_UNK D_800E0726;
extern M2C_UNK D_800E0739;
extern M2C_UNK D_800E0747;
extern M2C_UNK D_800E0766;
extern M2C_UNK D_800E0769;
extern M2C_UNK D_800E077C;
extern M2C_UNK D_800E078A;


typedef struct S_80094270_1 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094270_1;   /* entry in request_familiar_deployment_change */

typedef struct S_80094270_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80094270_2;   /* item in request_familiar_deployment_change */

/* Use or equip the item in the given slot: build the result message for the outcome, or fall through to the failure path. */
s32 request_familiar_deployment_change(void *actor, s32 param_a, void *param_b, S_80094270_2 *item, s32 slot) {
    s16 out_a;
    s16 out_b;
    s16 kind;
    s32 text;
    u8 bits;
    s32 msg;
    s32 call_result;
    S_80094270_1 *entry;
    void *hdr;
    void *hdr3;

    ((Rec_func_8008ACDC_arg0 *)actor)->unk_8A = (s16) slot;
    if (reject_forbidden_familiar_recall(0) == 0) {
        if (((S_80094270_3 *)((actor + (s16) slot)))->unk_FA == 2) {
            display_formatted_context_message(&D_800E0633);
            return 1;
        }
        entry = (void *) ((((Rec_func_8008ACDC_arg0 *)actor)->unk_8A * 4) + (u32) actor);
        if (entry->unk_D0 == item) {
            if (!(((S_80094270_5 *)(((S_80094270_4 *)entry)->unk_AC))->unk_1C & 0x20000)) {
                /* Format the selected outcome, then terminate the message. */
                msg = get_unused_text_buffer();
                text = expand_text_control_codes(&D_800E0726, msg);
                if (((Rec_func_8008ACDC_arg0 *)actor)->unk_8A != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                text = expand_text_control_codes(hdr, text);
                call_result = expand_text_control_codes(&D_800E0739, text - 3);
                func_80099290(call_result);
                goto finish;
            } else {
                clear_player_linked_action_flags();
                D_80082E80.unk_030 = 0;
                begin_familiar_deployment_change(actor, param_a, param_b, 0, 0);
                ((Rec_func_8008ACDC_arg0 *)actor)->unk_60 = 0;
            }
        } else {
            kind = check_familiar_deployment_placement(actor, param_a, param_b, &out_a, &out_b, item);
            hdr3 = (void *)((s32) actor);
            if (kind != 0) {
                msg = get_unused_text_buffer();
                if (kind == 1) {
                    kind = item->unk_03 & 0x1F;
                    text = expand_text_control_codes(&D_800E0747, msg);
                    text = write_text_byte_and_advance(0xA, text);
                    call_result = append_entity_display_text(D_800E3DF0[kind], text);
                    text = expand_text_control_codes(&D_800E0766, call_result);
                } else if (kind == 2) {
                    text = expand_text_control_codes(&D_800E0769, msg);
                    if ((s16)slot != 0)
                        hdr = &D_800E05F0;
                    else
                        hdr = &D_800E05E1;
                    text = expand_text_control_codes(hdr, text);
                    text = expand_text_control_codes(&D_800E077C, text - 3);
                } else {
                    bits = item->unk_03 & 0x1F;
                    call_result = append_entity_display_text(D_800E3DF0[bits], msg);
                    text = expand_text_control_codes(&D_800E078A, call_result);
                }

                /* The three outcomes share the termination and display tail. */
                func_80099290(text);
finish:
                display_text_with_fullwidth_adjustment(msg);
                play_sound_if_enabled(0x506);
                return 1;
            }
            ((Rec_func_8008ACDC_arg0 *)hdr3)->unk_C8 = 0;
            D_80082E80.unk_030 = (s32) item;
            begin_familiar_deployment_change(actor, param_a, param_b, out_a, (s32) out_b);
            clear_player_linked_action_flags();
        }
        return 0;
    }
    return 1;
}
