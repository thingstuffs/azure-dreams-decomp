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
    register s32 one ASM_REG("$5");

    if (arg2 == 5) {
        register s32 result ASM_REG("$2");
        result = (s32)0x80010000;
        ASM_KEEP(result);
        return result + 0x7774;
    }
    if (arg2 == 4) {
        register s32 result ASM_REG("$2");
        result = (s32)0x80010000;
        ASM_KEEP(result);
        return result + 0x601C;
    }
    one = 1;
    ASM_KEEP(one);
    if (arg2 == one) {
        register u8 *state1 ASM_REG("$2");
        register s32 *table1 ASM_REG("$3");
        state1 = (u8 *)0x80020000;
        ASM_KEEP(state1);
        state1 = *(u8 **)(state1 - 0x16B0);
        ASM_KEEP(state1);
        table1 = (s32 *)0x80010000;
        ASM_KEEP(table1);
        index = state1[4];
        ASM_KEEP(index);
        table = (s32 *)((u8 *)table1 + 0x7FF4);
    } else {
        register u8 **state_page ASM_REG("$3");
        register u8 *state0 ASM_REG("$4");
        state_page = (u8 **)0x80020000;
        ASM_KEEP(state_page);
        state0 = *(u8 **)((u8 *)state_page - 0x16B0);
        ASM_KEEP(state0);
        if (state0[6] != 0) {
            state_page = (u8 **)0x80010000;
            ASM_KEEP(state_page);
            index = state0[4];
            ASM_KEEP(index);
            table = (s32 *)((u8 *)state_page + 0x7FF4);
        } else {
            register u8 *reload ASM_REG("$2");
            state0[6] = one;
            reload = *(u8 **)((u8 *)state_page - 0x16B0);
            ASM_KEEP(reload);
            state_page = (u8 **)0x80010000;
            ASM_KEEP(state_page);
            index = reload[4];
            ASM_KEEP(index);
            table = (s32 *)((u8 *)state_page + 0x7FD4);
        }
    }
    return table[index];
}

/* MECHANISM: The row is a frameless leaf: true-base local jumps are C joins,
   not calls. The third argument selects two address returns or indexed table
   loads through one table/index join; the state[6] write forces a fresh
   D_8001E950 reload afterward. */
