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

# ALMOST PASSING AL EXER8080 TESTS
Issue #1: Always Clear Bit 5 and Bit 3, and Set Bit 1 for POP PSW
instruction.

Issue #2: Auxillary Carry Flag (AC) value calculation incorrect for
subtraction.

Issue #3: ANA and ANI set Auxillary Carry Flag (AC) to the OR'ing of
bits 3 of the two operands.

Issue #4: XRA, XRI, ORA, ORI clear Auxillary Carry Flag (AC).

Issue #5: Auxillary Carry Flag (AC) value calculation incorrect for
addition.

Issue #6: The prior Carry Flag (CY) value needs to be taken into
account for SBB and SBI subtraction with borrow instuctions.

Issue #7: The prior Carry Flag (CY) value needs to be taken into
account for ADC and ACI addition with carry instructions.

Issue #8: The DAA adjustment can also cause the Carry Flag (CY) to be
set during the addition to the 4 low order bits.

Issue #9: The DAA adjustment can cause the Carry Flag (CY) to be set,
but not to be clear if it was already set.