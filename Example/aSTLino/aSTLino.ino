#include "include/string.hpp"
#include "include/stl.hpp"

#include "include/math/matrix4x4.hpp"
#include "include/event.hpp"

class serverEventArgs : public std::eventArgs {
public:
   serverEventArgs(std::string msg)  { m_msg = msg; }
   std::string getMessage() { return m_msg; }
private:
    std::string m_msg;   
};
class Server : public std::object
{
public:
    std::event<serverEventArgs> MessageSent;

    void SendMessage(serverEventArgs p_msg)
    {
        MessageSent(this, p_msg);
    }
};
class EventTest {
  public: 
    void run() {
        Server server;
        
        server.MessageSent += new std::delegate<EventTest, serverEventArgs>
                (this, &EventTest::Server_OnMessageSent);
        server.MessageSent += new std::delegate<EventTest, serverEventArgs>
                (this, &EventTest::Server_OnMessageSent);
        server.MessageSent += new std::delegate<EventTest, serverEventArgs>
                (this, &EventTest::Server_OnMessageSent);
        
        server.SendMessage(serverEventArgs(std::string("Hallo C++ EventSystem")));
    }
  protected:
    void Server_OnMessageSent(const std::object* sender, serverEventArgs msg) {
         Serial.print("Reach message from Server: ");
         Serial.println(msg.getMessage().c_str());
    }
};
////------------------------------
EventTest eventTest; 

void setup() {
  Serial.begin(9600);
  
  
}

void loop() {
  std::string var = std::string("Hello world");
  Serial.print(var.c_str()); Serial.print(" from aSTL v. "); Serial.println(std::asstlVersion().c_str() );
  mathtest();
  
  eventTest.run();

  while(true) {}
}
void xfull() {
  Serial.println("End of memory");
}
void mathtest() {
  
  vec2();


 // std::math::mat4f mat = std::math::matrix4x4_identity<float>();
 // Serial.println("mat4f "); Serial.println( mat.to_string().c_str() );  
}
void vec2() {
        std::math::vec2f a = std::math::vec2f(3,2.5);
        std::math::vec2f b = std::math::vec2f(1.6,2);
        std::math::vec2f c = a + b;
        Serial.print("(3,2.5) + (1.6,2) = "); Serial.println(c.to_string().c_str());
}
