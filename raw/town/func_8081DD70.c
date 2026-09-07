#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);

extern s32 D_80020014;
extern s32 D_800206D0;
extern s32 D_80024420;
extern s32 D_8002445C[];
extern s32 D_80045340;

void func_8081DD70(void *arg0, void *arg1) {
    register void *source_arg ASM_REG("$18");
    register void *record_arg ASM_REG("$19");
    void *held_global;
    void *object;
    void *copy_dst;
    void *packet;
    register u8 *src_seed ASM_REG("$6");
    register u8 *dst_seed ASM_REG("$7");
    register u8 *end_seed ASM_REG("$8");
    u8 *src;
    u8 *dst;
    u8 *end;
    register s32 word0 ASM_REG("$2");
    register s32 word1 ASM_REG("$3");
    register s32 word2 ASM_REG("$4");
    register s32 word3 ASM_REG("$5");

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
            word0 = FIELD(src, s32, 0);
            word1 = FIELD(src, s32, 4);
            word2 = FIELD(src, s32, 8);
            word3 = FIELD(src, s32, 0xC);
            FIELD(dst, s32, 0) = word0;
            FIELD(dst, s32, 4) = word1;
            FIELD(dst, s32, 8) = word2;
            FIELD(dst, s32, 0xC) = word3;
            ASM_SCHED_BARRIER();
            src += 0x10;
            dst += 0x10;
        } while (src != end);
        word0 = FIELD(src, s32, 0);
        word1 = FIELD(src, s32, 4);
        FIELD(dst, s32, 0) = word0;
        FIELD(dst, s32, 4) = word1;
        ASM_SCHED_BARRIER();

        {
            register void *call_object ASM_REG("$4");
            register void *call_data ASM_REG("$5");
            register void *copy_packet ASM_REG("$3");
            register s32 record0 ASM_REG("$2");
            register s32 record1 ASM_REG("$6");
            register s32 record2 ASM_REG("$7");
            register s32 record3 ASM_REG("$8");

            call_object = object;
            call_data = &D_80045340;
            ASM_USE2(call_object, call_data);
            copy_packet = FIELD(object, void *, 8);
            FIELD(object, void *, 0x10) = &D_800206D0;
            record0 = FIELD(record_arg, s32, 0);
            record1 = FIELD(record_arg, s32, 4);
            record2 = FIELD(record_arg, s32, 8);
            record3 = FIELD(record_arg, s32, 0xC);
            FIELD(copy_packet, s32, 0) = record0;
            FIELD(copy_packet, s32, 4) = record1;
            FIELD(copy_packet, s32, 8) = record2;
            FIELD(copy_packet, s32, 0xC) = record3;
            record0 = FIELD(record_arg, s32, 0x10);
            record1 = FIELD(record_arg, s32, 0x14);
            FIELD(copy_packet, s32, 0x10) = record0;
            FIELD(copy_packet, s32, 0x14) = record1;
            func_8004491C(call_object, call_data);
        }

        {
            register s32 temp_v0 ASM_REG("$2");
            register s32 temp_v1 ASM_REG("$3");
            register void *temp_a0 ASM_REG("$4");
            register void *temp_a1 ASM_REG("$5");
            register s32 temp_a2 ASM_REG("$6");

            temp_a2 = 0x00808080;
            ASM_USE(temp_a2);
            temp_v0 = 0x1000;
            temp_a1 = FIELD(object, void *, 0xC);
            ASM_USE2(temp_v0, temp_a1);
            temp_v1 = (s32)D_8002445C;
            FIELD(temp_a1, s16, 0x1E) = temp_v0;
            FIELD(temp_a1, s16, 0x1C) = temp_v0;
            temp_v0 = FIELD(source_arg, s16, 0x54);
            temp_v1 = *(s32 *)(temp_v1 + (temp_v0 * 4));
            temp_v0 = FIELD(temp_a1, u16, 0x14);
            ASM_KEEP(copy_dst);
            temp_a0 = (u8 *)copy_dst + 8;
            FIELD(temp_a1, s32, 0xC) = temp_a2;
            temp_a2 = (s32)&D_80024420;
            FIELD(temp_a1, s8, 4) = 0;
            FIELD(temp_a1, s8, 5) = 0;
            temp_v0 |= 0x80;
            FIELD(temp_a1, u16, 0x14) = temp_v0;
            FIELD(temp_a1, s32, 8) = temp_v1;
            FIELD(copy_dst, void *, 0x50) = held_global;
            temp_a1 = FIELD(object, void *, 8);
            func_8008F074(temp_a0, temp_a1, (void *)temp_a2);
        }
        ASM_KEEP(source_arg);
        ASM_KEEP(record_arg);
    }
}

/* MECHANISM: The 0x28 frame follows from held s2/s3 arguments, the s4 global base,
   and the s1 copy base; scoped ABI roles reproduce the 16+8-byte copy groups.
   A late keep on immutable s1 forms a0=s1+8 directly and removes the +1 cascade. */
