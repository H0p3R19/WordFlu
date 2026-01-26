//Yo
#pragma once

#include <unordered_map> //Used for 
#include <SDL2/SDL.h> //For ovbious purposes
#include <SDL2/SDL_ttf.h> //For text
#include <string> //Always comes in handy
//#include <SDL2/SDL_mixer.h> //Maybe used later for music



class Error_Handler{
    public:
        enum class Type{
            SDL,
            IMG,
            TTF,
            SPECIAL
        };
        void Error(const std::string& message , Type part , SDL_Window* win);
};

class My_Renderer{
    public:
        struct Drawable //soooooooooooooo
        {
            SDL_Rect rect{0, 0, 0, 0};
            SDL_Texture* texture = nullptr;
            TTF_Font* font = nullptr;
        };

        explicit My_Renderer(Error_Handler& err);
        bool Init_win();
        bool Init_TTF();
        bool Init_media();
        bool Init_renderer();
        void Draw_Obj(SDL_Texture* texture,SDL_Rect& rect,bool is_button , int offsetX ,int offsetY); //this actually draws the thingy
        void Render_Background();

        void Question_Creator(Drawable& obj , Drawable& obj_no , std::string question_no , const std::string& text);
        void Answer_Creator(Drawable& obj , Drawable& obj_no , std::string question_no , const std::string& text);


        SDL_Texture* Render_Obj( SDL_Texture* texture , const std::string& text , SDL_Rect& rect , TTF_Font*& old_font , TTF_Font* new_font); //Renderer has to render
        SDL_Rect Compute_Center(const SDL_Rect& rect , int offsetX , int offsetY);
        SDL_Window* win = nullptr;

        //Textures A.K.A things we actually draw on
        //Welcome Screen
        Drawable StartBtn;
        Drawable WelcomeText;

        //GamePlayLoop

        Drawable QuestionText;
        Drawable QuestionText_No;
        Drawable AnswerText;
        Drawable AnswerText_No;
        Drawable AnswerBtn;
        Drawable Question_btn;

        //End Screen
        Drawable End_Text;
        
        SDL_Color r_color;
        SDL_Renderer* hope = nullptr;
        SDL_Rect background_rect;
        ~My_Renderer();

    private:
        Error_Handler& err;
        int Screen_Width = 890;
        int Screen_Height = 600;
        TTF_Font* Font_Small;
        TTF_Font* Font_Large;
        TTF_Font* Font_Title;
        SDL_Color fColor;
        SDL_Rect fontRect;
        SDL_Surface* srf = nullptr; //There is only one surface becouse we only use it temporarily before renderer turns it into a texture
};

class Gameplay_Loop{
    public:
        explicit Gameplay_Loop(Error_Handler& err , My_Renderer& render);
        void Welcome();
        void Main_Loop();
        void GetQuestion();
        void GetAnswer();
        bool NextQuestion();
        int Question;
        enum class State{
            Welcome,
            Question,
            Answer,
            End
        };

        State game_state;
    private:
        
        Error_Handler& err;
        My_Renderer& render;
        
};

class Basic{ 
    public:
        Basic();
        Error_Handler err;
        My_Renderer render;
        Gameplay_Loop game;
        bool Running;
        void Run();

    private:
        bool General_Init();
        bool PointInRect(int x , int y, const SDL_Rect& rect); //the missle knows where it is becouse it knows where it isnt
        void Update();
        void Render();
        void Handle_Events();
        
};
