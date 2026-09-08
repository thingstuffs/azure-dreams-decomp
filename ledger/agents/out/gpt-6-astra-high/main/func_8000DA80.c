#include "common.h"

extern int func_8006A084();
extern int OpenEvent();
extern void printf();
extern void exit();
extern void func_8006A094();
extern int EnableEvent();

extern int D_80020000[];
extern int D_80020028[];
extern int D_80020A30[];
extern int D_80020A44[];
extern int D_80020A58[];
extern int D_80020A6C[];

extern int D_80028550[];
extern int D_80028554[];
extern int D_80028558[];
extern int D_8002855C[];
extern int D_80028560[];
extern int D_80028564[];
extern int D_80028568[];
extern int D_8002856C[];

/* Opens and enables memory card events, exiting if any setup step fails. */
void func_80020A80(void) {
    int card_done_event;
    int card_error_event;
    int card_timeout_event;
    int card_new_event;
    int hw_done_event;
    int hw_error_event;
    int hw_timeout_event;
    int hw_new_event;

    func_8006A084();
    card_done_event = OpenEvent(0xF4000001, 4, 0x2000, 0);
    D_80028550[0] = card_done_event;
    if (card_done_event == -1) {
        printf(&D_80020000, &D_80020028, 0xB9);
        exit(1);
    }
    card_error_event = OpenEvent(0xF4000001, 0x8000, 0x2000, 0);
    D_80028554[0] = card_error_event;
    if (card_error_event == -1) {
        printf(&D_80020000, &D_80020028, 0xBB);
        exit(1);
    }
    card_timeout_event = OpenEvent(0xF4000001, 0x100, 0x2000, 0);
    D_80028558[0] = card_timeout_event;
    if (card_timeout_event == -1) {
        printf(&D_80020000, &D_80020028, 0xBD);
        exit(1);
    }
    card_new_event = OpenEvent(0xF4000001, 0x2000, 0x2000, 0);
    D_8002855C[0] = card_new_event;
    if (card_new_event == -1) {
        printf(&D_80020000, &D_80020028, 0xBF);
        exit(1);
    }
    hw_done_event = OpenEvent(0xF0000011, 4, 0x1000, &D_80020A30);
    D_80028560[0] = hw_done_event;
    if (hw_done_event == -1) {
        printf(&D_80020000, &D_80020028, 0xC2);
        exit(1);
    }
    hw_error_event = OpenEvent(0xF0000011, 0x8000, 0x1000, &D_80020A44);
    D_80028564[0] = hw_error_event;
    if (hw_error_event == -1) {
        printf(&D_80020000, &D_80020028, 0xC4);
        exit(1);
    }
    hw_timeout_event = OpenEvent(0xF0000011, 0x100, 0x1000, &D_80020A58);
    D_80028568[0] = hw_timeout_event;
    if (hw_timeout_event == -1) {
        printf(&D_80020000, &D_80020028, 0xC6);
        exit(1);
    }
    hw_new_event = OpenEvent(0xF0000011, 0x2000, 0x1000, &D_80020A6C);
    D_8002856C[0] = hw_new_event;
    if (hw_new_event == -1) {
        printf(&D_80020000, &D_80020028, 0xC8);
        exit(1);
    }
    func_8006A094();
    if (EnableEvent(D_80028550[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xD4);
        exit(1);
    }
    if (EnableEvent(D_80028554[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xD6);
        exit(1);
    }
    if (EnableEvent(D_80028558[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xD8);
        exit(1);
    }
    if (EnableEvent(D_8002855C[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xDA);
        exit(1);
    }
    if (EnableEvent(D_80028560[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xDC);
        exit(1);
    }
    if (EnableEvent(D_80028564[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xDE);
        exit(1);
    }
    if (EnableEvent(D_80028568[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xE0);
        exit(1);
    }
    if (EnableEvent(D_8002856C[0]) == 0) {
        printf(&D_80020000, &D_80020028, 0xE2);
        exit(1);
    }
}
