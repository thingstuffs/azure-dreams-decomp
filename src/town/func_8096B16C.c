#include "common.h"

typedef struct S_80123604_0 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_80123604_0;   /* *dst in func_80123604 */

typedef struct S_80123604_1 {
    u8 pad_00[0x68];
    void * unk_68;
    void * unk_6C;
} S_80123604_1;   /* tail_dst in func_80123604 */

typedef struct S_80123604_2 {
    u8 pad_00[0x64];
    u16 unk_64;
    u16 unk_66;
    u8 pad_68[0x4];
    u16 unk_6C;
    u16 unk_6E;
} S_80123604_2;   /* tail_src in func_80123604 */

typedef struct S_80123604_3 {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
} S_80123604_3;   /* ((S_80123604_0 *)(*dst))->unk_04 in func_80123604 */

typedef struct S_80123604_4 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_80123604_4;   /* ((S_80123604_0 *)(*dst))->unk_08 in func_80123604 */

typedef struct S_80123604_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123604_5;   /* ((S_80123604_1 *)tail_dst)->unk_68 in func_80123604 */

typedef struct S_80123604_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123604_6;   /* ((S_80123604_1 *)tail_dst)->unk_6C in func_80123604 */

typedef struct S_80123604_7 {
    u8 pad_00[0x6];
    u16 unk_06;
    u16 unk_08;
} S_80123604_7;   /* ((S_80123604_5 *)(((S_80123604_1 *)tail_dst)->unk_68))->unk_08 in func_80123604 */

typedef struct S_80123604_8 {
    u8 pad_00[0x6];
    u16 unk_06;
    u16 unk_08;
} S_80123604_8;   /* ((S_80123604_6 *)(((S_80123604_1 *)tail_dst)->unk_6C))->unk_08 in func_80123604 */


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

void func_80123604(void) {
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
        dst = (void **)(D_80129728 + 0x38);
        src = (volatile SourceEntry *)D_80126A18;
#else
        page = (u8 *)0x80130000;
        TIE_LOCAL(page);
        page -= 0x68D8;
        TIE_LOCAL(page);
        dst = (void **)(page + 0x38);
        page = (u8 *)0x80120000;
        TIE_LOCAL(page);
        src = (volatile SourceEntry *)(page + 0x6A18);
#endif
        do {
            ((S_80123604_0 *)(*dst))->unk_00 = 0;
            ((S_80123604_3 *)(((S_80123604_0 *)(*dst))->unk_04))->unk_08 = src->first;
            ((S_80123604_3 *)(((S_80123604_0 *)(*dst))->unk_04))->unk_0A = src->second;
            i++;
            ((S_80123604_4 *)(((S_80123604_0 *)(*dst))->unk_08))->unk_06 = small;
            src++;
            ((S_80123604_4 *)(((S_80123604_0 *)(*dst))->unk_08))->unk_08 = large;
            dst++;
        } while (i < 0xE);
    }

    {
        register u8 *tail_src ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u8 *tail_dst ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

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
        ((S_80123604_7 *)(((S_80123604_5 *)(((S_80123604_1 *)tail_dst)->unk_68))->unk_08))->unk_06 =
            ((S_80123604_2 *)tail_src)->unk_64;
        ((S_80123604_7 *)(((S_80123604_5 *)(((S_80123604_1 *)tail_dst)->unk_68))->unk_08))->unk_08 =
            ((S_80123604_2 *)tail_src)->unk_66;
        ((S_80123604_8 *)(((S_80123604_6 *)(((S_80123604_1 *)tail_dst)->unk_6C))->unk_08))->unk_06 =
            ((S_80123604_2 *)tail_src)->unk_6C;
        ((S_80123604_8 *)(((S_80123604_6 *)(((S_80123604_1 *)tail_dst)->unk_6C))->unk_08))->unk_08 =
            ((S_80123604_2 *)tail_src)->unk_6E;
    }
}
