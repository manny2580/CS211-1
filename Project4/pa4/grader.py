#!/usr/bin/python
import autograde
import os, os.path

assignment_name = 'PA4'
release = 1

autograde.Test.output_limit = 50*1024*1024
autograde.Test.time_limit   = 60
autograde.Test.error_limit  = 5

assignment = autograde.Project("truthtable",
        autograde.FileTests(id="1", weight=5),
        autograde.FileTests(id="2", weight=5),
        autograde.FileTests(id="3", weight=5)
    )

if __name__ == '__main__':
    autograde.set_asan_symbolizer()
    autograde.main(assignment_name, assignment, release)
