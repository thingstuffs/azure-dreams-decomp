#include "common.h"

typedef struct {
    u16 field0;
    u16 field2;
    u8 field4;
    u8 field5;
} Event6;

extern u8 D_800133C4;
extern u8 D_800133C8;
extern u8 D_800133E2;
extern void *D_80089600[];
extern Event6 D_800D1910[];
extern u8 D_800D2FB4[];
extern u8 D_800D3814[12];
extern u8 D_80126494[12];
extern u8 D_8012669C[12];
extern u8 D_80126884[12];
extern u8 D_80126A6C[12];
extern u8 D_80126C54[12];
extern u8 D_80126E3C[12];
extern u8 D_80127024[12];
extern u8 D_80127FA8[12];

void func_8009CDB4(void);
void func_8009CDCC(s32, s32, s32, s32, void *);
void func_8009CE34(void);
void func_800AC488(s32, s32, s32, s32);
void func_800B7978(s32, s32, s32, s32);
void func_800B7A6C(s32, s32, void *, s32);

void func_800B8E08(s32 arg0) {
    static void *const switch_keep[7] = {
        &&case_6, &&switch_done, &&case_8, &&case_9,
        &&switch_done, &&case_11, &&case_12
    };
    Event6 *event;
    register Event6 *event_base ASM_REG("$2");
    volatile u8 *state;
    register u8 *c4 ASM_REG("$16");
    s32 kind;
    s32 state0;
    register s32 kind_use ASM_REG("$16");
    u32 switch_index;

    func_8009CDB4();
    state = D_800D3814;
    if (state[6] != 0) {
        state0 = state[0];
        kind = D_800D2FB4[state[6] << 5];
        kind_use = kind;
        func_800B7978(state0, state[1], kind_use, arg0);
        if (kind_use == 0x26) {
            ASM_KEEP(kind_use);
            switch_index = D_800133E2 - 6;
            if (switch_index >= 7) {
                goto switch_done;
            }
            (void)switch_keep;
            goto *D_80089600[switch_index];

case_6:
            func_800B7A6C(0x2E, 0x24, D_8012669C, arg0);
            goto switch_done;
case_8:
            func_800B7A6C(0x2E, 0x24, D_80126884, arg0);
            goto switch_done;
case_9:
            func_800B7A6C(0x2E, 0x24, D_80126A6C, arg0);
            goto switch_done;
case_11:
            func_800B7A6C(0x2E, 0x24, D_80126C54, arg0);
            goto switch_done;
case_12:
            func_800B7A6C(0x2E, 0x24, D_80126E3C, arg0);
switch_done:
        {
            s32 c8_value;
            register u8 *c8_page ASM_REG("$3");

            c8_page = (u8 *)0x80010000;
            ASM_KEEP(c8_page);
            c8_value = c8_page[0x33C8];
            c4 = (u8 *)0x80010000;
            if (7 == c8_value) {
                func_800B7A6C(0x40, 0xC, D_80127024, arg0);
            }
            ASM_KEEP(c4);
            if (c4[0x33C4] == 5) {
                func_800B7A6C(0xE, 0xE, D_80126494, arg0);
            }
        }
        } else if (kind_use == 0x27) {
            s32 c4_value;
            register u8 *c4_page ASM_REG("$3");

            ASM_KEEP(kind_use);
            c4_page = (u8 *)0x80010000;
            ASM_KEEP(c4_page);
            c4_value = c4_page[0x33C4];
            if (5 == c4_value) {
                func_800B7A6C(0x38, 0xE, D_80127FA8, arg0);
            }
        }
        event_base = D_800D1910;
        event = kind + event_base;
        ASM_KEEP(event_base);
        if (event->field0 != 0) {
            func_800AC488(event->field0, event->field2,
                          event->field4, event->field5);
        }

        {
            register u8 *end_page ASM_REG("$2");
            register volatile u8 *end_state ASM_REG("$3");
            u8 *end_entry;
            s32 end_state0;
            s32 end_state1;
            s32 end_index;

            end_page = (u8 *)0x800D0000;
            ASM_KEEP(end_page);
            end_state = end_page + 0x3814;
            end_state0 = end_page[0x3814];
            end_state1 = end_state[1];
            end_index = end_state[6] << 5;
            end_entry = D_800D2FB4 + end_index;
            func_8009CDCC(end_state0, end_state1,
                          end_entry[4], end_entry[5],
                          D_800D2FB4 + end_index + 12);
        }
    }
    func_8009CE34();
}
