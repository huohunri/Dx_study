#include <functional>
#include <stdio.h>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;

void printFirst1()
{
    printf("%d\n",1);
}
void printFirst2()
{
    printf("%d\n",2);
}
void printFirst3()
{
    printf("%d\n",3);
}
class Foo {
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        // 等待直至 main() 发送数据
	    std::unique_lock<std::mutex> lk(g_mutex);  
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
        counter++;
        cv1.notify_one();
    }

    void second(function<void()> printSecond) {
	    std::unique_lock<std::mutex> lk(g_mutex);
        cv1.wait(lk, [this](){return counter == 2;}); // 阻塞当前线程，直到条件变量被唤醒 
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        counter++;
        cv2.notify_one();
    }

    void third(function<void()> printThird) {
        
	    std::unique_lock<std::mutex> lk(g_mutex);
        cv2.wait(lk, [this](){return counter == 3;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
    
private:
    int counter = 1;
    std::condition_variable cv1;
    std::condition_variable cv2;
    // 使用lock和unlock手动加锁
    std::mutex g_mutex;
};

int main()
{
    Foo acc2();
 
    std::thread t2(&Foo::first,&acc2);
 

    t2.join();
    return 0;
}