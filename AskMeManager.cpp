//
// Created by GTX TOP on 6/24/2026.
//
#include "AskMeManager.h"
#include <bits/stdc++.h>
#include "storage.h"
#include "user.h"
#include "question.h"
#include "utils.h"
#include "colors.h"
using namespace std;

//__________________________________Constructor____________________________________________
AskMeManager::AskMeManager() {
    current_user = nullptr;
}

//__________________________________________Run The Whole System____________________________________
void AskMeManager::Run() {
    LoadData();
    while (true) {
        ShowMainMenu();
        int choice = getIntInput("Enter your choice (1-3): ");

        if (choice == 3) {
            cout << GREEN "Goodbye!\n" << RESET;
            break;
        }

        switch (choice) {
            case 1:
                Login();
                break;
            case 2:
                SignUp();
                break;
            default:
                cout << red << "Wrong choice!\n" << RESET;
                continue;
        }

        while (current_user != nullptr) {
            ShowUserMenu();
            int sel = getIntInput("Enter Number in Range (1-8): ");

            switch (sel) {
                case 1: PrintQuestionsToMe();
                    break;
                case 2: PrintQuestionsFromMe();
                    break;
                case 3: Answer_question();
                    break;
                case 4: Delete_question();
                    break;
                case 5: Ask_question();
                    break;
                case 6: List_system_users();
                    break;
                case 7: Feed();
                    break;
                case 8:
                    current_user = nullptr;
                    cout << YELLOW << "Logged out successfully.\n" << RESET;
                    break;
                default:
                    cout << red << "Invalid selection - Please input number in range 1-8\n" << RESET;
            }
        }
    }
    SaveData();
}

//_______________________________________________Show Main Menu_____________________________________________________
void AskMeManager::ShowMainMenu() {
    cout << "1: Login\n2: sign up\n3: Exit\n\n";
}

//______________________________________________Show User Menu______________________________________________________
void AskMeManager::ShowUserMenu() {
    cout << "menu:\n"
            "        1: Print questions to me\n" //done
            "        2: Print questions from me\n" //done
            "        3: Answer question\n"
            "        4: Delete question\n"
            "        5: Ask question\n"
            "        6: List system users\n"
            "        7: Feed\n"
            "        8: Logout\n"; //done
}

//______________________________________________Login___________________________________________________________________
void AskMeManager::Login() {
    cout << "\n------------------------- Login -------------------------\n";
    string username = getStringInput("Enter username:"),
            password = getStringInput("Enter password: ");

    for (auto &u: users_list) {
        if (u.get_username() == username && u.get_password() == password) {
            current_user = &u;
            cout << GREEN"Welcome Back!\n" << RESET;
            return;
        }
    }
    cout << red << "Invalid username or password!\n" << RESET;
    current_user = nullptr;
}

//_____________________________________________Sign Up____________________________________
void AskMeManager::SignUp() {
    cout << "\n                    Sign Up \n";
    string name = getStringInput("Enter name : "),
            mail = getStringInput("Enter email: "),
            username = getUsername("Enter username (No spaces):"),
            password = getStringInput("Enter password: ");
    bool AQ = getAQ("Allow anonymous questions? (0 or 1): ");

    int generated_id = users_list[users_list.size() - 1].get_id() + 1;
    user new_user(generated_id, username, password, name, mail, AQ);

    users_list.push_back(new_user);
    cout << GREEN << "Account created successfully! Please login.\n" << RESET;
}

//__________________________________________READ DATA____________________________________
void AskMeManager::LoadData() {
    ifstream users_file("users.txt");
    if (users_file.is_open()) {
        string line;
        while (getline(users_file, line)) {
            if (line.empty()) continue;
            user newUser;
            newUser.ReadUser(line);
            users_list.push_back(newUser);
        }
        users_file.close();
    }

    ifstream questions_file("questions.txt");
    if (questions_file.is_open()) {
        string line;
        while (getline(questions_file, line)) {
            if (line.empty()) continue;
            question newQuestion;
            newQuestion.ReadQ(line);
            questions_list.push_back(newQuestion);
        }
        questions_file.close();
    }
}

//__________________________________________SAVE UPDATED DATA____________________________________
void AskMeManager::SaveData() {
    fstream saveQData;
    saveQData.open("questions.txt", ios::out); //write

    if (!saveQData)
        throw runtime_error("Could not open file for saving new data");

    for (auto &q: questions_list) {
        saveQData << q.GetQuestionId() << ',' << q.GetParentId() << ','
                << q.GetFromUserId() << ',' << q.GetToUserId() << ','
                << q.IsAnonymous() << ',' << q.GetQuestionText() << ','
                << q.GetAnswerText() << '\n';
    }
    saveQData.close();

    fstream saveUdata;
    saveUdata.open("users.txt", ios::out); //write

    if (!saveUdata)
        throw runtime_error("Could not open file for saving new data");

    for (auto &u: users_list) {
        saveUdata << u.get_id() << ',' << u.get_username() << ',' << u.get_password() << ','
                << u.get_name() << ',' << u.get_mail() << ',' << u.get_anonymous() << '\n';
    }
    saveUdata.close();
}

//__________________________________________Print Questions To Me____________________________________
void AskMeManager::PrintQuestionsToMe() {
    bool findQ = false;

    for (auto &q: questions_list) {
        if (q.GetToUserId() == current_user->get_id() && q.GetParentId() == -1) {
            findQ = true;
            cout << "Question Id (" << q.GetQuestionId() << ") ";
            if (q.IsAnonymous())
                cout << "from anonymous user\t";
            else
                cout << "from user Id (" << q.GetFromUserId() << ") \t";
            cout << "Question: " << q.GetQuestionText() << '\n';
            if (!q.GetAnswerText().empty())
                cout << "\t Answer: " << q.GetAnswerText() << '\n';
            else cout << YELLOW"\t Not Answered Yet!\n"<<RESET;
            cout << '\n';


            for (auto &sub_q: questions_list) {
                if (sub_q.GetParentId() == q.GetQuestionId()) {
                    cout << "\tThread: Question Id (" << sub_q.GetQuestionId() << ") ";
                    if (!sub_q.IsAnonymous()) {
                        cout << "from user id(" << sub_q.GetFromUserId() << ")\t";
                    }
                    cout << "Question: " << sub_q.GetQuestionText() << "\n";

                    if (!sub_q.GetAnswerText().empty()) {
                        cout << "\tThread:\t\tAnswer: " << sub_q.GetAnswerText() << "\n";
                    }
                    else cout << YELLOW"\t Not Answered Yet!\n"<<RESET;
                }
            }
            cout << "\n--------------------------------------------------\n";
        }
    }

    if (!findQ)
        cout << "No questions for you yet.\n";
}

//__________________________________________Print Questions From Me____________________________________
void AskMeManager::PrintQuestionsFromMe() {
    bool findQ = false;
    for (auto &q: questions_list) {
        if (q.GetFromUserId() == current_user->get_id()) {
            findQ = true;
            cout << "Question Id (" << q.GetQuestionId() << ") To User id (" << q.GetToUserId() << ")    ";
            if (!q.IsAnonymous()) {
                cout << "( Not Anonymous Question )";
            }
            cout << "\n \t Question: " << q.GetQuestionText() << "\n";

            if (q.GetAnswerText().empty())
                cout << "\t Not Answered Yet ";

            else cout << "\t Answer: " << q.GetAnswerText() << "\n";
        }
    }
    if (!findQ)
        cout << "You haven't send any question yet.\n";
}

//__________________________________________Answer Question____________________________________
void AskMeManager::Answer_question() {
    int press = 0;
    press = getIntInput("Enter Question id or press -1 to cancel :");
    while (press != -1) {
        bool findQ = false;
        for (auto &q: questions_list) {
            if (q.GetQuestionId() == press) {
                if (q.GetToUserId() != current_user->get_id()) {
                    cout << red << "Error: This question is not addressed to you! You cannot answer it.\n" << RESET;
                    return;
                }
                findQ = true;
                cout << "Question Id (" << q.GetQuestionId() << ") ";
                if (!q.IsAnonymous())
                    cout << "from user Id (" << q.GetFromUserId() << ")\t";
                cout << "\n \t Question: " << q.GetQuestionText() << "\n";
                if (!q.GetAnswerText().empty()) {
                    cout << "Warning : This Question is already answered. Answer will be Updated\n";
                }
                q.SetAnswerText(getStringInput("Enter Answer: "));
            }
        }
        if (!findQ)
            cout << "No question with this id.\n";
        if (findQ) {
            cout << GREEN"Answer is added successfully!\n\n" << RESET;
            break;
        }
    }
    SaveData();
}

//__________________________________________Delete question____________________________________
void AskMeManager::Delete_question() {
    int q_id = getIntInput("Enter Question id to delete, or -1 to cancel: ");
    if (q_id == -1) return;

    bool findQ = false;
    int parent_id_to_check = -1;

    for (auto it = questions_list.begin(); it != questions_list.end(); ++it) {
        if (it->GetQuestionId() == q_id) {
            if (it->GetToUserId() != current_user->get_id() && it->GetFromUserId() != current_user->get_id()) {
                cout << red << "Error: You don't have permission to delete this question!\n" << RESET;
                return;
            }
            findQ = true;
            parent_id_to_check = it->GetParentId();
            questions_list.erase(it);
            break;
        }
    }

    if (!findQ) {
        cout << red << "Question id not found.\n" << RESET;
        return;
    }

    if (parent_id_to_check == -1) {
        for (auto it = questions_list.begin(); it != questions_list.end();) {
            if (it->GetParentId() == q_id) {
                it = questions_list.erase(it); // مسح التابع
            } else {
                ++it;
            }
        }
    }

    cout << GREEN << "Question deleted successfully.\n" << RESET;
    SaveData();
}

//__________________________________________List system users____________________________________
void AskMeManager::List_system_users() {
    cout << GREEN "---------------------------SYSTEM USERS--------------------------------\n";
    for (auto &u: users_list) {
        cout << YELLOW"User Id: " << u.get_id() << BB"\t Name: " << u.get_name() << '\n';
    }
    cout << GREEN "-----------------------------------------------------------------------\n" << RESET;
}

//__________________________________________Ask Question____________________________________
void AskMeManager::Ask_question() {
    int press = getIntInput("Enter To User id or press -1 to cancel : ");
    if (press != -1) {
        bool findU = false;
        for (auto &u: users_list) {
            if (u.get_id()== press) {
                findU = true;
                if (!u.get_anonymous())
                    cout<<PURPLE"Note: Anonymous Questions Aren't Allowed For This User\n"<<RESET;
                int sel= getIntInput("For Thread Question Enter Question ID, Or Prees -1 For New Question: ");
                if (sel == -1) {
                    question new_Q;
                    new_Q.set_Q_id(questions_list.back().GetQuestionId()+1);
                    new_Q.set_from_user_id(current_user->get_id());
                    new_Q.set_P_id(-1);
                    new_Q.set_to_user_id(u.get_id());
                    new_Q.set_Anonymous(u.get_anonymous());
                    new_Q.set_Qtxt(getStringInput("Enter Question Text: "));
                    questions_list.push_back(new_Q);
                }
                else {
                    bool findQ= false;
                    for (auto &q : questions_list) {
                        if (q.GetQuestionId()==sel) {
                            findQ = true;
                            question new_Q;
                            new_Q.set_Q_id(questions_list.back().GetQuestionId()+1);
                            new_Q.set_from_user_id(current_user->get_id());
                            new_Q.set_P_id(sel);
                            new_Q.set_to_user_id(u.get_id());
                            new_Q.set_Anonymous(u.get_anonymous());
                            new_Q.set_Qtxt(getStringInput("Enter Question Text: "));
                            questions_list.push_back(new_Q);
                            break;
                        }
                    }
                    if (!findQ) {
                        cout << red << "Question id is not found.\n" << RESET;
                        return;
                    }
                }

            }
        }
        if (!findU) {
            cout << red << "Question id is not found.\n" << RESET;
            return;
        }
            cout<<GREEN<<"Question Added Successfully\n"<<
                "_____________________________________________________________________\n"<<RESET;
            SaveData();
    }
}

//__________________________________________List users Feed____________________________________
void AskMeManager::Feed() {
    cout<<cyan"_______________________________users feed__________________________________\n";
    for (auto &q: questions_list) {
        if (q.GetAnswerText().empty())
            continue;
        cout<<"Question Id: "<<q.GetQuestionId()<<"\n";
        if (q.IsAnonymous())
            cout << "from anonymous user\t";
        else
            cout << "from user Id (" << q.GetFromUserId() << ") \t";
        cout<<"To User ID ("<<q.GetToUserId()<<")\n";

        cout <<LIGHT_YELLOW "Question: " << q.GetQuestionText() << '\t';
        cout<<LIGHT_PURPLE"Answer: "<<q.GetAnswerText() << '\n';
    }
    cout<<RESET"__________________________________________________________________________\n";
}
