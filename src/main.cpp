#include <iostream>

#include "application/application.h"

int main()
{
    Application app;
    app.Init();

    app.Execute();
    app.Terminate();

    return 0;
}