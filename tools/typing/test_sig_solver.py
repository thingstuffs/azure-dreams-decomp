"""Unit tests for the signature-consensus solver: ABI extractor, probe text variants, consensus, writer.

    python3 -m unittest tools/typing/test_sig_solver.py
"""
from pathlib import Path
import struct
import sys
import unittest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'headers')]
import abi_facts as A  # noqa: E402
import sig_consensus as K  # noqa: E402
import sig_probe as S  # noqa: E402
import sig_txn as T  # noqa: E402

REG = {n: i for i, n in enumerate(A.GPR_NAMES)}


# --- a tiny MIPS I encoder for test code
def r(funct, rd=0, rs=0, rt=0, sa=0):
    return (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | funct


def i_(op, rt, rs, imm):
    return (op << 26) | (rs << 21) | (rt << 16) | (imm & 0xffff)


def addu(d, s, t):
    return r(0x21, REG[d], REG[s], REG[t])


def move(d, s):
    return addu(d, s, 'zero')


def sll(d, t, sa):
    return r(0x00, REG[d], 0, REG[t], sa)


def sra(d, t, sa):
    return r(0x03, REG[d], 0, REG[t], sa)


def andi(t, s, imm):
    return i_(0x0c, REG[t], REG[s], imm)


def addiu(t, s, imm):
    return i_(0x09, REG[t], REG[s], imm)


def lw(t, off, base):
    return i_(0x23, REG[t], REG[base], off)


def lhu(t, off, base):
    return i_(0x25, REG[t], REG[base], off)


def sw(t, off, base):
    return i_(0x2b, REG[t], REG[base], off)


def sb(t, off, base):
    return i_(0x28, REG[t], REG[base], off)


def jal(target=0):
    return (0x03 << 26) | (target >> 2)


def jr(s):
    return r(0x08, 0, REG[s])


NOP = 0


def code(*words):
    return b''.join(struct.pack('<I', w) for w in words)


class AbiFunctionTests(unittest.TestCase):
    def test_arity_from_argument_reads_before_write(self):
        f = A.analyze(code(addu('v0', 'a0', 'a1'), move('a2', 'zero'), addu('v0', 'v0', 'a2'), jr('ra'), NOP))
        self.assertEqual(f['args'], ['a0', 'a1'])     # a2 written before its read
        self.assertEqual(f['arity'], 2)
        self.assertEqual(f['returns'], 'value')

    def test_stack_argument_reads_count(self):
        f = A.analyze(code(addiu('sp', 'sp', -24), lw('t0', 40, 'sp'), addiu('sp', 'sp', 24), jr('ra'), NOP))
        self.assertEqual(f['stack_args'], [0])        # 40 = frame 24 + 16: the fifth argument
        self.assertEqual(f['arity'], 5)

    def test_cop2_moves_consume_argument_registers(self):
        mtc2_a0 = 0x48840000
        ctc2_a2 = 0x48C60800
        gte_cmd = 0x4A180001
        f = A.analyze(code(mtc2_a0, ctc2_a2, gte_cmd, jr('ra'), NOP))
        self.assertEqual(f['args'], ['a0', 'a2'])
        self.assertEqual(f['arity'], 3)
        self.assertEqual(f['returns'], 'void')

    def test_return_width_from_extension_in_delay_slot(self):
        f = A.analyze(code(sll('v0', 'a0', 16), jr('ra'), sra('v0', 'v0', 16)))
        self.assertEqual(f['ret_defs'], ['s16'])
        self.assertEqual(f['ret_fits'], ['s16'])

    def test_return_fits_join_constants(self):
        f = A.analyze(code(andi('v0', 'a0', 0xff), jr('ra'), NOP))
        self.assertEqual(f['ret_fits'], ['u8', 'u16', 's16'])

    def test_call_site_arguments_and_result_use(self):
        relocs = {8: ('func_80001000', False)}
        f = A.analyze(code(lhu('a0', 0, 's0'), andi('a1', 's1', 0xffff), jal(), NOP,
                           sll('v0', 'v0', 16), sra('v0', 'v0', 16), jr('ra'), NOP), relocs, '.text.f')
        call = f['calls'][0]
        self.assertEqual(call['target'], 'func_80001000')
        self.assertEqual(call['args']['a0'], 'u16')
        self.assertEqual(call['args']['a1'], 'u16')
        self.assertEqual(call['set_in_block'], ['a0', 'a1'])
        self.assertIn('ext_s16', call['v0_use'])

    def test_copied_result_is_followed(self):
        relocs = {0: ('g', False)}
        f = A.analyze(code(jal(), NOP, move('s0', 'v0'), sb('s0', 0, 'a0'), jr('ra'), NOP), relocs, '.text.f')
        self.assertEqual(f['calls'][0]['v0_use'], ['returned', 'store8'])   # v0 also reaches jr ra

    def test_unused_result(self):
        relocs = {0: ('g', False)}
        f = A.analyze(code(jal(), NOP, addiu('v0', 'zero', 1), jr('ra'), NOP), relocs, '.text.f')
        self.assertEqual(f['calls'][0]['v0_use'], ['none'])


def elf(text_bytes, symbols, file_name='a.c', relocs=()):
    """Minimal ELF32 LE REL object: .text, .rel.text, .symtab, .strtab, .shstrtab."""
    shstr = b'\0.text\0.rel.text\0.symtab\0.strtab\0.shstrtab\0'
    off = {n: shstr.index(n.encode() + b'\0') for n in ('.text', '.rel.text', '.symtab', '.strtab', '.shstrtab')}
    strtab = b'\0' + file_name.encode() + b'\0'
    syms = [struct.pack('<IIIBBH', 0, 0, 0, 0, 0, 0), struct.pack('<IIIBBH', 1, 0, 0, 4, 0, 0xfff1)]
    for name, value, size, bind in symbols:
        syms.append(struct.pack('<IIIBBH', len(strtab), value, size, (bind << 4) | 2, 0, 1))
        strtab += name.encode() + b'\0'
    symtab = b''.join(syms)
    rel = b''.join(struct.pack('<II', o, (s << 8) | t) for o, t, s in relocs)
    body = [text_bytes, rel, symtab, strtab, shstr]
    pos, offs = 52, []
    for b in body:
        offs.append(pos)
        pos += len(b)
    shoff = pos
    head = b'\x7fELF\x01\x01\x01' + b'\0' * 9 + struct.pack('<HHIIIIIHHHHHH', 1, 8, 1, 0, 0, shoff, 0, 52, 0, 0,
                                                              40, 6, 5)
    sh = [b'\0' * 40,
          struct.pack('<10I', off['.text'], 1, 6, 0, offs[0], len(text_bytes), 0, 0, 4, 0),
          struct.pack('<10I', off['.rel.text'], 9, 0, 0, offs[1], len(rel), 3, 1, 4, 8),
          struct.pack('<10I', off['.symtab'], 2, 0, 0, offs[2], len(symtab), 4, 2, 4, 16),
          struct.pack('<10I', off['.strtab'], 3, 0, 0, offs[3], len(strtab), 0, 0, 1, 0),
          struct.pack('<10I', off['.shstrtab'], 3, 0, 0, offs[4], len(shstr), 0, 0, 1, 0)]
    return head + b''.join(body) + b''.join(sh)


class ObjectDifferenceTests(unittest.TestCase):
    def test_file_symbol_and_string_table_are_metadata(self):
        a = elf(code(jr('ra'), NOP), [('f', 0, 8, 1)], 'src/x.c')
        b = elf(code(jr('ra'), NOP), [('f', 0, 8, 1)], 'src/.sigprobe_123_x.c')
        self.assertNotEqual(a, b)
        self.assertIsNone(A.object_difference(a, b))

    def test_code_and_relocation_changes_are_reported(self):
        a = elf(code(jr('ra'), NOP), [('f', 0, 8, 1)])
        b = elf(code(jr('ra'), addiu('v0', 'zero', 1)), [('f', 0, 8, 1)])
        self.assertEqual(A.object_difference(a, b)['kind'], 'bytes')
        c = elf(code(jal(), NOP), [('f', 0, 8, 1), ('g', 0, 0, 1)], relocs=[(0, 4, 3)])
        d = elf(code(jal(), NOP), [('f', 0, 8, 1), ('h', 0, 0, 1)], relocs=[(0, 4, 3)])
        self.assertEqual(A.object_difference(c, d)['kind'], 'relocation')

    def test_object_facts_reads_functions_and_calls(self):
        o = elf(code(jal(), NOP, jr('ra'), NOP), [('f', 0, 16, 1), ('g', 0, 0, 1)], relocs=[(0, 4, 3)])
        facts = A.object_facts(o)
        self.assertEqual(facts['f']['calls'][0]['target'], 'g')


TU = '''#include "common.h"
#include "dungeon/item.h"

extern s16 find_rect(u16, u16);
extern s32 other(void);

/* Uses the rectangle query. */
s32 caller(s16 x, s16 y) {
    return find_rect(x, y) == other();
}
'''

DEF = '''#include "common.h"

s16 find_rect(s32 x, s32 y) {
    s32 index;

    for (index = 0; index < 4; index++) {
        if (x == index) {
            return index;
        }
    }
    return -1;
}
'''


class ProbeTextTests(unittest.TestCase):
    def test_hide_variant_wraps_includes_and_replaces_declarations(self):
        spans = [(a, b) for a, b, n, _ in S.local_decls(TU, 'find_rect')]
        out = S.hide_variant(TU, 'find_rect', spans, 's32 find_rect(s32 x, s32 y)')
        self.assertEqual(out.count('#define find_rect __sigprobe_find_rect'), 2)
        self.assertEqual(out.count('#undef find_rect'), 2)
        self.assertNotIn('extern s16 find_rect(u16, u16);', out)
        self.assertIn('extern s32 find_rect(s32 x, s32 y);\n', out)
        self.assertLess(out.index('extern s32 find_rect'), out.index('s32 caller('))
        self.assertGreater(out.index('extern s32 find_rect'), out.rindex('#undef find_rect'))

    def test_control_keeps_the_local_spelling(self):
        out = S.hide_variant(TU, 'find_rect')
        self.assertIn('extern s16 find_rect(u16, u16);', out)

    def test_split_and_return_text(self):
        prefix, params = S.split_proto('extern s16 *find_rect(u16 a, u16 b);', 'find_rect')
        self.assertEqual(S.ret_text(prefix), 's16 *')
        self.assertEqual(params, 'u16 a, u16 b')
        self.assertEqual(S.proto('s16 *', 'f', 'void'), 's16 *f(void)')

    def test_width_rule_rewrites_definition(self):
        out, added = S.retype_definition(DEF, 'find_rect', 's32', 's16')
        self.assertIn('s32 find_rect(s32 x, s32 y) {', out)
        self.assertIn('return (s16)index;', out)
        self.assertIn('return -1;', out)            # in-range constant: no cast
        self.assertEqual(added, 1)

    def test_narrowing_wraps_compound_expressions(self):
        body = '{ return a + b; return (s16)c; return 70000; }'
        out, n = S.narrow_returns(body, body, 's16')
        self.assertIn('return (s16)(a + b);', out)
        self.assertIn('return (s16)c;', out)
        self.assertIn('return (s16)70000;', out)
        self.assertEqual(n, 2)


def site(path, results, calibrated=True, arity=2, is_def=False, blocked=None):
    return dict(path=path, results=results, calibrated=calibrated, arity=arity, is_def=is_def, blocked=blocked,
                spelling='s16 f(u16, u16)')


DEFN = dict(path='src/d.c', proto='s16 f(s32 x, s32 y)', ret='s16', params='s32 x, s32 y', arity=2)


class ConsensusTests(unittest.TestCase):
    def test_definition_spelling_wins_when_neutral_everywhere(self):
        d = K.decide('f', 'include/d.h', DEFN, [site('a.c', {'D': 'neutral', 'W': 'neutral'}),
                                                 site('src/d.c', {'D': 'neutral', 'W': 'neutral'}, is_def=True)])
        self.assertEqual((d['status'], d['choice']), ('unified', 'D'))

    def test_width_rule_when_narrow_return_is_not_neutral(self):
        d = K.decide('f', 'include/d.h', DEFN, [site('a.c', {'D': 'changed', 'W': 'neutral'}),
                                                 site('src/d.c', {'D': 'neutral', 'W': 'neutral'}, is_def=True)])
        self.assertEqual((d['status'], d['choice'], d['ret'], d['narrowing']), ('unified', 'W', 's32', 's16'))

    def test_wide_definition_has_no_width_candidate(self):
        wide = dict(DEFN, ret='s32', proto='s32 f(s32 x, s32 y)')
        d = K.decide('f', 'include/d.h', wide, [site('a.c', {'D': 'changed', 'par_D': 'changed'})])
        self.assertEqual(d['status'], 'refused')
        self.assertEqual(d['floor_class'], 'param_width')
        self.assertEqual(d['casts_would_unify'], dict(sites=1, sufficient=True, kinds=['param_width']))

    def test_phantom_arguments_floor(self):
        # register_node: callers pass up to four arguments, the callee reads two
        d = K.decide('register_node', 'include/engine/node.h', dict(DEFN, ret='s32'),
                     [site('a.c', {'D': 'neutral'}), site('b.c', {'D': 'error'}, arity=4)],
                     abi=dict(arity=[2]))
        self.assertEqual(d['floor_class'], 'phantom_arguments')
        self.assertEqual(d['blocking'][0]['path'], 'b.c')
        rec = K.floor_record(d, dict(tree='abc'))
        self.assertEqual(rec['schema'], 'azure-clean.prototype-floor.v1')
        self.assertEqual(rec['abi'], dict(arity=[2]))

    def test_uncalibrated_and_unbuilt_sites(self):
        d = K.decide('f', 'h', DEFN, [site('a.c', {'D': 'neutral'}, calibrated=False),
                                       dict(path='u.c', unbuilt=True)])
        self.assertEqual(d['floor_class'], 'unprobeable')
        self.assertEqual(d['unbuilt'], ['u.c'])
        d = K.decide('f', 'h', DEFN, [site('a.c', {'D': 'neutral'}), dict(path='u.c', unbuilt=True)])
        self.assertEqual(d['status'], 'unified')

    def test_name_hold(self):
        d = K.decide('f', None, DEFN, [], hold='knr_definition')
        self.assertEqual((d['status'], d['floor_class']), ('refused', 'name_hold'))


class SdkEvidenceTests(unittest.TestCase):
    def test_named_library_rows_only(self):
        import json
        import tempfile
        import sig_census as C
        rows = [dict(name='rsin', addr='80060000', ret='int', params=['int'], cdecl='int rsin(int a);'),
                dict(name='game_helper', addr='80048D00', ret='void', params=[], cdecl='void SsUtReverbOff(void);'),
                dict(name='x', addr='80001000', ret='undefined4', params=[], cdecl='undefined4 FUN_80001000(void);'),
                dict(name='y', addr='80001004', err='nofunc')]
        with tempfile.NamedTemporaryFile('w', suffix='.jsonl', delete=False) as fh:
            fh.write('\n'.join(json.dumps(r) for r in rows) + '\n')
        ev = C.sdk_evidence(fh.name)
        Path(fh.name).unlink()
        self.assertEqual(sorted(ev), ['rsin'])
        self.assertEqual(ev['rsin']['params'], ['int'])


class WriterTests(unittest.TestCase):
    def test_apply_spans_removes_whole_lines(self):
        a, b, _, _ = S.local_decls(TU, 'find_rect')[0]
        out = T.apply_spans(TU, [(a, b, '')])
        self.assertNotIn('find_rect(u16', out)
        self.assertIn('extern s32 other(void);', out)
        self.assertNotIn('\n\n\n', out)

    def test_append_to_header_is_idempotent(self):
        h = '#ifndef X_H\n#define X_H\n#include "common.h"\ns32 g(void);\n#endif\n'
        out = T.append_to_header(h, ['s32 f(s32 x, s32 y);'])
        self.assertIn(T.R.APPEND_MARK + '\ns32 f(s32 x, s32 y);\n', out)
        self.assertTrue(out.rstrip().endswith('#endif'))
        self.assertEqual(T.append_to_header(out, ['s32 f(s32 x, s32 y);']), out)

    def test_pointer_kind_mismatch(self):
        vp, s32, void, s16 = ('void', 1, 'ptr'), ('s32', 0, 'int'), ('void', 0, 'void'), ('s16', 0, 'int')
        self.assertTrue(T.pointer_kind_mismatch((s32, (s32,), False), (vp, (s32,), False)))
        self.assertFalse(T.pointer_kind_mismatch((void, (s32,), False), (vp, (s32,), False)))
        self.assertFalse(T.pointer_kind_mismatch((s16, None, False), (s32, (vp,), False)))
        self.assertTrue(T.pointer_kind_mismatch((s32, (s32,), False), (s32, (vp,), False)))

    def test_floor_marker(self):
        text = 'extern s32 register_node();\nvoid f(void);\n'
        out = T.mark_floor(text, 0, len('extern s32 register_node();'), 'callers pass 2-4 arguments')
        self.assertIn('extern s32 register_node(); /* Unprototyped: callers pass 2-4 arguments */\n', out)
        self.assertEqual(T.mark_floor(out, 0, len('extern s32 register_node();'), 'x', True), out)


if __name__ == '__main__':
    unittest.main()
