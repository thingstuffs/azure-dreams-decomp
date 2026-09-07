#include "common.h"

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
} S_800869C0;

extern S_800869C0 D_800869C0[16];
extern u8 D_8007382B;
extern s32 D_80073830[9];
extern void func_80059DAC(void);

s32 func_80059F8C(u32 addr, s32 size)
{
    S_800869C0 *e;
    S_800869C0 *q;
    s32 i;
    s32 j;
    u32 cur;
    u32 nxt;

    if ((u32)(addr - 0x1010) > 0x7EFEF) {
        return -1;
    }
    if (addr + size > 0x7FFFF) {
        return -1;
    }
    e = D_800869C0;
    if (D_800869C0[0].addr != 0) {
        goto scan;
    }
    if (addr + size < (u32)(0x80000 - D_80073830[D_8007382B])) {
        D_800869C0[0].addr = addr;
        e->size = size;
        goto sort_ret;
    }
    return -1;

exact:
    e->addr = addr;
    e->size = size;
    return addr;

ins_q:
    q->addr = addr;
    q->size = size;
    goto sort_ret;

scan:
    i = 0;
    do {
        if (i != 0) {
            goto chk;
        }
        nxt = D_800869C0[0].addr;
        if (addr < nxt) {
            if (nxt < size + addr) {
                return -1;
            }
            for (; i < 16; i++) {
                if (D_800869C0[i].size == 0) {
                    goto foundA;
                }
            }
            goto done;
foundA:
            D_800869C0[i].addr = addr;
            D_800869C0[i].size = size;
            goto done;
        }
        goto mid;
chk:
        if (addr < e->addr) {
            goto next;
        }
mid:
        cur = e->addr;
        if (cur == addr) {
            goto exact;
        }
        j = i + 1;
        q = &D_800869C0[j];
        if (q->size == 0) {
            if (size + addr < (u32)(0x80000 - D_80073830[D_8007382B])) {
                goto ins_q;
            }
            return -1;
        }
        if (cur >= addr) {
            goto next;
        }
        nxt = q->addr;
        if (addr >= nxt) {
            goto next;
        }
        if (addr < cur + e->size) {
            return -1;
        }
        if ((s32)nxt < (s32)(addr + size)) {
            return -1;
        }
        for (; i < 16; i++) {
            if (D_800869C0[i].size == 0) {
                D_800869C0[i].addr = addr;
                D_800869C0[i].size = size;
                break;
            }
        }
done:
        if (i != 16) {
            goto sort_ret;
        }
        return -1;
next:
        i++;
        e++;
    } while (i < 16);

sort_ret:
    func_80059DAC();
    return addr;
}
