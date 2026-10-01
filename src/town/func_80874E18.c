#include "common.h"

typedef struct {
    u8 pad[0xBBC];
    s16 values[1];
} InputTable;

typedef struct {
    u8 pad[0x30];
    s32 flags;
} State;

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern InputTable D_80700000;
extern s16 D_80700BB2[];
extern State *D_80701968[3];
extern CallbackOwner *D_80701984[4];

#define STATE_ROOT D_80701968[0]

extern s32 func_80700D84(void);
extern s32 func_80701060(s32 *word, s32 old_value);
extern s32 func_807018AC(s16 value);

/* Record the pressed input, or toggle the 0x40000000 state flag from the callback's answer and advance the slot. */
s32 func_80700E18(s32 slot) {
    s32 callback;

    if (func_80700D84() > 0) {
        s16 value;
        s32 *word;
        s32 old_value;

        value = D_80700000.values[slot];
        word = &((s32 *)STATE_ROOT)[value / 32];
        old_value = *word;
        *word = (1 << (value % 32)) | old_value;
        return func_80701060(word, old_value);
    }

    if (D_80701984[0]->callback(2) != 0) {
        STATE_ROOT->flags |= 0x40000000;
    } else {
        STATE_ROOT->flags &= ~0x40000000;
    }
    if (func_807018AC(D_80700BB2[0]) == 0) {
        callback = D_80701984[0]->callback(2);
        if (callback == 0) {
            return slot;
        }
        slot += 1;
    } else {
        slot = 0;
    }
    return slot;
}
