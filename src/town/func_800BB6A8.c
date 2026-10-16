#include "common.h"

typedef struct {
    u16 field0;
    u16 field2;
    u8 field4;
    u8 field5;
} Event6;

extern u8 D_800133E2;
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

void townInitializeSharedScriptData(void);
void townScaleCoordinatesAndAppendPointers(s32, s32, s32, s32, void *);
void func_8009CE34(void);
void townSetTextureQuad32Uv(s32, s32, s32, s32);
void townBlitIndexedOriginU16Block(s32, s32, s32, s32);
void townBlitOriginU16Block(s32, s32, void *, s32);

/* Draws the active town entry and its state-dependent overlays. */
void townInitializeBuildingSceneObjects(s32 draw_param) {
    Event6 *event;
    Event6 *event_table;
    u8 *draw_state;
    u8 *status_page;
    s32 entry_kind;
    s32 draw_x;
    s16 draw_kind;
    u32 overlay_index;

    townInitializeSharedScriptData();
    draw_state = D_800D3814;
    if (draw_state[6] != 0) {
        draw_x = draw_state[0];
        entry_kind = D_800D2FB4[draw_state[6] * 32];
        draw_kind = entry_kind;
        townBlitIndexedOriginU16Block(draw_x, draw_state[1], draw_kind, draw_param);
        if (draw_kind == 0x26) {
            overlay_index = D_800133E2 - 6;
            switch (overlay_index) {
            case 0:
                townBlitOriginU16Block(0x2E, 0x24, D_8012669C, draw_param);
                break;
            case 2:
                townBlitOriginU16Block(0x2E, 0x24, D_80126884, draw_param);
                break;
            case 3:
                townBlitOriginU16Block(0x2E, 0x24, D_80126A6C, draw_param);
                break;
            case 5:
                townBlitOriginU16Block(0x2E, 0x24, D_80126C54, draw_param);
                break;
            case 6:
                townBlitOriginU16Block(0x2E, 0x24, D_80126E3C, draw_param);
                break;
            }
            {
                s16 status_c8;
                u8 *status_c8_page;

                status_c8_page = (u8 *)0x80010000;
                status_c8 = status_c8_page[0x33C8];
                status_page = (u8 *)0x80010000;
                if (7 == status_c8) {
                    townBlitOriginU16Block(0x40, 0xC, D_80127024, draw_param);
                }
                if (status_page[0x33C4] == 5) {
                    townBlitOriginU16Block(0xE, 0xE, D_80126494, draw_param);
                }
            }
        } else if (draw_kind == 0x27) {
            s32 status_c4;
            u8 *status_c4_page;

            status_c4_page = (u8 *)0x80010000;
            status_c4 = status_c4_page[0x33C4];
            if (5 == status_c4) {
                townBlitOriginU16Block(0x38, 0xE, D_80127FA8, draw_param);
            }
        }
        event_table = D_800D1910;
        event = entry_kind + event_table;
        if (event->field0 != 0) {
            townSetTextureQuad32Uv(event->field0, event->field2,
                          event->field4, event->field5);
        }

        {
            u8 *draw_entry;
            s32 final_x;
            s32 final_y;
            s32 entry_offset;

            event = (Event6 *)D_800D3814;
            final_x = D_800D3814[0];
            final_y = ((u8 *)event)[1];
            entry_offset = ((u8 *)event)[6] << 5;
            draw_entry = D_800D2FB4 + entry_offset;
            townScaleCoordinatesAndAppendPointers(final_x, final_y,
                          draw_entry[4], draw_entry[5],
                          D_800D2FB4 + entry_offset + 12);
        }
    }
    func_8009CE34();
}
