#include "common.h"


typedef struct Node {
    void *field0;
    struct Node *field4;
    u16 field8;
    s16 fieldA;
} Node;

#include "modules/main_server_ship_interfaces.h"
extern void format_unsigned_double_byte_decimal(s32 value, void *out);
extern void decode_note_text(void *entries, void *text, s32 initial_octave);
extern void strcat(void *dest, void *src);
extern void strcpy(void *dest, void *src);
extern void *D_800283B8[];
extern u8 D_800283C4[];
extern void *D_800283EC[];
extern void *D_800283F4[];
extern u8 D_800283FC[];


typedef struct S_80024818_0 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80024818_0;   /* root in card_boot_format_empty_slot_guidance */

typedef struct S_80024818_1 {
    u8 pad_00[0xB4C];
    Node * unk_B4C;
} S_80024818_1;   /* cursor in card_boot_format_empty_slot_guidance */

/* Builds status text and assigns it to two or three display nodes. */
void card_boot_format_empty_slot_guidance(void *context)
{
    u8 text_buf[0x40];
    u8 number_buf[0x10];
    s32 mode_one;
    s32 state;
    s32 below_three;
    s32 selection;
    s32 node_count;
    void *first_buffer;
    void *text_buffer;
    s32 text;

    selection = ((S_80024818_0 *)context)->unk_80;
    mode_one = selection == 1;
    state = card_boot_get_remaining_block_summary();
    if (mode_one != 0 && card_boot_count_cached_slots() == 0) {
        decode_note_text(context + 0x84, D_800283EC[0], 1);
        text_buffer = context + 0x204;
        text = (s32)D_800283EC[1];
        decode_note_text(text_buffer, (void *)text, 1);
        node_count = 2;
    } else {
        below_three = state < 3;
        first_buffer = context + 0x84;
        if (below_three != 0) {
            void **table;
            void *text_buffer;
            s32 selection;

            decode_note_text(first_buffer, D_800283C4, 1);
            text_buffer = context + 0x204;
            table = D_800283B8;
            selection = mode_one << 2;
            decode_note_text(text_buffer, *(void **)((u8 *)table + selection), 1);
            decode_note_text(context + 0x384, table[2], 1);
            node_count = 3;
        } else {
            {
                void **table;
                s32 selection;

                table = D_800283F4;
                selection = mode_one << 2;
                decode_note_text(first_buffer, *(void **)((u8 *)table + selection), 1);
            }
            format_unsigned_double_byte_decimal(state / 3, number_buf);
            strcpy(text_buf, number_buf);
            strcat(text_buf, D_800283FC);
            text_buffer = context + 0x204;
            text = (s32)text_buf;
            decode_note_text(text_buffer, (void *)text, 1);
            node_count = 2;
        }
    }
    {
        register s32 buffer_offset;
        register s16 node_value;
        register u8 *cursor;
        s32 node_kind;

        text = 0;
        if (node_count != 0) {
            node_kind = 0xA9;
            node_value = 0x110;
            buffer_offset = 0x84;
            cursor = context;
            do {
                Node *node;

                node = ((S_80024818_1 *)cursor)->unk_B4C;
                node->field0 = context + buffer_offset;
                node->field4->field8 = node_kind;
                node->field4->fieldA = node_value;
                buffer_offset += 0x180;
                cursor += 4;
                text += 1;
                node_value += 0x10;
            } while (text < node_count);
        }
    }
}
