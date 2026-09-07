#include "common.h"

typedef struct S_818C2E40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C2E40_0;   /* node in func_818C2E40 */

typedef struct S_818C2E40_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s8 unk_0A;
} S_818C2E40_1;   /* fields in func_818C2E40 */

typedef struct S_818C2E40_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_818C2E40_2;   /* display in func_818C2E40 */



typedef struct {
    s32 word[6];
} Copy24;

extern void *func_8003FC64(s32 arg0);
extern void func_800246F4() __attribute__((noreturn));
extern void func_8004491C(void *arg0, void *arg1);
extern u8 D_800240C0[9];
extern u8 D_800241D4[9];

/* Allocate and initialize a node with the supplied value and 24 bytes of data. */
void *func_818C2E40(s32 node_value, void *initial_data)
{
    void *node;
    S_818C2E40_1 *fields;
    S_818C2E40_2 *display;
    void *node_data;

    node = func_8003FC64(0x212);
    {
        void *dispatch_arg = node;

        if (node == 0) {
            register void *dispatch_result ASM_REG("$2") = 0;   /* MATCH pin: retail delay-slot contents depend on it */

            ASM_KEEP(dispatch_arg);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_TAILSLOT_PIN(dispatch_result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800246F4(dispatch_arg);
        }
    }

    ((S_818C2E40_0 *)node)->unk_10 = D_800240C0;
    func_8004491C(node, D_800241D4);
    fields = (u8 *)node + 0x20;
    ((S_818C2E40_0 *)node)->unk_20 = node_value;
    fields->unk_04 = 0;
    fields->unk_06 = 0;
    fields->unk_08 = 0x7DCF;
    fields->unk_0A = 0;

    display = ((S_818C2E40_0 *)node)->unk_0C;
    display->unk_1E = 0x1000;
    display->unk_1C = 0x1000;

    node_data = ((S_818C2E40_0 *)node)->unk_08;
    *(Copy24 *)node_data = *(Copy24 *)initial_data;
    return node;
}

/* MECHANISM: The 0x20 frame follows from node/node_value/initial_data held in s0/s1/s2 and
   the 24-byte struct assignment emits retail's grouped six-word copy.
   A guarded a0 lifetime defeats null-edge CSE; ASM_TAILSLOT_PIN sinks v0=0
   into the converted noreturn j delay slot at 2.7.2-cdk-G0. */
