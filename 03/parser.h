#include <functional>
#include <string>

class ParseException: public std::exception {

public:
    ParseException(const std::string& error_msg):
       msg {error_msg}
       {};

   const char * what () const noexcept {
      return msg.c_str();
   }

private:
   std::string msg;
};

using SimpleCallback = std::function<void()>;
template <typename T>
using TokenCallback = std::function<void(const T&)>;

class Parser {
public:
    void parse(const std::string&);
    void setOnStart(SimpleCallback callback) {onStart = callback;}
    void setOnFinish(SimpleCallback callback) {onFinish = callback;}
    void setOnNumber(TokenCallback<int> callback) {onNumber = callback;}
    void setOnString(TokenCallback<std::string> callback) {onString = callback;}

private:
    SimpleCallback onStart = nullptr;
    SimpleCallback onFinish = nullptr;
    TokenCallback<int> onNumber = nullptr;
    TokenCallback<std::string> onString = nullptr;
};
