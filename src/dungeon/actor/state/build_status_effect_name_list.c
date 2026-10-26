#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item/message.h"
extern u8 status_name_separator[12];
extern u8 D_800251E8[9];
extern u8 D_80025024[];
extern u8 D_800250B8[];
extern u8 D_800250D8[];
extern u8 D_800250F4[];
extern u8 D_80025110[];
extern u8 D_8002512C[];
extern u8 D_80025154[];
extern u8 D_80025184[];
extern u8 D_800251B4[];
extern u8 D_80025208[];
extern u8 D_8002522C[];
extern u8 D_80025244[];
extern u8 D_80025260[];
extern u8 D_80025284[];
extern u8 D_800252A4[];
extern u8 D_800252C8[];
extern u8 D_800252E4[];
extern u8 D_80025300[];
extern u8 D_80025318[];
extern u8 D_80025160[];
/* Build the status-effect name list for the object's 0x54 flag word, comma-separated; returns the fallback when no flag is set. */
void *build_status_effect_name_list(void *obj, void *fallback)
{
    void *text;
    s32 count;
    void *result;
    void *saved_fallback;
    count = 0;
    saved_fallback = fallback;
    text = expand_text_control_codes(D_800250B8, fallback);
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 1) {
        text = expand_text_control_codes(D_800250D8, write_text_byte_and_advance(0xA, text));
        count = 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 2) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_800250F4, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 4) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025110, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 8) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_8002512C, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025154, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x20) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025160, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x80) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025184, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x100) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_800251B4, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x8000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_800251E8, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x100000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025208, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_8002522C, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x02000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025244, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x04000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025260, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x08000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025284, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_800252A4, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x20000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_800252C8, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x40000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_800252E4, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x200000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025300, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x4000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(D_80025318, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((count << 0x10) != 0) {
        result = expand_text_control_codes(D_80025024, text);
    }
    else {
        result = saved_fallback;
    }
    return result;
}
