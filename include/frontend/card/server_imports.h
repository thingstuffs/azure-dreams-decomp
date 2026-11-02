#ifndef FRONTEND_CARD_SERVER_IMPORTS_H
#define FRONTEND_CARD_SERVER_IMPORTS_H
/*
 * Calls made by the devkit memory-card server (MAIN +0x269000, linked at 0x80400000; its assertion strings name
 * the file c_server.c) to functions that have no readable name at that address yet.
 *
 * The 0x804xxxxx entries are server functions whose C is linked at the 0x8001xxxx placeholder of its row id, so
 * their readable names lower to the placeholder address; they keep their true-address spelling until the row is
 * promoted to its true base.  The 0x8005xxxx entries are not functions of the retail SLUS (both addresses are
 * inside other SLUS functions): the server was linked against a devkit build of the executable.
 */
#include "common.h"

/* devkit executable: set every entry of a row, then one entry (mode 1 / mode 0) */
void func_80051DE4(void *entries, s32 mode);
void func_800514A8(void *entry, s32 mode);
/* devkit executable: release one text word (the card UI's own build calls noop_release_notification here) */
void func_80051FBC(s32 value);

/* server functions at their true addresses */
void func_804038C8(void *record);
void func_804039F8(void *templates, void *primary, void *secondary);
void func_80403B7C(void *record, void *value);
void func_80404708(void *templates, void *primary, void *secondary);
void func_80404B10(void *record);
void func_80404C3C(void *record, void *value);
void func_80402974(void *templates, void *primary, void *secondary);
void func_80402D90(void *record);
void func_80403DA0(void *entity, void *primary, void *secondary, s32 slot_index);
void func_80404308(void *record, s32 setup_value, s32 processing_value);
void func_80402EA4(void *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);

#endif
