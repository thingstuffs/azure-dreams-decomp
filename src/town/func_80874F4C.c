#include "common.h"

#ifdef NON_MATCHING
#define ({                                                                       register s32 zero ASM_REG("$0");                                    zero | (value);                                                      }) (value)
#else
#endif

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

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
#ifndef NON_MATCHING
    s32 value;
    s32 index;
    s32 old_value;
#else
    s16 value;
    s32 index;
    s32 old_value;
    s32 zero = 0;
#endif
    s32 shift;
    s32 offset;
    s32 *word;
    s32 callback;
#ifndef NON_MATCHING
    s32 tail_arg;
#else
    s32 tail_arg;
#endif

    if (func_80700D84(arg0, arg1, arg2, arg3) < 2) {
        goto callback_path;
    }

    old_value = D_80700000.values[arg0];
    value = old_value;
    index = value;
    if (value < 0) {
        index = value + 31;
    }
    index >>= 5;
    offset = index * 4;
    word = (s32 *)(offset + (s32)D_80701968[0]);
    shift = value - (index << 5);
    old_value = *word;
    *word = ((1) << shift) | old_value;
    return func_80701060(word, old_value);

callback_path:
    callback = D_80701984[0]->callback(2);
    tail_arg = 0x40000000;
    if (callback == 0) {
        goto clear_flags;
    }

    {
#ifndef NON_MATCHING
        void *state;
        register s32 new_flags ASM_REG("$3");   /* still load-bearing after the honest return join */
#else
        void *state;
        s32 new_flags;
#endif
        state = (void *)D_80701968[0];
        new_flags = FIELD(state, s32 *, 0x30) | tail_arg;
        FIELD(state, s32 *, 0x30) = new_flags;
    }
    goto return_arg;

clear_flags:
    {
#ifndef NON_MATCHING
        void *state;
        s32 clear_mask;
        s32 clear_value;
#else
        void *state;
        s32 clear_mask;
        s32 clear_value;
#endif
        state = (void *)D_80701968[0];
        clear_mask = 0xBFFFFFFF;
        clear_value = FIELD(state, s32 *, 0x30);
        clear_value &= clear_mask;
        FIELD(state, s32 *, 0x30) = clear_value;
    }
return_arg:
    return arg0;
}
