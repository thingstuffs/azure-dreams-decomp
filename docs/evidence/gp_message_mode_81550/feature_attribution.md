# 81550 / DF8C feature attribution

This is a current ownership experiment, not an impossibility verdict. Production
remains abc98f63. The 72-word retail body is in retail.s; lineage.json records
an exact retail slice through the unchanged lineage_fingerprint scan/classify
API (the clean CLI only accepts overlay targets).

The automatic lineage classifier is inconclusive. Manual full-body evidence
includes the split address at DF98/DFA0 (`lui s0,8008`, then `addiu s1,s0,3E18`,
with the saved-register store between them), the s0 base retained across calls,
and the compiler-split delay-slot store at DFBC. The two-register address use
supports the current CDK compiler's splitting capability; a return-copy note
alone does not establish the plain-2.7.2 family.

## Site map

- Frame32, saves s0/s1/s2/ra. s0: high page then buffer pointer; s1: initial
  text append pointer then control-code cursor; s2: addresses encoded as four
  bytes, kept through dispatch and used as the neighbor-store base.
- DF8C..DFDC: strcpy/strcat/strrchr, buffer D83E18, external suffix D71404.
  One existing ASM_KEEP pin keeps the original text-start live.
- DFE0..E004: control bytes 19,02,1A written sequentially via s1.
- E008..E02C: absolute two-instruction address of 81548 encoded into bytes.
- E030..E054: absolute two-instruction address of 8154C encoded into bytes.
- E058..E074: GP load of 81550 indexes external handler table714A4; jalr receives
  buffer pointer in a0 and has that move in its delay slot.
- E078..E08C: constants2300030C/2300040C; neighbor store -4(s2) writes81548;
  direct GP store writes8154C. Remaining instructions restore the frame.

## Features, owners and concrete route

| Feature | Owner | Evidence / route |
|---|---|---|
| GP load81550 versus external absolute expansion | actual data ownership | candidate defines s32 D81550=0; genuine load is now retail exact. |
| GP store8154C versus external absolute expansion | additional actual data ownership | direct named use plus E08C proves a separate four-byte word; assetB0C contains zeros. Defining this word makes all72 DF8C genuine words retail exact. 81548 remains a distinct external claim. |
| Stock one-instruction GP address for local8154C versus retail/genuine absolute pair | assembler convention, existing private generic correction | stock uses addiu s2,gp; generic and genuine use lui/addiu, while retaining GP store. The existing all-pass guarded generic candidate handles it; no new assembler implementation or keyed exception is needed. Global integration/approval remains pending. |
| DCEC register ordering and unfilled jalr slot under common defaultCDK | source declaration size, measured | existing char[16] emits split lui/addiu, allowing delay-slot scheduling; diagnostic char[2] emits bare la and exactly matches the16-word retail body without special flags. Full semantic/extent evidence is audited separately before accepting the declaration. |

No function body or pin was added/rewritten. The successful diagnostic candidate
is work/native_lane/gp_81550_partition/candidate_small. Its four-function scope
is156words, all genuine2.79 and privategeneric retail exact with zero masks at
defaultCDK. The original two-recipe trial and separate additional-data and
incomplete-array trials remain in that directory. Nonzero positional retail
counts in those receipts are rejection checks, not closeness scores across
length differences. The stock/generic DF8C disassembly diff isolates exactly
one absolute address-pair versus GP-address expansion.

Next concrete routes: B6C extent/handler audit -> reviewed declaration;
private full-link/genuine proof -> coordinated generic-assembler transition
package. Do not activate this owner under stock assembler, and do not infer
that selective generic assembly is an acceptable production whitelist.
