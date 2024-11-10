#include "getInputFromUser.h"
#include "test.h"


int main(){

    test();

    char selection {};

    do {

        displayMainMenu();

        selection = getSelection();

        switch (selection)
        {
        case 'A':
            handleDampedHarmonicOscillator();
            break;
        
        case 'B':
            handleDoublePendulum();
            break;

        case 'Q':
            handleQuit();
            break;

        default:
            handleUnknown();
            
        }

    } while (selection != 'Q');

    return 0;
}
