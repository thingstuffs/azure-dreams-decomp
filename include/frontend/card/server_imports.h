#ifndef FRONTEND_CARD_SERVER_IMPORTS_H
#define FRONTEND_CARD_SERVER_IMPORTS_H
/*
 * The devkit memory-card server (MAIN +0x269000-+0x275800, linked at 0x80400000; its assertion strings name the
 * file c_server.c) and its TOWN copy (+0x26E000-+0x272000, byte-identical at the same base): calls to functions
 * that have no readable name at that address, and the server's own library stubs.
 *
 * The 0x804xxxxx entries are server functions.  Their rows are linked at the true address (rowbase records,
 * tools/headers/rebase_placeholder_rows.py), so the address spelling names the same symbol as the readable name
 * in the comment; the callers keep the address spelling because include/frontend/card.h types those prototypes
 * with generated layouts the devkit callers do not use.  func_80404708 / func_80404308 are placed copies of other
 * homes (the readable name would lower to the home's address).  The 0x8003xxxx-0x8007xxxx entries are not
 * functions of the retail SLUS (mid-function or data): the server was linked against a devkit build of the
 * executable, so each is declared once here with its address spelling.
 *
 * foreign-program: main 0x269000-0x275800; town 0x26E000-0x272000
 */
#include "common.h"

/* devkit executable: set every entry of a row, then one entry (mode 1 / mode 0) */
void func_80051DE4(void *entries, s32 mode);
void func_800514A8(void *entry, s32 mode);
/* devkit executable: release one text word (the card UI's own build calls noop_release_notification here) */
void func_80051FBC(s32 value);

/* server functions at their true addresses */
void func_804038C8(void *record);   /* card_dev_init_row_panel */
void func_804039F8(void *templates, void *primary, void *secondary);
void func_80403B7C(void *record, void *value);   /* card_dev_set_word */
void func_80404708(void *templates, void *primary, void *secondary);
void func_80404B10(void *record);   /* card_background_init_components */
void func_80404C3C(void *record, void *value);   /* card_background_set_word */
void func_80402974(void *templates, void *primary, void *secondary);   /* card_dev_init_view_defaults */
void func_80402D90(void *record);   /* init_dialog_object */
void func_80403DA0(void *entity, void *primary, void *secondary, s32 slot_index);   /* card_dev_init_row_view */
void func_80404308(void *record, s32 setup_value, s32 processing_value);
void func_80402EA4(void *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);   /* set_layout_params */

/* --- imports (tools/headers/foreign_imports.py): one declaration per address --- */
void func_8003830C(s32, void *);
void *func_8003C480(s32);
void *func_8003C714(s32, void *, s32);
void func_8003D548(s32);
void func_8003FA78(void *, s32);
void func_8003FD58(s32, s32, s32, s32);
void func_80040560(void *, void *);
s32 func_80047358(s32, void *, s32);
s32 func_80047938(void *, s32, s32);
s32 func_80047FD8(void *);
s32 func_800484A4(s32, s32 *);
s16 func_8004DBDC(void);
s32 func_8004DCCC(s32);
void func_8004DDBC(void *, void *, void *);
s32 func_80051520(void *, s32 *, s32);
void func_80051804(s32, s32, s32 *);
void func_8005184C(s32, s32, void *);
void func_80051898(u32, void *);
void func_80051900(s32 *);
s32 func_80051B50(void *, s32, s32);
s32 func_80056450(s32, s32, u8);
s32 func_80056F14(s32);
s32 func_80058FF0(s32, s32, s32);
void func_800702F0(s32);
s16 func_80078570(s32, s32, s32, s32);
s16 func_80078640(s32, s32);
void func_8007BEF0(s32) __attribute__((noreturn));
void func_8007BF18(void *);
void func_8007BF50(void *, void *);
void func_8007BF80(void *, s32);
void func_8007BFE0(void *, s32);
void func_8007C040(void *, void *, s32);
s32 func_8007C958(void);
s32 func_8007C998(s32, s32, s32, void *);
s32 func_8007C9A8(s32);
s32 func_8007C9C8(s32);
s32 func_8007C9D8(s32);
void func_8007CA38(void);   /* devkit libapi stub, current EnterCriticalSection (0x8006A084, -0x129B4; 2 twin call pairs) */
void func_8007CA48(void);   /* devkit libapi stub, current ExitCriticalSection (0x8006A094, -0x129B4; 2 twin call pairs) */
s32 func_8007CA58(s32, s32);
s32 func_8007CA68(s32, s32, s32);
s32 func_8007CA78(s32, void *, s32);
s32 func_8007CA88(s32, void *, s32);
void func_8007CA98(s32);
void func_8007CAA8(s32);
s32 func_8007CAB8(void *, void *);
s32 func_8007CAC8(void *);
void func_8007CAD8(void *, void *);
void func_8007CAE8(void *);
void func_8007CB08(s32);   /* devkit libapi stub, current ChangeClearPAD (0x8006A154, -0x129B4; 2 twin call pairs) */
void func_80404618(void *, s32);
void func_80404888(s32);
/* the server's own libcard BIOS stubs (config/names.tsv: address-suffixed, the plain names are the SLUS stubs) */
s32 _card_status_80408644(s32);
void _card_wait_80408654(s32);
s32 _card_info_80408664(s32);
s32 _card_load_80408674(s32);
s32 _card_write_804086BC(s32, s32, s32);
void _new_card_804086CC(s32);
void func_804087C8(void);
void func_804088A0(void);
void func_80408958(void);
/* the server's libcard entries (assembler rows linked at their placeholder; callers jal the true address) */
void InitCARD2_80408798(s32);
void StartCARD2_804087A8(void);
void StopCARD2_804087B8(void);
/* --- end of imports --- */

#endif
