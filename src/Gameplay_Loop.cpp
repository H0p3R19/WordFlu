#include "headers.h"


Gameplay_Loop::Gameplay_Loop(Error_Handler& err , My_Renderer& render)
    : err(err) , render(render)
{Question = 1;}

void Gameplay_Loop::Main_Loop(){
    switch (game_state)
    {
    case State::Welcome:
        render.Draw_Obj(render.WelcomeText.texture , render.WelcomeText.rect , false , 0 , -50);
        render.Draw_Obj(render.StartBtn.texture , render.StartBtn.rect , true , 0 , 20);
        break;
    
    case State::Question:
        render.Draw_Obj(render.QuestionText_No.texture , render.QuestionText_No.rect , false , 0 , -200);
        render.Draw_Obj(render.QuestionText.texture , render.QuestionText.rect , false , 0 , -50);
        render.Draw_Obj(render.AnswerBtn.texture , render.AnswerBtn.rect , true , 0 , 20);
        break;
    
    case State::Answer:
        render.Draw_Obj(render.AnswerText_No.texture , render.AnswerText_No.rect , false , 0 , -200);
        render.Draw_Obj(render.AnswerText.texture , render.AnswerText.rect ,false , 0 , -50);
        render.Draw_Obj(render.Question_btn.texture , render.Question_btn.rect ,true , 0 , 20);
        break;
    case State::End:
        render.Draw_Obj(render.End_Text.texture , render.End_Text.rect , false , 0 , -50);

    default:
        break;
    }

}

void Gameplay_Loop::GetQuestion(){
    switch (Question)
    {
    case 1:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "1)" , "Open the lights.");
        break;
    case 2:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "2)" , "Carbon Dioxide effects the atmosphere.");
        break;
    case 3:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "3)" , "This backery has delicious deserts.");
        break;
    case 4:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "4)" , "Rebecca lays down to take a nap.");
        break;
    case 5:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "5)" , "Jim looses his sunglasses often.");
        break;
    case 6:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "6)" , "I think your smart.");
        break;
    case 7:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "7)" , "To who did you give all of our money?");
        break;
    case 8:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "8)" , "You can trim your bushes in anyway you choose");
        break;
    case 9:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "9)" , "I just got an envelop from her.");
        break;
    case 10:
        render.Question_Creator(render.QuestionText, render.QuestionText_No , "10)" , "What could be more fun then going to school?");
        break;
    default: //means game ended!
        game_state = State::End;
        break;
    }

}

void Gameplay_Loop::GetAnswer(){
    switch (Question)
    {
    case 1:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "1)" , "*TURN ON* the lights.");
        break;
    case 2:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "2)" , "Carbon Dioxide *AFFECTS* the atmosphere.");
        break;
    case 3:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "3)" , "This backery has delicious *DESSERTS*.");
        break;
    case 4:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "4)" , "Rebecca *LIES* down to take a nap.");
        break;
    case 5:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "5)" , "Jim *LOSES* his sunglasses often.");
        break;
    case 6:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "6)" , "I think *YOU'RE* smart.");
        break;
    case 7:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "7)" , "To *WHOM* did you give all of our money?");
        break;
    case 8:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "8)" , "You can trim your bushes in *ANY WAY* you choose");
        break;
    case 9:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "9)" , "I just got an *ENVELOPE* from her.");
        break;
    case 10:
        render.Answer_Creator(render.AnswerText, render.AnswerText_No , "10)" , "What could be more fun *THAN* going to school?");
        break;
    default:
        break;
    }

}