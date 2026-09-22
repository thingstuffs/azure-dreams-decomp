#include "common.h"

#ifdef NON_MATCHING
#define ({                                                                       register s32 zero ASM_REG("$0");                                   ASM_KEEP(zero);                                                      zero | (value);                                                      }) (value)
#else
#endif


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
extern CallbackOwner *D_80701984_ALT[4] __asm__("D_80701984");

#define STATE_ROOT D_80701968[0]

extern s32 func_80700D84(void);
extern s32 func_80701060(s32 *word, s32 old_value);
extern s32 func_807018AC(s16 value);

/* Record the pressed input, or toggle the 0x40000000 state flag from the callback's answer and advance the slot. */
s32 func_80700E18(s32 slot) {
    s32 callback;
#ifndef NON_MATCHING
    s32 tail_arg;
#else
    s32 tail_arg;
#endif

    if (func_80700D84() > 0) {
        s16 value;
        s32 input_offset;
        s32 index;
        s32 *word;
        s32 old_value;
#ifndef NON_MATCHING
#else
        s32 zero_nf = 0;
#endif

        input_offset = slot * 2;
        value = *(s16 *)((u8 *)&D_80700000 + 0xBBC + input_offset);
        index = value / 32;
        word = (s32 *)(index * 4 + (s32)STATE_ROOT);
        old_value = *word;
        *word = ((1) << (value - (index << 5))) | old_value;
        return func_80701060(word, old_value);
    }

callback_path:
    callback = D_80701984[0]->callback(2);
    tail_arg = 0x40000000;
    if (callback != 0) {
        {
#ifndef NON_MATCHING
            void *state;
            register s32 new_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
            void *state;
            s32 new_flags;
#endif
            state = (void *)STATE_ROOT;
            new_flags = ((State *)state)->flags | tail_arg;
            ((State *)state)->flags = new_flags;
        }
    } else {
#ifndef NON_MATCHING
        void *state;
        s32 clear_mask;
        s32 clear_value;
#else
        void *state;
        s32 clear_mask;
        s32 clear_value;
#endif
        state = (void *)STATE_ROOT;
        clear_mask = 0xBFFFFFFF;
        clear_value = ((State *)state)->flags;
        clear_value &= clear_mask;
        ((State *)state)->flags = clear_value;
    }
    if (func_807018AC(D_80700BB2[0]) != 0) {
        goto zero_return;
    }

    callback = D_80701984_ALT[0]->callback(2);
    if (callback == 0) {
        goto return_arg;
    }
    slot += 1;
    goto return_arg;

zero_return:
    slot = 0;

return_arg:
    return slot;
}
