#include "common.h"

typedef struct S_80027584_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_80027584_0_pre;   /* the 0x10 bytes before arg0 in card_boot_format_card_with_retry, addressed as arg0[-1] */

typedef struct S_80027584_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x1C];
    void * unk_2C;
    u8 pad_30[0x8];
    s32 unk_38;
} S_80027584_0;   /* arg0 in card_boot_format_card_with_retry */


extern void card_boot_recheck_selected_channel(void);
extern s32 card_boot_format_card_and_wait(s32 card_slot);
extern void card_boot_show_no_memory_card_notice(void *context);
extern void card_boot_show_format_failure_notice(void *value);
extern void card_boot_show_format_success_notice(void *input_value);
extern u8 D_800274A8[];
extern u8 D_800274D8[];
extern u8 D_8002789C[];

/* Polls status with bounded retries and dispatches the corresponding context update. */
void card_boot_format_card_with_retry(void *state) {
    s32 retry_status;
    s32 status;
    s32 retry_count;
    void *context;

    retry_count = 0;
    retry_status = 5;
    do {
        status = card_boot_format_card_and_wait(((S_80027584_0 *)state)->unk_0C);
        if (status != retry_status) {
            break;
        }
    } while (retry_count++ < 6);

    ((S_80027584_0 *)state)->unk_38 = 0;
    card_boot_recheck_selected_channel();
    if (status == 1) {
        context = (u8 *)state - 0x20;
        ((S_80027584_0 *)state)->unk_2C = D_8002789C;
        card_boot_show_format_success_notice(context);
        ((S_80027584_0_pre *)state)[-1].unk_00 = D_800274D8;
    } else if (status == 4) {
        context = (u8 *)state - 0x20;
        ((S_80027584_0 *)state)->unk_2C = D_8002789C;
        card_boot_show_no_memory_card_notice(context);
        ((S_80027584_0_pre *)state)[-1].unk_00 = D_800274A8;
    } else {
        context = (u8 *)state - 0x20;
        ((S_80027584_0 *)state)->unk_2C = D_8002789C;
        card_boot_show_format_failure_notice(context);
        ((S_80027584_0_pre *)state)[-1].unk_00 = D_800274D8;
    }
}
