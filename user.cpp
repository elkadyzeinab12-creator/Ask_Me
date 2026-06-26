//
// Created by GTX TOP on 6/24/2026.
//

#include "user.h"
#include "question.h"
#include <bits/stdc++.h>
using namespace std;


user::user() {
    id = 0;
    anonymous = false;
}

user::user(int id , string username , string name , string mail , string password , bool anonymous ) {
    this->id = id;
    this->username = username;
    this ->name = name;
    this->mail = mail;
    this->password = password;
    this->anonymous = anonymous;
}

void user::set_username(string username) {
    this->username = username;
}
string user::get_username() {
    return this->username;
}

void user::set_name(string name) {
    this->name = name;
}
string user::get_name() {
    return this->name;
}

void user::set_password(std::string password) {
    this->password = password;
}
string user::get_password() {
    return this->password;
}

void user::set_id(int id) {
    this->id = id;
}
int user::get_id() {
    return this->id;
}

void user::set_mail(string mail) {
    this->mail = mail;
}
string user::get_mail() {
    return this->mail;
}

void user::set_anonymous(bool anonymous) {
    this->anonymous = anonymous;
}
bool user::get_anonymous() {
    return this->anonymous;
}
void user::ReadUser(const string &line) {
    stringstream ss(line);
    string id, aq;
    getline(ss, id, ',');
    this -> id = stoi(id);

    getline(ss, this->username, ',');
    getline(ss, this -> password, ',');
    getline(ss, this->name, ',');
    getline(ss, this->mail, ',');

    getline(ss, aq, ',');
    this->anonymous = stoi(aq) == 1;
}




