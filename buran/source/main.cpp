#include <iostream>

#include "application/application.h"
#include "application/application_arguments.h"

int main(int argc, char* argv[])
{
    ApplicationArguments args(argc, argv);
    
    Application app;
    app.Init(args);

    app.Execute();
    app.Terminate();

    return 0;
}