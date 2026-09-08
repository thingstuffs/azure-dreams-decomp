#include "common.h"

typedef s32 (*IndexFunc)(s32);
typedef void (*UseFunc)(s16, s8);

extern s8 D_80016000[];
extern s8 *D_80018880[];
extern s16 D_8001888C[];
extern s8 *D_80018A1C;

extern s32 func_8001E670(u16);

void func_8001CD98(void) {
    s8 *selected;
    s8 *entry;
    s16 *value;
    register s32 initial ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 index;
    register s32 offset ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 tail_flag ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 **page;
    void **root_page;
    s32 result;
    void *root;
    void *api;
    IndexFunc get_index;
    UseFunc use;

    root = *(void **)D_80016000;
    initial = 0;
    index = initial;
    ASM_KEEP(initial);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    offset = (s32)D_80018880;
    selected = *(s8 **)(offset +
        (*(IndexFunc *)((s8 *)*(void **)((s8 *)root + 0x20) + 0x2D4))(initial)
        * 4);
    page = (s8 **)0x80020000;
    if ((((u8 *)*(s8 **)((s8 *)page - 0x75E4))[1] & 0xC0) != 0x80) {
        offset = index;
        value = D_8001888C;
loop:
        entry = (s8 *)(offset + (s32)*(s8 **)((s8 *)page - 0x75E4));
        if (!((u8)entry[1] & 1)) {
            result = func_8001E670(*(u16 *)(entry + 2));
            if (result == 0) {
                goto next;
            }
            root_page = (void **)0x80010000;
            entry = selected + index;
            goto use_entry;
        } else {
            result = func_8001E670(*(u16 *)(entry + 2));
            if (result == 1) {
                goto next;
            }
            root_page = (void **)0x80010000;
            entry = selected + index;
        }

use_entry:
        root = *(void **)((s8 *)root_page + 0x6000);
        api = *(void **)((s8 *)root + 0x20);
        use = *(UseFunc *)((s8 *)api + 0x304);
        use(*value, *entry);

next:
        offset += 0x14;
        value++;
        index++;
        page = (s8 **)0x80020000;
        tail_flag = ((u8 *)(offset + (s32)*(s8 **)((s8 *)page - 0x75E4)))[1];
        if ((tail_flag & 0xC0) != 0x80) {
            goto loop;
        }
    }
}
