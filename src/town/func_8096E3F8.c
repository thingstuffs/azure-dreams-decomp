#include "common.h"

typedef struct S_80126890_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    void * unk_20;
} S_80126890_0;   /* node in func_80126890 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8004B248(void *);
extern void func_80053DA8(s32);
extern void func_80123130(void);
extern s32 func_801264AC(void *);
extern void func_80126620(void *);

extern s32 D_8004CAA0;
extern s8 D_80080A84;
extern s32 D_800814A0;
extern s32 D_80126704;

/* Allocates and initializes a node for the supplied data, returning null on failure. */
static void *func_80126890(void *data) {
    void *node;
    void *payload;

    node = func_8003FC64(0);
    if (node != 0) {
        ((S_80126890_0 *)node)->unk_20 = data;
        payload = (u8 *)node + 0x20;
        if (func_801264AC(payload) != 0) {
            D_80080A84 = 1;
            func_80123130();
            ((S_80126890_0 *)node)->unk_0C = (u8 *)node + 0x68;
            func_80126620(payload);
            func_8004491C(node, &D_8004CAA0);
            ((S_80126890_0 *)node)->unk_10 = &D_80126704;
            func_80053DA8(0x701);
        } else {
            func_8004B248((u8 *)node + 0x7C);
            ((S_80126890_0 *)node)->unk_1E |= 0x8000;
            D_800814A0 |= 0x8000;
            node = 0;
        }
    }
    return node;
}
