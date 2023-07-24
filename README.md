# C64InTheDark
This is Commodore 64 port of In the Dark.

Compile with CC65 on a linux system to generate the prg file using the following command:
cl65 -O -o itdark.prg -t c64 itdark.c

The prg file can then be loaded onto a real commodore 64 or started in VICE using Smart Attach -> Choose prg file and hit Autostart.

The original can be found here:
https://github.com/kianryan/InTheDark

This was designed for the C64 or above.  It MAY work with a fully expanded 16K Vic 20, if compiled for that target, but has not been tested.

NOTE:
The BASIC version has been abandonned in favor of a C port, for speed reasons.