#include "common.h"

typedef struct {
    u8 pad[0xBBC];
    s16 values[1];
} InputTable;

typedef struct {
    s32 words[12];
    s32 flags;
} State;

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern InputTable D_80700000;
extern State *D_80701968[3];
extern CallbackOwner *D_80701984[4];

extern s32 func_80700D84(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80701060(s32 *word, s32 old_value);

s32 func_80874F4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 old_value;
    s32 shift;
    s32 *word;

    if (func_80700D84(arg0, arg1, arg2, arg3) >= 2) {
        old_value = D_80700000.values[arg0];
        word = &D_80701968[0]->words[old_value / 32];
        shift = old_value % 32;
        old_value = *word;
        *word = (1 << shift) | old_value;
        return func_80701060(word, old_value);
    }
    if (D_80701984[0]->callback(2) != 0) {
        D_80701968[0]->flags |= 0x40000000;
    } else {
        D_80701968[0]->flags &= ~0x40000000;
    }
    return arg0;
}
