# Test file for lab-4-state-machines


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

test "PINA: 0x00 => PORTB: 0x01, state: wait"
setPINA 0x00
continue 2
expectPORTB 0x01
checkResult
expect state wait

test "PINA: 0x01 => PORTB: 0x02, state: PB1_On"
setPINA 0x01
continue 2
expectPORTB 0x02
checkResult
expect state PB1_On

test "PINA: 0x00 => PORTB: 0x02, state: release_PB1_On"
setPINA 0x00
continue 2
expectPORTB 0x02
checkResult
expect state release_PB1_On

test "PINA: 0x01 => PORTB: 0x01, state: PB0_On"
setPINA 0x01
continue 2
expectPORTB 0x01
checkResult
expect state PB0_On

test "PINA: 0x00 => PORTB: 0x01, state: wait"
setPINA 0x00
continue 2
expectPORTB 0x01
checkResult
expect state wait

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
