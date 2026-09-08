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

/* Draws the active town entry and its state-dependent overlays. */
void func_800B8E08(s32 draw_param) {
    static void *const case_labels[7] = {
        &&case_6, &&switch_done, &&case_8, &&case_9,
        &&switch_done, &&case_11, &&case_12
    };
    Event6 *event;
    Event6 *event_table;
    volatile u8 *draw_state;
    u8 *status_page;
    s32 entry_kind;
    s32 draw_x;
    register s32 draw_kind ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u32 overlay_index;

    func_8009CDB4();
    draw_state = D_800D3814;
    if (draw_state[6] != 0) {
        draw_x = draw_state[0];
        entry_kind = D_800D2FB4[draw_state[6] << 5];
        draw_kind = entry_kind;
        func_800B7978(draw_x, draw_state[1], draw_kind, draw_param);
        if (draw_kind == 0x26) {
            overlay_index = D_800133E2 - 6;
            if (overlay_index >= 7) {
                goto switch_done;
            }
            (void)case_labels;
            goto *D_80089600[overlay_index];

case_6:
            func_800B7A6C(0x2E, 0x24, D_8012669C, draw_param);
            goto switch_done;
case_8:
            func_800B7A6C(0x2E, 0x24, D_80126884, draw_param);
            goto switch_done;
case_9:
            func_800B7A6C(0x2E, 0x24, D_80126A6C, draw_param);
            goto switch_done;
case_11:
            func_800B7A6C(0x2E, 0x24, D_80126C54, draw_param);
            goto switch_done;
case_12:
            func_800B7A6C(0x2E, 0x24, D_80126E3C, draw_param);
switch_done:
            {
                s32 status_c8;
                register u8 *status_c8_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

                status_c8_page = (u8 *)0x80010000;
                status_c8 = status_c8_page[0x33C8];
                status_page = (u8 *)0x80010000;
                if (7 == status_c8) {
                    func_800B7A6C(0x40, 0xC, D_80127024, draw_param);
                }
                ASM_KEEP(status_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                if (status_page[0x33C4] == 5) {
                    func_800B7A6C(0xE, 0xE, D_80126494, draw_param);
                }
            }
        } else if (draw_kind == 0x27) {
            s32 status_c4;
            u8 *status_c4_page;

            status_c4_page = (u8 *)0x80010000;
            status_c4 = status_c4_page[0x33C4];
            if (5 == status_c4) {
                func_800B7A6C(0x38, 0xE, D_80127FA8, draw_param);
            }
        }
        event_table = D_800D1910;
        event = entry_kind + event_table;
        if (event->field0 != 0) {
            func_800AC488(event->field0, event->field2,
                          event->field4, event->field5);
        }

        {
            register u8 *draw_state_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            register volatile u8 *final_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            u8 *draw_entry;
            s32 final_x;
            s32 final_y;
            s32 entry_offset;

            draw_state_page = (u8 *)0x800D0000;
            ASM_KEEP(draw_state_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            final_state = draw_state_page + 0x3814;
            final_x = draw_state_page[0x3814];
            final_y = final_state[1];
            entry_offset = final_state[6] << 5;
            draw_entry = D_800D2FB4 + entry_offset;
            func_8009CDCC(final_x, final_y,
                          draw_entry[4], draw_entry[5],
                          D_800D2FB4 + entry_offset + 12);
        }
    }
    func_8009CE34();
}
