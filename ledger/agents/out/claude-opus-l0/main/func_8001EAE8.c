#include "common.h"

extern void func_80403D7C(s32, s32);
extern void func_804045C8(s32, s32);
extern void func_80404668(s32);
extern void func_80405A00(s32, s32);

void func_80405AE8(void *arg0) {
    s32 sentinel;
    s32 i;

    if (*(s32 *)((u8 *)arg0 + 0x48) == 1) {
        sentinel = 1;
    } else {
        func_80403D7C(*(s32 *)((u8 *)arg0 + 0x18), *(s32 *)((u8 *)arg0 + 0x44));
        sentinel = 0;
    }
    i = 0;
    while (1) {
        if (i == *(s32 *)((u8 *)arg0 + 0x28)) {
            func_804045C8(*(s32 *)((u8 *)arg0 + i * 4 + 4), sentinel);
        } else {
            func_80404668(*(s32 *)((u8 *)arg0 + i * 4 + 4));
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    func_80405A00(*(s32 *)((u8 *)arg0 + 0x1C), *(s32 *)((u8 *)arg0 + 0x28));
}
