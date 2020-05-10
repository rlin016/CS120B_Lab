# Test file for "Lab7"


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

test "Testing output of Count"
timeContinue
expectPORTC 0x00
checkResult

test "Testing increment of Count"
setPINA 0xFE
timeContinue 
expectPORTC 0x01
checkResult

test "Testing max increment of Count (increment by 10)"
setPINA 0xFE
timeContinue 10
expectPORTC 0x09
checkResult

setPINA 0xFF
timeContinue

test "Testing decrement of Count"
setPINA 0xFD
timeContinue
expectPORTC 0x08
checkResult

test "Testing max decrement of count (decrement by 10)"
setPINA 0xFD
timeContinue 10
expectPORTC 0x00
checkResult

test "Testing reset (increment to 6 and reset)"
setPINA 0xFE
timeContinue 6
expectPORTC 0x05
checkResult
setPINA 0xFF
setPINA 0xFC
timeContinue
expectPORTC 0x00
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
