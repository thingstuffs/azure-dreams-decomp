#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Unk99108;

extern s32 D_80097D2C[3];
extern s32 D_800D04A4[];
extern s32 D_800D04B8[];

extern void func_80096918(Unk99108 *, s32, s32, s32 *);
extern void func_80096924(Unk99108 *, s32, s32, s32 *);

/* Dispatch to the matching or fallback handler using sentinel-terminated key lists. */
void func_80096868(Unk99108 *entry, s32 forwarded_a, s32 forwarded_b, s32 *match_cursor)
{
    s32 *key_cursor;
    s32 entry_key;

    key_cursor = D_800D04A4;
    if (*key_cursor != 0) {
        do {
            entry_key = entry->unk0;
            if (entry_key == *key_cursor) {
                if (entry_key == (s32)D_80097D2C) {
                    match_cursor = D_800D04B8;
                    if (*match_cursor != 0) {
                        do {
                            if (entry->unk4 != *match_cursor++) {
                                continue;
                            }
found:
                            func_80096924(entry, forwarded_a, forwarded_b, match_cursor);
                            return;
                        } while (*match_cursor != 0);
                    }
                } else {
                    goto found;
                }
            }
            key_cursor++;
        } while (*key_cursor != 0);
    }
    func_80096918(entry, forwarded_a, forwarded_b, match_cursor);
}
