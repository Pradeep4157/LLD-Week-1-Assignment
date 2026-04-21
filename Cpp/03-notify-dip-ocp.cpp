// 03-notify-dip-ocp.cpp
#include <bits/stdc++.h>
using namespace std;

/*

    OBSERVATIONS :

        SMTPMailer looks good, it is just sending the mails,

        twilioclient is also just sending otps..




*/

class IEmailService
{
public:
    virtual void send(const string &templ, const string &to, const string &body) = 0;
    virtual ~IEmailService() = default;
};
class ISmsService
{
public:
    virtual void sendOTP(const string &phone, const string &code) = 0;
    virtual ~ISmsService() = default;
};
class SmtpMailer : public IEmailService
{
public:
    void send(const string &templ, const string &to, const string &body) override
    {
        cout << "[SMTP] template=" << templ << " to=" << to << " body=" << body << "\n";
    }
};
class TwilioClient : public ISmsService
{
public:
    void sendOTP(const string &phone, const string &code) override
    {
        cout << "[Twilio] OTP " << code << " -> " << phone << "\n";
    }
};

struct User
{
    string email;
    string phone;
};
void handleWelcomeMessage(const string &email, IEmailService &mailer)
{
    mailer.send("welcome", email, "Welcome!");
}
string generateOTP()
{
    int otp = rand() % 900000 + 100000;

    return to_string(otp);
}
void handleSendOTP(const string &phone, ISmsService &sms)
{
    const string otp = generateOTP();
    sms.sendOTP(phone, otp);
}
class INotificationHandler
{
public:
    virtual void handle(const User &user) = 0;
};
class WelcomeEmailHandler : public INotificationHandler
{
    IEmailService &mailer;

public:
    WelcomeEmailHandler(IEmailService &mailer_) : mailer(mailer_) {};
    void handle(const User &user) override
    {
        handleWelcomeMessage(user.email, mailer);
    }
};
class OtpHandler : public INotificationHandler
{
    ISmsService &sms;

public:
    OtpHandler(ISmsService &sms_) : sms(sms_) {};
    void handle(const User &user) override
    {

        handleSendOTP(user.phone, sms);
    }
};
class SignUpService
{
    vector<unique_ptr<INotificationHandler>> handlers;

public:
    SignUpService(vector<unique_ptr<INotificationHandler>> handlers_) : handlers(move(handlers_)) {};
    bool signUp(const User &u)
    {
        if (u.email.empty())
            return false;
        for (auto &a : handlers)
        {
            a->handle(u);
        }
        return true;
    }
};

int main()
{

    vector<unique_ptr<INotificationHandler>> handlers;
    SmtpMailer mailer;
    TwilioClient sms;
    handlers.push_back(make_unique<WelcomeEmailHandler>(mailer));
    handlers.push_back(make_unique<OtpHandler>(sms));
    SignUpService svc(move(handlers));
    svc.signUp({"user@example.com", "+15550001111"});
    return 0;
}
