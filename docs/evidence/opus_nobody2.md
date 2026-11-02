# opus_nobody2 evidence (2026-11-02)

## Devkit card server: four more missing functions recovered

The MAIN devkit memory-card server (file 0x269000..0x275800, linked at 0x80400000) held four more function
starts with no C row (tools/codemap/target_census.py class MISSING).  Each is recovered as C that compiles to the
retail bytes at gcc 2.7.2 -G0 (2.6.3 gives the same bytes), relocation fields aside, and is registered as its own
home at its true address in config/link/main/ll34_269000_80400000.json:

| entry | file off | bytes | function | counterpart in the card UI | caller |
| --- | --- | ---: | --- | --- | --- |
| 0x804008A0 | 0x2698A0 | 104 | set_card_selection_state | sibling of reset_ / toggle_card_selection_state | card_devkit_poll_stable_slot_state, card_boot_handle_menu_selection_input |
| 0x80406F70 | 0x26FF70 | 172 | card_dev_build_load_slot_windows | card_devkit_build_save_slot_windows | card_dev_create_load_screen |
| 0x804070C4 | 0x2700C4 | 156 | card_dev_release_load_screen_parts | release_card_screen_parts | handle_menu_selection_input |
| 0x804075D0 | 0x2705D0 | 184 | card_dev_init_slot_entry_tables | card_background_init_entry_tables | init_card_slot_object |

Notes: the server's own extra-name equates and dual-symbol read-modify-write views of the counterparts are not
needed (plain array and scalar accesses give the retail macro expansions); the load-screen builder reaches its
node header through NODE_HEADER() (include/shared/object_node.h); the remaining TOWN devkit function at
0x80700188 still needs a registered load view.

## Devkit card server library names (owner ruling 11-02)

The server's BIOS stubs (B(5Ch) _card_status, B(5Dh) _card_wait, A(ABh) _card_info, A(ACh) _card_load,
B(4Eh) _card_write, B(50h) _new_card at 0x80408644..0x804086CC; li t2,0xA0/0xB0; jr t2; li t1,n) and its libcard
entries InitCARD2 / StartCARD2 / StopCARD2 (assembler rows main/func_80021798..B8, linked at their placeholder)
get address-suffixed names in config/names.tsv (`_card_status_80408644`, `InitCARD2_80408798`, ...): the plain
names are the retail SLUS entries.  They lower to the same func_<address> symbols, so the calls keep their bytes.

## Rows at their true address

Eight more placeholder-linked server rows (card_dev_init_view_defaults, init_dialog_object, set_layout_params,
card_dev_init_row_panel, card_dev_set_word, card_dev_init_row_view, card_background_init_components,
card_background_set_word) link at their true address (tools/headers/rebase_placeholder_rows.py rowbase records).
invoke_callback_with_zero (main/func_8001EAB4) stays at its placeholder: its source is also the TOWN native module
town_ovl_2da5e4, whose member links the same readable name at the real TOWN address 0x8001EAB4, so one readable
name cannot name both; its devkit callers keep the address spelling func_80405AB4.

## Foreign-program import headers (owner ruling 11-02)

Code linked against another build declares its imports once per program: include/frontend/card/server_imports.h
(MAIN card server and its TOWN copy), include/town/devkit/old_minigame_imports.h, include/town/devkit/
flag_test_imports.h, include/dungeon/stale_bank_imports.h, include/dungeon/effect/head_bank_imports.h.  Prototypes
were decided by probing every declaration site at its production recipe (tools/headers/foreign_imports.py);
sites no single prototype fits are recorded in ledger/prototype_floors.jsonl (floor_class foreign_import_spelling).
The stale-bank imports name their current-engine counterparts by twin alignment (tools/headers/foreign_twins.py).
