#include "headers.h"


void Error_Handler::Error(const std::string& message , Type part , SDL_Window* win){
    std::string error_message = message + "\nHere is why:\n";
    switch (part)
    {
    case Type::SDL:
        error_message += SDL_GetError();
        break;

    case Type::IMG:
        error_message += IMG_GetError();
        break;

    case Type::TTF:
        error_message += TTF_GetError();
        break;
    case Type::SPECIAL: //this is for my own things that doesnt have fancy error catchers.
        break;
    default:
        //Error for Error handler , what?
        error_message += "I have no idea (internal error)";
        break;
    }
    SDL_ShowSimpleMessageBox(
    SDL_MESSAGEBOX_ERROR,
    "ERROR",
    error_message.c_str(),   
    win);
    SDL_ClearError();
}