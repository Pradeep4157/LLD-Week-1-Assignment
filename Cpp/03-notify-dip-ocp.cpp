// 03-notify-dip-ocp.cpp
#include <iostream>
#include <string>

using namespace std;

/*

    OBSERVATIONS :

        SMTPMailer looks good, it is just sending the mails,

        twilioclient is also just sending otps..




*/

class SmtpMailer
{
public:
    void send(const string &templ, const string &to, const string &body)
    {
        cout << "[SMTP] template=" << templ << " to=" << to << " body=" << body << "\n";
    }
};
class TwilioClient
{
public:
    void sendOTP(const string &phone, const string &code)
    {
        cout << "[Twilio] OTP " << code << " -> " << phone << "\n";
    }
};

struct User
{
    string email;
    string phone;
};
void handleWelcomeMessage(const string &email, SmtpMailer &mailer)
{
    mailer.send("welcome", email, "Welcome!");
}
string generateOTP()
{
    int otp = rand() % 900000 + 100000;

    return to_string(otp);
}
void handleSendOTP(const string &phone, TwilioClient &sms)
{
    const string otp = generateOTP();
    sms.sendOTP(phone, otp);
}
class SignUpService
{
public:
    bool signUp(const User &u)
    {
        if (u.email.empty())
            return false;
        // pretend DB save here…

        // hard-coded providers
        SmtpMailer mailer;
        handleWelcomeMessage(u.email, mailer);
        TwilioClient sms;
        handleSendOTP(u.phone, sms);
        return true;
    }
};

int main()
{
    SignUpService svc;
    svc.signUp({"user@example.com", "+15550001111"});
    return 0;
}
