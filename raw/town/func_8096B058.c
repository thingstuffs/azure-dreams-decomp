#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#ifdef NON_MATCHING
#define TIE_LOCAL(value) ((void)0)
#else
#define TIE_LOCAL(value) ASM_KEEP(value)
#endif

extern u8 D_80126A18[0x70];
extern u8 D_80129728[0x38];

typedef struct SourceEntry {
    s32 word;
    u16 first;
    u16 second;
} SourceEntry;

void func_801234F0(void) {
    {
        volatile SourceEntry *src;
        register u8 *page;
        void **dst;
        s32 i = 0;
        s16 small = 0x10;
        s16 large = 0xE0;

        TIE_LOCAL(small);
        TIE_LOCAL(large);
#ifdef NON_MATCHING
        dst = (void **)D_80129728;
        src = (volatile SourceEntry *)D_80126A18;
#else
        page = (u8 *)0x80130000;
        TIE_LOCAL(page);
        dst = (void **)(page - 0x68D8);
        page = (u8 *)0x80120000;
        TIE_LOCAL(page);
        src = (volatile SourceEntry *)(page + 0x6A18);
#endif
        do {
            FIELD(*dst, s32, 0) = src->word;
            FIELD(FIELD(*dst, void *, 4), u16, 8) = src->first;
            FIELD(FIELD(*dst, void *, 4), u16, 0xA) = src->second;
            i++;
            FIELD(FIELD(*dst, void *, 8), s16, 6) = small;
            src++;
            FIELD(FIELD(*dst, void *, 8), s16, 8) = large;
            dst++;
        } while (i < 0xE);
    }

    {
        register u8 *tail_src ASM_REG("$5");
        register u8 *tail_dst ASM_REG("$4");

#ifdef NON_MATCHING
        tail_dst = (void **)D_80129728;
        tail_src = D_80126A18;
#else
        tail_dst = (u8 *)0x80130000;
        TIE_LOCAL(tail_dst);
        tail_dst -= 0x68D8;
        tail_src = (u8 *)0x80120000;
        TIE_LOCAL(tail_src);
        tail_src += 0x6A18;
#endif
        FIELD(FIELD(FIELD(tail_dst, void *, 0x30), void *, 8), u16, 6) =
            FIELD(tail_src, u16, 0x64);
        FIELD(FIELD(FIELD(tail_dst, void *, 0x30), void *, 8), u16, 8) =
            FIELD(tail_src, u16, 0x66);
        FIELD(FIELD(FIELD(tail_dst, void *, 0x34), void *, 8), u16, 6) =
            FIELD(tail_src, u16, 0x6C);
        FIELD(FIELD(FIELD(tail_dst, void *, 0x34), void *, 8), u16, 8) =
            FIELD(tail_src, u16, 0x6E);
    }
}
