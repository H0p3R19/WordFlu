//initilization
#include "headers.h"

My_Renderer::My_Renderer(Error_Handler& err)
    : err(err)
{}
bool My_Renderer::Init_win() {
    win = SDL_CreateWindow("WordFlu" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , Screen_Width , Screen_Height, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        err.Error("SDL_Window falied to initilize" , Error_Handler::Type::SDL , win);
        return false;
    }
    return true;
}

bool My_Renderer::Init_TTF(){
    if (TTF_Init() != 0)
    {
        err.Error("TTF failed to initilize" , Error_Handler::Type::TTF , win);
        return false;
    }
    return true;
}

bool My_Renderer::Init_renderer(){
    hope = SDL_CreateRenderer(win , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (hope == nullptr)
    {
        err.Error("Renderer failed to initilize" , Error_Handler::Type::SDL , win);
        return false;
    }
    return true;
}

SDL_Texture* My_Renderer::Render_Obj( SDL_Texture* texture , const std::string& text , SDL_Rect& rect , TTF_Font*& old_font , TTF_Font* new_font){

    
    if (hope == nullptr)
    {
        err.Error("Renderer is null!" , Error_Handler::Type::SDL , win);
        return nullptr;
    }
    
    srf = TTF_RenderUTF8_Blended(new_font, text.c_str() , fColor );
    if (srf == nullptr)
    {
        err.Error("TTF failed to draw to surface" , Error_Handler::Type::TTF , win);
        return nullptr;
    }

    if (old_font != new_font)
    {
        old_font = new_font;
    }
    
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(hope , srf); //make the actual texture
    SDL_FreeSurface(srf);
    if (new_texture == nullptr)
    {
        err.Error("texture failed to render" , Error_Handler::Type::SDL , win);
        
        return nullptr; 
    }
    SDL_QueryTexture(new_texture , nullptr ,nullptr , &rect.w, &rect.h);

    if (texture != nullptr)
    {SDL_DestroyTexture(texture);}
    
    return new_texture;
}

SDL_Rect My_Renderer::Compute_Center(const SDL_Rect& rect , int offsetX, int offsetY){

    SDL_Rect result = rect;
    result.x = (Screen_Width - rect.w)/2 + offsetX;
    result.y = (Screen_Height - rect.h)/2 + offsetY;
    return result;
}

void My_Renderer::Draw_Obj(SDL_Texture* texture, SDL_Rect& rect, bool is_button , int offsetX ,int offsetY)
{
    int textW, textH;
    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);

    int padding = is_button ? 8 : 0;

    
    rect.w = textW + padding * 2;
    rect.h = textH + padding * 2;


    rect = Compute_Center(rect, offsetX, offsetY);

    SDL_SetRenderDrawColor(hope, 0, 0, 0, 255);
    SDL_RenderFillRect(hope, &rect);


    SDL_Rect text_rect;
    text_rect.w = textW;
    text_rect.h = textH;

    text_rect.x = rect.x + (rect.w - textW) / 2;
    text_rect.y = rect.y + (rect.h - textH) / 2;

    SDL_RenderCopy(hope, texture, nullptr, &text_rect);
}



void My_Renderer::Question_Creator(Drawable& obj , Drawable& obj_no , std::string question_no , const std::string& text){
    obj_no.texture = Render_Obj(obj_no.texture , question_no , obj_no.rect , obj_no.font , obj_no.font );
    obj_no.rect = Compute_Center({0,0,100,50}, 0, -200);
    obj.texture = Render_Obj(obj.texture , text , obj.rect , obj.font , obj.font );
    obj.rect = Compute_Center({0,0,100,50}, 0, -50);
    AnswerBtn.rect = Compute_Center({0,0, 50,25} , 0 , 100); 
}

void My_Renderer::Answer_Creator(Drawable& obj , Drawable& obj_no , std::string question_no , const std::string& text) {
    obj_no.texture = Render_Obj(obj_no.texture , question_no , obj_no.rect , obj_no.font , obj_no.font );
    obj_no.rect = Compute_Center({0,0,100,50}, 0, -200);
    obj.texture = Render_Obj(obj.texture , text , obj.rect , obj.font , obj.font );
    obj.rect = Compute_Center({0,0,100,50}, 0, -50);
    Question_btn.rect = Compute_Center({0,0, 50,25} , 0 , 100); 
}


bool My_Renderer::Init_media(){

    Font_Small = TTF_OpenFont("../assets/amiga4ever.ttf" , 20);
    Font_Large = TTF_OpenFont("../assets/amiga4ever.ttf" , 45);
    Font_Title = TTF_OpenFont("../assets/amiga4ever.ttf" , 50);
    if (Font_Small == nullptr || Font_Large == nullptr)
    {
        err.Error("Failed to open font", Error_Handler::Type::TTF , win);
        return false;
    }

    //I am aware of how this mixes two naming schemes , but idc

    //color of the font
    fColor.r = 255;
    fColor.g = 255;
    fColor.b = 255;
    fColor.a = 255;

    //color of the font rect
    r_color.r = 225;
    r_color.g = 225;
    r_color.b = 225;
    r_color.a = 255;

    

    background_rect = {0 , 0 , Screen_Width , Screen_Height};

    //Get all the fixed textures ready
    //Rects dont move , so ill just position them here,

    //StartBtn
    StartBtn.texture = Render_Obj(nullptr, "Start!" , StartBtn.rect , StartBtn.font , Font_Small);
    StartBtn.rect = Compute_Center({0,0,50,25} , 0, 30);
    if (StartBtn.texture == nullptr) return false;

    //WelcomeText
    WelcomeText.texture = Render_Obj(nullptr, "-WORD FLU-" , WelcomeText.rect , WelcomeText.font , Font_Title);
    WelcomeText.rect = Compute_Center({0,0,100,50}, 0, -70);
    if (WelcomeText.texture == nullptr) return false;

    //QuestionText
    QuestionText.texture = Render_Obj(nullptr, "Default" , QuestionText.rect , QuestionText.font , Font_Small);
    QuestionText.rect = Compute_Center({0,0,100,50}, 0, -150);
    if (QuestionText.texture == nullptr) return false;
    
    //QuestionText_No
    QuestionText_No.texture = Render_Obj(nullptr, "Default" , QuestionText_No.rect , QuestionText_No.font , Font_Large);
    QuestionText_No.rect = Compute_Center({0,0,50,25}, 0, -100);
    if (QuestionText_No.texture == nullptr) return false;

    //Answerbtn
    AnswerBtn.texture = Render_Obj(nullptr, "See Answer" , AnswerBtn.rect , AnswerBtn.font , Font_Small);
    AnswerBtn.rect = Compute_Center({0,0,200,50}, 0, -70);
    if (AnswerBtn.texture == nullptr) return false;

    //Questionbtn
    Question_btn.texture = Render_Obj(nullptr, "Next Question" , Question_btn.rect , Question_btn.font , Font_Small);
    Question_btn.rect = Compute_Center({0,0,200,50}, 0, -70);
    if (Question_btn.texture == nullptr) return false;


    //AnswerText_No
    AnswerText_No.texture = Render_Obj(nullptr, "Default" , AnswerText_No.rect , AnswerText_No.font , Font_Large);
    AnswerText_No.rect = Compute_Center({0,0,100,50}, 0, -70);
    if (AnswerText_No.texture == nullptr) return false;

    //AnswerText
    AnswerText.texture = Render_Obj(nullptr, "Default" , AnswerText.rect , AnswerText.font , Font_Small);
    AnswerText.rect = Compute_Center({0,0,100,50}, 0, -70);
    if (AnswerText.texture == nullptr) return false;

    //End_Text
    End_Text.texture = Render_Obj(nullptr, "Thanks for playing!" , AnswerBtn.rect , AnswerBtn.font , Font_Small);
    End_Text.rect = Compute_Center({0,0,100,50}, 0, -70);
    if (End_Text.texture == nullptr) return false;


    if (End_Text.texture == nullptr) return false;

    return true;
}





My_Renderer::~My_Renderer(){ 
    SDL_DestroyRenderer(hope);
    SDL_DestroyTexture(StartBtn.texture); //Here comes the hedious part...
    SDL_DestroyTexture(WelcomeText.texture);
    SDL_DestroyTexture(QuestionText.texture);
    SDL_DestroyTexture(AnswerBtn.texture);
    SDL_DestroyTexture(Question_btn.texture);
    SDL_DestroyTexture(AnswerText.texture);
    SDL_DestroyTexture(End_Text.texture); //Its finnaly over- now that i think about it was really not that bad.
    hope == nullptr;
    StartBtn.texture == nullptr;
    WelcomeText.texture == nullptr;
    QuestionText.texture == nullptr;
    AnswerBtn.texture == nullptr;
    AnswerText.texture == nullptr;
    Question_btn.texture == nullptr;
    End_Text.texture == nullptr;
}
