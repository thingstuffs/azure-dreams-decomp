#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define self arg0
#define coords arg1
#define source work
#define iteration work

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern u8 D_80024AE0;
extern u16 D_80024A70;
extern s32 D_800814A0;
extern void *D_800814A8;
extern s16 D_80083228;
extern void *D_800E3D18;

extern void func_80024410(void) __attribute__((noreturn));
extern void func_80024464(void) __attribute__((noreturn));
/* Ordinary declaration: the private selector authenticates this one
 * returning tail by qid/geometry/context instead of using an asm symbol alias. */
extern void func_800244DC(void);
extern void func_800246C4(void) __attribute__((noreturn));
extern void *func_80024924(void *, s32, s32, s32, void *, s32, s32, s32, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800644B8(s32);
extern void func_800B8D64(s16, s16, s16);


void func_8199AAD4(void *arg0, void *arg1)
{
    u16 delta[3];
    s32 target[3];
    register s32 start_x ASM_REG("$19");
    register s32 start_y ASM_REG("$20");
    register s32 start_z ASM_REG("$21");
    s16 state;
    register volatile void *work ASM_REG("$16");
    void *target_node;
    void *call_node;
    void *position;
    register void *entry_base ASM_REG("$3");
    register void *entry ASM_REG("$2");
    void *created;
    register u8 *table_end ASM_REG("$22");
    register u8 *table_start ASM_REG("$23");
    s32 index;
    s32 curve;
    s32 global_value;
    u16 count;
    u16 position_z;
    register u32 tail_z ASM_REG("$2");
    register s32 *global_flags ASM_REG("$4");
    register void *hit_out ASM_REG("$6");
    register s32 nine ASM_REG("$3");
    D_80024A70++;

    state = FIELD(self, s16, 0x28);
    if (state != 1) {
        if (state < 2) {
            if (state != 0) {
                func_800246C4();
            }
            goto state_zero;
        }

        ASM_KEEP(table_start);
        tail_z = 2;
        ASM_KEEP(tail_z);
        if (state == (s32)tail_z) {
            iteration = NULL;
            goto state_two;
        }
        func_800246C4();

state_zero:
            source = FIELD(FIELD(self, void *, 0), void *, 0xC);
            if ((FIELD(source, u16, 0x14) & 0x8000) ||
                func_8003DE58(FIELD(source, void *, 8), source, delta, 0)) {
                position = FIELD(FIELD(self, void *, 0), void *, 8);
                FIELD(coords, u16, 2) = FIELD(position, u16, 2);
                FIELD(coords, u16, 6) = FIELD(position, u16, 6);
                position_z = FIELD(position, u16, 0xA);
                FIELD(coords, u16, 0xA) = position_z;

                if (FIELD(source, u16, 0x14) & 0x8000) {
                    goto fixed_position;
                }
                FIELD(coords, u16, 2) += delta[0];
                FIELD(coords, u16, 6) += delta[1];
                ASM_KEEP(source);
                tail_z = FIELD(coords, u16, 0xA);
                tail_z += delta[2];
                ASM_TAILSLOT_PIN(tail_z);
                func_80024410();

fixed_position:
                ASM_KEEP(source);
                FIELD(coords, u16, 0xA) = position_z - 0x20;
            }

            if (FIELD(FIELD(self, void *, 0xC), u16, 0) & 0x80) {
                FIELD(self, volatile s16, 0x2E) = 8;
                tail_z = FIELD(self, volatile u16, 0x28);
                ASM_KEEP(tail_z);
                nine = 9;
                FIELD(self, s16, 0x30) = nine;
                func_80024464();
            }
            goto done;
    }

    count = FIELD(self, u16, 0x30) - 1;
    FIELD(self, u16, 0x30) = count;
    if ((s16)count > 0) {
        goto done;
    }
    FIELD(self, u16, 0x28)++;
    func_800246C4();

finish:
    FIELD(coords, s32, 0) = target[0];
    FIELD(coords, s32, 4) = target[1];
    FIELD(coords, s32, 8) = target[2];
    func_800B8D64(FIELD(coords, s16, 2), FIELD(coords, s16, 6),
                  FIELD(coords, s16, 0xA));
    tail_z = FIELD(self, u16, -2);
    ASM_KEEP(tail_z);
    global_flags = (s32 *)0x80080000;
    ASM_KEEP(global_flags);
    FIELD(self, u16, -2) = tail_z | 0x8000;
    count = FIELD(self, u16, 0x28);
    ASM_KEEP(count);
    global_value = FIELD(global_flags, s32, 0x14A0);
    count++;
    global_value |= 0x8000;
    ASM_KEEP(global_value);
    FIELD(self, u16, 0x28) = count;
    FIELD(global_flags, s32, 0x14A0) = global_value;
    func_800246C4();

state_two:
    ASM_KEEP(iteration);
    entry = (void *)0x80020000;
    ASM_KEEP(entry);
    table_end = (u8 *)entry + 0x4AE0;
    ASM_KEEP(table_end);
    table_start = table_end - 0x54;
    ASM_KEEP(table_start);
    entry = FIELD(self, void *, 4);
    start_x = FIELD(coords, s16, 2);
    start_y = FIELD(coords, s16, 6);
    target_node = FIELD(entry, void *, 8);
    ASM_KEEP(entry);
    start_z = FIELD(coords, s16, 0xA);
    target[0] = FIELD(target_node, s32, 0);
    target[1] = FIELD(target_node, s32, 4);
    target[2] = (FIELD(self, s16, 0x38) - 0x50) << 16;

    index = (D_80083228 + FIELD(D_800814A8, s16, 0x2A) + 0x100) >> 7;
    hit_out = delta;
    ASM_KEEP(hit_out);
    entry_base = D_800E3D18;
    ASM_KEEP(entry_base);
    index &= 0x1C;
    entry = (void *)(index + (s32)entry_base);
    ASM_KEEP(entry);
    call_node = FIELD(self, void *, 4);
    if (func_8003DE58(FIELD(entry, void *, 0), FIELD(call_node, void *, 0xC), hit_out, 0)) {
        target[0] += (s32)(s16)delta[0] << 16;
        target[1] += (s32)(s16)delta[1] << 16;
        target[2] += (s32)(s16)delta[2] << 16;
    }

    FIELD(coords, s32, 0) +=
        (target[0] - FIELD(coords, s32, 0)) / FIELD(self, s16, 0x2E);
    FIELD(coords, s32, 4) +=
        (target[1] - FIELD(coords, s32, 4)) / FIELD(self, s16, 0x2E);
    curve = func_800644B8(FIELD(self, s16, 0x2E) * 170);
    FIELD(coords, s32, 8) +=
        (target[2] - FIELD(coords, s32, 8)) / FIELD(self, s16, 0x2E) -
        (curve << 7);

    created = func_80024924(FIELD(self, void *, 8), start_x, start_y, start_z,
                            coords, FIELD(self, s32, 0x10), 4,
                            FIELD(self, s32, 0x14), iteration);
    if (created != NULL) {
        FIELD(self, void *, 8) = created;
        FIELD(self, s32, 0x14) = FIELD(created, s32, 8);
    }

    count = FIELD(self, u16, 0x2E) - 1;
    FIELD(self, u16, 0x2E) = count;
    if ((s16)count <= 0) {
        goto finish;
    }

    FIELD(self, u8 *, 0x10) += 0xC;
    if (FIELD(self, u8 *, 0x10) >= table_end) {
        FIELD(self, u8 *, 0x10) = table_start;
    }
    func_800244DC();
    iteration = (u8 *)iteration + 1;
    ASM_KEEP(iteration);

done:
    return;
}

/* MECHANISM: The census baseline holds the 0x68 sibling-local frame and retail saved-register set.
   Register pins encode the surviving bases and late call operands; residual work starts at word 120. */
