#/usr/bin/python

import autograde
import os, sys, os.path

assignment_name = 'PA1'
release = 1

class FactorTests(autograde.FileTests):
    def get_tests(self, prog, data_dir):
        args = []
        for fname in os.listdir(data_dir):
            if fname.startswith(self.prefix) and fname.endswith(self.ref_suffix):
                arg = fname[len(self.prefix):-len(self.ref_suffix)]
                args.append((int(arg), arg, fname))

        args.sort()

        for (_,arg,ref_name) in args:
            ref = os.path.join(data_dir, ref_name)

            yield autograde.FileRefTest(cmd=[prog, arg], ref_file=ref)

class StanzaTests(autograde.StringTests):
    def get_tests(self, prog, data_dir):
        test_file = os.path.join(data_dir, self.file)

        if not os.path.exists(test_file):
            autograde.logger.warning('Test file not found: %r', test_file)
            return

        autograde.logger.debug('Opening tests file: %r', test_file)

        with open(test_file) as lines:
            args = [prog]
            for line in lines:
                line = line.strip()
                if line.startswith('@'):
                    args.append(line[1:])
                else:
                    yield self.Test(cmd=args, ref=line)
                    args = [prog]


assignment = autograde.MultiProject(
    FactorTests.Project('factor'),
    StanzaTests.Project('warble'),
    StanzaTests.Project('rle'),
    autograde.StdinFileTests.Project('list'),
    autograde.FileTests.Project('mexp'),
    autograde.Project('bst',
        autograde.StdinFileTests(id='1', weight=1.5),
        autograde.StdinFileTests(id='2', weight=1.5)
    ),
    autograde.StdinFileTests.Project('cell', weight=2)
)

if __name__ == '__main__':
    autograde.set_asan_symbolizer()
    autograde.main(assignment_name, assignment, release)
