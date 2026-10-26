#include "shared/item_ids.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "dungeon/item.h"
#include "engine/town.h"
#include "dungeon/item/message.h"

typedef struct { u8 unk0; u8 unk1; s8 unk2; u8 unk3; } FuncData;
extern u8 * copy_selected_text_without_terminator();
extern u8 *D_800DD720;
extern u8 *item_type_text_prefixes[];
extern u8 *item_type_text_suffixes[];

/* Appends formatted data with type-specific affixes and a numeric value to the buffer. */
u8 *append_typed_formatted_value(FuncData *data, u8 *buffer) {
    u8 *prefix_id;
    u8 *suffix_id;
    s32 value;
    u8 prefix_kind;
    u8 suffix_kind;
    u8 kind;
    u8 *unused_cursor;
    u8 *format;
    u8 *value_end;
    u8 *out;

    out = buffer;
    if (!(dungeon_actor_ring_anchor->flags1C & ACTOR_BLIND)) {
        prefix_kind = data->unk1;
        prefix_id = item_type_text_prefixes[prefix_kind];
        if ((prefix_id != 0) && ((prefix_kind != ITEM_KIND_SWORD) || (data->unk0 < 0xEU))) {
            out = expand_text_control_codes(prefix_id, out);
        }
    }
    out = copy_selected_text_without_terminator(data, out);
    if (!(dungeon_actor_ring_anchor->flags1C & ACTOR_BLIND)) {
        suffix_kind = data->unk1;
        suffix_id = item_type_text_suffixes[suffix_kind];
        if ((suffix_id != 0) && ((suffix_kind != ITEM_KIND_SWORD) || (data->unk0 < 0xEU))) {
            out = expand_text_control_codes(suffix_id, out);
        }
        kind = data->unk1;
        switch (kind) {
        case ITEM_KIND_BALL:
            if (!(data->unk3 & 0x80)) {
                format = D_800DD720;
                value = data->unk2;
                *out++ = *format++;
                *out = *format++;
                value_end = format_unsigned_double_byte_decimal(value, out + 1);
                out = value_end;
                *out++ = *format++;
                *out++ = *format++;
            }
            break;
        case ITEM_KIND_COIN:
        case ITEM_KIND_EGG:
        case ITEM_KIND_FAMILIAR:
        case ITEM_KIND_TRAP:
            break;
        default:
            if (!(data->unk3 & 0x80)) {
                value = data->unk2;
                if (value != 0) {
                    out = append_signed_value_bytes(value, out);
                    if (value < 0)
                        value = -value;
                    out = format_unsigned_double_byte_decimal(value, out);
                }
            }
            break;
        }
    }
    return out;
}
