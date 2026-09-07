#include "common.h"

#ifdef NON_MATCHING
#define TBL_PAGE ((u8 *)jtbl_8002D658)
#define TBL_OFFSET 0
#else
#define TBL_PAGE ((u8 *)0x80030000)
#define TBL_OFFSET (-0x29A8)
#endif

typedef struct {
    u16 type;
    u16 next;
    u32 source;
    u16 x;
    u16 y;
    s16 flags;
} StreamCommand;

typedef struct {
    s32 value;
    s32 pad4;
    s32 pad8;
} LargeWord;

extern void func_8003E140(u8 *);
extern s32 func_8003E4FC(s32, void *, void *);
extern u8 *func_8004068C(u8 *, u8 *);
extern void func_8003F80C(s32, s32, s32, s32);
extern s32 DrawSync(s32);
extern s32 LoadImage(void *, void *);
extern void *memcpy(void *, const void *, u32);
extern LargeWord D_80081480;
extern LargeWord D_8008148C;
extern void *jtbl_8002D658[];

void func_80041588(u32 *arg0, u8 *arg1, s32 arg2)
{
    StreamCommand *cmd;
    u8 *base;
    u8 *buffer;
    u8 *data;
    u16 *p;
    register u32 *words ASM_REG("$8");
    void **table;
    s32 i;
    s32 j;
    register s32 flags ASM_REG("$7");
    register s32 flagword ASM_REG("$3");
    s32 limit;
    s32 index;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 bufferValue;
    register void *short_src ASM_REG("$4");
    u32 *input;
    static void *const keepalive[] = {
        &&case_1, &&case_2, &&case_3, &&case_4, &&case_5,
        &&case_6, &&case_7, &&case_8, &&case_9
    };

    input = arg0;
    cmd = (StreamCommand *)arg1;
    if (arg2 == 0) {
        func_8003E4FC(6, input, 0);
        *(u8 *)cmd = 0;
        func_8003E4FC(0xFF, func_8003E140, cmd);
        return;
    }

    base = (u8 *)(*input & 0x7FFFFF);
    cmd = (StreamCommand *)((u32)base | 0x80000000);
    base = (u8 *)cmd;
    DrawSync(0);
    ASM_SCHED_BARRIER();
    {
        register u8 *tblpage ASM_REG("$2") = TBL_PAGE;
        ASM_KEEP_NV(tblpage);
        bufferValue = D_8008148C.value;
        ASM_KEEP_NV(bufferValue);
        table = (void **)(tblpage + TBL_OFFSET);
    }
    buffer = (u8 *)bufferValue;
    D_80081480.value = (s32)buffer;

dispatch:
    index = cmd->type - 1;
    words = (u32 *)cmd;
    if ((u32)index >= 9) {
        goto done;
    }
    goto *table[index];

case_1:
            func_8004068C(base + words[1], buffer);
            LoadImage(&cmd->x, buffer);
            goto sync;

case_2:
            LoadImage(&cmd->x, base + words[1]);
            goto sync;

case_3:
            a1 = cmd->x;
            a2 = cmd->y;
            short_src = (void *)words[1];
            flags = cmd->flags;
            short_src = (void *)(base + (s32)short_src);
            a0 = (s32)short_src;
            goto call_tile;

case_4:
            flagword = (u16)cmd->flags;
            a1 = cmd->x;
            a2 = cmd->y;
            short_src = (void *)words[1];
            flagword |= 2;
            short_src = (void *)(base + (s32)short_src);
            a0 = (s32)short_src;
            goto convert_flags;

case_5:
            a0 = (s32)(base + words[1]);
            limit = (s32)cmd->y << 4;
            data = (u8 *)a0;
            p = (u16 *)(data + 2);
            i = 1;
            while (i < limit) {
                *p |= 0x8000;
                i++;
                p++;
            }
            goto masked_tile;

case_6:
            a0 = (s32)(base + words[1]);
            limit = cmd->y;
            data = (u8 *)a0;
            p = (u16 *)data;
            i = 0;
            if (limit != 0) {
                do {
                    p++;
                    j = 1;
                    do {
                        *p |= 0x8000;
                        j++;
                        p++;
                    } while (j < 16);
                    i++;
                } while (i < limit);
            }

masked_tile:
            flagword = (u16)cmd->flags;
            a1 = cmd->x;
            a2 = cmd->y;
            flagword |= 2;
convert_flags:
            flags = (s16)flagword;
    ASM_KEEP(flagword);
call_tile:
            func_8003F80C(a0, a1, a2, flags);
sync:
            DrawSync(0);
            goto advance;

case_7:
            func_8004068C(base + words[1], (u8 *)words[2]);
            goto advance;

case_8:
            memcpy((void *)words[2], base + words[1], words[3]);
            goto advance;

case_9:
            i = cmd->x;
            data = base + words[1];
            if (i > 0) {
                u32 add = (u32)base | 0x80000000;
                data += 4;
                do {
                    *(u32 *)data += add;
                    i--;
                    data += 8;
                } while (i > 0);
            }
advance:
        if (cmd->next == 0) {
            goto done;
        }
        cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
        goto dispatch;
done:
        return;
}
