#include "../include/terminal.h"

void splashScreen() {
    terminalClear();
    terminalSetColor(13, 0);
    terminalPrint("\n\n\n\n\n\n");
    terminalPrint("  @@@@@@@   @@@     @@@@ @@@@@@@@@@@@@   @@@@@@@@        .@@@       @@@@@@@@@  \n");
    terminalPrint("    @@@     @@@   @@@@        @@@       @     @@@@    @@@@@@@      @@@@   @@@@ \n");
    terminalPrint("    @@@     @@@ @@@@          @@@             @@@@       @@@@       @@@@@@@@@  \n");
    terminalPrint("    @@@     @@@@@@@@          @@@           @@@@         @@@@      @@@@   @@@@ \n");
    terminalPrint("    @@@     @@@   @@@@        @@@        @@@@&           @@@@      @@@     @@@ \n");
    terminalPrint("  @@@@@@@   @@@     @@@@      @@@       @@@@@@@@@@@   @@@@@@@@@@    @@@@@@@@@  \n");
    terminalPut('\n');
    terminalPrint("                             OS Made By Group 10                               \n\n\n");
    terminalSetColor(7, 0);
}