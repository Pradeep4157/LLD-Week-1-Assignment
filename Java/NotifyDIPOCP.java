class SmtpMailer {
    void send(String templ, String to, String body) {
        System.out.println("[SMTP] template=" + templ + " to=" + to + " body=" + body);
    }
}
class TwilioClient {
    void sendOTP(String phone, String code) {
        System.out.println("[Twilio] OTP " + code + " -> " + phone);
    }
}
class User {
    String email;
    String phone;
    User(String email, String phone) { this.email = email; this.phone = phone; }
}

class SignUpService {
    boolean signUp(User u){
        if (u.email == null || u.email.isEmpty()) return false;
        // pretend DB save here…

        SmtpMailer mailer = new SmtpMailer();  // hard-coded
        mailer.send("welcome", u.email, "Welcome!");

        TwilioClient sms = new TwilioClient(); // hard-coded
        sms.sendOTP(u.phone, "123456");
        return true;
    }
}

public class NotifyDIPOCP {
    public static void main(String[] args) {
        SignUpService svc = new SignUpService();
        svc.signUp(new User("user@example.com", "+15550001111"));
    }
}
