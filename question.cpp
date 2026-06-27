//
// Created by GTX TOP on 6/24/2026.
//

#include "question.h"
#include <string>
#include <fstream>
#include <sstream>

question::question() {
    Q_id = -1;
    to_user_id = -1;
    from_user_id = -1;
}

question::question(int q_id, int p_id, int from_id, int to_id, bool is_anon, std::string q_txt, std::string a_txt) {
    this -> Q_id = q_id;
    this -> to_user_id = to_id;
    this -> from_user_id = from_id;
    this ->AnsTxt = a_txt;
    this -> isAnonymous = is_anon;
    this ->Q_txt = q_txt;
    this ->PQid = p_id;
};

void question::set_P_id(int p_id) {
    this -> Q_id = p_id;
}
void question::set_from_user_id(int from_user_id) {
    this -> from_user_id = from_user_id;
}
void question::set_to_user_id(int to_user_id) {
    this -> to_user_id = to_user_id;
}
void question::set_Anonymous(bool Anonymous) {
    this->isAnonymous = Anonymous;
}
void question::set_Qtxt(std::string qtxt) {
    this -> Q_txt = qtxt;
}
void question::set_Q_id(int q_id) {
    this -> Q_id = q_id;
}
void question :: SetAnswerText(const std::string& ans) {
    this->Q_txt = ans;
}

int question:: GetQuestionId() const {
    return this->Q_id;
}
int question::GetParentId() const {
    return this->PQid;
}
int question:: GetFromUserId() const {
    return this->from_user_id;
}
int question::GetToUserId() const {
    return this->to_user_id;
}
bool question:: IsAnonymous() const {
    return this->isAnonymous;
}
std::string question:: GetQuestionText() const {
    return this->Q_txt;
}
std::string question:: GetAnswerText() const {
    return this->AnsTxt;
}

void question::ReadQ(const std::string& line) {
    std::stringstream ss(line);
    std::string q_id_str, p_id_str, from_id_str, to_id_str, anon_str;

    std::getline(ss, q_id_str, ',');
    this->Q_id = std::stoi(q_id_str);

    std::getline(ss, p_id_str, ',');
    this->PQid = std::stoi(p_id_str);

    std::getline(ss, from_id_str, ',');
    this->from_user_id = std::stoi(from_id_str);

    std::getline(ss, to_id_str, ',');
    this->to_user_id = std::stoi(to_id_str);

    std::getline(ss, anon_str, ',');
    this->isAnonymous = std::stoi(anon_str);

    std::getline(ss, this->Q_txt, ',');
    std::getline(ss, this->AnsTxt, ',');
}
