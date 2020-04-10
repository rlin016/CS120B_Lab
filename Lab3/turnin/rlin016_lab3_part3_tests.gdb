# Test file for "Lab3"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n


test "PINA: 0x70 => PORTC: 0x40"
setPINA 0x70
setPINB 0x00
continue 2
expectPORTC 0x40
checkResult

test "PINA: 0x30 => PORTC: 0xC0"
setPINA 0x30
continue 2 
expectPORTC 0xC0
checkResult

test "PINA: 0x71 => PORTC: 0x60"
setPINA 0x71
setPINB 0x00
continue 2
expectPORTC 0x60
checkResult

test "PINA: 0x31 => PORTC: 0xE0"
setPINA 0x31
continue 2
expectPORTC 0xE0
checkResult

test "PINA: 0x73 => PORTC: 0x70"
setPINA 0x73
setPINB 0x00
continue 2
expectPORTC 0x70
checkResult

test "PINA: 0x33 => PORTC: 0xF0"
setPINA 0x33
continue 2
expectPORTC 0xF0
checkResult

test "PINA: 0x75 => PORTC 0x78"
setPINA 0x75
continue 2
expectPORTC 0x78
checkResult

test "PINA: 0x35 => PORTC 0xF8"
setPINA 0x35
continue 2
expectPORTC 0xF8
checkResult

test "PINA: 0x77 => PORTC 0x7C"
setPINA 0x77
continue 2
expectPORTC 0x7C
checkResult

test "PINA: 0x37 => PORTC 0xFC"
setPINA 0x37
continue 2
expectPORTC 0xFC
checkResult

test "PINA: 0x7A => PORTC 0x3E"
setPINA 0x7A
continue 2
expectPORTC 0x3E
checkResult

test "PINA: 0x3A => PORTC: 0xBE"
setPINA 0x3A
continue 2
expectPORTC 0xBE
checkResult

test "PINA: 0x7D => PORTC 0x3F"
setPINA 0x7D
continue 2
expectPORTC 0x3F
checkResult

test "PINA: 0x3D => PORTC 0xBF"
setPINA 0x3D
continue 2
expectPORTC 0xBF
checkResult

test "PINA 0x50 => PORTC 0x00"
setPINA 0x50
continue 2
expectPORTC 0x40
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
