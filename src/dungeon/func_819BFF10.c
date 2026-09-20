#include "common.h"

typedef struct S_func_819BFF10_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_func_819BFF10_0;

typedef struct S_func_819BFF10_1 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_func_819BFF10_1;

typedef struct S_func_819BFF10_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_func_819BFF10_2;

typedef struct S_func_819BFF10_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_func_819BFF10_3;

extern s32 func_80024AE8();

/* Mark and process entries at the given coordinates with thresholds in the specified range. */
void func_80025710(void *list_head, s32 x, s32 y, s16 upper_bound, s32 lower_bound) {
    s32 match_x = x;
    s32 match_y = y;
    s32 upper_limit;
    s32 lower_limit;
    s16 threshold;
    u16 flags;
    S_func_819BFF10_2 *range_data;
    S_func_819BFF10_3 *position_data;
    S_func_819BFF10_0 *entry;
    S_func_819BFF10_1 *list_link;
    void *head;

    list_link = list_head;
    head = list_link;
    list_head = list_link->unk_5C;
    list_link = list_head + 0x20;
    list_head = list_link;
    if (list_link != head) {
        upper_limit = (s16)upper_bound;
        lower_limit = (s16)lower_bound;
        entry = (void *)list_head - 0x20;
        do {
            void *next_entry;
            position_data = ((S_func_819BFF10_0 *)((u8 *)list_link - 0x20))->unk_0C;
            range_data = entry->unk_08;
            if ((position_data->unk_24 == (match_x & 0xFFFF)) &&
                (position_data->unk_25 == (match_y & 0xFFFF))) {
                threshold = range_data->unk_0A;
                if ((upper_limit >= threshold) && (lower_limit < threshold)) {
                    flags = entry->unk_1E;
                    if (!(flags & 0x2000)) {
                        entry->unk_1E = flags | 0x2000;
                        func_80024AE8(entry, range_data, position_data);
                    }
                }
                next_entry = list_link->unk_5C;
                list_link = next_entry + 0x20;
            } else {
                next_entry = list_link->unk_5C;
                list_link = next_entry + 0x20;
            }
            entry = (void *)list_link - 0x20;
        } while (list_link != head);
    }
}
