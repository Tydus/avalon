[ -f Makefile ] && make distclean
rm aclocal.m4 autom4te.cache configure depcomp install-sh Makefile.in missing -rf
find -iname Makefile.in | xargs rm
