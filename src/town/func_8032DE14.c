#include "common.h"

typedef struct Copy4 {
    u8 bytes[4];
} Copy4;

extern void append_shop_entry(const Copy4 *);
extern s32 get_free_shop_slot_count(void);
extern void set_script_flag_bit(s32);
extern s32 get_script_flag_mask(s32);
extern Copy4 D_8001BE5C;
extern s32 D_8001EACC;
extern s32 D_8001EBCA;

/* Select the response and set flag 0xD80 when its prerequisite passes. */
s32 *select_response_and_set_d_80(void) {
    if (get_script_flag_mask(0xD80) == 0) {
        if (get_free_shop_slot_count() != 0) {
            set_script_flag_bit(0xD80);
            append_shop_entry(&D_8001BE5C);
            return &D_8001EACC;
        }
    }
    return &D_8001EBCA;
}
