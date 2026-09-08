#include "common.h"

typedef struct S_8080E838_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8080E838_0;   /* copy_src in func_8080E838 */

typedef struct S_8080E838_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8080E838_1;   /* copy_dst in func_8080E838 */

typedef struct S_8080E838_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    s32 unk_10;
} S_8080E838_2;   /* obj in func_8080E838 */

typedef struct S_8080E838_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080E838_3;   /* initial in func_8080E838 */

typedef struct S_8080E838_4 {
    s32 unk_00;
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s16 unk_1C;
    s16 unk_1E;
} S_8080E838_4;   /* part in func_8080E838 */

typedef struct S_8080E838_5 {
    u8 pad_00[0x54];
    s16 unk_54;
} S_8080E838_5;   /* source in func_8080E838 */

typedef struct S_8080E838_6 {
    u8 pad_00[0x130];
    s32 unk_130;
} S_8080E838_6;   /* table_base in func_8080E838 */

typedef struct S_8080E838_7 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8080E838_7;   /* payload in func_8080E838 */


typedef struct {
    s32 words[4];
} Copy16;

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern void func_8023FA58(void *, void *, void *);

extern u8 D_8003C558[];
extern u8 D_8052643C[];
extern u8 D_80529594[];
extern s32 D_805300F4[];


void func_8080E838(void *arg0, void *arg1) {
    void *obj;
    void *result;
    register void *source ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *initial ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u8 *payload ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *part;
    register u8 *held ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Copy16 *copy_src;
    Copy16 *copy_dst;
    Copy16 *copy_end;
    s32 loop0;
    register s32 loop1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 loop2;
    register s32 loop3 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 word0;
    register s32 word1 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 word2 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 word3 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *call_data ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 *table_base ASM_REG("$1");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    source = arg0;
    ASM_KEEP_NV(source);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    initial = arg1;
    ASM_KEEP_NV(initial);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    result = func_800373DC(0x136);
    held = D_8052643C;
    ASM_KEEP_NV(held);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    obj = result;
    payload = (u8 *)obj + 0x20;
    if (obj != 0) {
        copy_dst = (Copy16 *)payload;
        copy_src = (Copy16 *)source;
        copy_end = (Copy16 *)((u8 *)source + 0x50);
        do {
            loop0 = ((S_8080E838_0 *)copy_src)->unk_00;
            loop1 = ((S_8080E838_0 *)copy_src)->unk_04;
            loop2 = ((S_8080E838_0 *)copy_src)->unk_08;
            loop3 = ((S_8080E838_0 *)copy_src)->unk_0C;
            ((S_8080E838_1 *)copy_dst)->unk_00 = loop0;
            ((S_8080E838_1 *)copy_dst)->unk_04 = loop1;
            ((S_8080E838_1 *)copy_dst)->unk_08 = loop2;
            ((S_8080E838_1 *)copy_dst)->unk_0C = loop3;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy_src++;
            copy_dst++;
        } while (copy_src != copy_end);
        word0 = ((S_8080E838_0 *)copy_src)->unk_00;
        loop1 = ((S_8080E838_0 *)copy_src)->unk_04;
        ((S_8080E838_1 *)copy_dst)->unk_00 = word0;
        ((S_8080E838_1 *)copy_dst)->unk_04 = loop1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        loop2 = (s32)obj;
        ASM_KEEP(loop2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_data = D_8003C558;
        part = ((S_8080E838_2 *)obj)->unk_08;
        ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        word0 = (s32)D_80529594;
        ((S_8080E838_2 *)obj)->unk_10 = word0;
        word0 = ((S_8080E838_3 *)initial)->unk_00;
        word1 = ((S_8080E838_3 *)initial)->unk_04;
        word2 = ((S_8080E838_3 *)initial)->unk_08;
        word3 = ((S_8080E838_3 *)initial)->unk_0C;
        ((S_8080E838_4 *)part)->unk_00 = word0;
        ((S_8080E838_4 *)part)->unk_04.at00.v = word1;
        ((S_8080E838_4 *)part)->unk_08 = word2;
        ((S_8080E838_4 *)part)->unk_0C = word3;
        word0 = ((S_8080E838_3 *)initial)->unk_10;
        word1 = ((S_8080E838_3 *)initial)->unk_14;
        ((S_8080E838_4 *)part)->unk_10 = word0;
        ((S_8080E838_4 *)part)->unk_14.s32 = word1;
        func_8003BC18((void *)loop2, call_data);

        word1 = 0x800000;
        ASM_KEEP(word1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        part = ((S_8080E838_2 *)obj)->unk_0C;
        word0 = 0x1000;
        ((S_8080E838_4 *)part)->unk_1E = word0;
        ((S_8080E838_4 *)part)->unk_1C = word0;
        word0 = ((S_8080E838_5 *)source)->unk_54;
        ASM_KEEP(word0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        word1 |= 0x8080;
        word0 <<= 2;
        table_base = (s32 *)0x80530000;
        table_base = (s32 *)((s32)table_base - -word0);
        loop3 = ((S_8080E838_6 *)table_base)->unk_130;
        ASM_KEEP(loop3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        word0 = ((S_8080E838_4 *)part)->unk_14.u16;
        ((S_8080E838_4 *)part)->unk_04.at00u.v = 0;
        ((S_8080E838_4 *)part)->unk_04.at01.v = 0;
        ((S_8080E838_4 *)part)->unk_0C = word1;
        word0 |= 0x80;
        ((S_8080E838_4 *)part)->unk_14.u16 = word0;
        ASM_KEEP(word0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_8080E838_4 *)part)->unk_08 = loop3;
        ((S_8080E838_7 *)payload)->unk_50 = held;
        ASM_KEEP_NV(payload);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        call_data = ((S_8080E838_2 *)obj)->unk_08;
        ASM_KEEP(call_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        word1 = (s32)D_805300F4;
        ASM_KEEP(word1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_8023FA58(payload + 8, call_data, (void *)word1);
    }
}
