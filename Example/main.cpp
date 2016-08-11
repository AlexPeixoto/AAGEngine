#include "MyGame.h"


int main(int argc, char* argv[])
{
    MyGame* mg = new MyGame(argc, argv);
    mg->run();
    return EXIT_SUCCESS;
}