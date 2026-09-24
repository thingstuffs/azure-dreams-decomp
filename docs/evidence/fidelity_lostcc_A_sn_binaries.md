# Lost-compiler hunt A: genuine SN binaries from the 1997-04..07 window

This is a measurement only (brief `work/fidelity/LOSTCC_A_BRIEF.md`). The owner approved the downloads on 2026-09-24.
Nothing was edited under src/, include/, ledger/, config/, tools/maspsx, tools/gate, tools/build or toolchain/. No
gate, landing or git command was run.

- **Data and binaries:** `work/fidelity/lostcc/A/`, which is git-ignored.
- **Harness:** step 1c's `tools/fidelity/epilogue_model.py --psyq` leg. This lane did not change it. The cc1 is
  swapped in through `EPILOGUE_MODEL_CC1` and a wibo wrapper, `work/fidelity/lostcc/A/wrap/cc1wrap.py`.
- **Concurrent harness edit by lane B:** lane B added fields to `epilogue_model.py` while these runs were going
  (`src_sha`, `psyq_s_sha`, `psyq_s_equal_t272`). The additions are additive only.
  - 618 of the 800 `psx_0004_t800` records, and the two re-run 68-row journals, carry `src_sha`. The other journals
    predate the edit.
  - Every field compared here exists in both versions and is computed the same way.
- **What the wrapper adds:** optional prefix options, and a copy of every cc1 output saved under
  sha1(`.i` + options), so two compilers' outputs can be paired text for text.
- **Runner and comparators:** the runner is `run_a.sh`. The comparators are `compare.py` and `compare_sn16.py`, and
  their outputs are `compare_603.txt`, `compare_t800.txt` and `compare_sn16.txt`.

"Retail-exact" below means that the genuine ASPSX 2.79 object equals the row's maspsx object *at its registered
recipe*, which the gate proves retail-exact. The journals record `maspsx_exact` = True for every compared row: 593 of
593, and 800 of 800. This is the same measure step 1c used. It is not `aspsx_diff`'s trial-cell `exact_versions`.

## Headline

1. **SN build 0006 is still cygnus-970404.** The N64 cc1 of SN build 0006 prints
   **`cygnus-2.7.2-970404 SN32.3.7.0006`** and was PE-linked 1997-11-26.
   - SN's PSX build 0004 (PE 1997-08-22) and N64 build 0006 (1997-11-26) are the same Cygnus snapshot. SN did not
     move the 3.7 line off 970404 before 2.8.0.
   - We gave 0006 the PSX target options that its PSX sibling has as defaults. With them, 0006 produces **the same
     assembly text as PSX 4.1's 0004** on **all 1,403 rows' translation units tested**. 1,393 of them compile
     cleanly. The other 10 fail identically under both builds, with identical partial output. The only differences are the
     `-fverbose-asm` header comments and the scratch path in `.file`.
   - Those 1,403 rows are the 603 rows of step 1c's 2.8-era set, plus 800 randomly chosen other rows.
   - 0006 emits the 2.7.2 **text epilogue**: 467 `text`, 0 `filled`. It rejects `-mno-split-addresses`.
   - **No row becomes retail-exact under 0006 that 0004 misses (0).**
2. **The US Run-time Library 4.0 "Release 2.0" disc holds nothing new for the question.** The disc (PVD 1997-06-20
   12:18) carries the Win32 toolset of JP 4.0, **byte-identical** to the held psyq4.0: CC1PSX `2.7.2.SN32.3.7.0002`,
   ASPSX 2.56, CCPSX 3.02 Build 0002.
   - The one binary we did not hold is the DOS `CC1PSX.EXE` **`2.7.2.SN16.3.7.0002`**. It belongs to the FSF 2.7.2
     line, not Cygnus.
   - On the 68-row sample it is **identical in every measured field** to the Win32 SN32 0002 (63 of 63 rows that
     both compile) and to the DOS SN16 0003 (68 of 68).
3. **Cheap check (item 3): SN's Saturn compiler of the same week is Cygnus 97r1a.** SN's Saturn Psy-Q cc1 is
   **`2.7-97r1a SOA-971029 SN32.3.8.0006`**, PE-linked 1997-11-25, one day before N64 0006.
   - So SN held a second, differently tagged Cygnus base: the GNUPro 97r1 line, which Cygnus announced 1997-07-02.
     SN numbered that line 3.8, and shipped it for Saturn while PSX and N64 stayed on 970404 (3.7).
   - Its middle-end date is not established. Nothing in its printable strings shows middle-end text newer than
     970404 (see task 3).
   - This is a parallel line. The next observed PSX production base was FSF 2.8.0 (Build 4.0.0007, 1998-02).
   - It is the first binary evidence that SN built from a Cygnus tree other than 970404 in 1997. It is consistent
     with the "Cygnus Experimental compiler" that SN offered for PSX and N64 in May 1998, but that link is a
     conjecture.
   - No MIPS build of it has surfaced. Its SH target cannot be tested on our rows.
4. **Bottom line for the 1997-04..07 window.** Every SN PSX or N64 cc1 that survives publicly (builds 0001, 0002,
   0003, 0004 and 0006) is either FSF 2.7.2 or cygnus-970404. None has code generation later than 970404.
   - The rows that need that code generation are 115 epilogue-helper rows plus 20 controls, all still at 2.8-era
     cells. Neither 0004 nor 0006 reproduces any of the 135.
   - The compiler they need is not in any public SN binary we could find. The owner's reading, that "it existed
     but no one has it", now rests on the build series below and on the Saturn 3.8 binary.

## SN's cc1 build series, as observed

| SN build | target / host | version string | PE link (UTC) | where | sha256 |
|---|---|---|---|---|---|
| 0001 | N64, Win32 | `2.7.2.SN32.3.7 Build 0001` | 1997-02-10 12:14 | decompme/compilers `n64_sn272_build0001.tar.gz` | `f19bab2b617b50ab949e437284f3e2a6b19fe69e6f2e9d54b2994e801bbb5179` (`cc1n64.exe`) |
| 0002 | PSX, Win32 | `2.7.2.SN32.3.7.0002` | 1997-04-29 14:56 | held psyq4.0; **also US RTL 4.0 R2.0 `GNU/CC1PSX.EXE`** (identical) | `ddaa03030d1b012716cccce5a88b8a9484378c915529c5f1458e261c6b928220` |
| 0002 | PSX, DOS (go32) | `2.7.2.SN16.3.7.0002` | n/a (DJGPP), file date 1997-05-15 | **US RTL 4.0 R2.0 `GNU/DOS/CC1PSX.EXE` (new)** | `0764030a7af41cef52b2f003f13aaef7e37489f05579a7955b277a241240a353` |
| 0003 | PSX, DOS | `2.7.2.SN16.3.7.0003` | n/a | held (4.1/4.3 `GNU/DOS/`) | `6801fea8e7618f75b182306ce461ed89b4571383131f2b5a9652687b24917e87` |
| 0004 | PSX, Win32 | `cygnus-2.7.2-970404 SN32.3.7.0004` (SonyPSX) | 1997-08-22 11:23 | held psyq4.1; **= the "N64 0004" `cc1n64.exe`** (below) | `17b0d9dc6a80b2aaec90f912bb442321ec8bc5cecaf7071f5bd187e1d6525d49` |
| 0005 | none seen | | | | |
| 0006 | N64, Win32 | `cygnus-2.7.2-970404 SN32.3.7.0006` (Nintendo64) | 1997-11-26 12:21 | decompme/compilers `n64_sn272_build0006cygnus.tar.gz` | `b214ac010442ce04d00f6b7dd854a8f057b71a8d1c4348b8a65b0c5b9903b1c6` (`cc1n64.exe`) |
| 3.8.0006 | Saturn (SH), Win32 | `2.7-97r1a SOA-971029 SN32.3.8.0006` | 1997-11-25 17:52 | archive.org `psy-q` (`win/GNUSH.exe` SFX to `GNUSH.ZIP`) | `d6d2819d9348b33e51b5a64b338df30da5d7a20b3026236427f6a9b943f4d146` (`CC1SH.EXE`) |
| 4.0.0007 | PSX, Win32 | `2.8.0 SN32 Build 4.0.0007` | 1998-02-17 | held (JP 4.3) | step 1c #10 |

- **The build number is shared across targets and hosts.** 0006 exists as N64 on 3.7 (970404) and as Saturn on
  3.8 (97r1a), linked a day apart. 0002 exists both as SN32 and as SN16.
- **"N64 build 0004" is the PSX binary renamed.** decomp.me's N64 compiler `gcc2.7.2sn0004` downloads
  `https://github.com/Mr-Wiseguy/pcsx-redux/releases/download/n64/cc1n64.exe`, whose sha256 is `17b0d9dc…d49`. That
  is PSX 4.1's `CC1PSX.EXE`, and the file's banner says `(SonyPSX)`. The release note (2022-05-10) says so itself:
  "the appropriate cc1psx (renamed to cc1n64)". No distinct N64 0004 is known to exist.
- **0001 is FSF 2.7.2.** N64 0001 is `2.7.2.SN32.3.7 Build 0001`: it carries no Cygnus tag.

## Task 1: SN N64 build 0006

### Downloads (2026-09-24 09:03Z)

| file | URL | size | sha256 |
|---|---|---|---|
| `n64_sn272_build0006cygnus.tar.gz` | `https://github.com/decompme/compilers/releases/download/compilers/n64_sn272_build0006cygnus.tar.gz` (asset updated 2025-03-17) | 1,671,935 | `1a35a875278f38bfc285c2bd80b782cec38859dedfd925d8b8a2f1733ba9acad` |
| `n64_sn272_0006.tar.gz` (the same asset under its short name) | same release | 1,671,935 | identical: `1a35a875…acad` |
| `n64_sn272_build0001.tar.gz` (for comparison) | same release | 1,601,261 | `17c57ccd5f2305fe5445c576d4cc2c1fea681dd78b29dd3d1f15c5ca0fdf2cea` |
| `cc1n64.exe` ("0004") | `https://github.com/Mr-Wiseguy/pcsx-redux/releases/download/n64/cc1n64.exe` | 1,430,016 | `17b0d9dc…d49` (= psyq4.1 `CC1PSX.EXE`) |

- decomp.me PR #1489 (`https://github.com/decompme/decomp.me/pull/1489`, merged 2025-03-19) adds the builds.
- decompme/compilers `values.yaml` (`https://raw.githubusercontent.com/decompme/compilers/main/values.yaml`) maps
  `gcc2.7.2sn0004` to the renamed PSX binary above.

**The 0006 package** (`work/fidelity/lostcc/A/n64_0006/`). The `sn.ini` in the package is dated 2025 and was added
by decomp.me; it is not genuine.

| file | PE link (UTC) | sha256 | version |
|---|---|---|---|
| `cc1n64.exe` | 1997-11-26 12:21:47 | `b214ac010442ce04d00f6b7dd854a8f057b71a8d1c4348b8a65b0c5b9903b1c6` | `cygnus-2.7.2-970404 SN32.3.7.0006`; `-version` banner `(Nintendo64)` |
| `cc1pln64.exe` | 1997-11-26 12:21:54 | `b6ddeb966b6df90e9f7ed67f06c7ff338cd3ed87eed7c2a621c1f762cd6b5398` | C++ (not used) |
| `cppn64.exe` | 1997-11-26 12:21:43 | `c319b3e5e31496df543d4b9f2e698e1a772cb576640afbff233df18167098904` | `cygnus-2.7.2-970404 SN32.3.7.0006` |
| `ccn64.exe` | 1997-11-26 12:14:40 | `8d9d4ec9da8af56b36c3bd752e217d8b63c3ea41cbb757c684ec9ba38d7f13e9` | driver: `N64 version 3.04`, `PSX version 3.02` |
| `asn64.exe` | 1997-11-13 17:13:34 | `fa347c452077ad88e4a89e8a25eda60a464750622f4098032cf30242f978e693` | `SN ASN64 version 2.72` |

**0006 against 0004, as binaries.**
- `.text` is 1,225,450 bytes against 1,224,810 (+640). `.data` is +256.
- The only human-readable string changes are:
  - the version (`…0004` becomes `…0006`);
  - the target name (`SonyPSX` becomes `Nintendo64`);
  - one `__main` string, which disappears.
- An unfiltered `strings -n 4` diff shows only four changed lines with words: the two version strings,
  `Nintendo64` and `__main`. Both builds accept and reject the same options, including
  `-meb`/`-mel`, `-mips1..3`, `-mcpu=3000/4300`, `-mgpopt` and `-G`.
- Neither build has `split-addresses`, the option Wilson added to FSF on 1997-05-01.

**Can it emit PSX code?** Yes, as a cc1 with explicit target options.
- Its defaults are N64: R4300, ISA 3, big-endian, `-G0`, no `-mgpopt`. PSX 0004's defaults are R3000, ISA 1,
  little-endian, `-G8`, `-mgpopt -msoft-float`.
- Our gcc driver passes no target options to cc1 (checked with `gcc -v`). The wrapper therefore prefixes
  `-mips1 -mcpu=3000 -mel -msoft-float -mgpopt -G8`, and the row's own options (for example `-G0`) come after them.
- Checked by hand on a probe (bitfields, unions, long long, doubles, byte and short loads, `$gp` data) at the
  default, `-G0` and `-G4`: the output equals 0004's apart from the header comments.

### Results

Journals: `work/fidelity/lostcc/A/n64_0006.jsonl` and `psx_0004.jsonl` (603 rows), and `n64_0006_t800.jsonl` and
`psx_0004_t800.jsonl` (800 rows). Saved `.s`: `s_*`.

- **The 603 rows** are step 1c's 2.8-era set. By current registered cell: 378 are now at 2.7.2-cdk after the
  step 1c recipe moves; 152 are at 2.8.1, 42 at 2.8.0, 22 at 2.95.2 and 9 at 2.91.66.
  - 593 compile under both builds.
  - The same 10 rows fail under both, with identical errors: 6 × `Invalid option 'no-split-addresses'`,
    `-fstrict-aliasing`, `-fno-gcse`, and 2 `__attribute__` parse errors.
  - **Every journal field is identical for 593 of 593 rows.** The fields are `psyq_s_equal`, `psyq_s_diff`,
    `psyq_epi`, retail-exact as emitted, retail-exact under the t272 rule, and the word-diff sizes under
    ASPSX 2.79/2.77.
  - **The saved cc1 outputs are identical for 603 of 603.** That includes the partial listings of the 10 failing
    rows: gcc 2.x's `Invalid option` error is not fatal, and a parse error still leaves a listing. 602 pair by key. The 603rd pairs by normalised text,
    because its `.i` names its scratch path.
- **The 800 other rows** were drawn at random with seed 19971126: 687 at 2.7.2-cdk, 80 at 2.7.2, 33 at 2.6.3; 334
  from town, 311 from dungeon, 107 from slus, 45 from main and 3 from ovmovie.
  - All 800 compile under both builds, and every field is identical for 800 of 800.
  - The saved `.s` are identical for 800 of 800: 790 by key and 10 by normalised text.
- **Retail-exact counts, with genuine ASPSX 2.79 and no maspsx helper:**

| set | rows | registered cell (base) | base + t272 rule | 0006 as emitted | 0004 as emitted |
|---|---|---|---|---|---|
| 603 set (compiled) | 593 | 457 | 575 | **440** | **440** |
| step 1c's 151 cdk-not-exact rows | 151 | 36 | 151 | 16 | 16 |
| – helper rows still at 2.8-era cells | 115 | 0 | 115 | **0** | **0** |
| – rows since moved to cdk | 16 | 16 | 16 | 16 | 16 |
| – controls (need newer code only) | 20 | 20 | 20 | **0** | **0** |
| 800 other rows | 800 | 789 | 789 | 738 | 738 |

- **Rows retail-exact with 0006 but not 0004: 0.**
- **Return forms emitted by 0006 on the 593:** 467 `text`, 48 `$31`-only `text`, 2 `$31`-only `text_filled` (the
  2.7.2 epilogue-delay form), and **0 `filled`**. These are the same numbers as step 1c's 0004 and cdk.
- **Update to step 1c's numbers.** 16 of the 151 rows (dungeon, all `_maybe_unfill_return_delay`) have since been
  registered at 2.7.2-cdk by the census re-derivation landing, and are now genuine-exact there. The residue that
  needs code later than 970404 is now **115 helper rows + 20 controls = 135 rows**. The 115 are 110 `_maybe_unfill_return_delay` rows
  (73 at 2.8.1, 22 at 2.8.0, 11 at 2.95.2, 4 at 2.91.66) and 5 `_unfill_via_load_delay` rows.

**Verdict for task 1.**
- Build 0006 has no code generation later than 970404. It is 0004 retargeted.
- It emits the text epilogue.
- It makes no row retail-exact that cdk misses.
- The web-search report's lead 2 resolves to case (b): SN never moved the 3.7 line's Cygnus base before 2.8.0.

## Task 2: US Run-time Library 4.0 "Release 2.0" (DTL-S2002)

**The download (2026-09-24 09:05Z).**
- URL: `https://archive.org/download/ps1_sdks/Programmer%20Tools%20-%20Run-time%20Library%204.0%20(USA)%20(Release%202.0)_DTL-S2002_redump.zip`.
  Size 391,591,294 bytes.
- It matches archive.org's metadata: sha1 `494eceea809ad064193bdb59befa9fc2079ea310`, md5
  `eec31ecd185183cbde0343f4ed416472`.
- Our sha256 of the zip: `c98c056c3949987aa713d494f9773f9010d4402333ffac07774c1883367ccad5`.
- Track 1 (`MODE2/2352`), sha256 `17fb62e3e40a812e9cc9504378ca08e717678a72ccc4f07f7aec5df1d4c7aa81`. The cue sheet
  (`work/fidelity/lostcc/A/rtl40r2/disc.cue`) marks tracks 2-8 as `AUDIO`, so only track 1 is data.

**The primary volume descriptor.**
- System `PLAYSTATION`, volume `PROGTOOL`, publisher `SONY_COMPUTER_ENTERTAINMENT_AMERICA`, preparer `SCEA`.
- Created **1997-06-20 12:18:03**, which matches redump 71991.
- The disc's directory timestamps are 1997-06-20 19:4x-19:57. `GNU/DOS/CCPSXD.S` names the build tree
  `…\PROGTOOL\GNU\DOS\` under an `ALPHA2.0` directory.

**Extraction.** Track 1 was converted to 2048-byte sectors and listed with 7-Zip: 2,381 files. The full listing is
`rtl40r2/listing.txt`.
- 7-Zip reports "unexpected end of archive". The PVD volume size (231,315 sectors) spans the audio tracks, while
  track 1 has 114,852.
- All 134 files under `GNU/` and `PSSN/BIN/` extracted at their listed sizes.
- The zip, the bin and the ISO were **deleted** after extraction. Only `GNU/`, `PSSN/BIN/`, the cue sheet and the
  listing are kept (`work/fidelity/lostcc/A/rtl40r2/x/`, 15 MB).
- No other directory holds a compiler. `3RDPARTY/METROWER` holds only DECI flash tools.

### Inventory of compiler, assembler and driver binaries on the disc

| path | date on disc | sha256 | version | already held? |
|---|---|---|---|---|
| `GNU/CC1PSX.EXE` | 1997-05-15 | `ddaa03030d1b012716cccce5a88b8a9484378c915529c5f1458e261c6b928220` | `2.7.2.SN32.3.7.0002` | **yes**, psyq4.0 (identical) |
| `GNU/CC1PLPSX.EXE` | 1997-05-15 | `65837f430b20683a9123e221b478ca4154eb5a54f43372425936b9b91b542e2d` | `2.7.2.SN32.3.7.0002` (C++) | yes, psyq4.0 |
| `GNU/CPPPSX.EXE` | 1997-05-15 | `ff010a95def561d9d7f314038f7b00fce1f233efcd422c5ecaa59662b749c841` | `2.7.2.SN32.3.7.0002` | yes, psyq4.0 |
| `GNU/CCPSX.EXE` | 1997-05-20 | `7ea2ea5e16f8847f6ccdce229f74d4cd6188d7aefdd7a035200d27b524962aa5` | `3.02 Build 0002`, `PSX version 3.02` | yes, psyq4.0 |
| `GNU/CPLUSPSX.EXE` | 1995-04-09 | `0f4ec3855402ff699f297424f3825a0d606c3154db105b5ce16d1fa258844d7e` | old DJGPP-hosted C++ (`[AL 1.1, MM 40]`) | not relevant |
| `GNU/DOS/CC1PSX.EXE` | 1997-05-15 | `0764030a7af41cef52b2f003f13aaef7e37489f05579a7955b277a241240a353` | **`2.7.2.SN16.3.7.0002`** (go32) | **no (new)** |
| `GNU/DOS/CC1PLPSX.EXE` | 1997-05-15 | `cc4f081fc15199ff650506ed881b4c62c815363d7261dd37de40546cf6590747` | `2.7.2.SN16.3.7.0002` (C++) | no; C++, not tested |
| `GNU/DOS/CPPPSX.EXE` | 1997-05-15 | `f62590bd82ade1f8259a4e2a0b82aee7443afb5e37e6bad0b974e17cfaae67df` | `2.7.2.SN16.3.7.0002` | no; cpp, not tested |
| `GNU/DOS/CCPSXD.EXE` | 1997-06-13 | `faa86115c8f8befd5900c2e3508a6224a58f8f8f025fba3f53329494c76bbeb9` | driver `PSX version 3.02` | driver only |
| `PSSN/BIN/ASPSX.EXE` | 1997-05-20 | `7f928fa89e143facd75737822b08bb63fb41a06415ba943393db727aa398efc8` | `Psy-Q ASPSX version 2.56` | yes, psyq4.0 |
| `PSSN/BIN/DOS/ASPSXD.EXE` | 1997-05-20 | `f13ff060b2b14ef3259957b0679a2e67faa66e3c46df99fc1e1b78b03daabfbc` | `Psy-Q ASPSX version 2.56` (DOS) | DOS twin of 2.56 |
| `PSSN/BIN/ASMPSX.EXE` | 1997-05-20 | `a004d4befb77bcbadfd6b042bd5f384bd33ee16061f694812ccb9a8a4c661fe5` | `Psy-Q PSX Version 2.34` | yes, psyq4.0 |
| `PSSN/BIN/PSYLINK.EXE` | 1997-05-20 | `2d04dfaa25b44e9e243d26de488fbf48d160a6aa3bcfc4da20b46e8eda7288ef` | `Psylink version 2.52` | yes, psyq4.0 |

**The mid-window Sony discs carried plain 2.7.2.** Both mid-window discs carry build 0002, which is FSF 2.7.2
(`[AL 1.1, MM 40]`):
- JP 4.0 (PVD 1997-05-28);
- this US 4.0 Release 2.0 disc (PVD 1997-06-20).

The first Cygnus build (0004) was linked 1997-08-22.

**The one new cc1 was tested.** DOS `2.7.2.SN16.3.7.0002` was run under dosemu2 on step 1c's 68-row stratified
sample (`work/fidelity/step1c/sample_all.txt`). The two held builds of the same era were run again **on the same
day** for a like-for-like comparison: `sn16_0002.jsonl`, `psyq40_now.jsonl`, `sn16_0003_now.jsonl`.

| compiler | compiled | retail-exact as emitted | twin of the registered cell | return forms |
|---|---|---|---|---|
| DOS SN16 0002 (new) | 68/68 | 16 | 2.7.2 10, 2.6.3 3, cdk 1 | text 32, `$31`-only text 16, leaf text 3; 0 filled |
| Win32 SN32 0002 (psyq4.0) | 63/68 | 16 | same | text 31, 15, 3 |
| DOS SN16 0003 | 68/68 | 16 | same | text 32, 16, 3 |

- **Against SN32 0002:** every field is identical on 63 of 63 rows that both compile.
- **Against SN16 0003:** every field is identical on 68 of 68 rows.
- **Why 5 more rows "compile" under DOS.** The Win32 0002 rejects 5 rows: `-mno-split-addresses` twice, two
  `__attribute__`/`asm` constraint errors, and one parse error. Under the DOS cc1 those rows count as compiled only
  because step 1c's dosemu wrapper takes whatever output file exists and does not check the exit status. This is a
  caveat on those 5 rows, not a difference in code generation.
- **Verdict:** SN16 0002 is FSF 2.7.2 code generation with the text epilogue, the same as its SN32 twin. It is not
  a window compiler.

## Task 3: other leads, one cheap check each

| lead | check (2026-09-24) | outcome |
|---|---|---|
| decomp.me `gcc2.7.2snew` "GCC 2.7.2 (SN, experimental)" | `values.yaml` | It is `https://github.com/decompals/SN64-gcc/releases/download/gcc-2.7.2-970404/…`, described by its repository as a "Recreation of the SN64 toolchain's gcc", built from 970404 source. **Negative** (not genuine, and 970404) |
| The "N64 0004" binary | sha256 + release note | It is the PSX 4.1 cc1 renamed (above). **Negative** |
| archive.org full-text search: `gnupro`, `"97r1"`, `cygnus AND 1997 AND (mips OR gnu)`, `psyq AND (4.2 OR 1997)`, `"SN Systems" AND (gnu OR compiler OR bbs)`, `ccpsx OR cc1psx` (results `work/fidelity/lostcc/A/dl/archive_search.txt`) | metadata API | No GNUPro binary. The 4.2 item holds libraries only, as already known. `SCE-SDevTC-Aug1998` is a 1998 manual. Two items were checked further (the next two rows) |
| **SN Saturn Psy-Q** (`https://archive.org/download/psy-q/psy-q.zip`, 10,845,193 B, sha256 `29b957d35a4bda0eb3f7010ac3dfaa732ac14a8d23c1a5f8d38ed9d8c0367595`) | `win/GNUSH.exe` + `.r00` (RAR SFX) contain `GNUSH.ZIP`, which holds `CC1SH.EXE`, `CC1PLSH.EXE` and `CPPSH.EXE`, PE-linked 1997-11-25 17:51-17:52 | **`2.7-97r1a SOA-971029 SN32.3.8.0006`**. CC1SH sha256 `d6d2819d9348b33e51b5a64b338df30da5d7a20b3026236427f6a9b943f4d146`; CC1PLSH `d51416e0edbeae70b8d2d74017b00426da7851b04a9293e0777c8fee81e16480`; CPPSH `9a009bf5a7e246e75cbf50e361495395d8b20bfa9b5f78640df66c9732879e99`. **Positive as evidence** (see below), but untestable: its target is SH |
| Frogger: He's Back source leak (`https://archive.org/download/Frogger-Hes-Back-source-code/95jeq3.zip`, sha256 `08b0e1219e3a6b4771f552a1e0c3c806b7c35f8d72327c808bf9aa5802e1c2dc`; inner archive `Frogger_source_archive_041297.zip`, files dated 1997-04..08) | listing + grep of the makefiles and batch files | It shows only a `ccpsx -comments-c++ …` invocation. No compiler binary, and no cc1 listing carrying a version banner. **Negative**. The extracted source was deleted |
| Web search for `"SN32.3.8"` / `"97r1a"` with cc1psx/cc1n64/ccpsx, and for 97r1 sources | web search | Nothing beyond the EE Times 97r1 announcement (`https://www.eetimes.com/cygnus-solutions-announces-gnupro-toolkit-97r1-release/`). **Negative** |
| gcc-mirror trunk snapshots (web-search lead 1) | not done here | This is lane B (`docs/evidence/fidelity_lostcc_B_trunk_bisect.md`) |
| SN BBS "GNU" area and GNUPro 97r1 CDs (leads 4 and 5) | not obtainable publicly | Not pursued, as the web-search report recommends |

### What the Saturn binary does and does not show

**What it shows.**
- In November 1997 SN built from **two Cygnus bases in the same week**:
  - `SN32.3.7.0006` on cygnus-970404 for N64, and 0004 for PSX;
  - `SN32.3.8.0006` on **Cygnus GNUPro 97r1a** for Saturn.
- The "3.8" line is SN's number for the 97r1 base. GNUPro 97r1 was announced 1997-07-02, so its snapshot predates
  that. 97r1a is a later revision. Whether its `SOA-971029` stamp is Cygnus's or SN's is not known.
- SN's May-1998 web page offered "PSX and N64 versions of the Cygnus Experimental compiler" separately from 2.8.0
  and 2.8.1 (Wayback `…/19980523231120/…/snsys/default.asp`, cited in the web-search report). The obvious candidate
  for that is a MIPS build of this 3.8 line.
- **This is the first binary evidence that SN built from a Cygnus tree other than 970404 in 1997.** Suppose its
  middle end is newer than 970404 and 97r1 was cut before Law's 1997-07-11 change. Then a PSX build of it would fit
  the 135 rows' profile: newer code generation with the text epilogue. Neither condition is established by anything
  we hold.

**What it does not show.**
- It does not show that a PSX 3.8 build was shipped, or that Konami had one.
- It says nothing about the MIPS backend in 97r1. The SH cc1 cannot compile our rows, and there is no SH build of
  970404 or 2.8.0 to compare its target-independent passes against.
- We probed accepted options on 15 markers with `CC1SH` against PSX 0004 and SN 2.8.0. 97r1a accepts exactly
  970404's set on all of them:
  - `-fregmove`, which is Cygnus devo only;
  - no `-fstack-check`, `-fcheck-memory-usage`, `-fprefix-function-name` or `-fsjlj-exceptions`, all of which
    SN 2.8.0 accepts.

  So 97r1a sits on the devo lineage, not FSF trunk's 2.8 option set.
- We also compared printable strings (at least 6 characters, containing a 4-letter word). 234 strings are in 97r1a
  but not in PSX 0004. All of them are SH-target text (insn patterns, `.def` and `.little` directives,
  `SegaSaturn`), with one exception: `%d givs counted, sorting...`. That string is in the 970404 source's `loop.c`
  itself (`combine_givs`), and in 2.8.1's.
  - Only 2 of the 234 strings also appear in the 970802 trunk or SN 2.8.0 but not in 0004: `.ascii "` and
    `epilogue`, both target text.
  - **No string shows a middle end newer than 970404.** Strings are a weak measure, and option names do not
    measure code generation either. The middle-end date of 97r1a stays unknown.

## Decisions for the owner / orchestrator

1. **Close web-search leads 2 and 3 as negative.**
   - N64 0006 is 970404: all 1,403 rows tested produce identical text (1,393 compile cleanly), and 0 rows are
     gained.
   - The US 4.0 Release 2.0 disc carries build 0002 (FSF 2.7.2), identical to held 4.0, plus a DOS twin that is
     identical in every measured field.

   No public SN 3.7-line binary has code generation later than 970404. Optional housekeeping, which this step could
   not do because toolchain/ edits are off-limits: catalogue the following under the genuine toolchain.
   - `cc1n64_0006.exe`;
   - DOS SN16 0002;
   - Saturn CC1SH 3.8.0006.
2. **Record the evidence chain for "it existed but no one has it".**
   - SN's build series (the table above).
   - Two Cygnus bases in the same week of November 1997, with the 3.8/97r1a Saturn binary as the witness.
   - SN's advertised "Cygnus Experimental compiler" for PSX and N64.
   - The 135 rows that need newer code generation plus the text epilogue, which no held or public SN binary gives.

   Every link cites a sha256 or a URL above.
3. **Lane B's FSF trunk is a proxy, and this sharpens that caveat.** The next PSX production base we observe is
   FSF 2.8.0 (Build 4.0.0007, February 1998). Alongside the 970404 line, SN also had a parallel Cygnus line (3.8,
   97r1a), seen only for Saturn. That line is conjecturally the "Cygnus Experimental" PSX/N64 compiler of May 1998,
   and it is not FSF trunk.
   - A trunk snapshot that reproduces the 135 rows would still be a stand-in, because devo and trunk exchanged many
     changes in 1997, but how closely 97r1 tracked trunk is not known from any binary we hold.
   - Judge lane B's best snapshot on that basis. If the epilogue revert becomes the route, the provenance note should
     say "Cygnus 97r1-era devo, not held; FSF trunk <sha> as proxy".
4. **No recipe changes follow from this step.** 0006 behaves as the cdk cell on every row tested, so there is nothing
   to land.
