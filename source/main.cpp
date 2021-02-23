#include "Menu.h"



int main()try
{
  
        Menu menu;
        menu.run();
        return 0;
    }
    catch (std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unknown exception\n";
        return EXIT_FAILURE;
    }