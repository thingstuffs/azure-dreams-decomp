# Event scripts: dialogue, choices and story logic

Azure Dreams runs its town dialogue, events, shop counters, choices and much of its story logic
through a small byte-code interpreter in the resident executable, driven by compiled C modules that
are loaded per town scene. This guide describes both layers from the decompiled source: how a script
is laid out, how the interpreter runs it, every opcode, the numbered calls into game code, how a
typical event is built, what the shipped game never uses, and the original bugs worth knowing about.

Retail-use statements come from a decode of every script the US game loads: the 58 event files of
TOWN.BIN that the scene loader can load (434,800 bytes; 1,499 of their 1,500 in-file script
addresses land on decoded instruction starts), plus the text-bearing scripts in the resident
executable and the DUNGEON overlays. "Common" means more than 100 uses, "rare" means a handful.

- [1. Two layers](#1-two-layers)
- [2. Byte format](#2-byte-format)
- [3. How the interpreter runs](#3-how-the-interpreter-runs)
- [4. Opcode reference](#4-opcode-reference)
- [5. Call numbers, system variables and flags](#5-call-numbers-system-variables-and-flags)
- [6. The compiled scene modules](#6-the-compiled-scene-modules)
- [7. How an event is built](#7-how-an-event-is-built)
- [8. What the shipped game does not use](#8-what-the-shipped-game-does-not-use)
- [9. Original-game quirks](#9-original-game-quirks)
- [10. Notes for editing scripts](#10-notes-for-editing-scripts)
- [11. Source index](#11-source-index)

## 1. Two layers

**Compiled scene modules.** TOWN.BIN holds 54 event modules, one per town scene or location. Each is
MIPS code compiled from C, with a 0x20-byte header (magic word `0x4C070707`), and every module loads
at `0x80016000`. A module sets up its scene: people, doors, cameras, the shop counter, which event
runs when the player talks to someone. Modules call town functions **by number** through one shared
call table (section 5). The list of modules, their file offsets and entry points is in
[`town_script_modules.json`](../evidence/town_script_modules.json).

**The byte-code interpreter.** Dialogue and the logic around it (which line to say, menus, flag
checks, money checks, camera moves between lines) are byte-code scripts run by the interpreter in the
resident executable, [`interpret_script_opcodes_until_action_changes`](../../src/slus/konami_runtime_w_80038AB8.c),
through an 89-slot handler table at `0x8006AA90`. The opcode numbers and handler names are the
[`enum ScriptOpcode`](../../include/engine/script.h); the handlers are in
[`src/engine/script/`](../../src/engine/script/) and [`src/engine/script/vm/`](../../src/engine/script/vm/).

**Where scripts live.** Most scripts sit in *event files* inside TOWN.BIN: 0x800-aligned subfiles
whose first word is a block number and whose scripts start at offset 4. A scene loads one or more
event files into a fixed area of RAM (for example `0x8001DCD0` for the first town module); which
file is loaded depends on the scene and, in some scenes, on the event in progress. A few scripts are
resident in the executable (the gift-giving response, for one) or come with DUNGEON overlays. The scene module knows the entry
addresses: it keeps tables of script addresses (one per person or event) and hands one to the
interpreter when the event starts.

Script addresses are **absolute RAM addresses**. A script only works at the address it was built for.

## 2. Byte format

The interpreter reads a stream of bytes. What a byte means depends only on its value:

| Byte | Meaning |
| --- | --- |
| `0x01`-`0x58` | Opcode. The handler reads its own operands from the bytes that follow. |
| `0x81`-`0x9F`, `0xE0`-`0xFC` | Lead byte of a two-byte Shift-JIS glyph; the glyph is drawn in the message window. |
| `0xFD n` | Print variable `vn` as a decimal number. |
| `0xFE n` | Insert message string `n`. `0xFE 0x00` is the hero's name (inferred from context; 541 uses in the English scripts); `0xFE 0x01`, a second name, occurs twice. |
| `0xFF a0 a1 a2 a3` | Insert the string at the 32-bit address `a`. |
| `0x00` | Text return: ends an inserted string and pops back to the byte after the insertion. |

The rule in the interpreter is simple: a byte that is positive as a signed 8-bit value (1-127) is an
opcode; anything else (0 or 128-255) goes to the text path. Opcodes above `0x58` are never emitted
(they would index past the handler table). Shipped English text uses Shift-JIS lead bytes almost
exclusively; a decode of every English script finds only five other bytes in text position.

- **Text.** Even the US build stores its English as fullwidth Shift-JIS, two bytes per Latin letter
  (`Ａ` is `82 60`). The font maps the fullwidth forms to an 8-pixel-wide ASCII font, so a message
  line holds about 31 characters; the shipped US text piles up at 30-31 characters per line and
  almost never exceeds it.
- **Operands** are little-endian and unaligned. 16-bit values (`u16`, `flag16`) are two bytes,
  addresses and constants (`addr32`, `imm32`, `data32`, `func32`) four. A `var` operand is one byte,
  the number of a variable.
- **Choice tables.** `0x1A` (`script_jump_by_choice`) is followed by an inline table of 32-bit
  addresses, one per option of the menu just before it (`0x19`, `0x2A` or `0x2C`). A disassembler
  must remember the option count of the last menu to know the table length.
- **Page start.** `0x57` (`script_page_break`) takes one byte, but the byte is read only after the
  dispatcher has stopped and the voice channel is free (section 3).
- **Script ends.** A script ends at `0x01` (end of message), `0x16` (return), `0x17` (jump),
  `0x1A` (jump by answer) or `0x48` (jump to a variable). Units in an event file are packed one after
  another, sometimes with 1-3 pad bytes before a 4-aligned start.

A typical line of dialogue, as bytes:

```
0F 0B 03     actor 11: motion 3 (face the player, start talking)
57 0B        page start, speaker 11
82 67 82 89  "Hi" (fullwidth Shift-JIS)
0A           new line
...          more text
11           wait for a button
08           clear the window
01           end of message
```

## 3. How the interpreter runs

**State.** Game code hands a script to the script controller `runtime_script_state`
(`0x80082A38`). Every handler receives the running script's context, which it reads at these offsets:

| Offset | Field |
| --- | --- |
| `+0x10` | Current action: the dispatcher, or a waiting handler installed by an opcode |
| `+0x1C` | Cursor: address of the next byte |
| `+0x27` | Answer of the last choice menu, counted from 0 |
| `+0x28` | Text speed |
| `+0x2E` | Message state (2 = instant text) |
| `+0x7C` | Call stack pointer for `0x15` / `0x16` and text insertions |
| `+0x80` | Pointer to the variable block |
| `+0x88` | Loop counter for `0x54` / `0x55` |

The variable block that `+0x80` points to holds the pointer to the call table (`+0x40`), the pointer
to the system-variable table (`+0x44`) and sixteen 32-bit variables `v0`-`v15` (`+0x48` to `+0x84`).

- `v0`-`v3` are the arguments of every numbered or native call (`0x2E`, `0x25`, `0x2F`, `0x4C`).
- `v15` receives every call's return value and the result of `0x3D` (compare).
- Scripts use the others freely. Variables are signed 32-bit words; the six conditional jumps
  compare one variable with zero.

**Starting a script.** Game code starts a script with
[`start_script`](../../src/engine/script/start_script.c) (mode 1),
[`call_script`](../../src/engine/script/call_script.c) (mode 2) or
[`set_script_address`](../../src/engine/script/set_script_address.c) (mode 0). All three go through
`prepare_script_controller_and_set_cursor`, which sets up the message window for the requested mode
and points the cursor at the script.

**Dispatch.** Each frame, the interpreter loops: read the byte at the cursor, advance the cursor, call
`script_opcode_handlers[byte]`. It keeps going while the next byte is an opcode *and* the handler left
the dispatcher installed as the current action. An opcode that has to wait (a button press, a number
of frames, an actor, the sound driver, a menu answer) installs its own action instead; the loop stops,
and that action runs once per frame until it hands control back. When the next byte is text, the
text path draws glyphs at the current text speed (or all at once in instant mode).

`0x57` works through the same mechanism: its handler installs a terminator action and steps the
cursor back. The dispatcher then skips forward and installs a wait handler that, once the voice
channel is free, plays the page sound chosen by the byte after `0x57`, consumes the byte and pauses
five frames before the text starts.

**Flags** are bits in a resident bitmap. The script opcodes take the developer's own flag numbers,
the same `F_*` values the compiled modules test, so the names in
[`script_symbols.h`](../../include/script_symbols.h) apply directly (`F_*`, `Fr_*` scene progress,
`Ft_*` talked-to, `Fp_*`, `Ftt_*` and so on).

## 4. Opcode reference

Names are the handler names from [`script.h`](../../include/engine/script.h) (drop `script_` for a
mnemonic). Operands are listed in script order.

### Text and the message window

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x01` | `script_end_message` | - | End of message: unless the dispatch mode is 2, wait for the voice channel and play sound 0xC4; then park the window. The script ends here. | common |
| `0x08` | `script_clear_text_window` | - | Clear the text window and put the cursor back at the top left. | common |
| `0x09` | `script_set_text_speed` | u8 | Text speed: delay between glyphs. | used |
| `0x0A` | `script_new_line` | - | New line; scrolls when the window is full. | common |
| `0x0B` | `script_instant_text` | - | Instant text: the rest of the page is drawn at once (used for menu option lines). | common |
| `0x11` | `script_wait_button` | - | Wait for a button press. | common |
| `0x57` | `script_page_break` | u8 | Page start. The dispatcher stops, waits while the voice channel is busy, then uses the byte as a sound mode: 0 silent, 1 sound 0xB4, anything else sound 0x74 and wait until it finishes; the byte is consumed and a 5-frame pause follows. In shipped scripts the byte is the speaker of the page (see below). | common |

### Flow control

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x15` | `script_call` | addr32 | Call a script subroutine: push the return address, jump. | common |
| `0x16` | `script_return` | - | Return from a subroutine (pops the return address). | common |
| `0x17` | `script_jump` | addr32 | Jump. | common |
| `0x48` | `script_jump_to_variable` | var | Jump to the script address held in a variable. | used |
| `0x4B` | `script_call_variable` | var | Call the script address held in a variable. | used |
| `0x23` | `script_park` | - | Park: install an idle action and stop; game code resumes or replaces the script. | used |
| `0x30` | `script_yield` | - | Yield: stop for this frame, continue on the next. | common |
| `0x12` | `script_wait_frames` | u16 | Wait N frames. | used |
| `0x54` | `script_set_loop_counter` | u8 | Set the loop counter. | used |
| `0x55` | `script_wait_loop_counter` | - | Repeat this byte while the decremented loop counter stays >= 0. With 0x54 n it waits n+1 frames. | used |

### Event flags

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x0C` | `script_set_flag` | flag16 | Set an event flag. | common |
| `0x0D` | `script_clear_flag` | flag16 | Clear an event flag. | used |
| `0x18` | `script_jump_if_flag_set` | flag16, addr32 | If the flag is set, jump. | used |
| `0x2B` | `script_jump_if_flag_clear` | flag16, addr32 | If the flag is clear, jump. | used |
| `0x13` | `script_wait_flag_set` | flag16 | Wait until the flag is set. | used |

### Variables and arithmetic

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x31` | `script_clear_variable` | var | v = 0. | rare |
| `0x32` | `script_fill_variables` | u8 | Fill v0..v15 with the byte. | unused |
| `0x33` | `script_copy_variable_a` | var dst, var src | dst = src. | used |
| `0x44` | `script_copy_variable_b` | var dst, var src | dst = src (second copy of 0x33). | unused |
| `0x37` | `script_copy_variable_reversed` | var src, var dst | dst = src (0x33 with the operands swapped). | unused |
| `0x34` | `script_set_variable_a` | var, imm32 | v = constant. Also used to load a script address for 0x48 / 0x4B. | common |
| `0x45` | `script_set_variable_b` | var, imm32 | v = constant (second copy of 0x34). | rare |
| `0x3B` | `script_add` | var a, var b | a = a + b. | used |
| `0x3C` | `script_subtract` | var a, var b | a = a - b. | used |
| `0x49` | `script_multiply` | var a, var b | a = a * b. | unused |
| `0x4A` | `script_divide` | var a, var b | a = a / b. | unused |

### Compare and branch

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x3D` | `script_compare` | var a, var b | Compare: v15 = a - b. | rare |
| `0x3E` | `script_jump_if_zero` | var, addr32 | If v == 0, jump. | used |
| `0x3F` | `script_jump_if_nonzero` | var, addr32 | If v != 0, jump. | used |
| `0x40` | `script_jump_if_nonpositive` | var, addr32 | If v <= 0, jump. | rare |
| `0x41` | `script_jump_if_negative` | var, addr32 | If v < 0, jump. | rare |
| `0x42` | `script_jump_if_nonnegative` | var, addr32 | If v >= 0, jump. | used |
| `0x43` | `script_jump_if_positive` | var, addr32 | If v > 0, jump. | rare |

### System variables and memory

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x35` | `script_load_system_variable` | var, u8 index | Load a system variable: v = *table[index] (the variable table, see below; index 21 = money). | rare |
| `0x39` | `script_store_system_variable` | var, u8 index | Store a system variable: *table[index] = v. | rare |
| `0x36` | `script_load_table_word_a` | var, u8 i, data32 | v = word i of the table at data32. | rare |
| `0x46` | `script_load_table_word_b` | var, u8 i, data32 | Second copy of 0x36. | rare |
| `0x47` | `script_load_table_word_by_variable` | var, var i, data32 | v = word [vi] of the table at data32. | rare |
| `0x3A` | `script_store_table_word` | var, u8 i, data32 | Word i of the table at data32 = v. | rare |
| `0x4D` | `script_load_indirect` | var, u8 i, data32 | v = *(pointer i of the table at data32). | unused |
| `0x4F` | `script_load_indirect_by_variable` | var, var i, data32 | v = *(pointer [vi] of the table at data32). | unused |
| `0x4E` | `script_store_indirect` | var, u8 i, data32 | Meant as *(pointer i) = v; see the quirks section. | unused |
| `0x50` | `script_store_indirect_by_variable` | var, var i, data32 | Meant as *(pointer [vi]) = v; see the quirks section. | unused |

### Choice menus

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x19` | `script_choice_menu` | u8 n | Choice menu with n options (the option lines are the text just before it). The answer, counted from 0, is kept for 0x1A. | common |
| `0x2A` | `script_timed_choice_menu` | u8 n | Timed choice menu with n options. | rare |
| `0x2C` | `script_wide_choice_menu` | u8 n | Wide choice menu with n options. | used |
| `0x1A` | `script_jump_by_choice` | n x addr32 | Jump by answer: an inline table of n addresses follows the opcode, n taken from the menu before it. | common |

### Calls into game code

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x2E` | `script_call_service` | call# | Call service number n with v0..v3 as arguments; the return value goes to v15. | common |
| `0x25` | `script_poll_service` | call# | Poll service number n every frame (with v0..v3) until it returns nonzero; result in v15. | unused |
| `0x2F` | `script_call_service_from_table` | call#, data32 | Call entry n of a function table whose pointer is stored at data32; result in v15. | unused |
| `0x26` | `script_call_indexed_handler` | u8 | Call entry n of a resident handler table, then resume the message window. | unused |
| `0x27` | `script_poll_group_handler` | u8 group, u8 entry | Poll handler [group][entry] until it returns nonzero. | unused |
| `0x4C` | `script_call_native` | func32 | Call the native function at the given address with v0..v3; result in v15. | common |

### Actors and staging

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x0F` | `script_set_actor_motion` | u8 actor, u8 motion | Set an actor's motion or expression; waits while the actor is busy. Actor 0 takes no motion byte. | common |
| `0x24` | `script_wait_actor_ready` | u8 actor | Wait until the actor is ready. | common |

### Sound and voice

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x1C` | `script_set_sound_entry_byte` | u8 key, u8 value | Set byte 2 of the sound-table entry for key. | common |
| `0x53` | `script_set_sound_entry_bytes` | u8 key, u8 value | Set bytes 2 and 3 of the sound-table entry for key. | used |
| `0x1E` | `script_sound_command` | u16 | Send a sound command to the sound driver (SD_Call). | used |
| `0x1D` | `script_play_voice_cue` | imm32, imm32 | Play a voice / CD audio cue (two words), then sound command 0x300; waits while sound is busy. | rare |
| `0x06` | `script_wait_voice_then_advance` | - | Wait for the voice channel, then continue the message. | unused |
| `0x56` | `script_wait_sound_idle` | - | Wait while the sound status is busy. | unused |

### No-ops and odd slots

| Op | Name | Operands | What it does | Retail |
| --- | --- | --- | --- | --- |
| `0x00` | `script_nop` | - | Never dispatched: a 0x00 byte is the text return (see the byte format). | not an opcode |
| `0x02` | `script_nop_02` | - | No-op. | unused |
| `0x03` | `script_nop_03` | - | No-op. | unused |
| `0x04` | `script_nop_04` | - | No-op. | unused |
| `0x07` | `script_nop` | - | No-op (shared function). | used |
| `0x0E` | `script_nop_0e` | - | No-op. | unused |
| `0x10` | `script_nop_10` | - | No-op. | rare |
| `0x14` | `script_nop_14` | - | No-op. | unused |
| `0x1B` | `script_nop_1b` | - | No-op. | unused |
| `0x1F` | `script_nop_1f` | - | No-op. | unused |
| `0x20` | `script_nop_20` | - | No-op. | unused |
| `0x21` | `script_nop_21` | - | No-op. | unused |
| `0x22` | `script_nop_22` | - | No-op. | unused |
| `0x28` | `script_nop` | - | No-op (shared function). | unused |
| `0x29` | `script_nop` | - | No-op (shared function). | unused |
| `0x2D` | `script_nop_2d` | - | No-op. | unused |
| `0x51` | `script_nop` | - | No-op (shared function). | unused |
| `0x52` | `script_nop` | - | No-op (shared function). | unused |
| `0x05` | `script_set_block_byte_3d` | u8 | Store the byte at offset 0x3D of the VM block. | unused |
| `0x38` | `script_skip_byte` | u8 | Skip one byte. | unused |
| `0x58` | `dispatch_town_transition` | - | Slot 88 holds dispatch_town_transition, which game code also calls directly; most likely the word after the real table, not an opcode. | not an opcode |

**The byte after `0x57`.** In the shipped scripts this byte is the speaker of the page. When a `0x0F`
actor command precedes the page, the two numbers usually agree, and `n - 1` indexes the 6-character
speaker-name table at `0x8006AC60` (0 = no speaker; 1 = the player, used for choice prompts; then
Kewne, Guy and the rest of the cast). The interpreter code traced so far uses the byte only as the
page-sound mode, which gives the observed pattern: narration pages are silent, the player's prompts
use sound `0xB4`, other speakers use `0x74`. Where the name tab picks the byte up is not traced yet.

## 5. Call numbers, system variables and flags

### The call table

The game has **one** table of numbered calls, 213 entries at `0x800D3CC8` in the town engine.
**Number `n` selects entry `n`.** The compiled modules reach it through the town state that the town
engine publishes at `0x80016000` (`field20` of that state), and the byte-code interpreter gets the
same table pointer in its variable block, so `0x2E`, `0x25` and `0x2F` use the same numbering as the
modules. Ranges:

| Numbers | Contents |
| --- | --- |
| 0-34 | `S_*` system calls (shops, warehouse, town map, building, flags, CD) |
| 35-99 | One shared empty stub: a developer-console band. Only `S_printf` (90) and `S_exit` (93) are called, by the modules' assert macro; `S_sprintf` (91) and `S_getchar` (92) are named but never called. |
| 100-212 | `FNO_*` function numbers (cameras, person positions, name windows, minigames, map changes) |

Two `S_` entries, `S_NULL1` (6) and `S_NULL2` (16), are NULL words. The numbering was settled in the
[call-table investigation](../evidence/script_call_table_20260908.md); read its 2026-09-28 correction
first, because the older text below it uses numbers one too low.

The `S_` calls:

| No. | Name | No. | Name |
| --- | --- | --- | --- |
| 0 | `S_open_buy_dougu` | 20 | `S_get_item_buy_money` |
| 1 | `S_open_sell_dougu` | 21 | `S_rand_sn` |
| 2 | `S_open_buy_buki` | 22 | `S_flgtst` |
| 3 | `S_open_sell_buki` | 23 | `S_f_LandBuildingNo` |
| 4 | `S_open_buy_mamono` | 24 | `S_open_twin_souko` |
| 5 | `S_open_sell_mamono` | 25 | `S_Control_CD` |
| 6 | `S_NULL1` | 26 | `S_open_shop` |
| 7 | `S_open_sell_mama` | 27 | `S_get_item_sell_money` |
| 8 | `S_open_buy_daiku` | 28 | `S_CheckBuildBuildingLand` |
| 9 | `S_close_twin_shop` | 29 | `S_plt_carry_on_chk_ext` |
| 10 | `S_active_twin_shop` | 30 | `S_plt_carry_item_del_ext` |
| 11 | `S_sleep_twin_shop` | 31 | `S_itm_mon_koyaw_set` |
| 12 | `S_store_twin_shop` | 32 | `S_load_bin_nametwin` |
| 13 | `S_openbox_twin_shop` | 33 | `S_set_no_change_seq` |
| 14 | `S_closebox_twin_shop` | 34 | `S_mascot_anime_chg` |
| 15 | `S_town_map_set` | 90 | `S_printf` |
| 16 | `S_NULL2` | 91 | `S_sprintf` |
| 17 | `S_town_map_del` | 92 | `S_getchar` |
| 18 | `S_CheckBuildBuildingLandNo` | 93 | `S_exit` |
| 19 | `S_BuildLandBuilding` |  |  |

Numbers the byte-code scripts call with `0x2E` (US, reached scripts):

| No. | Name | Sites |
| --- | --- | --- |
| 17 | `S_town_map_del` | 2 |
| 30 | `S_plt_carry_item_del_ext` | 1 |
| 101 | `FNO_start_mogura_func` | 1 |
| 102 | `FNO_start_tako_func` | 1 |
| 103 | `FNO_func_koya_tamago_pal_ld` | 1 |
| 104 | `FNO_func_koya_mon_talk_pal_ld` | 1 |
| 105 | `FNO_ext_plsel_hold_item_set` | 2 |
| 106 | `FNO_ext_plsel_kaesu_set` | 1 |
| 107 | `FNO_koya_mon_status_open` | 2 |
| 108 | `FNO_koya_mon_status_close` | 3 |
| 109 | `FNO_koya_mon_namewin_open` | 1 |
| 110 | `FNO_koya_mon_namewin_closechk` | 1 |
| 112 | `FNO_mcard_func_set` | 3 |
| 113 | `FNO_mcard_end_check` | 3 |
| 120 | `FNO_get_item_chk` | 4 |
| 121 | `FNO_mam_bita_give` | 4 |
| 123 | `FNO_start_keima_func` | 1 |
| 126 | `FNO_sn_namewin_open` | 1 |
| 127 | `FNO_sn_namewin_close_check` | 1 |
| 128 | `FNO_change_map_of` | 5 |
| 129 | `FNO_func_sn_ball` | 1 |
| 130 | `FNO_tcame_chase_set` | 14 |
| 131 | `FNO_tcame_chase2_set` | 22 |
| 132 | `FNO_tcame_lock` | 22 |
| 133 | `FNO_tcame_return` | 25 |
| 134 | `FNO_change_map` | 2 |
| 139 | `FNO_baken_uriba` | 1 |
| 144 | `FNO_town_sd_sq_callagain` | 10 |
| 145 | `FNO_player_now_ang_get` | 7 |
| 146 | `FNO_player_now_pos_get` | 40 |
| 148 | `FNO_anyone_org_pos_get` | 11 |
| 149 | `FNO_anyone_now_ang_get` | 10 |
| 150 | `FNO_anyone_now_pos_get` | 61 |
| 157 | `FNO_event_pool_clean_in` | 1 |
| 161 | `FNO_zukan_func_set` | 1 |
| 162 | `FNO_zukan_end_check` | 1 |
| 165 | `FNO_t_soukowin_open` | 3 |
| 166 | `FNO_t_soukowin_close_check` | 3 |
| 173 | `FNO_washed_dish_suu_inc` | 5 |
| 174 | `FNO_into_dn_door_demo_set` | 1 |
| 175 | `FNO_obj_disp23_cancel_sw_set` | 3 |
| 186 | `FNO_kewn_namewin_open` | 1 |
| 194 | `FNO_kewn_namewin_close_check` | 1 |
| 199 | `FNO_sb01_over_push` | 2 |
| 200 | `FNO_sb01_over_pull` | 2 |
| 203 | `FNO_mes_skip_disable_set` | 1 |
| 206 | `FNO_to_camera_zero_00` | 4 |
| 207 | `FNO_present_flower_set` | 1 |
| 210 | `FNO_tcame_return_plus` | 1 |
| 211 | `FNO_tcame_chase_tgt_reset` | 7 |

The camera calls (`FNO_tcame_*`), the position getters (`FNO_anyone_now_pos_get` reads an indexed
person's position into script variables) and the map change account for most uses. The full list of
`FNO_*` names is in [`script_symbols.h`](../../include/script_symbols.h).

### System variables

`0x35` and `0x39` read and write through a second table, the variable table at `0x800D401C`. Its
index numbers are the `V_*` and `S_ARG_*` names of the symbol dump. They are **not** call numbers,
even where the values overlap (21 is both `S_rand_sn` and `S_ARG_MYMONEY`).

| Index | Name | Notes |
| --- | --- | --- |
| 0 | `V_buki_gosyu_sno` |  |
| 1 | `V_cheriru00` |  |
| 2 | `V_daiku_num_bilud` |  |
| 21 | `S_ARG_MYMONEY` | money |
| 22 | `S_ARG_MAX_TOWER` | highest tower floor (by name) |
| 23 | `S_ARG_TOWER` | NULL slot in retail |
| 24 | `S_ARG_CNT_TOWER` | NULL slot in retail |
| 25 | `S_AEG_SNFG_P` |  |
| 26 | `V_pobj` |  |
| 27 | `V_item_type_data` |  |
| 28 | `V_sys` |  |
| 29 | `V_gamew2` |  |

Indices 3-20 are `V_pad03`-`V_pad20`, spare work words next to `V_buki_gosyu_sno` and
`V_cheriru00`. The money checks in the shipped scripts all follow one pattern: load money with
`0x35 v, 21`, subtract a price, branch on the sign, store it back with `0x39`.

### Flags

Flag operands are the developer's flag numbers (`F_*` family) from
[`script_symbols.h`](../../include/script_symbols.h); see also
[`script_symbols.tsv`](../evidence/script_symbols.tsv) and [`SYMBOLS.md`](../SYMBOLS.md). The same
dump names scene steps (`SSTP_*`) and portraits (`IMG_*`), which belong to other number spaces. Look a
number up in the family the opcode uses: the value `0x99` is both a flag and an `FNO_` number.

## 6. The compiled scene modules

Every module calls the town engine through the same four-instruction pattern: load the town state
pointer from `0x80016000`, load its call table (`+0x20`), load entry `n`, jump to it. All 835 call
sites in TOWN.BIN use constant numbers, 66 distinct entries in total. The most frequent are the
assert macro's `S_printf` and `S_exit`, `S_plt_carry_on_chk_ext` (47 sites; by its name, a check of what the
player carries), `FNO_change_map` (24) and `FNO_tw_sd_sq_ld_call` (18).

A module and its scripts work together:

- The module holds the **entry tables**: which script address runs when the player talks to each
  person or triggers each event, often chosen by testing flags first.
- Scripts call back into **the module's own helper functions** with `0x4C` (`script_call_native`).
  Most `0x4C` targets are addresses inside the current scene module (`0x80016000` and up): small C
  functions that move people, give items, start a minigame or return a value in `v15` for the script
  to branch on.
- Both sides share the **flags**: a module tests a flag with `S_flgtst` or directly, a script sets it
  with `0x0C`.

The modules link their own copies of the town-scene runtime (`main.o`, `player.o`, `lshop.o`), which
is why the same helper appears in many modules at different addresses.

## 7. How an event is built

The listings below are written for this guide in a readable pseudo-assembly. Each line is one
instruction; the comment shows its bytes. Labels stand for 32-bit addresses.

### A single line of dialogue

```
talk_baker:                      ; address listed in the scene module's talk table
    actor        7, 3            ; 0F 07 03     turn to the player and talk
    page         7               ; 57 07        speaker 7
    "Fresh bread today."         ; Shift-JIS text, 0A between lines
    wait_button                  ; 11
    clear_text_window            ; 08
    end_message                  ; 01
```

### A question with a remembered answer

```
ask_help:
    jump_if_flag_set   F_helped, already       ; 18 <flag16> <already>
    page               7                        ; 57 07
    "Could you help me?"
    wait_button                                 ; 11
    clear_text_window                           ; 08
    page               1                        ; 57 01   the player's prompt
    instant_text                                ; 0B
    "[Yes]"                                     ; option 1
    new_line                                    ; 0A
    instant_text                                ; 0B
    "[No]"                                      ; option 2
    choice_menu        2                        ; 19 02
    jump_by_choice     yes, no                  ; 1A <yes> <no>
yes:
    set_flag           F_helped                 ; 0C <flag16>
    clear_text_window
    page 7  "Thank you!"  wait_button  clear_text_window
    end_message
no:
    clear_text_window
    page 7  "Oh well."  wait_button  clear_text_window
    end_message
already:
    page 7  "Thanks again."  wait_button  clear_text_window
    end_message
```

### Money, a service call and a native helper

```
pay_fee:
    load_system_variable  v0, 21         ; 35 00 15      v0 = S_ARG_MYMONEY
    set_variable_a        v1, 100        ; 34 01 64000000
    subtract              v0, v1         ; 3C 00 01      v0 = money - 100
    jump_if_negative      v0, too_poor   ; 41 00 <too_poor>
    store_system_variable v0, 21         ; 39 00 15      money = v0
    set_variable_a        v0, 3          ; 34 00 03000000   argument: person 3
    call_service          150            ; 2E 96         FNO_anyone_now_pos_get
    call_native           helper         ; 4C <helper>   a function in this scene module
    jump_if_zero          v15, done      ; 3E 0F <done>  branch on what it returned
    ...
done:
    end_message
too_poor:
    page 9  "You can't afford it."  wait_button  clear_text_window
    end_message
```

Larger events combine the same pieces: subroutines (`0x15` / `0x16`) for lines shared by several
branches, camera services (`FNO_tcame_*`) and actor motions between pages, `0x30` (yield) or
`0x54` / `0x55` to wait a few frames for movement, and jump tables loaded into a variable with `0x34`
or `0x47` and followed with `0x48` (the shop counters pick their buy and sell scripts this way).

## 8. What the shipped game does not use

- **Never in any shipped script:** `0x03`, `0x04`, `0x05`, `0x0E`, `0x14`, `0x1B`, `0x1F`, `0x21`,
  `0x22`, `0x2D`, `0x32` (fill), `0x37` (reversed copy), `0x38` (skip byte), `0x44` (second copy),
  `0x49` (multiply),
  `0x4A` (divide), `0x4D`-`0x50` (pointer-table loads and stores), `0x56`, and the call variants
  `0x25`, `0x26`, `0x27` and `0x2F`. (The Japanese development units left in TOWN.BIN, which the
  game never loads, decode with `0x25` calls to the shop-menu services.) `0x20` never occurs in a
  script; menu labels that contain an ASCII space would run it as a no-op if the interpreter draws
  them, which is not confirmed.
- **Not opcodes:** slot `0x00` (the byte is the text return) and slot `0x58`; the shared no-op slots
  `0x02`, `0x28`, `0x29`, `0x51`, `0x52` never occur.
- **Voice commands:** `0x06` appears only in Japanese event files that no scene loads, where it gates
  voiced lines. `0x1D` (voice cue) appears there and in one DUNGEON overlay. The US town scripts
  dropped the per-line voice commands.
- **Rare:** `0x2A` (timed menu, one quiz), `0x31`, `0x35` and `0x39` (money), `0x36`, `0x3A`,
  `0x3D`, `0x40`, `0x41`, `0x43`, `0x45`, `0x46`, `0x47`; each occurs a handful of times.

## 9. Original-game quirks

These are in the shipped code; the decompiled C keeps them and says so in comments.

- **`0x4E` and `0x50` store through one byte.** The pointer-table stores read only the first byte of
  the table entry as the store address (`lbu`), where the matching loads `0x4D` / `0x4F` assemble all
  four. A script using them would write to a low address. No shipped script does.
  ([`0x4E`](../../src/engine/script/opcode_78_store_word_indirect_immediate.c),
  [`0x50`](../../src/engine/script/opcode_80_store_word_indirect_indexed.c))
- **`0x25` reads its call number back as signed.** The handler stores the number and the polling
  action reads it with a signed load, so numbers `0x80`-`0xFF` would index before the start of the
  table. ([source](../../src/engine/script/opcode_37_read_handler_arg.c))
- **Duplicate opcodes.** `0x44` repeats `0x33`, `0x45` repeats `0x34`, `0x46` repeats `0x36`, and
  `0x37` is `0x33` with its operands swapped. The second copies are rarely or never used.
- **Slot `0x58`** holds `dispatch_town_transition`, a function that game code also calls directly; it
  is most likely the word after the real table rather than an intended opcode.
- **Variable-table holes.** Entries 23 and 24 of the variable table (`S_ARG_TOWER`,
  `S_ARG_CNT_TOWER`) are NULL in the shipped table, so a script reading them would dereference NULL.
  None does.
- **A stray byte.** One shipped script, in the Kim brothers' scene, contains a single `0x10` (a no-op)
  right after a page start; it is harmless.

## 10. Notes for editing scripts

- Scripts are position-dependent. Moving or growing a script means rewriting every absolute address
  that points into it: operands of `0x15`, `0x17`, `0x18`, `0x2B`, `0x3E`-`0x43`, `0x1A` tables,
  script addresses loaded with `0x34` / `0x45`, the jump tables read by `0x47`, and the entry tables
  in the scene module.
- Each event file loads into a fixed RAM window; a larger file must still fit before whatever the
  scene places after it.
- Keep message lines at 31 characters or fewer and pages at the window's line count; the window does
  not wrap.
- `0x1A` tables must have exactly as many entries as the preceding menu has options.

## 11. Source index

| Topic | Source |
| --- | --- |
| Interpreter loop and byte format | [`konami_runtime_w_80038AB8.c`](../../src/slus/konami_runtime_w_80038AB8.c) |
| Opcode enum and names | [`include/engine/script.h`](../../include/engine/script.h) |
| Opcode handlers | [`src/engine/script/`](../../src/engine/script/), [`src/engine/script/vm/`](../../src/engine/script/vm/) |
| Starting scripts | [`start_script.c`](../../src/engine/script/start_script.c), [`call_script.c`](../../src/engine/script/call_script.c), [`set_script_address.c`](../../src/engine/script/set_script_address.c) |
| Numbered calls | [`vm_op_call_function_table.c`](../../src/engine/script/vm/vm_op_call_function_table.c) (`0x2E`), [`vm_op_call_absolute_function.c`](../../src/engine/script/vm/vm_op_call_absolute_function.c) (`0x4C`) |
| System variables | [`vm_op_load_table_pointer_value.c`](../../src/engine/script/vm/vm_op_load_table_pointer_value.c), [`vm_op_store_table_pointer_value.c`](../../src/engine/script/vm/vm_op_store_table_pointer_value.c) |
| Page start and sound modes | [`vm_op_install_terminator_action.c`](../../src/engine/script/vm/vm_op_install_terminator_action.c), [`select_message_wait_handler.c`](../../src/engine/message/select_message_wait_handler.c), [`entry_sd_call.c`](../../src/engine/message/entry_sd_call.c) |
| Developer symbols | [`script_symbols.h`](../../include/script_symbols.h), [`script_symbols.tsv`](../evidence/script_symbols.tsv), [`SYMBOLS.md`](../SYMBOLS.md) |
| Call table research | [`script_call_table_20260908.md`](../evidence/script_call_table_20260908.md) |
| Scene modules | [`town_script_modules.json`](../evidence/town_script_modules.json), [town guide](town.md), [engine guide](engine.md) |
