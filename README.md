# DLD
DLD was the dynamic loading library written by Wingshun Wilson Ho, later donated
to the GNU project.

Since it wasn't easy to find and many versions were scattered on other sites,
having a repository to collect all the versions seems a good idea.

## Do you need it?
Well, today you have `dlopen()`, so it's not that useful.\
But if you tinker with vintage computers and you have some software that needs
it (for example the Interlisp Maiko emulator for SunOS) and didn't come bundled,
now you can have a copy.

## Which version do you need?
Depends. If you have an ANSI-C compiler and GCC, the 3.3 (the latest known) will
do fine.\
If you have only a K&R C compiler, then use the 3.2.7 (or the 3.2.8, let me know
if you have it), since that the 3.3 needs a tool to convert the sources to K&R
form that was bundled with early GhostScript releases.

## Sources
- https://github.com/oldlinux-web/oldlinux-files/tree/master/Linux-0.98/Yggdrasil-0.98.3/usr/src/usr.bin/swipr-rest/prolog/dld-3.2
- https://github.com/oldlinux-web/oldlinux-files/blob/master/ftp-archives/tsx-11.mit.edu/1996-10-07/binaries/libs/dld-3.2.5.bin.tar.gz
- https://www.nic.funet.fi/index/amiga/gnu/beta/
- https://bio-test.nic.funet.fi/pub/OS/4.3bsd/bsdi.com/contrib/lib/
- https://bio-test.nic.funet.fi/pub/OS/4.3bsd/bsdi.com/contrib/database/
- https://ftp.gnu.org/old-gnu/dld/
- https://ooc.sourceforge.net/ooc-list/msg00269.html
- https://www.scnresearch.com/pub/gnu/
- ftp.cs.indiana.edu:/pub/scheme-repository/imp/SCM-support/dld-3.2.6.tar.gz (from Archive.org)
