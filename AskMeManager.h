//
// Created by GTX TOP on 6/24/2026.
//

#ifndef ASK_ME_ASKMEMANAGER_H
#define ASK_ME_ASKMEMANAGER_H

#include <vector>
#include "user.h"
#include "question.h"

class AskMeManager {
private:
    std::vector<user> users_list;
    std::vector<question> questions_list;
    user* current_user;

    void LoadData();//done
    void SaveData();//done

    void ShowMainMenu();//done
    void ShowUserMenu();//done
    void Login();//done
    void SignUp();//done
    void PrintQuestionsToMe();//done
    void Feed();

    void PrintQuestionsFromMe();//done
    void Answer_question();
    void Delete_question();
    void Ask_question();
    void List_system_users();

public:
    AskMeManager();
    void Run();//done
};


#endif //ASK_ME_ASKMEMANAGER_H