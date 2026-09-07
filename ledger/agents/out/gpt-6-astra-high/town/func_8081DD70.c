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

/* Create an object, copy its source and record data, and initialize its rendering state. */
void func_8081DD70(void *source_data, void *record_data) {
    register void *source ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *record ASM_REG("$19");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *global_data;
    void *object;
    void *copy_dst;
    void *packet;
    u8 *src_start;
    u8 *dst_start;
    register u8 *src_limit ASM_REG("$8");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u8 *src;
    u8 *dst;
    u8 *src_end;
    register s32 word_0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 word_1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 word_2;
    s32 word_3;

    source = source_data;
    record = record_data;
    global_data = &D_80020014;
    object = func_8003FC64(0x136);
    copy_dst = (u8 *)object + 0x20;
    if (object != 0) {
        dst_start = copy_dst;
        src_start = source;
        src_limit = (u8 *)source + 0x50;
        dst = dst_start;
        src = src_start;
        src_end = src_limit;
        do {
            word_0 = ((S_8081DD70_0 *)src)->unk_00;
            word_1 = ((S_8081DD70_0 *)src)->unk_04;
            word_2 = ((S_8081DD70_0 *)src)->unk_08;
            word_3 = ((S_8081DD70_0 *)src)->unk_0C;
            ((S_8081DD70_1 *)dst)->unk_00 = word_0;
            ((S_8081DD70_1 *)dst)->unk_04 = word_1;
            ((S_8081DD70_1 *)dst)->unk_08 = word_2;
            ((S_8081DD70_1 *)dst)->unk_0C = word_3;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            src += 0x10;
            dst += 0x10;
        } while (src != src_end);
        word_0 = ((S_8081DD70_0 *)src)->unk_00;
        word_1 = ((S_8081DD70_0 *)src)->unk_04;
        ((S_8081DD70_1 *)dst)->unk_00 = word_0;
        ((S_8081DD70_1 *)dst)->unk_04 = word_1;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */

        {
            register void *call_object ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            void *call_data;
            register void *copy_packet ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
            s32 record_word_0;
            s32 record_word_1;
            register s32 record_word_2 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
            register s32 record_word_3 ASM_REG("$8");   /* MATCH pin: retail schedule: same instructions, different order without it */

            call_object = object;
            call_data = &D_80045340;
            ASM_USE2(call_object, call_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
            copy_packet = ((S_8081DD70_2 *)object)->unk_08;
            ((S_8081DD70_2 *)object)->unk_10 = &D_800206D0;
            record_word_0 = ((S_8081DD70_3 *)record)->unk_00;
            record_word_1 = ((S_8081DD70_3 *)record)->unk_04;
            record_word_2 = ((S_8081DD70_3 *)record)->unk_08;
            record_word_3 = ((S_8081DD70_3 *)record)->unk_0C;
            ((S_8081DD70_4 *)copy_packet)->unk_00 = record_word_0;
            ((S_8081DD70_4 *)copy_packet)->unk_04 = record_word_1;
            ((S_8081DD70_4 *)copy_packet)->unk_08 = record_word_2;
            ((S_8081DD70_4 *)copy_packet)->unk_0C = record_word_3;
            record_word_0 = ((S_8081DD70_3 *)record)->unk_10;
            record_word_1 = ((S_8081DD70_3 *)record)->unk_14;
            ((S_8081DD70_4 *)copy_packet)->unk_10 = record_word_0;
            ((S_8081DD70_4 *)copy_packet)->unk_14 = record_word_1;
            func_8004491C(call_object, call_data);
        }

        {
            s32 setup_value;
            s32 resource_addr;
            void *state_fields;
            S_8081DD70_5 *object_packet;
            s32 color_or_context;

            color_or_context = 0x00808080;
            setup_value = 0x1000;
            object_packet = ((S_8081DD70_2 *)object)->unk_0C;
            resource_addr = (s32)D_8002445C;
            object_packet->unk_1E = setup_value;
            object_packet->unk_1C = setup_value;
            setup_value = ((S_8081DD70_6 *)source)->unk_54;
            resource_addr = *(s32 *)(resource_addr + (setup_value * 4));
            setup_value = object_packet->unk_14;
            ASM_KEEP(copy_dst);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            state_fields = (u8 *)copy_dst + 8;
            object_packet->unk_0C = color_or_context;
            color_or_context = (s32)&D_80024420;
            object_packet->unk_04 = 0;
            object_packet->unk_05 = 0;
            setup_value |= 0x80;
            object_packet->unk_14 = setup_value;
            object_packet->unk_08 = resource_addr;
            ((S_8081DD70_7 *)copy_dst)->unk_50 = global_data;
            object_packet = ((S_8081DD70_2 *)object)->unk_08;
            func_8008F074(state_fields, object_packet, (void *)color_or_context);
        }
        ASM_KEEP(source);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(record);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}

/* MECHANISM: The 0x28 frame follows from held s2/s3 arguments, the s4 global base,
   and the s1 copy base; scoped ABI roles reproduce the 16+8-byte copy groups.
   A late keep on immutable s1 forms a0=s1+8 directly and removes the +1 cascade. */
