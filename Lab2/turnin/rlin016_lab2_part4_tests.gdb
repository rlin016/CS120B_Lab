# Test file for "Lab2"


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

test "PINA: 0x8C, PINB: 0x00, PINC: 0x00 => PORTD: 0x8E"
setPINA 0x8C
setPINB 0x00
setPINC 0x00
continue 2
expectPORTD 0x8E
checkResult

test "PINA: 0x8D, PINB: 0x00, PINC: 0x00 => PORTD : 0x8F"
setPINA 0x8D
setPINB 0x00
setPINC 0x00
continue 2
expectPORTD 0x8F
checkResult

test "PINA: 0x00, PINB: 0x8D, PINC: 0x00 => PORTD: 0x8D"
setPINA 0x00
setPINB 0x8D
setPINC 0x00
continue 2
expectPORTD 0x8D
checkResult

test "PINA: 0x00, PINB: 0x00, PINC: 0x8D => PORTD: 0x8F"
setPINA 0x00
setPINB 0x00
setPINC 0x8D
continue 2
expectPORTD 0x8F
checkResult

test "PINA: 0x46, PINB: 0x00, PINC: 0x46 => PORTD: 0x8C"
setPINA 0x46
setPINB 0x00
setPINC 0x46
continue 2
expectPORTD 0x8C
checkResult

test "PINA: 0x47, PINB: 0x00, PINC: 0x46 => PORTD: 0x8D"
setPINA 0x47
setPINB 0x00
setPINC 0x46
continue 2
expectPORTD 0x8D
checkResult

test "PINA: 0x78, PINB: 0x00, PINC: 0x14 => PORTD: 0x8E"
setPINA 0x78
setPINB 0x00
setPINC 0x14
continue 2
expectPORTD 0x8E
checkResult

test "PINA: 0x78, PINB: 0x00, PINC: 0x15 => PORTD: 0x8F"
setPINA 0x78
setPINB 0x00
setPINC 0x15
continue 2
expectPORTD 0x8F
checkResult

test "PINA: 0x64, PINB: 0x14, PINC: 0x14 => PORTD: 0x8C"
setPINA 0x64
setPINB 0x14
setPINC 0x14
continue 2
expectPORTD 0x8C
checkResult

test "PINA: 0x65, PINB: 0x15, PINC: 0x14 => PORTD: 0x8F"
setPINA 0x65
setPINB 0x15
setPINC 0x14
continue 2
expectPORTD 0x8F
checkResult

test "PINA: 0x00, PINB: 0x00, PINC: 0x00 => PORTD: 0x00"
setPINA 0x00
setPINB 0x00
setPINC 0x00
continue 2
expectPORTD 0x00
checkResult

test "PINA: 0x01, PINB: 0x01, PINC: 0x01 => PORTD: 0x00"
setPINA 0x01
setPINB 0x01
setPINC 0x01
continue 2
expectPORTD 0x00
checkResult

test "PINA: 0x0A, PINB: 0x0A, PINC: 0x0A => PORTD: 0x1C"
setPINA 0x0A
setPINB 0x0A
setPINC 0x0A
continue 2
expectPORTD 0x1C
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
