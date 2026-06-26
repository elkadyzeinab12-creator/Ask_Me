//
// Created by GTX TOP on 6/24/2026.
//

#ifndef ASK_ME_USER_H
#define ASK_ME_USER_H

#include "question.h"
#include <string>

class user {
    private:
    std::string username , name ,
    password, mail;
    int id;
    bool anonymous;

    public:
    user();
    user(int id , std::string username , std::string name , std::string mail , std::string password , bool anonymous );

    std::string get_password();
    void set_password(std::string password);

    std::string get_username();
    void set_username(std::string username);

    std::string get_name();
    void set_name(std::string name);

    std::string get_mail();
    void set_mail(std::string mail);

    int get_id();
    void set_id(int id);

    bool get_anonymous();
    void set_anonymous(bool anonymous);
    void ReadUser(const std::string &line);

};




#endif //ASK_ME_USER_H