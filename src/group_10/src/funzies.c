#include "terminal.h"

void splashScreen() {
    terminalClear();
    terminalSetColor(13, 0);
    terminalPrint("\n\n\n\n\n\n");
    terminalPrintWithDelay("  @@@@@@@   @@@     @@@@ @@@@@@@@@@@@@   @@@@@@@@        .@@@       @@@@@@@@@  \n", 400);
    terminalPrintWithDelay("    @@@     @@@   @@@@        @@@       @     @@@@    @@@@@@@      @@@@   @@@@ \n", 400);
    terminalPrintWithDelay("    @@@     @@@ @@@@          @@@             @@@@       @@@@       @@@@@@@@@  \n", 400);
    terminalPrintWithDelay("    @@@     @@@@@@@@          @@@           @@@@         @@@@      @@@@   @@@@ \n", 400);
    terminalPrintWithDelay("    @@@     @@@   @@@@        @@@        @@@@&           @@@@      @@@     @@@ \n", 400);
    terminalPrintWithDelay("  @@@@@@@   @@@     @@@@      @@@       @@@@@@@@@@@   @@@@@@@@@@    @@@@@@@@@  \n", 400);
    terminalPut('\n');
    terminalPrintWithDelay("                             OS Made By Group 10                               \n\n\n", 3000);
    terminalSetColor(7, 0);
}