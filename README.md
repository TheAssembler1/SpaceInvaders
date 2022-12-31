# SpaceInvaders
Space Invaders emulator written in C

#### Logging lib used can be found here
- https://github.com/rxi/

#### Source to look at for reference
- https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf
- http://www.emulator101.com/reference/8080-by-opcode.html
- https://pastraiser.com/cpu/i8080/i8080_opcodes.html

#### Following this order of emulators 
- Chip 8
- Space Invaders
- Pacman
- Gameboy
- GBC
- Sega Master System 
- Sega Genesis

#### Intel 8080 Test
https://altairclone.com/downloads/cpu_tests/
You can find some Intel 8080 CPU tests on this website. These can be run with no OS, 
just a minimal support framework described below:

These binaries should be loaded to memory starting at 0x0100, and at startup, your 
CPU should jump to 0x0100. You should also put two handlers at addresses 0x0000 and 0x0005:

    The handler at 0x0000 signals the end of the test run.

    The handler at 0x0005 is used to communicate the values of the registers C, D and E 
    with the outside world. Register C selects from multiple functions:
        C = 0x02 signals printing the value of register E as an ASCII value
        C = 0x09 signals printing the value of memory pointed to by DE until a '$' character
        is encountered

The easiest is to put an OUT instruction at 0x0000 onwards, and an IN followed by a RET at 
0x0005 onwards, and then set your emulator to do the right thing on port writes / reads.

I have implemented this protocol in a testbench for an FPGA Intel 8080 implementation inspired 
by a software emulator test suite; both of these could be useful references for you in 
implementing the scaffolding necessary to run these CPU tests without any complicated OS,
or even any computer, around your CPU.
