# C64InTheDark
This is Commodore 64 port of In the Dark.

Compile with CC65 on a linux system to generate the prg file using the following command:
cl65 -o itdark.prg -t c64 itdark.c

Note well - do NOT use the -O optimze switch - it breaks handling of loop exits and booleans in general.

The prg file can then be loaded onto a real commodore 64 or started in VICE using Smart Attach -> Choose prg file and hit Autostart.

VICE can also be used to create a D64 image that can be loaded on a real C64:
c1541 -format inthedark,id d64 inthedark.d64 -attach inthedark.d64 -write itdark.prg

The original can be found here:
https://github.com/kianryan/InTheDark

This was designed for the C64 or above.  It MAY work with a fully expanded 16K Vic 20, if compiled for that target, but has not been tested.

NOTE:
The BASIC version has been abandonned in favor of a C port, for speed reasons.