# `extern-j-only` split-audit targets: are they mis-split functions?

*2026-09-22. Retail-byte investigation of every `extern-j-only` target named in the split-audit
finding. Method: `mipsel-linux-gnu-objdump -D -b binary -m mips:3000 -EL` over the container image
(`build_ovl/work/s3_splat/extract/{DUNGEON_DUNGEON,TOWN_TOWN}.BIN`), addresses resolved through the
delta the row links at (`config/overlays/<fam>.rowbase.jsonl` + registered `true_name`s, the same
`Segments` resolution `tools/split_audit.py` uses). Jumper/caller counts re-derived with the same
whole-image `j`/`jal` index.*

## 0. Headline

**None of the targets is a mis-split function, and no row merge is needed.** Three distinct
non-mis-split causes account for all of them:

| cause | targets | what it really is |
|---|---|---|
| switch jump table / case label | `func_80025DF4`, `func_80172670/78/80` | a label inside one function; the table lives in a neighbouring row |
| `#define` alias defeats the audit's regex | `func_8017153C`/`15E4`/`1650`/`174C`/`17E4`/`1910` | the row's **own** intra-function labels, renamed by `#define` to the true-space spelling |
| genuine inter-overlay noreturn tail jump | `func_80016120` | a real call into a co-resident overlay |

**One real defect found, in the tooling, not in the split:** `tools/split_audit.py` (and
`tools/levels.py`, whose `tail_jump_targets` it imports) reads the C **before** the preprocessor and
resolves the target address with the **declaring row's own delta**. Both assumptions break on
overlay containers, and in the `dungeon/func_80BD3BA8` case they break together and produce a
false `extern-j-only` that is currently holding a row at L3. §3 and §5.

Freshly re-run audit (this investigation, 2026-09-22): 139 records over 99 rows —
`intra` 87, `extern-jal` 26, `unresolved` 22, `extern-j-only` 3, `asm` 1. The 3 `extern-j-only`
records are `town/func_8047E0D8 -> func_80016120`, `dungeon/func_80BD3BA8 -> func_801717E4`,
`dungeon/func_80BD3BA8 -> func_80171910`. The larger jumper counts in the original finding
(10 / 5 / 2) are **not reproducible against the current tree**; §5 explains where they came from.

---

## 1. `dungeon` `func_80025DF4` — the shared epilogue of `func_80024F10`, already one row

**Declared by** `dungeon/func_818FE800` (foff `0x191E800`, size `0x1B0`, true base `0x80024000`,
delta `0x7E705800`). **Target** `0x80025DF4` = dungeon foff `0x19205F4`.

**Bytes at the target** (the finding's `lw ra,124(sp)` …), and the prologue they pair with:

```
80024f10:  27bdff80   addiu  sp,sp,-128        <- prologue of func_80024F10
80024f30:  afbf007c   sw     ra,124(sp)
...
80025df4:  8fbf007c   lw     ra,124(sp)        <- "func_80025DF4"
80025df8:  8fbe0078   lw     s8,120(sp)
80025dfc:  8fb70074   lw     s7,116(sp)
   ... s6 s5 s4 s3 s2 s1 s0 ...
80025e1c:  27bd0080   addiu  sp,sp,128
80025e20:  03e00008   jr     ra
80025e24:  00000000   nop                      <- function ends 0x80025E28
```

The frame size (`-128`) and the `ra` slot (`124(sp)`) match exactly: `0x80025DF4` is the epilogue
of the function whose prologue is at `0x80024F10`.

**Jumpers** — 10 `j`, 0 `jal`, every one inside `[0x80024F10, 0x80025E28)`:
`0x80025364, 0x800254DC, 0x800255A0, 0x800255D0, 0x80025614, 0x80025BA8, 0x80025CD4, 0x80025D18,
0x80025D88, 0x80025DE8`.

**Row layout is already correct.** `func_80024F10` is *one whole row*:
`dungeon/func_818FF710`, foff `0x191F710`, size `0xF18` = `[0x80024F10, 0x80025E28)` — prologue to
`jr ra` inclusive. Nothing is cut. The segment's other rows also land exactly on function
boundaries (`jr ra` at `0x800241A8 / 0x800243F8 / 0x800244C4 / 0x800245E4 / 0x800246F0 /
0x80024748 / 0x80024778 / 0x80024994 / 0x80024DB0 / 0x80024F08` against row ends `0x800241B0 /
0x80024400 / 0x800244CC / 0x800245EC / 0x800246F8 / 0x80024750 / 0x80024780 / 0x8002499C /
0x80024DB8 / 0x80024F10`).

**Why the name exists at all.** `src/dungeon/func_818FE800.c` mentions `func_80025DF4` only inside
its `#ifdef __mips__` arm, as entry 7 of

```c
static void (*const func_80024000_bank2[])(void)
    __attribute__((section(".text.func_80024000"))) = {
    func_80025030, func_800250A4, func_8002536C, func_8002561C, func_80025BB0,
    func_80025CDC, func_80025D20, func_80025DF4, func_80025D90,
};
```

which is the jump table of the `jr v0` switch at `0x80025028` — inside `func_80024F10`. Every
entry lies in `[0x80024F10, 0x80025E28)`. Case 7 of that switch is `break;`, i.e. it branches
straight to the shared epilogue, which is why a case label coincides with the epilogue.

**Verdict: NOT a mis-split, NOT a shared fragment.** Computed-goto / `casesi` table entry.
`dungeon/func_818FF710`'s `l5_residue` already records `computed_goto`.

**Proposed row layout: unchanged.** The only honest follow-up is an L4 *module* fact, not a split
change: the tables at `0x80024000..0x8002407C` (`func_80024000_bank`, a 12-word data block, and
`func_80024000_bank2`) sit at the head of the overlay's text and serve switches in *other*
functions of the same TU (`func_80024000_bank`'s entries `0x80024658/74/9C` belong to the `jr v0`
at `0x80024650` inside `func_800245EC`; `bank2` belongs to `func_80024F10`). They should be placed
in the same module as those functions when `l4_modules` runs; they are not a separate function.

---

## 2. `dungeon` `func_80172670` / `func_80172678` / `func_80172680` — three 8-byte case bodies

**Declared by seven rows**, all 0x350-byte jump-table rows of seven *duplicate copies* of the same
monster-AI overlay bank:

| row | foff | true base | segment run (foff) | is `0x80172670` in its own run? |
|---|---|---|---|---|
| `dungeon/func_81251000` | `0x1271000` | `0x80170800` | `[0x1271000,0x127468C)` | **yes** (foff `0x1272E70`) |
| `dungeon/func_81257000` | `0x1277000` | `0x8016A800` | `[0x1277000,0x127A68C)` | no (arithmetic lands at foff `0x127EE70`, a foreign segment) |
| `dungeon/func_81263000` | `0x1283000` | `0x8015E800` | `[0x1283000,0x128668C)` | no (foff `0x1296E70`) |
| `dungeon/func_81269000` | `0x1289000` | `0x80158800` | `[0x1289000,0x128C68C)` | no (foff `0x12A2E70`) |
| `dungeon/func_81275000` | `0x1295000` | `0x8014C800` | `[0x1295000,0x129868C)` | no (foff `0x12BAE70`) |
| `dungeon/func_8127B000` | `0x129B000` | `0x8016F800` | `[0x129B000,0x129E68C)` | **yes** (foff `0x129DE70`) |
| `dungeon/func_8128D000` | `0x12AD000` | `0x8015D800` | `[0x12AD000,0x12B068C)` | no (foff `0x12C1E70`) |

**Bytes at the target** (bank `0x80170800`, delta `0x7EEFF800`):

```
801725f8:  10400023   beqz   v0,0x80172688         <- switch bounds check
801725fc:  3c028017   lui    v0,0x8017
80172600:  24420860   addiu  v0,v0,2144            <- jump table at 0x80170860
80172608:  00621821   addu   v1,v1,v0
8017260c:  8c620000   lw     v0,0(v1)
80172614:  00400008   jr     v0                    <- casesi dispatch
...
8017261c:  0805c99c   j      0x80172670            <- case, delay slot li s5,1
80172624:  0805c99e   j      0x80172678
8017262c:  0805c9a0   j      0x80172680
...
80172644:  1062000c   beq    v1,v0,0x80172678      <- second (if/else) dispatch
80172654:  1062000a   beq    v1,v0,0x80172680
80172670:  0805c9a3   j      0x8017268c            <- "func_80172670": 8 bytes
80172674:  2611000e   addiu  s1,s0,14
80172678:  0805c9a3   j      0x8017268c            <- "func_80172678": 8 bytes
8017267c:  2611000b   addiu  s1,s0,11
80172680:  0805c9a3   j      0x8017268c            <- "func_80172680": 8 bytes
80172684:  26110008   addiu  s1,s0,8
80172688:  00008821   move   s1,zero               <- default
8017268c:  92220000   lbu    v0,0(s1)              <- join
```

Each "function" is **two instructions**: set `s1` to a member pointer and `j` to the join at
`0x8017268C`. They are the bodies of a three-way selection (`s1 = &s0->unk_0E / unk_0B / unk_08`),
reached both from the `casesi` table at `0x80170860` and from a following `beq` chain — and the
table in `src/dungeon/func_81251000.c` spells exactly that:

```c
    func_80172680, func_80172678, func_80172670, func_80172688,
    func_8017262C, func_80172624, func_8017261C,
```

**Jumpers** (resolved in the bank that actually owns the address, `0x80170800`): `func_80172670`
1 `j` (`0x8017261C`), `func_80172678` 1 `j` (`0x80172624`), `func_80172680` 1 `j` (`0x8017262C`),
0 `jal` each. The extra table references are `lw`/`jr v0`, not `j`, so they do not show in a
`j`/`jal` index.

**Verdict: NOT functions, NOT a mis-split, NOT a dispatcher entry set.** They are case labels
inside one large un-split function of the bank; that function is not a row, so no row was cut. It
is the same `casesi` class as §1.

**Proposed row layout: unchanged.** Two naming debts to record, neither a split change:

1. In five of the seven rows (`81257000`, `81263000`, `81269000`, `81275000`, `8128D000`) the name
   `func_80172670` denotes an address that is **not in that bank**; each bank's own copy of the
   label sits at a different absolute address. In those five files the names are dead
   `extern void func_801726xx(void);` declarations only (their tables are raw
   `static const u32 bank_words[] __asm__("func_812xx000")`), so nothing links against them — but
   they are wrong names and should be dropped or re-spelled per bank.
2. Cross-bank duplicate code: seven byte-similar copies of one AI routine at different link bases.
   That duplication is what makes address-keyed reasoning about this container unsafe (§5).

---

## 3. `dungeon` `func_8017153C` / `801715E4` / `80171650` / `8017174C` / `801717E4` / `80171910`
### — the declaring row's *own* labels; the `extern-j-only` verdict is FALSE

**Declared by** `dungeon/func_80BD3BA8` (foff `0xBF3BA8`, size `0x634`, true base `0x8015F3A8`,
delta `0x7F56B800`). Currently at **L3**, and two of these are the tree's only dungeon
`extern-j-only` records — so the L3 rests on a false classification.

`src/dungeon/func_80BD3BA8.c` lines 6-13 are:

```c
#define func_8017153C func_8015F53C
#define func_801715E4 func_8015F5E4
#define func_80171650 func_8015F650
#define func_8017174C func_8015F74C
#define func_801717E4 func_8015F7E4
#define func_801718D4 func_8015F8D4
#define func_801718D8 func_8015F8D8
#define func_80171910 func_8015F910
```

The legacy `func_80171xxx` spelling is the row's pre-true-base naming, exactly `0x12000` above the
true-space name. Every `func_8015Fxxx` target lies **inside** the row's own extent
`[0x8015F3A8, 0x8015F9DC)`. The retail bytes confirm the row is one whole function:

```
8015f3b0:  27bdffd0   addiu  sp,sp,-48      <- single prologue
8015f9d4:  03e00008   jr     ra             <- single epilogue, row ends 0x8015F9DC
```

and every `j` in the row's 0x634 bytes stays inside it:

```
8015f404 j 8015f9b4   8015f418 j 8015f9b4   8015f530 j 8015f53c   8015f5d0 j 8015f5e4
8015f624 j 8015f650   8015f6e8 j 8015f74c   8015f71c j 8015f74c   8015f774 j 8015f910
8015f790 j 8015f7e4   8015f848 j 8015f910   8015f874 j 8015f8d4   8015f8a8 j 8015f8d8
```

(the only `jal`s go to `0x800A9E70`, `0x800AA36C`, `0x80047738`, `0x800A020C`, `0x800478B8`,
`0x800BCB04` — ordinary external calls.)

The two live call sites are `func_80171910();` (line 201) and `func_801717E4(motion_flags);`
(line 220); after preprocessing they are `func_8015F910()` and `func_8015F7E4()` — **label-as-call
pseudo-calls to the row's own labels**, i.e. the ITC/LAC class, not a tail jump out of the row.

**Verdict: NOT a mis-split and NOT a shared fragment. The audit record is wrong: the correct kind
is `intra`.** The row already *is* the whole function; nothing to merge.

**Why the audit says otherwise** — the two failures compose:

* `levels.tail_jump_targets` matches the raw C, so it takes the token `func_801717E4`, not the
  `#define`d `func_8015F7E4`. `split_audit.py` then computes `ta = 0x801717E4`, which is `0x12000`
  above the row's extent, so it never reaches the `intra` branch.
* `split_audit.py` resolves the target file offset with the **declaring row's** delta:
  `0x801717E4 - 0x7F56B800 = 0xC05FE4`. That offset is **not in the row's segment**
  (`[0xBF3060, 0xBF6E34)`); it is in a foreign dungeon segment `[0xC05060, 0xC08E34)` whose delta
  is `0x7F547800`, where the code links at `0x8014D7E4`, not `0x801717E4`.
* That foreign segment is a near-duplicate of the same routine `0x12000` later in the file, so its
  own intra-function jumps mirror the row's exactly. The audit therefore reports plausible-looking
  jumper counts that are in fact another copy's jumps:

| target | audit's foff | reported jumpers | what they really are |
|---|---|---|---|
| `func_8017153C` | `0xC05D3C` | `0x8014D530` | foreign copy's `j` at foff `0xC05D30` |
| `func_801715E4` | `0xC05DE4` | `0x8014D5D0` | foff `0xC05DD0` |
| `func_80171650` | `0xC05E50` | `0x8014D624` | foff `0xC05E24` |
| `func_8017174C` | `0xC05F4C` | `0x8014D6E8`, `0x8014D71C` | foff `0xC05EE8`, `0xC05F1C` |
| `func_801717E4` | `0xC05FE4` | `0x8014D790` | foff `0xC05F90` |
| `func_80171910` | `0xC06110` | `0x8014D774`, `0x8014D848` | foff `0xC05F74`, `0xC06048` |

Each foreign offset is exactly `0x12000` above the row's own corresponding jump (`0xBF3F74 +
0x12000 = 0xC05F74`, and so on) — proof that the match is the duplicate, not a shared tail.

**Proposed fix (source, byte-neutral by construction; NOT applied here — see §6).** Delete the 8
`#define` lines and the 8 legacy `extern void func_80171xxx() __attribute__((noreturn));`
declarations (lines 21-28), and spell the two call sites `func_8015F910()` / `func_8015F7E4(...)`.
The preprocessed translation unit is then identical except for eight duplicate declarations being
removed, so the compiled object cannot change. **But it re-classifies the row honestly and that
costs a level**: `levels.intra_tail_calls` would then see 2 pseudo-calls to labels inside the row,
which blocks **L1**, so `dungeon/func_80BD3BA8` drops from L3 to L0 until the labels are given a
real C shape (`goto` / if-else join, the LAC templates of
`docs/L0_BLOCKED_PLAN_20260922.md` §6). That is a deliberate owner-level trade, not a cleanup, so
it is proposed, not done.

**Proposed fix (tooling, the better one).** Make `levels.tail_jump_targets` resolve object-like
`#define A B` aliases over `func_[0-9A-F]{8}` before collecting targets. That alone turns these two
records into `intra` for every row that carries the true-base `#define` shim, with no source edit.
It is a change to a level-defining tool and moves rows between levels, so it needs the owner's
call.

---

## 4. `town` `func_80016120` — a genuine inter-overlay noreturn tail jump

**Declared by** `town/func_8047E0D8` (foff `0x3FE0D8`, size `0x58`, true base `0x8001F0D8`,
delta `0x7FC21000`). Currently **L0**, `l4_residue: [tail_jump, not_in_module]` — matching
`docs/L0_BLOCKED_PLAN_20260922.md` §6's "LAC-other hold-set (no C spelling, genuine inter-row j),
1 row, 88 bytes".

**The whole row, from retail:**

```
8001f0d8:  3c028001   lui   v0,0x8001
8001f0dc:  8c436000   lw    v1,24576(v0)     <- the fixed word 0x80016000 (docs/SYMBOLS.md §5.1)
8001f0e0:  27bdffe8   addiu sp,sp,-24
8001f0e4:  afbf0010   sw    ra,16(sp)
8001f0e8:  8c620008   lw    v0,8(v1)
8001f0ec:  8c630040   lw    v1,64(v1)
8001f0f0:  000210c0   sll   v0,v0,0x3
8001f0f4:  00431021   addu  v0,v0,v1
8001f0f8:  8c420000   lw    v0,0(v0)
8001f100:  14400005   bnez  v0,0x8001f118
8001f108:  0c00584c   jal   0x80016130       <- ra := 0x8001f110
8001f110:  08005848   j     0x80016120       <- the audited "jumper"
8001f118:  0040f809   jalr  v0
8001f120:  8fbf0010   lw    ra,16(sp)
8001f128:  03e00008   jr    ra
```

**Jumpers: 1 — and it is this row's own `j` at `0x8001F110`.** There is no second site, so
"shared tail fragment" has no support at all.

**The target is outside this row's segment.** `0x80016120 - 0x7FC21000 = 0x3F5120`, and those
bytes are Shift-JIS script text, not code:

```
003f5110: 8373 835e 82cc 8ec0 82f0 8ee8 82c9 93fc
003f5120: 82ea 82bd 8149 8149 110a 0c16 002e 7901
```

(`0x8373 0x835E` = カタ…, `0x8149` = "！"). `Segments` assigns that offset no delta at all. So the
audit's `extern-j-only` here is again single-delta aliasing: the target lives in a co-resident town
overlay, not in this scene module, and the only `j` the index could find at that offset was the
row's own.

**This `j` has no C call producer, and that is the point.** `docs/FIDELITY.md` and the
`tools/split_audit.py` docstring: genuine cc1 emits `jal` even for an
`__attribute__((noreturn))` call, and official ASPSX never rewrites `jal`→`j`. So no C *call* of
any kind produces this `j` — it is the `hold-set` residue class of
`docs/L0_BLOCKED_PLAN_20260922.md` §6: "LAC-other hold-set (no C spelling, genuine inter-row j)".
The audit exists to decide whether such a `j` means a mis-split; here it does not (§ jumpers
above), so what is left is a producer-less jump with no honest C spelling.

**Retail independently proves the target cannot return**, which is why the noreturn placeholder is
the right stand-in rather than a guess: `jal 0x80016130` sets `ra = 0x8001F110`; the very next
instruction is `j 0x80016120`. If `0x80016120` ended in `jr ra` it would branch back to that same
`j` and spin forever. So `extern void func_80016120(void) __attribute__((noreturn));` states a
fact about the callee, and the row stays an L4-tracked tail-jump residue.

**Beware a same-named row.** `town/func_80632120` (foff `0x5B2120`, size `0x5C`) is registered with
`true_name func_80016120` and *is* a complete returning function
(`addiu sp,sp,-24` … `jr ra` at `0x80016174`). It belongs to a **different** town chunk that also
links at `0x80016120`; it is not this target. The neighbouring `func_80016130` is likewise
registered in yet another chunk (`town/func_80614930`, foff `0x594930`), while under chunk
`0x5B2120`'s delta `0x80016130` falls in the middle of `func_80016120`'s body. Town chunks overlap
in address space; an address-keyed identity for `0x80016xxx` is meaningless without the chunk.

**Verdict: NOT a mis-split, NOT a shared fragment.** A producer-less inter-overlay `j` into a
co-resident overlay whose callee never returns — the `hold-set` class, not a split error. The
honest C spelling is the noreturn placeholder the tree already uses; it stays an L4-tracked
tail-jump residue, per `levels.py`'s L4 rule.

**Proposed row layout: unchanged.**

---

## 5. What the original finding's larger jumper counts were

The finding quoted 10 jumpers for `func_80025DF4`, 5 for each of `func_80172670/78/80`, 2 for
`func_8017174C`/`func_80171910` and 1 for the rest. Re-running `tools/split_audit.py` against the
current tree produces **3** `extern-j-only` records, and `git show HEAD:ledger/split_audit.jsonl`
has the same 3 — so the larger set is not reproducible here. The measurements above explain both
halves:

* the **counts** are real numbers of `j` instructions, but for `func_80172670/78/80` and the
  `func_80171xxx` family they are counts taken in a *foreign duplicate segment* that the
  declaring row's delta happened to point at (§2, §3). Five of the seven banks in §2 resolve the
  trio outside their own segment; which foreign offset you land on — and therefore how many
  jumpers you count — changes whenever a `rowbase` record or a `true_name` registration changes the
  run boundaries. `config/overlays/*.rowbase.jsonl` are modified in the working tree today, so the
  audit's resolution has moved since the finding was taken.
* the **`func_80025DF4` 10-jumper count is exactly right** (§1) and reproduces today; what changed
  is only whether `levels.tail_jump_targets` still lists it as a dependency of
  `dungeon/func_818FE800` (it does not: the name appears only in an initializer list, never as a
  call).

### 5.1 How far does the `#define` shim reach? — census

`rg -n --max-filesize 4M '#\s*define\s+func_[0-9A-Fa-f]{8}' src/` over `src/` finds **three files
only**, in two distinct shapes:

| file | shim | effect on the audit |
|---|---|---|
| `src/dungeon/func_80BD3BA8.c` | `#define func_<legacy> func_<true>` × 8 | **misdirects**: the audit reads the legacy token, lands `0x12000` away in a foreign segment, and reports foreign jumpers (§3). 2 false `extern-j-only` records, the only ones in dungeon. |
| `src/dungeon/func_81898B70.c` | `#define func_80024264_returning func_80024264` (with `__asm__(".set …")` in the `__mips__` arm) | **hides**: `func_80024264_returning(` does not match `func_[0-9A-F]{8}\s*\(`, so no record is demanded at all. |
| `src/dungeon/func_80CEB850.c` | `#define func_80171BEC_returning func_80171BEC` (same shape) | **hides**: same. |

The legacy-rename shape is a one-off (one file), so the §3 defect is bounded: **2 records, 1 row**.
It is not a systematic product of true-base landings — `promote_honest.py` registers the true name
in `ledger/splits/<fam>.jsonl`, it does not emit `#define` shims.

The `_returning` shape is *honest in intent* (it marks a call the family-wide noreturn census would
otherwise misread) and both of its targets check out: `func_80024264` (dungeon foff `0x18B8A64`)
and `func_80171BEC` (foff `0xD083EC`) each lie inside their declaring row's own run and are each
reached by a real `jal`, 0 `j` — genuine returning functions. But because the spelling evades
`tail_jump_targets`, `levels.py`'s L3 rule ("every tail-jump dependency carries a record") passes
those two rows without a record ever being written. Worth a line in the level rule; not a false
verdict and not a mis-split.

**No shimmed row produces an `extern-jal`**, so nothing here is currently feeding
`ledger/split_audit_false_members.candidates.jsonl` (that file came out empty on this run). The
§5 hardening is therefore a correctness nicety for the audit, **not** a blocker for the sibling
appending to `config/noreturn_false_members.jsonl`.

**Recommended hardening of `tools/split_audit.py`** (proposal only, not applied):

1. Resolve the target with the segment that *contains the target offset*, and emit a new kind —
   `cross-segment` — when the target address is not inside the declaring row's own run. Today such
   a target is silently attributed to whatever foreign code occupies the arithmetic offset, and
   every jumper reported for it is another module's. This is the single highest-value fix: it
   turns §2/§3/§4 from confident-looking false verdicts into an honest "not decidable in this
   row's segment".
2. Expand object-like `#define func_X func_Y` aliases before extracting targets (§3).
3. Recognise a target that is an entry of a `(*const [])(void)` jump table in the same row as a
   `casesi` label rather than a call (§1, §2); it has no `j`/`jal` producer in the declaring row at
   all.

---

## 6. Actions taken and not taken

* **Taken:** measurement only, plus the §5.1 shim census. No row merged, no split changed, no
  window re-gated — because no target is a mis-split. `tools/split_audit.py` was re-run with
  `--out` into a scratch path, so `ledger/split_audit.jsonl` is unchanged; `tools/levels.py` and
  `tools/status.py` were deliberately NOT run (they rewrite `ledger/levels.jsonl`, which the
  concurrently landing sibling agents read, and nothing was landed that would change them). `config/`, `ledger/splits/`, `config/overlays/*.rowbase.jsonl` and the
  window yamls are untouched by this investigation.
* **Superseded by §7** (owner direction 2026-09-22: accuracy first). The proposals below were
  made and landed; the paragraph is kept for the record.
* **Not taken at the time (needed the owner's call, both change levels):** the `#define` cleanup in
  `src/dungeon/func_80BD3BA8.c` (§3) — byte-neutral for the object, but it drops that row from L3
  to L0 by making an already-true ITC residue visible; and the `tail_jump_targets` alias expansion
  (§3) plus the `cross-segment` kind (§5), which are edits to the level-defining tools.


---

## 7. Fixes applied (owner direction: accuracy first, 2026-09-22)

### 7.1 `tools/split_audit.py` — new kind `cross-segment`

`Segments.run(foff)` was added (the merged same-delta run holding a file offset; `delta()` is now
derived from it, so the two can never disagree). When a target address is **not inside the
declaring row's own run**, the record is `cross-segment`: the verdict is written, the foreign
segment's `j`/`jal` sites are **not**. `target_foff` and `row_run` are recorded, and the proof
names the other run and the address the code there really links at. The kind is documented in the
module docstring next to the others. `extern-jal` false-member candidates are unaffected by
construction (a `cross-segment` record can never generate one — which is the point: before the
fix, `dungeon/func_813284E4 -> func_800A9A0C` was an `extern-jal` resting on another segment's
`jal`, and had that symbol been on the dungeon noreturn list it would have produced a bogus
candidate line).

### 7.2 `tools/levels.py` — `resolve_spellings()` before every tail-jump scan

`_noreturn_call_targets()` and `_call_text()` now read an alias-expanded, jump-table-blanked view:

* object-like `#define <ident> func_XXXXXXXX` and its `__mips__` twin
  `__asm__(".set <ident>, func_XXXXXXXX")` are expanded (chains followed, cycle-guarded), so the
  token a call is counted under is the symbol the preprocessor really emits. Read from the whole
  file, both arms, on purpose — a `_returning` shim spells the same alias in each arm.
* `(*const NAME[])(...) … = { … };` initializers are blanked, so a `casesi`/dispatch table entry
  can never become a "call", whatever list the symbol is on.
* the rewrite is **line-count preserving** (`_blank_keep_lines`), because every caller zips the
  text against `pin_census.arm_labels()`, which is per-line.

`audit_gate()`'s docstring now states that `cross-segment` clears L3 like `extern-jal` and blocks
L4 like every tail-jump dependency (it needed no code change: the L3 rule excludes only `intra`,
`unresolved` and the `missing` sentinel, and L4 tolerates none of any kind).

### 7.3 Tests

`tools/tests/test_levels.py`, keeping its existing structure (synthetic rows, `_CONTAINER_SYMS`
pre-seeded empty, no filesystem writes): `test_cross_segment_record_reaches_l3_but_not_l4` in
`TailJumpLadder`; a new `SpellingShims` class with one test per fix
(`test_define_alias_is_expanded_to_the_true_spelling` — which also pins the L3→L0 consequence on
the pre-cleanup shape of `dungeon/func_80BD3BA8`; `test_returning_shim_no_longer_hides_a_container_list_dependency`
over both shim spellings; `test_function_pointer_table_entry_is_not_a_call`, which also checks a
real call of the same symbol still counts; `test_resolve_spellings_preserves_line_count`); and a
new `SegmentRuns` class unit-testing `Segments.run()` without reading `config/` or an image.
`./.venv/bin/python3 -m pytest tools/tests -k "levels or census" -q` -> **38 passed** (31 before).

### 7.4 Source cleanups landed (all byte-exact, all windows MATCH)

| row | change | verify | window |
|---|---|---|---|
| `dungeon/func_80BD3BA8` | 8 `#define` shims + 8 duplicate legacy `extern`s deleted, the two call sites spelled `func_8015F910()` / `func_8015F7E4(...)` | `exact: true` | `dungeon_deep_bf3060_truebase_8015e860` MATCH |
| `dungeon/func_80BD3BA8` (2nd pass) | the 6 now-unused `noreturn` label declarations deleted | `exact: true` | MATCH |
| `dungeon/func_81257000`, `81263000`, `81269000`, `81275000`, `8128D000` | all 28 dead `extern void func_8017xxxx(void);` declarations deleted — every one unused **and** naming an address outside that bank's own run | `exact: true` ×5 | `dungeon_deep_t8b_{1277000,1283000,1289000,1295000,12ad000}` MATCH |
| `dungeon/func_8127B000` | the 6 dead declarations that name an address outside its run deleted (its other 22 are dead but correctly named, so left alone) | `exact: true` | `dungeon_deep_t8b_129b000` MATCH |
| `dungeon/func_81251000` | **untouched**: all 28 of its declarations are used (it is the bank that carries the real pointer table) and all name addresses inside its own run | — | — |

Landed through `tools/promote.py --source agents:claude-opus-l0` (7 rows, `{'landed': 7}`).

### 7.5 Effect: kind histogram and levels

`ledger/split_audit.jsonl` kind histogram, same tree, fixes off -> on (the ledger also moves under
concurrent sibling landings; this pair is the isolated control, both runs over the same `src/`):

| kind | before | after |
|---|---:|---:|
| `intra` | 55 | 57 |
| `extern-j-only` | 3 | **0** |
| `cross-segment` | 0 | **2** |
| `extern-jal` | 1 | 1 |
| `unresolved` | 9 | 9 |
| `asm` | 1 | 1 |
| total | 85 | 86 |

Record-level diff (the whole of it):

* `dungeon/func_80BD3BA8 -> func_801717E4` / `-> func_80171910` (`extern-j-only`, foreign jumps)
  become `-> func_8015F7E4` / `-> func_8015F910` (`intra`) — the honest reading.
* `town/func_8047E0D8 -> func_80016120`: `extern-j-only` -> `cross-segment`.
* `dungeon/func_813284E4 -> func_800A9A0C`: `extern-jal` -> `cross-segment` (a *false* `extern-jal`:
  the `jal` belonged to another segment).
* `dungeon/func_80CEB850 -> func_80171BEC`: **new record**, `extern-jal` — the dependency the
  `_returning` shim hid.

**Rows whose level changed because of the fixes:**

* **`dungeon/func_80BD3BA8`: L3 -> L0.** Its two pseudo-calls are calls of labels inside its own
  extent, so `blocking` is true and L1 is not reached. This is the correct reading and the owner
  accepts it; the tool fix and the source cleanup each produce it independently (the unit test
  pins the tool-fix half on the pre-cleanup text).
* **`dungeon/func_80CEB850`: L3 -> L2 -> L3.** The levels fix surfaced its hidden dependency; it
  sat at L2 (`split_audit: ["missing"]`) until the audit was re-run, and is back at L3 with an
  honest `extern-jal` record. It was never L3-legitimate before — it simply had no record because
  no scan could see the call.
* **No other row moved.** Running `levels.py` twice over the same tree, fixes off vs on, gives the
  same level for every one of 6,767 rows.

Rows *not* moved but now honestly labelled: `town/func_8047E0D8` (L0 for its own reasons) and
`dungeon/func_813284E4` (L3 before and after — `cross-segment` clears L3 like `extern-jal`).

### 7.6 The one ITC attempt, measured and refused

`dungeon/func_80BD3BA8`'s remaining blocker is two label-as-call sites. The retail mapping is now
known exactly: `0x8015F910` is the `finish_motion:` label the C already carries, and `0x8015F7E4`
is the `if (!(… & 8))` test of the later block, whose two predecessors differ only by `+=` vs `-=`
on `entity+0x90` and join in the branch delay slot (`sw v1,144(s1)`).

Site 1 rewritten as `goto finish_motion;` (the §6 ITC template) **did not verify**: `exact: false,
class: block-order, subs 14, indels 22` — gcc reorders the basic blocks when the jump out of the
nested arm becomes a `goto`. Reverted, not landed. Site 2 needs the "init join" restructure
(shared `height_sum`/`motion_flags` locals across both arms) and was not attempted. What *was*
landed from this attempt is the byte-exact part: the 6 dead `noreturn` declarations.

### 7.7 Open items found while doing this

* **`func_80171BEC` is a genuine false-member candidate.** Retail reaches it by `jal` from
  `0x80175184` and by `j` from nowhere (JAL-ONLY), and `src/dungeon/func_80CEB850.c` works around
  the census membership with the `_returning` shim. It is still in
  `config/noreturn_syms.dungeon.txt` and still absent from `config/noreturn_false_members.jsonl`
  (52 data entries, none of them this symbol), which is **why** the candidates file has one line.
  The `already` filter is consulted normally on this path — verified by re-running the audit with
  that one entry injected into the false-members read: **0 candidate lines**. `config/` was not
  edited here.
* **`gen_noreturn_syms.py` cannot regenerate the censuses today — and it is not a one-line fix.**
  The two copies are byte-identical (`md5 99861076…`). `tools/gate/`'s copy resolves
  `ROOT = parents[1]` to `<repo>/tools`, which has no `config/` or `overlays/`, so from the repo
  root every family matches 0 source files and it **fails closed** (`--check`: four
  `FAIL … 0 source files match its scan globs`) — it never writes a wrong census. The working copy
  is `build_ovl/tools/gen_noreturn_syms.py`, where `ROOT = build_ovl` is correct by design
  (`build_ovl/config/*` are symlinks to `<repo>/config/*`, `build_ovl/overlays/` is real). Changing
  `parents[1]` to `parents[2]` in the shared file would repoint that working copy at a *different*
  corpus and rewrite censuses that gate every overlay window, so it was **not** made.
  The deeper cause is that `CONTAINERS`' globs still name the old corpus
  (`overlays/<fam>/first_pass_matched/*.c`, plus `src/**/*.c` for `main`) while the live C now
  lives in `src/<container>/`: `build_ovl/tools/gen_noreturn_syms.py --check` reports
  `FAIL [main] regeneration yields 0 symbols but the tracked file holds 32` and
  `DRIFT config/noreturn_syms.town.txt` (213 tracked lines vs 21 regenerated). Until the glob set
  is moved to the `src/<container>/` layout, the censuses can only be maintained by hand — which
  is what the 21-symbol hand edit of `config/noreturn_syms.dungeon.txt` had to do. Only `--check`
  was run here; nothing was written.
* `tools/split_audit.py`'s remaining hardening proposal from §5 — recognising a jump-table entry at
  the *audit* level — is now unnecessary for levels (§7.2 blanks tables before a target is ever
  collected), so no audit-side change was made for it.

* **CORRECTION (2026-09-22, both bullets above are now resolved).** The glob diagnosis was wrong:
  `overlays/<fam>/first_pass_matched/*.c` *does* resolve — `build_ovl/overlays/<fam>/first_pass_matched`
  are symlinks to `src/<fam>`. The census broke because the transform layers **strip the
  `__attribute__((noreturn))` declarations out of `src/`** (45 of 2,743 dungeon files still carry one);
  the evidence lives in the frozen, git-tracked `raw/<container>/*.c`, which the scan globs now read
  (`src/` measurably adds zero symbols in every family, held as a test). `ROOT` now resolves to the
  first ancestor holding both `raw/` and the false-members file, so both copies of the script agree.
  The missing `config/noreturn_evidence.main.c` (main's 7 attribute-less callees) was restored, the
  nine hand-deleted dungeon symbols got proven false-member records, and a shrink guard was added.
  `--check` is `ok` with zero drift on all four families from both copies. `func_80171BEC` is
  **applied**: dungeon 1,015 → 1,014, and `gate_all.py --container dungeon --retry` is 1,458/1,458
  MATCH — `--retry` is required, because `inputs_sha` does not hash the censuses.

### 7.8 `main/func_7FDD3D54` at the true base — cause found, fixed, landed

`docs/L0_BLOCKED_PLAN_20260922.md` section 6 left this as the open item: with the rowbase record
`row_23d54_8008acb4` (delta `0x80066F60`, true base `0x8008ACB4`) in place the row went from exact
to **11 subs / const-remat**, every `%hi`/`%lo` of `D_8008B368` / `D_8008B36A` / `D_8008B36C` /
`D_800814A0` reading `lui $v0, 0`, "while the instruction stream is otherwise unchanged".

**Cause (primary evidence, `match.py`'s own stderr):**

```
match.py WARNING: ld FAILED (src/main/func_7FDD3D54.c:(.text+0x30): relocation truncated to fit:
R_MIPS_26 against `func_7008ACFC') -> comparing the UNLINKED object; ALL relocs read 0
```

Nothing is wrong with the record, the bank, or the delta arithmetic. The row's own C still called
the **stale synthetic spelling** `func_7008ACFC`, which the injector name-encodes as the absolute
symbol `0x7008ACFC`. `R_MIPS_26` only reaches inside the PC's own 256 MB region: from a `.text`
linked at `0x7FDD3D54` that symbol is reachable, from one linked at `0x8008ACB4` it is not, so `ld`
fails, `build_text` falls back to the **unlinked object** (`--unresolved-symbols=ignore-all` never
gets a chance) and every relocated field reads 0. Only the `%hi`/`%lo` of the four data symbols
show up as substitutions because the scorer reloc-masks `j`/`jal` words. That is also why the
symptom looked data-specific: it is not: it is "no relocations at all".

Ruled out on the way: a `-G`/small-data overflow (the config is `-G0`; the failing reloc is named
`R_MIPS_26`, not `GPREL16`), a `.rodata`/`.data` twin (the row has no local data sections —
`_local_section_placements` derives none), a symbol file keyed on synthetic addresses (the same
catalogs resolve those four `D_` symbols correctly at the synthetic base), and the delta itself
(`0x23D54 + 0x80066F60 = 0x8008ACB4`, and `0x23DF8`, this row's `foff_end`, is the `foff_start` of
the already-**proven** `main_menu_t8_23DF8_true` region at the identical delta).

**Fix.** The symbol was never a callee. Retail is `j 0x8008acfc` at row `+0x30` with `sh v0,2(a1)`
in its delay slot — `base + 0x48`, a forward jump out of the `type == 0 && (flags & 2)` arm into
the row's own shared tail. Spelled as a C `goto` (the section 6 ITC template: forward jump to a
shared tail, no pin in front) it is **byte-exact at the true base first try**, and no symbol
outside the row is referenced any more, so the link succeeds.

**Landed 2026-09-22.** `src/main/func_7FDD3D54.c` (`tools/promote.py --source
agents:claude-opus-crossimage`: exact, class `match`, total 0); record `row_23d54_8008acb4`
re-added and **promoted solved -> proven** (`build_ovl/tools/rowbase.py promote`, absolute
candidate path, `2.7.2-cdk -fno-schedule-insns2`). Both covering windows re-gated:
`main_7fdd` MATCH (20,480 B) and `main_menu_t8` MATCH (28,676 B).

The promotion is what makes the `goto` legitimate: a `solved` region links **synthetic** in the
window gate, and a local-label `j` is base-dependent (at `0x7FDD3D54` it would encode
`0x7FDD3D9C`, not retail's `0x8008ACFC`). The old stale-symbol spelling was accidentally
base-independent — `func_7008ACFC` encodes retail's low 26 bits exactly — which is why the row had
been gate-clean while carrying a symbol that does not exist.

**Effect:** the row's only tail-jump dependency is gone (no record demanded at all, not merely a
better one), L2 -> **L3** with an empty `l5_residue`; `l4_residue` is `not_in_module` alone.
`main/func_7FDD3F8C` (the sibling at foff `0x23F8C`, target `func_7008AFF4`) is almost certainly
the same shape and the same one-line fix, but it has **no** rowbase record and is left alone here.

### 7.9 `tools/split_audit.py` — new kind `cross-image`

A target that does not land inside the declaring container's image under the row's own delta was
always `unresolved`, which blocks L3. Two things can still decide it, and both are now
`cross-image` (a decided verdict: clears L3 like `extern-jal`, blocks L4 like every tail-jump
dependency):

* `image: "slus"` — the address maps into a **code** subsegment of `baserom/slus_006.14` (the
  base executable, co-resident under every overlay) and a `jal` in SLUS code reaches it, or a
  `// type:func` symbol in `config/slus_006.14.symbols.txt` names it. The `// overlay self-define`
  stub lines are excluded: they name OVERLAY addresses so an overlay TU can link, and reading one
  as SLUS code is the false positive this kind must not make. The SLUS index is built only over
  the yaml's `asm`/`c` subsegments — indexing the resident data block would decode ASCII as `jal`.
* `image: "absent"` — retail **calls** it: a `jal`, in the row's own retail bytes or at least
  inside the row's own segment run, while its code is on no image in the tree. A `jal` is a call
  and a call **has** a C producer; a retail `j` is what has none, which is this audit's premise.
  Sources are taken only from the declaring row's own run (`run_jumps`), never address-keyed
  across a container — that is the section 7.1 `cross-segment` bug.

A `j` with no `jal` anywhere and no image to read the target's bytes in stays `unresolved`, and
the proof now names every place that was looked.

**`func_8007BEF0` is NOT a SLUS function.** `docs/HANDOVER.md` section 3.1 ("a real function:
`main/func_8001BF84` reaches it by `jal`") and the `row_2714dc_804084dc` proof in
`config/overlays/town.rowbase.jsonl` ("a function of the SLUS base executable") are both wrong and
should be corrected by their owners. Measured: `0x8007BEF0` is SLUS file offset `0x4F6F0`, inside
the `[0x3e018, bin]` resident-data block — the middle of the libgte string
`"Error: Can't push matrix,stack(max 20) is full!"`; **zero** `j`/`jal` words in
`baserom/slus_006.14` target it; it is in neither `config/slus_006.14.symbols.txt` nor any
registered `slus` row's `defs`. It is the `exit` of the declaring module's own linked runtime,
whose text was never carved into the container — section 7-8 of
`docs/evidence/konami_assertion_sites.md` and `docs/evidence/void_callees_20260922.md` already say
so. All three declaring rows carry the `jal` in their own retail bytes, at the offset of the C
call (`0x804077F8`, `0x80407858`, `0x80408508`), against 11 (main) / 2 (town) `jal` sites in their
own segment run and **no** `j` to it anywhere in any image.

Records changed: `main/func_800207D4`, `main/func_80020830`, `town/func_802F14DC` -> `func_8007BEF0`,
`unresolved` -> `cross-image` (`image: "absent"`); all three rows L2 -> L3. Nothing else changed
kind. Tests: `tools/tests/test_split_audit_cross_image.py` (16), `tools/tests/test_levels.py` (16).
