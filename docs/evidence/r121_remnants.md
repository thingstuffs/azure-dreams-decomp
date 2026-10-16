# r121 remnants: byte coverage and source-kind recovery

Review: pending. This delivery adds 51 canonical DUNGEON C rows / 6,776 bytes,
all strictly exact at 2.7.2-cdk-G0, with zero pins, inline asm, volatile accesses,
whole-function assembly, or masked words. None overlaps a previously registered
DUNGEON row. It also classifies 1,396 previously unrowed code bytes as SDK
assembly and inventories 310 data regions / 582,476 bytes for relabelling.
The latter is a physical interval inventory, not new C ownership.

## Main

The three inherited "C gaps" belong to held Sony library members:

| Existing identity | file extent | provenance |
|---|---|---|
| func_800217C8 | 0x2717C8 + 104 | LIBCARD END.OBJ / _ExitCard +0 |
| func_800218A0 | 0x2718A0 + 136 | LIBCARD PATCH.OBJ / _patch_card +0x58 |
| func_80021958 | 0x271958 + 108 | LIBCARD PATCH.OBJ / _patch_card2 +0x110 |

The complete 128-byte linked END member matches all 103 fixed catalogue bytes
(the remaining 25 bytes are relocation wildcards). The complete 416-byte PATCH
member matches all 356 fixed bytes (60 relocation wildcard bytes), selecting the
held 3.6.10/3.6.11/3.7 catalogue family among the tested catalogues. The existing
original LNK relocation replay in main_libcard_patch_delay.md independently
binds PATCH: 416/416 bytes. These facts supersede the older assertion that the
exact containing objects were unidentified. They do not select an original SDK
release uniquely, or prove original assembly source authorship.

The retail ABI is assembly-shaped: fixed BSS saves/restores of $ra, no stack
frame across calls, BIOS dispatch through $t2 with selector in $t1, and copied
handler templates. It belongs at the SDK assembly boundary. No new C row or
universal compiler-impossibility claim is made. The 24-byte private delay is
already an original-object-proven SDK assembly extent; preserve that existing
classification. The three MAIN and six TOWN BIOS trampolines match all 16 bytes
of their held LIBCARD members (A74/75/76; A92/93/C171/C172/A78/A80).
SDK identification is distinct from compiling these bytes: this package leaves
existing assembly/fallback mechanisms in place and never counts them as C.

## Ovmovie

The full 920-byte LIBPRESS VLC.OBJ at [0x1638,0x19D0) matches 896 fixed catalogue
bytes and 24 relocation wildcard bytes in held 3.6.10/3.6.11/3.7/4.0 catalogues.
The 880 code bytes are two functions, not three:

- DecDCTvlcSize: file [0x163C,0x166C), true 0x80177E3C, 48 bytes.
- DecDCTvlc: file [0x166C,0x19AC), true 0x80177E6C, 832 bytes.

The first old spelling func_80041638 has foff 0x163C; its spelling incorrectly
names the preceding 4-byte limit word (0x00ffffff). 0x165C is an internal branch
arm. 0x1978 is an internal context-save block reached by the branch at file
0x1834, not a new entry point. The supposed 780-byte body plus 52-byte body is
one 832-byte decoder. Direct $at arithmetic, trapping add/addi/sub, the explicit
register context, and mfc0/mtc0 SR at file 0x195C/0x196C corroborate the assembly
boundary. C is not forced over these platform instructions. The following
36 bytes [0x19AC,0x19D0) are its nine-word spill workspace, as established in r120
and confirmed by this object's complete catalogue span and load/store pairs.
No ordinary-C row, synthetic helper, or duplicate 52-byte coverage is installed.

## Dungeon engine

The alleged 1,576-byte func_80083800 is a mixed discovery interval. File
[0xA3800,0xA3D40) is 1,344 bytes of address tables and Japanese/ASCII strings
(including USE/GIVE/DEMO), with no jr ra. The true C entry starts at file
0xA3D40, synthetic func_80083D40, true func_800894A0, and occupies 232 bytes.
Its complete natural body is exact. The old primary and mirror records now
cover only the data prefix. The canonical new C record belongs to dungeon;
dungeon_engine remains a mirror, not a second row denominator.

The delivery additionally registers 50 previously uncovered bodies / 6,544
bytes between existing engine rows. These include empty and return-zero leaves,
callback wrappers, flag checks, chain visitors, status handlers and three-phase
movement/state handlers. Several are opcode/register twins of existing rows;
the new source is independently compiled at its own address, so internal jumps
and imported addresses are actually resolved. The row union is checked against
the pre-delivery registry; these are new physical C coverage, not duplicate row
identities. This measured 6,544-byte inventory supersedes the audit's approximate
"~2.3 KB tiny stubs" description, which did not enumerate every uncovered body.

Existing proven rowbase region xfer_dungeon_A3000 covers every new C extent
with delta 0x7FFE5760. Its runtime DMA/page proof, the independently registered
neighbours, and current true-name linking are retained. No rowbase extent or
retail byte was changed. New rows use the existing cdk-G0 cohort recipe, with
no row-specific compiler/assembler switches. The lineage scans are compatible
with that family where discriminating; neutral functions do not select cdk over
all other compilers by themselves.

Actual m2c first passes are retained under raw/dungeon/m2c_first_pass. Their
measured failures/near misses remain in baseline history with explicit source
paths. Each new registered row also gets a frozen, exact canonical baseline at
raw/dungeon/<id>.c, plus readable src/ C, recipe, reverify and promotion records.
This preserves the ordinary raw-baseline tools' contract. No native module/TU
membership, ownership review or L4/L5 certification is manufactured for new rows.

Two status handlers initially borrowed a +zero promotion from an old sibling.
It was removed: a real u16 unsigned-bit temporary followed by s8 conversion is
exact and preserves both byte reads without that artifact.

The rendered-packet body has three unchanged color-byte write-backs, retaining
retail lbu at file 0xF1248/0xF124C/0xF1250. The entity controller has one unchanged
16-bit flags write-back, retaining retail lhu at file 0xED8D4. All four stores
compile away; the reads exist in retail and no additional read is inserted.
These are the explicitly allowed decision-39 reconstruction in
r97_decisions.md, with source comments and exact receipts. Removing the packet
write-backs measures aligned 7 (2 substitutions, 5 indels). No new volatile,
asm, fake dependency, dead arm, function, or prototype arity was introduced to
preserve these sites. The source-transfer advisories remain available in the
lane; partial type declarations are not a completed module ABI review.

## Hold and next route

File [0xD7914,0xD79C4), func_800B7914 / true func_800BD074, is a newly recorded
NOMATCH 176-byte body, never a MATCH row. The bounded symbolic two-field C has
aligned 5 (3 substitutions, 2 indels). Retail holds HIGH alone across a call;
our symbolic expression materializes the low base for its first load. The
next-door C sibling uses a literal 0x80010000 page view. Its exact shape is held
as diagnostic rather than added to coverage without independent declaration
proof. Continue with holds/state_base.md (route az-c-rebuild); do not alter the
assembler or fit a compiler recipe to this source-declaration issue.

No refs/r121_instances_REPORT.md had arrived while this delivery was prepared.
Further NOT-an-instance work depends on that forwarded report.

## Proofs and accounting

The recovered receipt binds each complete C body, exact canonical baseline and
actual m2c draft by SHA-256. The SDK receipt gives per-catalogue/member evidence;
wildcard matches are provenance, never a masked C equality claim. Strict C row
scoring uses the unmodified project kit and complete generated/retail word counts.
Every covering window is enumerated; the only covering C window is the existing
393,216-byte dungeon_engine window. The production checks additionally exercise
MAIN boot, OVMOVIE and the TOWN BIOS window. Unowned bytes still use the existing
retail fallback, so window equality is not a claim of complete native coverage.

Reproduction scripts, raw disassemblies, aligned diffs, staging, gate logs,
source-legitimacy controls and package replay live under
work/native_lane/r121_remnants. No commit or shared-queue write was made.

Final production proof: all four windows MATCH, totaling 611,004 bytes. The
engine manifest contains 862 C-derived spans, including all 51 new rows. Every
new compiler-linked rowbase binary was separately compared unmasked to its
retail extent: 51/51, 6,776 bytes, zero retail substitution. After recording the
completed gate annotations and bounded SDK notes, the unmodified production
split/match projection is unchanged for every new C source, recipe, size and
true link address. No source or build tool changed after the successful run.

The first engine job was rejected by its input-change guard after baseline
metadata changed during compilation; it is not a passing proof. Inspection
also caught missing mirror splits that would have left new spans on fallback.
All 51 C mirrors plus the one held discovery were added before the successful
stable run. That full run recompiled every C body and passed in 1085.979 seconds.
The current native cd_control certificate needs renewal after landing because
its bank/window metadata changed; no renewed certificate is claimed here.
Other missing proof artifacts in the private root are not asserted to be live
regressions. Source/type review remains pending.
