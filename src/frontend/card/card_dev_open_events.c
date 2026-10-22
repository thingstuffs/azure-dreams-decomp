#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern void func_8007BEF0(s32 value) __attribute__((noreturn));
extern void func_8007C040(void *ptr, void *ptr2, s32 value);
extern s32 func_8007C998(s32 value0, s32 value1, s32 value2, void *ptr);
extern s32 func_8007C9D8(s32 event_handle);
extern void func_8007CA38(void);
extern void func_8007CA48(void);

/* Opens and enables memory card events, asserting that each operation succeeds. */
void card_dev_open_events(s32 unused0, s32 unused1, s32 unused2, s32 unused3) {
    s32 event_handle;
    func_8007CA38();
    event_handle = func_8007C998(0xF4000001, 4, 0x2000, 0);
    *(s32 *)0x80409270 = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xB4);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF4000001, 0x8000, 0x2000, 0);
    *(s32 *)0x80409274 = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xB6);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF4000001, 0x100, 0x2000, 0);
    *(s32 *)0x80409278 = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xB8);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF4000001, 0x2000, 0x2000, 0);
    *(s32 *)0x8040927C = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xBA);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF0000011, 4, 0x1000, D_804009C0);
    *(s32 *)0x80409280 = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xBD);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF0000011, 0x8000, 0x1000, D_804009D4);
    *(s32 *)0x80409284 = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xBF);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF0000011, 0x100, 0x1000, D_804009E8);
    *(s32 *)0x80409288 = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xC1);
        func_8007BEF0(1);
    }
    event_handle = func_8007C998(0xF0000011, 0x2000, 0x1000, D_804009FC);
    *(s32 *)0x8040928C = event_handle;
    if (event_handle == -1) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xC3);
        func_8007BEF0(1);
    }
    func_8007CA48();
    if (func_8007C9D8(D_80409270[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xCF);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_80409274[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xD1);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_80409278[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xD3);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_8040927C[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xD5);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_80409280[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xD7);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_80409284[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xD9);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_80409288[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xDB);
        func_8007BEF0(1);
    }
    if (func_8007C9D8(D_8040928C[0]) == 0) {
        func_8007C040(card_server_assert_format, dev_server_filename, 0xDD);
        func_8007BEF0(1);
    }
}
