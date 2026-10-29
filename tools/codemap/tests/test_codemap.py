"""codemap: clang declaration/call facts, retail ABI facts and the conflict classifier on small fixtures."""
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
sys.path[:0] = [str(ROOT / 'tools/codemap'), str(ROOT / 'tools/build')]
import abi            # noqa: E402
import ast_facts      # noqa: E402
import codemap as CM  # noqa: E402

CLANG = shutil.which('clang')
AS = shutil.which('mipsel-linux-gnu-as')


class Pure(unittest.TestCase):
    def test_split_function_type(self):
        self.assertEqual(ast_facts.split_function_type('s32 (s32, void *)'), ('s32', ['s32', 'void *'], False, True))
        self.assertEqual(ast_facts.split_function_type('void (void)'), ('void', [], False, True))
        self.assertEqual(ast_facts.split_function_type('s32 ()'), ('s32', [], False, False))
        self.assertEqual(ast_facts.split_function_type('void (s32, ...)'), ('void', ['s32'], True, True))
        self.assertEqual(ast_facts.split_function_type('void (*(s32))(void)')[1], ['s32'])

    def test_norm_and_classify(self):
        self.assertEqual(CM.norm_sig('const u8 * (s32,  const void *)'), 'u8*(s32,void*)')
        self.assertEqual(CM.classify({'s16(s32,s32)', 's32(s32,s32)'}), 'ret_width')
        self.assertEqual(CM.classify({'void(void*,void*)', 'void(void*)'}), 'arity')
        self.assertEqual(CM.classify({'void(Actor*)', 'void(void*)'}), 'param_type')
        self.assertEqual(CM.classify({'void*(s32)', 's32(s32,s32)'}), 'mixed:arity+ret_other')


@unittest.skipUnless(CLANG, 'clang not installed')
class ClangFacts(unittest.TestCase):
    def setUp(self):
        (ROOT / 'tmp').mkdir(exist_ok=True)
        self.dir = Path(tempfile.mkdtemp(dir=ROOT / 'tmp'))
        (self.dir / 'include').mkdir()
        (self.dir / 'src').mkdir()
        (self.dir / 'include/h.h').write_text('typedef int s32;\ntypedef short s16;\nextern s32 f(s32, s32);\n')
        (self.dir / 'src/a.c').write_text(
            '#include "h.h"\n'
            'extern s16 g();\n'
            's32 f(s32 a, s32 b) { return a + b; }\n'
            'void h(unsigned char x) {\n'
            '    s16 v;\n'
            '    extern void k(s32);\n'
            '    extern s32 f();\n'
            '    f(1, 2);\n'
            '    v = f(x, 2);\n'
            '    if (f(1, x)) k(0);\n'
            '    (void)g();\n'
            '    k((s16)f(3, 4));\n'
            '}\n')

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def test_decls_and_calls(self):
        headers = []
        decls, calls, error = ast_facts.unit_facts(self.dir, 'src/a.c', headers)
        self.assertIsNone(error)
        self.assertEqual(headers, ['include/h.h'])
        by = {(d['name'], d['file'], d['kind']): d for d in decls}
        self.assertEqual(by[('f', 'include/h.h', 'proto')]['line'], 3)
        self.assertEqual(by[('f', 'src/a.c', 'def')]['params'], ['s32', 's32'])
        self.assertFalse(by[('g', 'src/a.c', 'proto')]['has_proto'])
        self.assertTrue(by[('k', 'src/a.c', 'proto')]['local'])
        local_f = [d for d in decls if d['name'] == 'f' and d['local']][0]
        # clang prints the redeclaration as the composite type; the site was written unprototyped.
        self.assertEqual((local_f['signature'], local_f['composite'], local_f['has_proto']),
                         ('s32 ()', 's32 (s32, s32)', False))
        self.assertEqual(CM.canonical_site(local_f), 'int()')
        uses = [(c['callee'], c['ret_use']) for c in calls]
        self.assertEqual(uses, [('f', 'ignored'), ('f', 'conv:s16+assigned:s16'), ('f', 'cond'), ('k', 'ignored'),
                                ('g', 'ignored'), ('k', 'ignored'), ('f', 'cast:s16')])
        second = calls[1]
        self.assertEqual(second['arg_types'], ['unsigned char', 'int'])
        self.assertEqual(second['param_types'], ['s32', 's32'])
        self.assertEqual(second['caller'], 'h')


@unittest.skipUnless(CLANG, 'clang not installed')
class Refresh(unittest.TestCase):
    """build -> edit a header -> check reports it -> refresh re-parses only its consumers."""

    def setUp(self):
        (ROOT / 'tmp').mkdir(exist_ok=True)
        self.dir = Path(tempfile.mkdtemp(dir=ROOT / 'tmp'))
        for rel, text in {'include/h.h': 'int f(int);\n', 'src/a.c': '#include "h.h"\nint a(void) { return f(1); }\n',
                          'src/b.c': 'extern long f();\nint b(void) { return 0; }\n'}.items():
            (self.dir / rel).parent.mkdir(parents=True, exist_ok=True)
            (self.dir / rel).write_text(text)
        self.map = CM.CodeMap(self.dir, self.dir / 'build/codemap.db', workers=1, nice=0, log=lambda m: None)

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def test_incremental(self):
        self.map.open(fresh=True)
        self.map.refresh(force=True)
        db = self.map.db
        fam = CM.q_census(db)
        self.assertEqual(fam['names_with_two_or_more'], 1)            # f: int(int) vs long()
        self.assertEqual(CM.q_callers(db, 'f')['ret_use'], {'returned': 1})
        (self.dir / 'include/h.h').write_text('int g(int);\n')
        self.assertFalse(self.map.check()['fresh'])
        self.map.refresh()
        names = {r[0] for r in db.execute("SELECT name FROM decl WHERE file='include/h.h'")}
        self.assertEqual(names, {'g'})                                  # the removed header site is gone
        self.assertTrue(self.map.check()['fresh'])
        stats = json.loads(db.execute("SELECT value FROM meta WHERE key='last_refresh'").fetchone()[0])
        self.assertEqual(stats['parsed'], 1)                            # only a.c sees h.h


@unittest.skipUnless(AS, 'mipsel-linux-gnu-as not installed')
class RetailAbi(unittest.TestCase):
    def assemble(self, body, extra=''):
        (ROOT / 'tmp').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=ROOT / 'tmp') as td:
            src, out = Path(td) / 'x.s', Path(td) / 'x.o'
            src.write_text('.set noreorder\n.set noat\n.section .text.f,"ax"\n.globl f\n.type f,@function\nf:\n'
                           + body + '\n.size f, .-f\n' + extra)
            subprocess.run([AS, '-EL', '-march=r3000', '-o', str(out), str(src)], check=True)
            return abi.analyze_object(out.read_bytes())

    def test_narrow_return_and_args(self):
        facts = self.assemble('addu $v0, $a0, $a1\nsll $v0, $v0, 16\njr $ra\nsra $v0, $v0, 16')
        f = facts['functions'][0]
        self.assertEqual(f['args_read'], ['a0', 'a1'])
        self.assertEqual(f['return_ext'], ['s16'])
        self.assertTrue(f['v0_all_paths'])

    def test_void_function_and_call_site(self):
        facts = self.assemble('addiu $sp, $sp, -24\nsw $ra, 16($sp)\nmove $a1, $a0\nlhu $a0, 4($a0)\n'
                              'jal g\nnop\nandi $v0, $v0, 0xffff\nlw $ra, 16($sp)\njr $ra\naddiu $sp, $sp, 24')
        f, call = facts['functions'][0], facts['calls'][0]
        self.assertEqual(f['args_read'], ['a0'])
        self.assertEqual(call['callee'], 'g')
        self.assertEqual((call['args']['a0'], call['args']['a1'], call['args']['a2']), ('load_lhu', 'move', 'inherited'))
        self.assertEqual(call['v0_use'], 'ext_u16')
        self.assertEqual(f['return_ext'], ['u16'])

    def test_path_without_v0(self):
        facts = self.assemble('beqz $a0, 1f\nnop\naddiu $v0, $zero, 1\n1:\njr $ra\nnop')
        f = facts['functions'][0]
        self.assertFalse(f['v0_all_paths'])
        self.assertEqual(f['v0_at_return'], ['none', 'own'])

    def test_sibcall_returns_callee_value(self):
        facts = self.assemble('j g\nmove $a0, $a1')
        f, call = facts['functions'][0], facts['calls'][0]
        self.assertEqual((call['kind'], call['v0_use']), ('sibcall', 'tail'))
        self.assertEqual(f['args_read'], ['a1'])
        self.assertEqual(f['sibcalls'], 1)


if __name__ == '__main__':
    unittest.main()
