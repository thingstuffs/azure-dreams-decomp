#include "common.h"

extern s32 D_8001601C;
extern u8 D_80017774[];
extern s32 D_80017FD4[];
extern s32 D_80017FF4[];
extern u8 *D_8001E950;

s32 func_8001B148(s32 arg0, s32 arg1, s32 arg2)
{
    u8 *state;
    s32 *table;
    u32 index;
    s32 one;

    if (arg2 == 5) {
        s32 result;
        result = (s32)0x80010000;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return result + 0x7774;
    }
    if (arg2 == 4) {
        s32 result;
        result = (s32)0x80010000;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return result + 0x601C;
    }
    one = 1;
    if (arg2 == one) {
        u8 *state1;
        s32 *table1;
        state1 = (u8 *)0x80020000;
        ASM_KEEP(state1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        state1 = *(u8 **)(state1 - 0x16B0);
        ASM_KEEP(state1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        table1 = (s32 *)0x80010000;
        ASM_KEEP(table1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        index = state1[4];
        ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        table = (s32 *)((u8 *)table1 + 0x7FF4);
    } else {
        u8 **state_page;
        u8 *state0;
        state_page = (u8 **)0x80020000;
        ASM_KEEP(state_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        state0 = *(u8 **)((u8 *)state_page - 0x16B0);
        if (state0[6] != 0) {
            state_page = (u8 **)0x80010000;
            ASM_KEEP(state_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            index = state0[4];
            table = (s32 *)((u8 *)state_page + 0x7FF4);
        } else {
            u8 *reload;
            state0[6] = one;
            reload = *(u8 **)((u8 *)state_page - 0x16B0);
            state_page = (u8 **)0x80010000;
            ASM_KEEP(state_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            index = reload[4];
            ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            table = (s32 *)((u8 *)state_page + 0x7FD4);
        }
    }
    return table[index];
}

/* MECHANISM: The row is a frameless leaf: true-base local jumps are C joins,
   not calls. The third argument selects two address returns or indexed table
   loads through one table/index join; the state[6] write forces a fresh
   D_8001E950 reload afterward. */
