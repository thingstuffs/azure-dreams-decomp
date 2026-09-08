#include "common.h"

extern u32 strcpy();
extern void *func_8009F830();
extern void *D_80100AF0[];

/* kewn_namewin_close_check: Copies the entered name to the main and matching item buffers when the close flag is set. */
s32 func_8009E424(void) {
    s32 close_flag;
    void *matched_item;

    close_flag = *(u16 *)((u8 *)D_80100AF0[0] + 0x1E) & 0x8000 & 0xFFFF;
    if (close_flag != 0) {
        strcpy((void *)0x80010238, (void *)0x80010AB4);
        matched_item = func_8009F830(2, 0x13);
        if (matched_item != 0) {
            strcpy(
                (void *)(0x80010324 +
                         ((*(u8 *)((u8 *)matched_item + 3) & 0x1F) * 0x54)),
                (void *)0x80010AB4);
        }
    }
    return close_flag;
}
