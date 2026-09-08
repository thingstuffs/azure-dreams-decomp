# The script call table: research record (2026-09-08)

*Three Opus readers in parallel (VM call path, per-chunk table scan, S_ system calls), every claim re-derived by an independent verifier, one critic. 16 agents. What follows is their own text, lightly trimmed; the settled result is in `docs/SYMBOLS.md` §5.1 and `ledger/evidence/fno_table.json`.*

## Settled

- One call table at `0x800D3CC8` (TOWN.BIN `0x56568`), number *n* → entry *n+1*. Published through `0x80016000` → `D_801131B8` → `field20` (compiled script modules) and installed into the bytecode VM system object `D_80082A38+0x40` from the resident word `0x8006ADD8`; opcodes 46 / 37 / 47 reach it. Variable table at `0x800D401C`. The previous evidence-layer rule (`0x800D3D0C`, `n−100`) was off by 17 slots and has been replaced; 14 landed rows that had received a wrong name were corrected through the gated landing path.

## Reader `callpath` — 26 claims, 21 verified of 26 judged

**Summary.** The town "call a function by number" path is NOT the slus bytecode VM — it is a link/export table that the town main chunk publishes to the 54 compiled event-script modules. func_8009D5C0 (row town/func_8009FE60) stores &D_801131B8 into the fixed word 0x80016000; the modules do `state = *(TownState**)0x80016000; f = state->field20[n+1]; f(...)`. state->field20 = 0x800D3CC8, so the number-indexed base is 0x800D3CCC. This resolves the "0x800D3D0C is never materialised" negative: the address the code actually forms is 0x800D3CC8 (TOWN foff 0x1FEF8, `lui v0,0x800d; addiu v0,v0,15560`), 0x44 bytes below what the ledger calls the FNO table. MAJOR CORRECTION: ledger/evidence/fno_table.json is off by 17 slots. The correct rule is `number n -> *(u32*)(0x800D3CCC + 4n)`, not `0x800D3D0C + 4*(n-100)`. Five independent semantic anchors prove it (S_NULL1/S_NULL2 land on the table's only two NULL words; S_rand_sn lands on `rand()%a0`; S_set_no_change_seq lands on a one-byte flag setter; FNO_strcmp lands on the PSX BIOS A(0x17)=strcmp stub; FNO_nouse___168 and FNO_nouse___170 are the ONLY two FNO numbers that land on the empty stub). Consequently the premise of task item 3 is refuted: numbers 118-182 are ordinary implemented functions. The 65-entry stub run is numbers 34..98 — the developer-console band that starts exactly at S_printf=34 and contains S_sprintf=90/S_getchar=91/S_exit=92. Nothing supplies implementations for it: there is no second copy of the table anywhere on the disc and no code in any container stores into the table. Only 2 of the 65 stub slots are ever called — number 89 (printf) and number 92 (S_exit), from the compiled modules' assert macro.

**Mechanism.** CALL PATH (compiled script module -> town function by number)

1. Publication. src/town/func_8009FE60.c defines func_8009D5C0 (row town/func_8009FE60, TOWN.BIN foff 0x1FE60, true vram 0x8009D5C0). It fills the TownState at D_801131B8 and publishes it:
   - src/town/func_8009FE60.c:63  `state->field20 = D_800D3CC8;`  == TOWN foff 0x1FEF4-0x1FEFC `lui v0,0x800d / addiu v0,v0,15560 / sw v0,32(s0)` (s0 = 0x801131B8)
   - src/town/func_8009FE60.c:64  `state->field24 = D_800D401C;`  == TOWN foff 0x1FF00-0x1FF08
   - src/town/func_8009FE60.c:70  `TOWN_SYSTEM_SCRATCH->state = state;` == TOWN foff 0x1FF38 `sw s0,24576(at)` with at=0x80010000, i.e. *(u32*)0x80016000 = 0x801131B8.
   This `sw` is the ONLY store to 0x80016000 in TOWN.BIN, DUNGEON.BIN, MAIN.BIN or baserom/slus_006.14 (const-propagating scan, work/research_fno/callpath/scan2.py).

2. Consumption. Every one of the 54 event-script modules (docs/evidence/town_script_modules.json; they are compiled MIPS C, not bytecode) does:
     lw  vX, 0x6000(0x80010000)   ; vX = *(u32*)0x80016000 = 0x801131B8
     lw  vX, 32(vX)               ; = state->field20 = 0x800D3CC8
     lw  vX, IMM(vX)              ; IMM = 4*(number+1)
     jalr vX
   Canonical site: TOWN foff 0x2AE798-0x2AE7B4 (module 0, file_off 0x2AB800, load base 0x80016000).
   Histogram of state-field loads by module code: state+0x20 x887, +0x38 x264, +0x1C x182, +0x30 x172, +0x14 x148, +0x18 x94, +0x8 x45, +0x24 x38, +0x40 x14.
   All ~1000 call sites use a CONSTANT IMM (no runtime-indexed call into this table exists anywhere in TOWN.BIN), so the numbers are link-time constants.

3. Index rule. number n selects field20[n+1], i.e. *(u32*)(0x800D3CCC + 4n). Proven by six anchors:
   - S_NULL1=5 -> 0x800D3CE0 = 0x00000000 and S_NULL2=15 -> 0x800D3D08 = 0x00000000. These are the ONLY two zero words in the whole table.
   - S_rand_sn=20 -> 0x800D3D1C -> 0x800C0E7C = src/town/func_800C371C.c `return rand() % arg0;`
   - S_set_no_change_seq=32 -> 0x800D3D4C -> 0x800C0F50 = src/town/func_800C37F0 (TOWN foff 0x437F0: `lui v1,0x8008 / addiu v0,1 / sb v0,2696(v1)` = *(u8*)0x80080A88 = 1)
   - S_printf=34 -> 0x800D3D54 = the FIRST word of the 65-word stub run.
   - FNO_strcmp=154 -> 0x800D3F34 -> 0x80069E58 = `addiu t2,zero,160 / jr t2 / addiu t1,zero,23` = PSX BIOS A(0x17) = strcmp.
   - FNO_nouse___168=167 -> 0x800D3F68 and FNO_nouse___170=169 -> 0x800D3F70 are the only two FNO numbers whose entry is the empty stub 0x800C0E5C.
   Corroborating structure: FNO 113-117 (jyotyu_set_reserve_all/papa/nyul/pool/dngn) -> five consecutive 8-byte `jr ra; nop` functions 0x8008B2BC/2C4/2CC/2D4/2DC; FNO 102-109 (8 koya_*/ext_plsel_* names) -> the eight consecutive 0x2C-byte thunks 0x800C0AC8..0x800C0BFC; all seven tcame_* names (129-132,136,137,209,210) -> the single cluster 0x800A5080..0x800A516C; FNO 211 (the last named FNO) -> 0x800D4018, the LAST function-pointer slot before state->field24's table begins at 0x800D401C.

4. The stub band. 0x800D3D54..0x800D3E54 (65 words) all hold 0x800C0E5C = row town/func_800C36FC (`jr ra; nop`, TOWN foff 0x436FC). Under the corrected rule this is numbers 34..98 = the developer-console band (S_printf=34 ... S_sprintf=90, S_getchar=91, S_exit=92). Only two of the 65 are ever called by shipped code:
   - number 89 (slot 0x800D3E30) = printf: 335+ call sites, e.g. TOWN foff 0x2AE588/0x2AE79C with a0="Assertion failed: file \"%s\", line %d\n" (module data at 0x80016034), a1="lshop.c"/"main.c"/"player.c", a2=line number.
   - number 92 = S_exit (slot 0x800D3E3C): 128-152 call sites, always `exit(1)` immediately after the printf (TOWN foff 0x2AE5BC, 0x2AE7D4).
   No implementation is supplied elsewhere: byte-searching TOWN/DUNGEON/MAIN/SLUS for the 5-word table signature 8008B2BC,8008B2C4,8008B2CC,8008B2D4,8008B2DC finds exactly one hit (TOWN 0x56730), and a const-prop scan for stores into 0x800D3CC8..0x800D4020 finds ZERO stores in any container. So there is no second table, no per-scene copy and no load-time patching.

5. The slus bytecode VM (separate machinery, same shape). src/slus/konami_runtime_w_80038AB8.c:57 `opcode_handlers[opcode](context)` over D_8006AA90[0..88]. Two of its handlers take a NUMBER operand and dispatch through a pointer table:
   - opcode 46 = func_80039DBC (src/slus/konami_runtime_w_80039DBC.c:29-35): reads one byte from the script stream and calls `table->handlers[index](table->arg0..arg3)`, handlers at context+0x40, args at +0x48..0x54, result at +0x84.
   - opcode 47 = func_80039E1C (src/slus/konami_runtime_w_80039E1C.c:28-40): reads a byte index PLUS a 32-bit little-endian pointer-to-pointer-to-table from the stream, then calls handlers[index](args).
   - func_80038690 (src/slus/konami_runtime_w_80038690.c:37) and func_8003875C (src/slus/konami_runtime_w_8003875C.c:24) do the same from state fields; the latter uses a table-of-tables `*(Handler**)(&D_80110E98 + group*4)`.
   The context these handlers use is the record at 0x80082A38 (func_8009D5C0 passes system_work = D_80082A80-0x48 = 0x80082A38 to func_80034F88, and sets *(s32*)(system_work+0x84)=0; the args block D_80082A80 = record+0x48 is state->field1C). func_800C0EAC (src/town/func_800C374C.c:46-47, TOWN foff 0x437A4) reads record+0x40 and +0x44 and forwards them to the module entry in a 15-word Packet together with 0x800D3C00 (a 25-entry {size,type,CD-sector} module load table) and 0x800D3950 (a second 172-entry function table).

**Open questions.**
- Numbers -1..12 (S_open_sell_dougu .. S_closebox_twin_shop) hold pointers into the 0x38-byte RAM window 0x80110E80..0x80110EB4 rather than code addresses, and no module call site targets those slots. Whether they are indirect (pointer-to-function-pointer) shop handles filled by another overlay, or data descriptors consumed by a different path, is unresolved. Note S_close_twin_shop=8 is the odd one out: it holds a real function, 0x800AE30C (row town/func_800B0BAC).
- FNO_func_sn_casino = 3 collides with S_open_buy_mamono = 3 in this table (both would be slot 0x800D3CD8 = 0x80110E84). So FNO numbers below 100 are almost certainly a different namespace (a per-scene function number), but the consumer of that namespace has not been located.
- The dump names S_printf = 34, yet the printf actually called by the modules' assert macro is number 89 (slot 0x800D3E30), with S_sprintf=90/S_getchar=91/S_exit=92 sitting immediately after it. Either 89 is an unnamed second printf entry or the S_printf record's value is stale. Both slots are the empty stub in retail, so it cannot be settled from behaviour.
- Nothing was found that writes the bytecode-VM handler-table pointer at record+0x40 (0x80082A78) or D_80110E98. func_800C0EAC reads 0x80082A78/0x80082A7C and forwards them to the module, so they are non-zero at run time, but the writer is not reachable by constant-address scanning (it must go through a struct base pointer). Locating it would tie the slus bytecode VM's numbered calls to a concrete table.
- The index space of the second 172-entry table at 0x800D3950 (Packet.data1, targets 0x800C4F6C..0x800CF6D8) and of state->field24 = 0x800D401C (38 module reads, entries point to 0x80113160+) is not identified. The PSN_DM_ (21 person commands) and sn_ (22 scene) families are the obvious candidates for one of them.
- Table slots 213+ (numbers 212 and up, from 0x800D401C) are pointers to 0x801131xx rather than functions, so 0x800D401C is where the function table ends. Whether numbers above 211 are legal at all is unverified — module call sites stop at number 211.
- The 63 stub numbers other than 89 and 92 are never called by any of the 54 modules. Their developer names are unknown because the dump's S_ family only names 0..34 and 90..92 in that band; recovering the rest would need a devkit build or another symbol blob.

**Claims the verifiers rejected.**
- (scall 8) TOWN.BIN foff 0x2AE79C `lw v0,360(v0)` after `lw v0,32(state)`; args a0=0x80016034 = "Assertion failed: file \"%s\", line %d\n", a1=0x8001605C = "lshop.c", a2=113 (module 0 image at file 0x2AB800). 33 → MECHANICS CONFIRMED, IDENTITY NOT. Confirmed exactly: TOWN foff 0x2AE798 `lw v0,24576(s3)` (s3 = 0x80010000 from `lui s3,0x8001` at 0x2AE770), 0x2AE7A0 `lw v0,32(v0)`, 0x2AE7A8 `lw v0,360(v0)` -> 0x80
- (table 23) TOWN.BIN 0x564A0..0x56568: 25 pairs, first word always 0x_016000 with a 0x01..0x04 type byte, second word a monotonically rising sector 0x1BE3..0x1CF5 (final entry 0x1C10). Referenced exactly once in  → PARTLY RIGHT, field decomposition WRONG. Extent and count check out: TOWN.BIN 0x564A0..0x56568 (vram 0x800D3C00..0x800D3C68) = 200 bytes = 25 eight-byte pairs, bounded below by the 0x800D3950 table en
- (table 24) TOWN.BIN 0x561F0..0x564A0, 172 words, all targets in 0x800C4F6C..0x800CF6D8. Materialised only at TOWN foff 0x437AC `addiu v0,v0,14672` (func_800C0EAC, src/town/func_800C374C.c:45 `packet.data1 = (s32 → COUNT AND NATURE RIGHT, THREE SUB-CLAIMS FALSE. Right: the table is TOWN.BIN 0x561F0..0x5649F (vram 0x800D3950, preceded by a 0x00000000 word at 0x561EC), 172 words, all distinct, and all 172 are genu
- (mechanism 25) ledger/evidence/names_proposed.tsv line 3: `0x8008E094 func_8008E094 start_mogura_func  script function number 100: dispatch table 0x800D3D0C entry 0 = this function`. Under the corrected rule FNO 100 → Substance confirmed, MAGNITUDE WRONG: the displacement is 84 slots (336 bytes), not 17. Re-derivation: (1) The quoted line is real - ledger/evidence/names_proposed.tsv line 3 is exactly `0x8008E094\tf
- (mechanism 26) TOWN.BIN 0x56568..0x56598 holds 0x80110EB4, 0x80110E80, 0x80110EA0, 0x80110EAC, 0x80110E84, 0x80110E90, 0, 0x80110EA8, 0x80110EB0, 0x800AE30C, 0x80110E94, 0x80110E88, 0x80110E8C, 0x80110E9C, 0x80110EA → Bytes match, conclusion overstated and wrong for one slot. (1) Byte content: TOWN.BIN words at foff 0x56568,0x5656C,...,0x565A0 (vram 0x800D3CC8..0x800D3D00) are, in order, 0x80110EB4, 0x80110E80, 0x8

## Reader `tablescan` — 73 claims, 72 verified of 74 judged

**Summary.** Task B's data-driven scan found NO second FNO table anywhere (TOWN/DUNGEON/MAIN/OVMOVIE/SLUS are all negative for a 65- or 122-entry function-pointer table other than the known one). But the scan produced a bigger result: the premise is wrong. ledger/evidence/fno_table.json anchors the FNO table at TOWN.BIN 0x565AC / vram 0x800D3D0C, which is simply the first word of the pointer *run*; the real table base is 0x800D3CCC (TOWN.BIN 0x5656C), 84 entries (0x150 bytes) later. Under the corrected base every one of the 112 named numbers 100..211 lands on a real function start (112/112), and the "65 stubbed numbers 118-182" evaporate: all 65 resolve to real functions (list delivered). Only TWO slots in the whole named range hold the empty stub 0x800C0E5C — numbers 167 and 169, whose developer names are literally FNO_nouse___168 and FNO_nouse___170. The 65-stub run is really table indices 34..98, a block that carries no FNO_ name at all (named values are 3 and 100..211), i.e. genuinely unused low slots, not stubbed-out gameplay functions. I also found the mechanism that reaches the table without any code materialising its address, which closes the standing negative result.

**Mechanism.** HOW THE TABLE IS REACHED (closes the "no instruction materialises 0x800D3D0C" negative).

1) Corrected table geometry. Base = TOWN.BIN foff 0x5656C = vram 0x800D3CCC, index = FNO number, 4-byte entries, last entry index 211 at foff 0x568B8 = vram 0x800D4018 (= FNO_serch_item_plown, the highest named number). The word at 0x568BC (vram 0x800D401C) is 0x80113160, the head of a different, adjacent pointer array — so the FNO table is exactly [0x800D3CCC, 0x800D401C), 212 entries.

2) Registration, not address materialisation. In the TOWN main chunk at vram 0x8009D654 (TOWN.BIN foff 0x1FEF4) a setup routine fills a descriptor struct at 0x801131B8 (s0):
   0x1FEF4 8009D654  3C02800D  lui   v0,0x800D
   0x1FEF8 8009D658  24423CC8  addiu v0,v0,0x3CC8      ; = 0x800D3CC8 = &fno_table[-1]
   0x1FEFC 8009D65C  AE020020  sw    v0,0x20(s0)
   0x1FF00 8009D660  3C02800D  lui   v0,0x800D
   0x1FF04 8009D664  2442401C  addiu v0,v0,0x401C      ; = 0x800D401C = one past the last entry
   0x1FF08 8009D668  AE020024  sw    v0,0x24(s0)
   ... 0x1FF34/0x1FF38  lui at,0x8001 ; sw s0,0x6000(at)   ; publishes the descriptor at 0x80016000
   ... 0x1FF3C  jal 0x80034F88 (resident, src/slus/konami_runtime_w_80034F88.c) with a1 = 0x80016004
These are the ONLY two lui-0x800D + addiu pairs in the whole town main chunk (and in the resident) whose low half falls anywhere inside [0x3CC0,0x4020] — verified by an exhaustive lui/offset pairing scan (work/research_fno/tablescan/insn.py-style scan over foff 0..0x60000 and over baserom/slus_006.14: 2 hits in town main, 0 in SLUS). There is no lui 0x800D paired with 0x3D0C anywhere in real code; the earlier negative result was correct and is explained: the table is handed to consumers by pointer, in a descriptor.

3) Consumers. The published pointer at 0x80016000 is read 1673 times in TOWN.BIN by the shape `lui rX,0x8001 ; lw rX,0x6000(rX)`, the first hits being inside script module 0 (e.g. TOWN.BIN 0x2ABA04/0x2ABA08 = vram 0x80016204/0x80016208 `lui v1,0x8001 ; lw v1,0x6000(v1)` then `lw v1,0x24(v1)` then `lw v1,0x74(v1)`). Script modules load at 0x80016000 with header word0 = 0 (docs/evidence/town_script_modules.json); that word0 is patched at runtime with the descriptor pointer, so every module reaches the town interface (and its FNO table at +0x20) through its own load base.

4) Base pinning — three independent, exact pins (all under base 0x800D3CCC, index = number):
   - FNO_strcmp = 154 -> TOWN.BIN 0x567D4 = 0x80069E58, which config/slus_006.14.symbols.txt:235 names `strcmp = 0x80069e58`. 0x80069E58 occurs exactly once in the array, so this pins the base uniquely (0x567D4 - 154*4 = 0x5656C).
   - FNO_nouse___168 = 167 and FNO_nouse___170 = 169 (docs/evidence/script_symbols.tsv:250,252) are the ONLY two named slots holding the empty stub 0x800C0E5C (TOWN.BIN 0x56808 and 0x56810).
   - Sibling families land as contiguous equal-stride function runs: numbers 113..117 (FNO_jyotyu_set_reserve_all/papa/nyul/pool/dngn) -> 0x8008B2BC,+8,+8,+8,+8 (five 8-byte functions); numbers 102..109 (the eight koya_*/ext_plsel_* wrappers) -> 0x800C0AC8 + 0x2C*k; numbers 146..149 (anyone_org/now_ang/pos_get) -> 0x800C4BE0/4C3C/4C88/4D20; numbers 129..132 (tcame_chase_set/chase2_set/lock/return) -> 0x800A5094/50B8/50E0/510C; numbers 100,101,122,123,128,175,177 (the start_mogura/tako/keima/keima2/sn_ball/gym/casino_slot minigame starters) all land in one 0x800C22D8..0x800C24C8 family at 0x28/0x34 stride. Under the old base 0x800D3D0C every one of these families is split.
   The descriptor's start field is &table[-1] (0x800D3CC8), the classic 1-based-array idiom; if the VM indexes it 1-based then the script's on-disc number is (dump value + 1), which is exactly what the developer's own `nouse___168`/`nouse___170` names say. Either reading gives the identical symbol -> function mapping; only the absolute integer is ambiguous by +1.

**Open questions.**
- What is the exact integer the script byte carries: the symbol dump's value V (0-based index from 0x800D3CCC) or V+1 (1-based index from the descriptor's 0x800D3CC8)? The descriptor stores &table[-1], and the developer's own FNO_nouse___168 / FNO_nouse___170 names match V+1, while the dump's value column says V. Both readings give the identical symbol->function mapping; only the on-disc opcode operand differs by one. Resolving it needs one script byte-stream read: find an FNO call opcode in a script module and compare its operand with a known target.
- Which VM opcode carries the FNO number, and where is the actual indexed load? No code anywhere materialises the table address, so the load must be 'lw rX,0x20(desc)' followed by an indexed lw. Grepping TOWN.BIN for 'lw rX,0x20(rY)' preceded by the 0x80016000 descriptor load would find the dispatcher (the descriptor read idiom is already localised: 1673 sites, e.g. TOWN.BIN 0x2ABA04).
- Table indices 0..15 point into 0x80110E80..0x80110EB4 at a 4-byte stride, which is too tight for function bodies. That region belongs to an overlay loaded at 0x80110000 (FNO_func_sn_casino = 3 -> 0x80110E84). Are these pointers-to-pointers, a jump-vector array, or evidence that the 0x80110000 overlay is not in TOWN.BIN at all? The 0x80110000 space is unmapped in this tree's address map.
- Indices 16..33 hold 18 real function pointers with no FNO_ name, and indices 34..98 are 65 copies of the empty stub. Is 16..98 a reserved low band shared with another script family (S_ / PSN_DM_), or simply FNO numbers whose names were dropped from the disc dump?
- The S_ system-call dispatch is still unlocated: the (number,pointer) scan found nothing, and no 35- or 44-entry pointer table exists in SLUS. The likeliest remaining shape is a switch jump table in .rodata; SLUS foff 0x6608..0x6B00 (vram 0x80032E08..0x80033300) holds a dense cluster of jump tables (126, 59, 58, 23 entries) targeting func_80057D20, func_800595C0 and func_8005EDA0 — those three functions are the best candidates to disassemble next.
- The 'import table at TOWN.BIN 0x56760-0x568C0' in the port notes is really the interior of the FNO table (numbers 125..211 plus the first word of the adjacent 0x80113160 array). That label should be retired wherever it is recorded.

**Claims the verifiers rejected.**
- (table ) TOWN.BIN 0x593C8 (vram 0x800D6B28, 62 entries, 51 resolved) and 0x5985C (vram 0x800D6FBC, 119 entries, 84 resolved). Both are menu/animation state tables built from a repeating 6-8 slot motif over 0x8 → PARTIALLY confirmed; marked false because two stated details do not reproduce. CONFIRMED: (a) baserom/slus_006.14 foff 0x45000 = vram 0x80071800 (vram = 0x8002D000 + foff - 0x800). (b) The exact self-

## Reader `scalls` — 54 claims, 36 verified of 54 judged

**Summary.** TASK C is solved, and it also overturns the current FNO registration.

There is ONE call table, not two. It lives at vram 0x800D3CC8 (TOWN.BIN file 0x56568), has 213 word entries (indices 0..212), and is indexed by the RAW script call number. Its address is baked into the resident's data at 0x8006ADD8 and is installed into the script system object D_80082A38 at +0x40 by func_80034EC4 (src/slus/konami_runtime_w_80034E48.c is the caller; the store is 0x80034EF4 `sw $v0, 0x40($a0)`). Index 0..34 = the S_ system calls, 35..99 = the empty stub 0x800C0E5C (65 entries, the hole in the numbering), 100..212 = the FNO_ functions. A sibling table at 0x800D401C (installed at D_80082A38+0x44 by the same function) is the script VARIABLE table, 30 entries, each a pointer to a variable — that is the V_ / S_ARG_ namespace, which answers question 3.

Three opcode handlers reach the call table:
- opcode 46 = func_80039DBC: reads ONE byte call number from the cursor and calls table[n](reg0,reg1,reg2,reg3) once, storing the return value in reg15.
- opcode 37 = func_80039BBC: reads ONE byte into state+0x32 and installs func_80038690 as the per-frame action, which calls the SAME table[n] with the same four register args every frame until it returns nonzero — the blocking form of a system call.
- opcode 47 = func_80039E1C: reads one byte index plus a 4-byte pointer-to-a-table-pointer taken from the script stream, i.e. a call into a table the script names explicitly.
There is no switch and no jtbl anywhere in this path; the "large switch" hypothesis in the brief is wrong.

The dump's numbering is off by exactly one from the runtime index for the S_ and FNO_ blocks (but NOT for the V_ block). Runtime index = dump value + 1. Three independent proofs are given below; the strongest is that FNO_strcmp (dump 154 -> index 155) lands on 0x80069E58, which config/slus_006.14.symbols.txt:235 independently names `strcmp`.

Consequence: ledger/evidence/fno_table.json is mis-registered. It took 0x800D3D0C (= index 17 of the real table) as number 100, so every FNO name in it is assigned to a function 83 numbers away from the right one. Its "entries for numbers 118-182 are stubs" is really indices 35..99 — the gap between the last system call and the first function number. Its FNO_start_mogura_func -> 0x8008B7F4 (row town/func_8008E094) is in fact S_town_map_del.

S_printf (runtime 35) and S_sprintf/S_getchar/S_exit (91/92/93) all point at the empty stub 0x800C0E5C — the brief's "developer-console calls unimplemented in retail" hypothesis is confirmed by the data.

**Mechanism.** THE SCRIPT SYSTEM OBJECT
func_80034EC4 (resident 0x80034EC4, called from func_80034E48 with &D_80082A38, see src/slus/konami_runtime_w_80034E48.c:18) initialises the script system object:
  80034ED8 lui $v0, 0x8007 / 80034EDC addiu $v0,$v0,-0x5244   -> $v0 = 0x8006ADBC
  80034EE0 lw $v1, 0x20($v0)   ; word at 0x8006ADDC = 0x800D401C
  80034EE8 sw $v1, 0x44($a0)   ; obj->var_table  = 0x800D401C
  80034EEC lw $v0, 0x1C($v0)   ; word at 0x8006ADD8 = 0x800D3CC8
  80034EF4 sw $v0, 0x40($a0)   ; obj->call_table = 0x800D3CC8
The object is D_80082A38 (proved by 0x80037ED4-0x80037EEC, which clears the 16-word register file at D_80082A38+0x48..+0x84 exactly as opcode 50 does, and by 0x8003AAF8-0x8003AB10 which writes D_80082A38+0x48/+0x4C = registers 0 and 1).

OBJECT LAYOUT (all offsets verified in the disassembly)
  +0x40  call/function table pointer  = 0x800D3CC8
  +0x44  variable table pointer       = 0x800D401C
  +0x48 .. +0x84  16-word register file (reg0..reg15); reg0..reg3 are the 4 call arguments, reg15 (+0x84) receives the return value.

READER/INTERPRETER
The VM reader (arg0 of every opcode handler) has +0x1C = bytecode cursor and +0x80 = pointer to the system object. The interpreter is func_80038AB8 (src/slus/konami_runtime_w_80038AB8.c:57 `opcode_handlers[opcode](context)`), table D_8006AA90, 89 entries (ledger/evidence/vm_tables.json table 0).

HOW A SYSTEM CALL IS REACHED
1) Immediate call, opcode 46 = func_80039DBC (src/slus/konami_runtime_w_80039DBC.c:29-36):
   80039DC8 lw $v0,0x1C($a0)      ; cursor
   80039DCC lw $s0,0x80($a0)      ; system object
   80039DD0 lbu $v1,0x0($v0)      ; ONE-BYTE call number
   80039DD4 lw $a1,0x40($s0)      ; call table = 0x800D3CC8
   80039DE0/DE8/DEC/DF8 lw a0,a2,a3,a1 from 0x48/0x50/0x54/0x4C   ; reg0..reg3
   80039DEC sll $v1,$v1,2 / 80039DF0 addu $v1,$v1,$a1 / 80039DF4 lw $v0,0x0($v1) / 80039DFC jalr $v0
   80039E04 sw $v0,0x84($s0)      ; result -> reg15
2) Blocking call, opcode 37 = func_80039BBC (src/slus/konami_runtime_w_80039BBC.c:15-21): reads one byte into state+0x32 and sets state->action = func_80038690. func_80038690 (0x800386A4-0x800386EC) then does `lb $v0,0x32($s1); lw $s0,0x80($s1); lw $v1,0x40($s0); ... jalr` with the same reg0..reg3, stores the result in +0x84, and only advances the script (action = func_80038A10) when the callee returns nonzero — i.e. the call is polled every frame until it completes. This is how the "open a shop / wait for it to close" style calls are meant to run.
3) Explicit-table call, opcode 47 = func_80039E1C (src/slus/konami_runtime_w_80039E1C.c:28-40): one byte index + a 4-byte little-endian pointer read from the stream; the pointed-to word is the table base.
4) Two-level group call, opcode 39 = func_80039C0C (src/slus/konami_runtime_w_80039C0C.c:16-25): reads TWO bytes (state+0x32 group, state+0x33 entry) and installs func_8003875C, which at 0x80038768-0x8003879C does `base = 0x80110E98; group = *(base + group*4); f = *(group + entry*4); f(state+0x34)` and polls until nonzero. This is the mechanism the 13 shop/twin-shop call-table entries point into (see below).

ARGUMENT SET-UP OPCODES (all write the +0x48 register file)
  opcode 49 = func_80039F28: reg[b] = 0            (0x80039F40 sw $zero,0x48($v0))
  opcode 50 = func_80039F4C: fills all 16 registers with the operand byte (loop 0x80039F68)
  opcode 51 = func_80039F80: reg[d] = reg[s]       (0x80039FB0/0x80039FBC)
  opcode 52 = func_80039FC0: reg[d] = imm32 read from the stream (0x8003A004)
  opcode 53 = func_8003A01C: reg[d] = *(u32*)vartable[i]  — 0x8003A03C `lw $v0,0x44($a2)` (the VARIABLE table), 0x8003A048 `lw $v0,0x0($v1)` (the variable's address), 0x8003A050 `lw $v0,0x0($v0)` (its value), 0x8003A05C `sw $v0,0x48($a1)`
  opcode 54 = func_8003A060: reg[d] = 32-bit LE value fetched from an in-script array

THE NUMBERING (index = dump value + 1) — three independent proofs
  a) ledger/evidence/script_symbols.json S_NULL1 = 5 and S_NULL2 = 15; the only two NULL words in the table are index 6 (0x800D3CE0) and index 16 (0x800D3D08), 10 apart, exactly matching.
  b) FNO_nouse___168 has dump value 167 and FNO_nouse___170 has dump value 169; the only two stub entries in the function block are index 168 (0x800D3F68) and index 170 (0x800D3F70) = 0x800C0E5C. The developer's own names carry the true numbers.
  c) FNO_strcmp has dump value 154; index 155 (0x800D3F34) = 0x80069E58, and config/slus_006.14.symbols.txt:235 says `strcmp = 0x80069e58`. Under the dump value (index 154) it would be 0x800A0A54, and under the current fno_table.json registration it would be the empty stub.
The V_ / variable block shows NO such shift: V_cheriru00=0 .. NUM_SN_VAR_WORK=20 map onto the 21 consecutive pointers 0x80113160..0x801131B0 at variable indices 0..20, and the consecutive run breaks exactly at index 21.

WHY 0x800D3D0C WAS NEVER MATERIALISED
Because it is not a table base. The base 0x800D3CC8 IS present as a data word, in the RESIDENT, at 0x8006ADD8 (baserom/slus_006.14 file offset 0x3E5D8), together with 0x800D401C at 0x8006ADDC. A second identical pair sits at 0x8006AE08/0x8006AE0C (the descriptor record is 0x34 bytes; a second copy starts at 0x8006ADF0). The resident image was linked already knowing the town overlay's table addresses.

**Open questions.**
- Why the S_ and FNO_ blocks are shifted by exactly +1 relative to script_symbols.json while the V_/variable block is not. The shift itself is proven three ways (S_NULL1/S_NULL2, FNO_nouse___168/170, FNO_strcmp), but the source-level or dump-tool cause is not. The enum-leak observation (S_open_buy_dougu=5327, FNO_func_sn_casino=3, Mode_inhouse=29 each continuing the previous enum) is suggestive but does not by itself produce a +1 on every following member.
- The 13 shop / twin-shop call-table entries (numbers 0-5, 7, 8, 10-14) hold the ADDRESS of a group-pointer slot in 0x80110E80..0x80110EB4, not a function pointer. Calling one through opcode 46/37 would jalr a data address. Nothing in TOWN.BIN's main chunk or in the resident ever writes those 13 slots (each word occurs exactly once in TOWN.BIN, inside the call table itself). Unresolved: which module fills D_80110E98[-6..+7], and whether the shop calls are in practice issued as opcode 39 (group,entry) pairs rather than as numbered calls -- in which case the table entries are generator artefacts. A candidate group table sits at 0x800D157C = {0x800AE510 (return 0), 0x800AE518, 0x800AE534, 0x800AE550}, three of which store their argument to 0x80110EB8 and a mode 3/5/7 to 0x80110EC0.
- Variable-table entries 23 (S_ARG_CNT_TOWER) and 24 (S_AEG_SNFG_P) are NULL pointers, so reading them through opcode 53 would fault -- presumably unused in retail. Not confirmed against any script.
- Whether the 65-entry stub run at indices 35..99 was ever populated in a development build (i.e. whether there were system calls 35..99), or whether the gap is purely a numbering convention with FNO functions starting at 100.
- No script bytecode was decoded in this pass: the mapping is established from the table and the dispatchers, not from an observed opcode-46/37 operand in any of the 54 event-script modules (docs/evidence/town_script_modules.json). Decoding one module and reading its call operands would be an independent end-to-end check of the +1 shift.
- ledger/evidence/fno_table.json needs regenerating from base 0x800D3CC8 with index = number, and the 113 FNO name->row assignments derived from it (and anything downstream in ledger/evidence/names_proposed.tsv or config/names.tsv) should be re-checked. Not done here: this task was read-only.

**Claims the verifiers rejected.**
- (mechanism ) In ledger/evidence/script_symbols.json they sit in an unbroken declaration run with the V_ variables: records 3552..3582 are V_cheriru00=0, V_daiku_num_bilud=1, V_pad03..V_pad20=2..19, NUM_SN_VAR_WORK → HEADLINE RIGHT, MAPPING WRONG. Verified parts: ledger/evidence/script_symbols.json records 3552..3582 are exactly as quoted (V_cheriru00=0 ... S_ARG_MYMONEY=21, S_ARG_MAX_TOWER=21, S_ARG_TOWER=22, S_A
- (global ) baserom/slus_006.14: word at 0x8006ADD8 = 0x800D3CC8, word at 0x8006ADDC = 0x800D401C (file offsets 0x3E5D8/0x3E5DC). A second copy of the 0x34-byte record starts at 0x8006ADF0 (0x8006AE08 = 0x800D3CC → TWO LEGS RIGHT, TWO WRONG. Right: words at baserom/slus_006.14 file 0x3E5D8/0x3E5DC (vram 0x8006ADD8/0x8006ADDC) are 0x800D3CC8 and 0x800D401C; a scan of the whole resident finds 0x800D3CC8 at exactly
- (scall 15) table[15] (0x800D3D04) = 0x8008B654; TOWN.BIN foff 0xDEF4. Two-argument function (a0,a1 saved to s5,s6 at 0x8008B65C/0x8008B664), allocates via func_8003FC64(0x11). Dump value 14. → MAPPING RIGHT, NUMBER OFF BY ONE. Bytes: TOWN.BIN foff 0x565A4 = 0x8008B654 (vram 0x800D3D04) — confirmed by struct.unpack. Row: ledger/rows.jsonl town/func_8008DEF4 foff=0xDEF4 size=416 true_name=fun
- (scall 16) table[16] = 0x00000000; dump value 15. Sits exactly 10 slots after the S_NULL1 null, matching the 10-apart dump values 5 and 15. → WORD RIGHT, NUMBER OFF BY ONE. TOWN.BIN foff 0x565A8 = 0x00000000 (vram 0x800D3D08) — confirmed. The two-nulls observation is real and is in fact the anchor that fixes the table: the only zero words i
- (scall 17) table[17] (0x800D3D0C) = 0x8008B7F4; TOWN.BIN foff 0xE094. Disasm: `lui $v1,0x8010; addiu $v0,$zero,0xFF; sb $v0,-0x3BE8($v1)` -> writes 0xFF (the 'no map' marker) to byte 0x8000C418 and returns 1. Th → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 16), AND ONE ADDRESS TYPO. Bytes: TOWN.BIN foff 0x565AC = 0x8008B7F4. Row: town/func_8008E094 foff=0xE094 size=20 true_name=func_8008B7F4. Disasm at
- (scall 18) table[18] (0x800D3D10) = 0x800B85E8; TOWN.BIN foff 0x3AE88. Dump value 17. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 17). Bytes: TOWN.BIN foff 0x565B0 = 0x800B85E8. Row: town/func_800BAE88 foff=0x3AE88 size=588 true_name=func_800B85E8. Under the proven base 0x800D3
- (scall 19) table[19] (0x800D3D14) = 0x800B89C4; TOWN.BIN foff 0x3B264. Dump value 18. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 18). Bytes: TOWN.BIN foff 0x565B4 = 0x800B89C4. Row: town/func_800BB264 foff=0x3B264 size=124 true_name=func_800B89C4. Under base 0x800D3CCC, 0x800D
- (scall 20) table[20] (0x800D3D18) = 0x8004A638, inside the resident (defined in src/slus/code.c). A resident callee reached directly, no trampoline. Dump value 19. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 19). Bytes: TOWN.BIN foff 0x565B8 = 0x8004A638. Resident check: baserom/slus_006.14 foff 0x1DE38 (vram = 0x8002D000 + foff - 0x800 = 0x8004A638) = 2
- (scall 21) table[21] (0x800D3D1C) = 0x800C0E7C; TOWN.BIN foff 0x4371C. Dump value 20. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 20). Bytes: TOWN.BIN foff 0x565BC = 0x800C0E7C. Row: town/func_800C371C foff=0x4371C size=48 true_name=func_800C0E7C. src/town/func_800C371C.c is li
- (scall 22) table[22] (0x800D3D20) = 0x800C0EAC; TOWN.BIN foff 0x4374C. Dump value 21. (S_ARG_MYMONEY/S_ARG_MAX_TOWER also carry 21 but belong to the variable table, see the S_ARG claim.) → SLOT RIGHT, NUMBER OFF BY ONE (correct number is 21), SEMANTICS UNCONFIRMED. Bytes: TOWN.BIN foff 0x565C0 = 0x800C0EAC. Row: town/func_800C374C foff=0x4374C size=148 true_name=func_800C0EAC. Under bas
- (scall 23) table[23] (0x800D3D24) = 0x800C0E64; TOWN.BIN foff 0x43704. Dump value 22. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 22). Bytes: TOWN.BIN foff 0x565C4 = 0x800C0E64. Row: town/func_800C3704 foff=0x43704 size=24 true_name=func_800C0E64. src/town/func_800C3704.c:6 're
- (scall 24) table[24] (0x800D3D28) = 0x800B2BA0; TOWN.BIN foff 0x35440. Dump value 23. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 23). Bytes: TOWN.BIN foff 0x565C8 = 0x800B2BA0. Row: town/func_800B5440 foff=0x35440 size=204 true_name=func_800B2BA0. src/town/func_800B5440.c allo
- (scall 25) table[25] (0x800D3D2C) = 0x8003E4FC, resident (src/slus/code.c). Dump value 24. → TARGET RIGHT, NUMBER OFF BY ONE (correct number is 24), AND THE ROW IS WRONG. Bytes: TOWN.BIN foff 0x565CC = 0x8003E4FC. Resident check: baserom/slus_006.14 foff 0x11CFC (vram 0x8003E4FC) = 27BDFFE8 —
- (scall 26) table[26] (0x800D3D30) = 0x800AE1AC; TOWN.BIN foff 0x30A4C. Same 0x800AExxx cluster as S_close_twin_shop. Dump value 25. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 25). Bytes: TOWN.BIN foff 0x565D0 = 0x800AE1AC. Row: town/func_800B0A4C foff=0x30A4C size=248 true_name=func_800AE1AC; src/town/func_800B0A4C.c allo
- (scall 27) table[27] (0x800D3D34) = 0x8004A618, resident (src/slus/code.c); sits 0x20 bytes before S_get_item_buy_money's 0x8004A638, the expected buy/sell pair. Dump value 26. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 26). Bytes: TOWN.BIN foff 0x565D4 = 0x8004A618. Resident check: baserom/slus_006.14 foff 0x1DE18 (vram 0x8004A618) = 27BDFFE8 'addiu $sp,$sp,-24' th
- (scall 28) table[28] (0x800D3D38) = 0x800B83DC; TOWN.BIN foff 0x3AC7C. Dump value 27. → MAPPING RIGHT, NUMBER OFF BY ONE (correct number is 27). Bytes: TOWN.BIN foff 0x565D8 = 0x800B83DC. Row: town/func_800BAC7C foff=0x3AC7C size=524 true_name=func_800B83DC. src/town/func_800BAC7C.c:4-11
- (scall 35) table[35] (0x800D3D54) = 0x800C0E5C, the empty stub. It is the first of the unbroken run of 65 stub entries at indices 35..99. Dump value 34. Confirms the brief's hypothesis that the developer-console → REFUTED on the number. The raw dump record is name@0x82B374="S_printf", value@0x82B394=0x0000005A=90, NOT 35. The claim read 34 from the misaligned ledger/evidence/script_symbols.json and added 1; but
- (mechanism 5327) script_symbols.json records 3506..3512: GOODS_pad1=5321 ... GOODS_pad6=5326, S_open_buy_dougu=5327, then record 3513 S_open_sell_dougu=0. The value 5327 is simply the continuation of the preceding GOO → CONCLUSION RIGHT, MECHANISM WRONG - so verified=false. Right: S_open_buy_dougu is runtime system call 0 and 5327 is not a call number. Wrong: it is not a source-level brace/scope leak. The raw bytes s

## Critic
## VERDICT ON THE MOST CONSEQUENTIAL CLAIM

The corrected index rule (`number n -> *(u32*)(0x800D3CCC + 4n)`, i.e. `field20[n+1]`) **survives an independent test the readers never ran**: I scanned DUNGEON.BIN and MAIN.BIN for the call shape. DUNGEON.BIN file 0x51E7D4-0x51E7E8 is `lui v0,0x8001 / lw v0,24576(v0) / lw v0,32(v0) / lw v0,536(v0)`; 536 = 4·133+4 → number 133 = **FNO_change_map**, in the dungeon container, called from a site none of the three readers looked at. MAIN.BIN: 0 sites. A dungeon overlay calling `change_map` by number is a semantic anchor from outside the town evidence set. Treat the corrected rule as settled and `ledger/evidence/fno_table.json` as wrong.

Everything below is what is still missing or in conflict.

---

## 1. HARD CONTRADICTION NOBODY RESOLVED: what is the word at 0x80016000?

Two claims are each byte-true and mutually exclusive as stated, and the callpath reader asserts both in one narrative (mechanism steps 1 and 5) without noticing.

- **It is a data pointer.** `func_8009D5C0` writes it: TOWN foff 0x1FF38 `sw s0,24576(at)`, at=0x80010000, s0=0x801131B8 (src/town/func_8009FE60.c:70). Module code reads it as a struct base — I disassembled module 0's entry myself: TOWN file 0x2AFC84 = vram 0x8001A484, and at 0x8001A4CC-0x8001A4F0 it does `lui v0,0x8001 / lw v1,24576(v0) / sw s0,40(v1) / sw v0,52(v1) / sw v0,44(v1)` — the module **writes into** `state->field28/field2C/field34` through that pointer. (This also closes a loop nobody closed: `func_8009D5C0` later calls `func_8008B23C(state->field34)` — field34 is supplied *by the module*, so the module runs before that line.)
- **It is a function pointer.** I disassembled `func_800C0EAC` in full (TOWN foff 0x4374C-0x437DC): 0x43750 `lui t1,0x8001` / 0x43754 `ori t1,t1,0x6000` / **0x437C0 `lw v0,0(t1)`** / 0x437C8 `jalr v0` / delay `addiu a0,sp,16`. It calls whatever word sits at 0x80016000.

Verifier 22 flagged this as caveat (a) and stopped; nobody carried it. **New fact that reframes it:** `func_800C0EAC` is *itself* table slot 21 — `0x800D3D20 = 0x800C0EAC`, and number 21 is **S_flgtst** (with S_ARG_MYMONEY/S_ARG_MAX_TOWER on the same value). So claim 22's "town forwards to the module entry" is wrong in kind: `func_800C0EAC` is a **script system call the module makes**, which calls *back* through 0x80016000. Its neighbour, number 22 = **S_f_LandBuildingNo** → 0x800C0E64, sits immediately before it. The assertion-string census (verifier 8) even lists `flgtst.c` in TOWN.BIN. Nobody connected the packet dispatcher to its own table slot.

**Why the readers could not see the writer:** all three scanners are absolute `lui`+lo-immediate const-prop (they each say so). They are structurally blind to `sw rX,0(rY)` where rY was *loaded* or *passed in* — and `func_800C0EAC` passes `packet.handler = 0x80016000` to the callee (TOWN 0x43790 `sw t1,16(sp)`), i.e. it hands out the slot address in a form no absolute scan can follow. So claim 1's "the ONLY store to 0x80016000 in any container" and claim 7(c)'s "ZERO stores into the table" are both much weaker than written: they mean *no store via an absolute address pair*. Every negative in this result set inherits that hole.

DUNGEON.BIN shows the slot is **polymorphic**, which is probably the resolution: at file 0x2AA4DC it is a jump table — `sltiu ...,13 / lui v0,0x8001 / addiu v0,v0,24576 / sll v1,v1,2 / addu v1,v1,v0 / lw v0,0(v1) / jr v0` (13-entry bound check); at 0xDAA8-0xDABC it is `0x80016000 + X` then `lw a0,72(a0)`; at 0x8D17C0 it is the town-state read again (`lw v1,24576(v1) / lw v1,48(v1)` = state->field30 = 0x800D381C).

---

## 2. A CODE PATH NOBODY READ: the resident scene registry at 0x8006ADC0-0x8006AF20

The brief hypothesised "an overlay header/export table, a registration mechanism, or the resident scanning something." It is sitting in the resident and no reader opened it. Verifier 9(e) noticed two of the words and drew no conclusion.

baserom/slus_006.14, vram 0x8006ADA0+ (foff = vram − 0x8002D000 + 0x800):

- 0x8006ADC0 = `800D4360`, 0x8006ADD8 = **`800D3CC8`**, 0x8006ADDC = **`800D401C`** — and the identical triple repeats at 0x8006ADF0 / 0x8006AE08 / 0x8006AE0C (stride 0x30). The **resident statically contains the town table base/limit pair**. `D_8006ADC0[0]` is exactly the word `func_8009D5C0` tests (`if (D_8006ADC0[0] != 0)`, src/town/func_8009FE60.c:47).
- From 0x8006AEC4 there is a 0x14-stride record array: `{0034000C, 01000100, 800D4378, 8003B400, 00010000}`, `{0001000C, 00E00090, 800D4360, 8003B188, 0}`, `{0001000C, 00E00090, 800D4360, 8003B1E4, 0}`, `{0002000C, …, 800D4360, 8003B1E4}`, `{0003000C, 01200090, 800D4360, …}` — word2 points at TOWN blob-descriptor lists, word3 at resident handlers 0x8003B188/1B4/1E4/210/264/2C4/324/35C/400, i.e. the immediate neighbourhood of **0x8003B470, the opcode-88 state-transition dispatcher** named in the brief.
- TOWN mirrors the same 0x14-byte record shape with its own handlers: 0x800D4340 = `{800D4380, 800C1A44, 00010000}`, 0x800D434C = `{0035000C, 012002A0, 800D4380, 800C1A90, 00010000}`, plus 0x800C1B74.
- Writers exist and were never followed: resident 0x8003BD58/0x8003BD5C (`sw` into 0x8006ADBC/0x8006ADC0), 0x80053CBC and 0x80053CE8 (`sw` into 0x8006ADC0), 0x8003BC64/0x8003BC68 (`sw` into 0x8006ADF0); town-side 0x800C11A0/0x800C11B8 (`sb`) and 0x8009D618 (`lw`).

**This also corrects claim 23's field decomposition** (which verifier 23 marked wrong but did not replace). The first word is not "size 0x016000 + type": 0x800D4360 = `0A016000/000013CF`, `04816000/000013EF`, `04816000/000013F8`, `02016000/000019EE`, `02016000/00001401`, `01816000/000019F3`, `03816000/00001405`. `0x016000` is the **load address 0x80016000 masked**, with a type/count byte on top and a CD sector beneath. Same shape at 0x800D3C00. These are "load blob N from sector S to 0x80016000" descriptors, and the resident state machine selects which list to use.

---

## 3. CONTAINER NOBODY SCANNED

- **DUNGEON.BIN**: never scanned for the number-call ABI or for 0x80016000 use. It has both (§1, §2 above). One number call (n=133), one field30 read, one 13-entry jump table, two more address formations at 0xDAA8 and 0x525CDC. Zero `0x4C070707` module headers (TOWN has 110 = 2 per module × 54 + 2), so the dungeon uses the same slot with a different payload layout.
- **The module images themselves as *callees***. 878/571 call *sites* were harvested, but nobody disassembled a module's code that *writes* through `packet.handler`, which is the only place the 0x80016000 writer can live given the scan blindness in §1.

---

## 4. THE S_ QUESTION IS ONLY HALF ANSWERED — and the unanswered half has a shape

Numbers −1..13 hold, verified word by word from TOWN 0x56568+:

```
 -1 80110EB4    0 80110E80 S_open_sell_dougu   1 80110EA0 S_open_buy_buki
  2 80110EAC    3 80110E84 FNO_func_sn_casino/S_open_buy_mamono
  4 80110E90    5 00000000 S_NULL1             6 80110EA8   7 80110EB0
  8 800AE30C S_close_twin_shop                 9 80110E94  10 80110E88
 11 80110E8C   12 80110E9C                    13 80110EA4
```

The non-NULL, non-0x800AE30C entries are **exactly the 14 words 0x80110E80..0x80110EB4 minus 0x80110E98** — a permutation with one hole, and the hole is `D_80110E98` itself, the slus VM's table-of-tables base (`src/slus/konami_runtime_w_8003875C.c:24`, `group = *(Handler**)((u8*)&D_80110E98 + state->table_group*4)`). Verifier 21 saw the coincidence and filed it as "corroboration the claimant missed"; nobody tested the obvious consequence — **the S_open_*/twin_shop calls are dispatched by the bytecode VM through `func_8003875C`'s group table, not by the town call shape**, which is why no module call site targets those slots (claim 26 left this "unresolved"). That is a testable hypothesis, not a mystery.

Two numeric anomalies nobody addressed, now quantified from ledger/evidence/script_symbols.json (44 `S_`, 113 `FNO_` records): **exactly one** S_ exceeds 99 (`S_open_buy_dougu = 5327`) and **exactly one** FNO_ is below 100 (`FNO_func_sn_casino = 3`, colliding with S_open_buy_mamono). 43/44 and 112/113 fit the single 0..211 array. Both exceptions are unexplained; 5327 in particular is never mentioned by any reader.

Also unreconciled: `func_8009D5C0` sets the VM cursor to `TOWN_SYSTEM_SCRATCH->payload` = **0x80016004** (`func_80034F88(system_work, …)`, src/town/func_8009FE60.c:71, and src/slus/konami_runtime_w_80034F88.c:11-13 sets `unk_34 = unk_38 = value`). Under docs/evidence/town_script_modules.json's mapping, 0x80016004 is the header magic `0x4C070707`, whose first byte 0x07 is one of the six **unimplemented VM stub opcodes** (0,7,40,41,81,82). Either the "all modules load at 0x80016000" mapping or the callpath reader's "they are compiled MIPS C, not bytecode" is incomplete. Nobody noticed the collision.

---

## 5. WHERE THE READERS CONTRADICT EACH OTHER (beyond §1)

| Item | Reader | Verifier |
|---|---|---|
| printf call-site count (n=89) | 335 | 331 strict / 300 loose — "did not reproduce" |
| S_rand_sn (n=20) call sites | 18 | 6 strict / 23 loose — "the only part I could not confirm" |
| total dispatch sites harvested | 878 sites / 67 distinct IMMs | 571 sites (verifier 16) |
| state field-load histogram +0x18 | ×94 | ×249 |
| stub-run file offset | 0x565F0 | 0x565F4 (0x565F0 holds 0x800C830C) |
| tcame_* under the old rule | "scatter 0x8003BAF8..0x800C2400" | six of eight land on the stub |
| claim 5 sub-clause "nouse names on real functions" | asserted | **false** — both lie inside 118..182 |
| claim 18 title | "seven" | eight names |
| claim 23 descriptor fields | {u24 size, u8 type, u32 sector} | "field decomposition WRONG" (no replacement given; see §2) |

No agreed call-site harvest exists. Since the whole "only 2 of 65 stub slots are ever called" argument (claims 7d, 8, 9) rests on that harvest, the population discrepancy (878 vs 571) is load-bearing and unresolved.

---

## 6. A CLAIM THAT IS SIMPLY WRONG, AND IT HAS ALREADY CONTAMINATED THE TREE

Claim 25 says the 46 misaligned names in `ledger/evidence/names_proposed.tsv` are "NOT yet applied … no source names in the tree are affected", justified by a `comm` on the *address* column against config/names.tsv. That test is the wrong test. **15 of the 46 proposed names already appear in src/ as documentation comments:**

- src/town/func_800C37F0.c:5 `/* jyotyu_set_reserve_pool: … */` — corrected name is **set_no_change_seq** (n=32; verifier 12 caught this one file)
- src/town/func_8008DB5C.c:3 `/* tw_seq_end_chk: … */` — corrected name is **FNO_jyotyu_set_reserve_all** (n=113)
- src/town/func_8008E094.c:5 `/* start_mogura_func: … */` — corrected n=100 target is 0x800C22D8, not 0x8008E094
- src/slus/code.c:543 `/* file_load_com: … */` and :651 `/* jyotyu_set_reserve_nyul: … */` — FNO-derived names applied to **resident** functions, which under either rule are town-table targets
- plus func_8008DB64, DB6C, DB74, DB7C, 8008DDF0, 80092C48, 800B5440, 800C3704, 800C43C0, 800CABAC

---

## 7. THE SINGLE NEXT STEP

**Disassemble the callee of `func_800C0EAC` — find the code that *writes* the word at 0x80016000 — by following `packet.handler` (packet word 0, `sp+0x10`) inside the module images, not by absolute-address scanning.**

Concretely: from any of the 54 module images (start with module 0, file 0x2AB800, entry 0x8001A484), find every function that receives a `Packet*` and does `lw rY,0x10(a0)` followed by `sw …,0(rY)`, and disassemble it. This one probe settles, in order:

1. the §1 contradiction — whether the slot holds a state pointer, an entry pointer, or both in different phases (and therefore whether claim 22's "module entry" reading or claim 1's "state publication" reading is the right frame for `S_flgtst`);
2. the strength of every negative in the result set, since it is the exact store class all three scanners cannot see — including "the ONLY store to 0x80016000" (claim 1) and "no runtime patching of the table" (claim 7), the two claims that carry the whole "the 65 stubs get no implementation anywhere" conclusion;
3. the loader question, because the same routine is what consumes the `{type|0x016000, CD sector}` descriptors at 0x800D3C00 / 0x800D4360 / 0x800D4378 / 0x800D4380 that `func_800C0EAC` hands over as `packet.data0` and that the resident registry at 0x8006AEC4 selects between.

Second priority, if a second step is available: dump and name the resident registry at 0x8006ADC0..0x8006AF20 (§2). It is the "per-scene table / registration mechanism" the original brief posited, it statically names the town table pair, and it is where a dungeon-side equivalent of `0x800D3CC8` would have to appear.

Files opened for this critique (no files written; scratch dir work/research_fno/critic created and unused, all scripts inline): <home> <home> <home> <home> <home> <home> <home> <home> <home>
