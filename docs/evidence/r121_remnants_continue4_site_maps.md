# r121 continuation4 site maps and diagnostic routes

TOWN file0x8D6FA8, true0x80023FA8,120B. No frame or calls. Actor a0,
unused callback context a1, packet a2. Add0xFFEFEFF0 to packet word+0xC.
If actor signedhalfword+8 !=0, load packet byte+0xC into v1 and halfword+0x1E
into v0; shift byte right3, add0x120 to depth, subtract byte; store identical
halfwords at+0x1E/+0x1C. If colour lowbyte becomes0, set actor flags-2 and
resident D_800814A0 bit0x8000. Return jr-ra,nop. The typed u16 depth addition
then separate subtraction matches at fixed2.7.2-cdk-G0; spelling as one
addition/subtraction expression gives7 substitutions (no indels) because gcc
associates the constant with the subtrahend. No volatile or fake dependency.
Independent callbacks in preceding bodies materialize0x80023E64/0x80023FA8;
these name the complete no-op/this entry at file0x8D6E64/0x8D6FA8 and agree
with existing delta0x7F74D000. Queue omits the final8B; full extent includes it.

DUNGEON file0x12740F0/0x12743E8,8B each: separate complete jr-ra/nop entries,
each following an independently returned function. Existing img0328 delta is
corroborated by localjal at file0x1274310 to0x80173A48, complete entry at
file0x1274248. Full nearby local-call/entry census, alternative shifted bases,
raw hashes and independent return boundaries are retained. Placement of these
bounded functions only; no claim about allocation ownership or runtime use.

DUNGEON six file0xD117B8+N*0x6000,32B: frame0x18, ra+0x10; jal0x800AD058,
nop; restore ra/sp; jr-ra,nop. All four incoming args pass unchanged; scalar
return passes unchanged. Complete1144B resident callee at file0xC78F8 saves
all four input registers and uses them in distinct packet/entity/position/state
accesses, and defines v0 on every exit path. Do not infer a void ABI from the
old sibling wrapper func_800D481C. Independent localjal/entry witnesses in each
bank agree with its pre-existing proven region. Engine mapping/import/source
hashes are protected package inputs. No runtime occurrence claim.

TOWN file0x7F58AC,96B: restore nested nonzero and not-one arms, with the table
load left of AND. This restores the complete retail CFG, arithmetic and all
register roles; aligned11=3subs+8indels becomes2=2subs+0indels at2.6.3-G0.
Only li1 expansion remains, at body offsets8 and80: stock addiu versus retail
ori. Nine li-expansion candidates now need pipeline/provenance diagnosis.
No assembler change, SDK attribution, or impossibility claim is made.

DUNGEON file0x1954F40,488B: preserved prior complete site map applies. Gate0
still differs in mask/list s3/s4 roles; goto-list lifetime rewrite scores61 and
low-mask operand-first scores21, both worse than retained19=13subs+6indels.
No recipe sweep, pin, compiler patch or assembler change was made. Fingerprint
is family-neutral; fixed neighbouring2.7.2-cdk-G0 recipe is unchanged.

Six other long dungeon tails initially failed m2c because their real indirect
switch tables were absent. Their actual table words/accessors and all in-body
targets are now recovered: all six full diagnostic m2c inputs succeed. Both
original failures and successful first passes are retained. Next reconstruct
types, stack arrays, symbolic globals and active imports before full byte checks.
These remain unported; no new placement admission, guessed switch arms or asm
classification.0x1847144 still lacks its containing entry.
Two other large complete diagnostic first passes are retained as synthesis
material only; they have not passed types, imports, storage or byte checks.

TOWN transitive failures reach indirect TownServiceTable callbacks, including
+0x168 and+0x174, whose current header intentionally retains incomplete
prototypes. The full contexts identify the ABI evidence still missing; no
wrapper arity is guessed.0x7F57B4 actually extends84B through0x7F5808 and
copies an unaligned four-byte local before calling table+0x50.

DUNGEON0x8D1658 wordwise context retains invalid encodings and packed halfwords
without using disassembly failure as data provenance. Find an accessor or asset
header before a data label. All other unresolved pieces retain prior routes.
