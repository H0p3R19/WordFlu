#include "headers.h"

Basic::Basic() : err(), render(err), game(err , render){
    Running = General_Init();
} 

bool Basic::General_Init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){return false;} //My error func uses SDL createwindow , so if SDL fails , no points of this shit
    if (!render.Init_win()){return false;} //Window initilization
    if (!render.Init_TTF()){return false;} //TTF initilization
    if (!render.Init_renderer()){return false;} //Renderer initilization
    if (!render.Init_media()){return false;} //Media initilization
    game.game_state = Gameplay_Loop::State::Welcome;
    return true;
}

void Basic::Run(){

    if (!Running)
    {
        return;
    }
    
    while (Running)
    {
        Handle_Events();
        Update();
        Render();
    }
}

bool Basic::PointInRect(int x, int y, const SDL_Rect& rect){
    return(
        x >= rect.x //is x not too much at the left
        &&
        x < rect.x + rect.w  //is x not too much to the right?
        &&
        y >= rect.y //is y not too low?
        &&
        y < rect.y + rect.h //is y not too high?
    );

}

void Basic::Handle_Events(){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            Running = false; //Bye!
        }
        
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                Running = false; //Bye! (Again)
            }
            
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) //No thingy for right mouse clicks cuz dont need it
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            switch (game.game_state)
            {
            case Gameplay_Loop::State::Welcome:
                if (PointInRect(mouseX , mouseY , render.StartBtn.rect))
                {
                    game.game_state = Gameplay_Loop::State::Question;
                }
                break;
            
            case Gameplay_Loop::State::Question:
                if (PointInRect(mouseX , mouseY , render.AnswerBtn.rect))
                {
                    game.game_state = Gameplay_Loop::State::Answer;
                }
                break;

            case Gameplay_Loop::State::Answer:
                if (PointInRect(mouseX , mouseY , render.Question_btn.rect))
                {
                    game.game_state = Gameplay_Loop::State::Question;
                    game.Question++;
                    break;
                    
                }
                
                break;
            default:
                break;
            }
            
        }
        
    }
}

void Basic::Update(){
    switch (game.game_state)
    {
    case Gameplay_Loop::State::Question:
        game.GetQuestion();
        break;
    
    case Gameplay_Loop::State::Answer:
        game.GetAnswer();
        break;
    default:
        break;
    }
}

void Basic::Render(){
    SDL_RenderClear(render.hope);
    game.Main_Loop();
    SDL_RenderPresent(render.hope);
}