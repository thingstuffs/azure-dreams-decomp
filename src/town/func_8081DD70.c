#include "common.h"

typedef struct S_8081DD70_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8081DD70_0;   /* src in func_8081DD70 */

typedef struct S_8081DD70_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8081DD70_1;   /* dst in func_8081DD70 */

typedef struct S_8081DD70_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8081DD70_2;   /* object in func_8081DD70 */

typedef struct S_8081DD70_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8081DD70_3;   /* record_arg in func_8081DD70 */

typedef struct S_8081DD70_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8081DD70_4;   /* copy_packet in func_8081DD70 */

typedef struct S_8081DD70_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8081DD70_5;   /* temp_a1 in func_8081DD70 */

typedef struct S_8081DD70_6 {
    u8 pad_00[0x54];
    s16 unk_54;
} S_8081DD70_6;   /* source_arg in func_8081DD70 */

typedef struct S_8081DD70_7 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8081DD70_7;   /* copy_dst in func_8081DD70 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);

extern s32 D_80020014;
extern s32 D_800206D0;
extern s32 D_80024420;
extern s32 D_8002445C[];
extern s32 D_80045340;

void func_8081DD70(void *arg0, void *arg1) {
    register void *source_arg ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *record_arg ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *held_global;
    void *object;
    void *copy_dst;
    void *packet;
    u8 *src_seed;
    u8 *dst_seed;
    register u8 *end_seed ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *src;
    u8 *dst;
    u8 *end;
    register s32 word0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 word1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 word2;
    s32 word3;

    source_arg = arg0;
    record_arg = arg1;
    held_global = &D_80020014;
    object = func_8003FC64(0x136);
    copy_dst = (u8 *)object + 0x20;
    if (object != 0) {
        dst_seed = copy_dst;
        src_seed = source_arg;
        end_seed = (u8 *)source_arg + 0x50;
        dst = dst_seed;
        src = src_seed;
        end = end_seed;
        do {
            word0 = ((S_8081DD70_0 *)src)->unk_00;
            word1 = ((S_8081DD70_0 *)src)->unk_04;
            word2 = ((S_8081DD70_0 *)src)->unk_08;
            word3 = ((S_8081DD70_0 *)src)->unk_0C;
            ((S_8081DD70_1 *)dst)->unk_00 = word0;
            ((S_8081DD70_1 *)dst)->unk_04 = word1;
            ((S_8081DD70_1 *)dst)->unk_08 = word2;
            ((S_8081DD70_1 *)dst)->unk_0C = word3;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            src += 0x10;
            dst += 0x10;
        } while (src != end);
        word0 = ((S_8081DD70_0 *)src)->unk_00;
        word1 = ((S_8081DD70_0 *)src)->unk_04;
        ((S_8081DD70_1 *)dst)->unk_00 = word0;
        ((S_8081DD70_1 *)dst)->unk_04 = word1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        {
            register void *call_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            void *call_data;
            register void *copy_packet ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 record0;
            s32 record1;
            register s32 record2 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 record3 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

            call_object = object;
            call_data = &D_80045340;
            ASM_USE2(call_object, call_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy_packet = ((S_8081DD70_2 *)object)->unk_08;
            ((S_8081DD70_2 *)object)->unk_10 = &D_800206D0;
            record0 = ((S_8081DD70_3 *)record_arg)->unk_00;
            record1 = ((S_8081DD70_3 *)record_arg)->unk_04;
            record2 = ((S_8081DD70_3 *)record_arg)->unk_08;
            record3 = ((S_8081DD70_3 *)record_arg)->unk_0C;
            ((S_8081DD70_4 *)copy_packet)->unk_00 = record0;
            ((S_8081DD70_4 *)copy_packet)->unk_04 = record1;
            ((S_8081DD70_4 *)copy_packet)->unk_08 = record2;
            ((S_8081DD70_4 *)copy_packet)->unk_0C = record3;
            record0 = ((S_8081DD70_3 *)record_arg)->unk_10;
            record1 = ((S_8081DD70_3 *)record_arg)->unk_14;
            ((S_8081DD70_4 *)copy_packet)->unk_10 = record0;
            ((S_8081DD70_4 *)copy_packet)->unk_14 = record1;
            func_8004491C(call_object, call_data);
        }

        {
            s32 temp_v0;
            s32 temp_v1;
            void *temp_a0;
            S_8081DD70_5 *temp_a1;
            s32 temp_a2;

            temp_a2 = 0x00808080;
            temp_v0 = 0x1000;
            temp_a1 = ((S_8081DD70_2 *)object)->unk_0C;
            temp_v1 = (s32)D_8002445C;
            temp_a1->unk_1E = temp_v0;
            temp_a1->unk_1C = temp_v0;
            temp_v0 = ((S_8081DD70_6 *)source_arg)->unk_54;
            temp_v1 = *(s32 *)(temp_v1 + (temp_v0 * 4));
            temp_v0 = temp_a1->unk_14;
            ASM_KEEP(copy_dst);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            temp_a0 = (u8 *)copy_dst + 8;
            temp_a1->unk_0C = temp_a2;
            temp_a2 = (s32)&D_80024420;
            temp_a1->unk_04 = 0;
            temp_a1->unk_05 = 0;
            temp_v0 |= 0x80;
            temp_a1->unk_14 = temp_v0;
            temp_a1->unk_08 = temp_v1;
            ((S_8081DD70_7 *)copy_dst)->unk_50 = held_global;
            temp_a1 = ((S_8081DD70_2 *)object)->unk_08;
            func_8008F074(temp_a0, temp_a1, (void *)temp_a2);
        }
        ASM_KEEP(source_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(record_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: The 0x28 frame follows from held s2/s3 arguments, the s4 global base,
   and the s1 copy base; scoped ABI roles reproduce the 16+8-byte copy groups.
   A late keep on immutable s1 forms a0=s1+8 directly and removes the +1 cascade. */
