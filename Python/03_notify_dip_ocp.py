# 03-notify-dip-ocp.py

class SmtpMailer:
    def send(self, template: str, to: str, body: str) -> None:
        print(f"[SMTP] template={template} to={to} body={body}")

class TwilioClient:
    def send_otp(self, phone: str, code: str) -> None:
        print(f"[Twilio] OTP {code} -> {phone}")

class User:
    def __init__(self, email: str, phone: str):
        self.email = email
        self.phone = phone

class SignUpService:
    def sign_up(self, user: User) -> bool:
        if not user.email:
            return False
        
        # pretend DB save here...

        # hard-coded providers
        mailer = SmtpMailer()
        mailer.send("welcome", user.email, "Welcome!")

        sms = TwilioClient()
        sms.send_otp(user.phone, "123456")
        
        return True

def main():
    svc = SignUpService()
    svc.sign_up(User("user@example.com", "+15550001111"))

if __name__ == "__main__":
    main()