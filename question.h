//
// Created by GTX TOP on 6/24/2026.
//

#ifndef ASK_ME_QUESTION_H
#define ASK_ME_QUESTION_H
#include <string>


class question {
    private:
    int Q_id,
    from_user_id,
    to_user_id,
    PQid;
    bool isAnonymous;
    std::string Q_txt,
    AnsTxt;

    public:
    question();
    question(int q_id, int p_id, int from_id, int to_id, bool is_anon, std::string q_txt, std::string a_txt = "");

    int GetQuestionId() const;
    int GetParentId() const;
    int GetFromUserId() const;
    int GetToUserId() const;
    bool IsAnonymous() const;
    std::string GetQuestionText() const;
    std::string GetAnswerText() const;
    void SetAnswerText(const std::string& ans);

    void ReadQ(const std::string& line);
};


#endif //ASK_ME_QUESTION_H