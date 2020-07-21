#include <iostream>
using std::cout;
using std::endl;
#include <thread>
#include "PC.h"

const int no_to_consume{50};
const int no_to_produce{75};

PC q(200);

void consumer(int id){
    for(int i = 0; i < no_to_consume; ++i){
        int value = q.take();
        std::cout << "Consumer " << id << " fetched " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void producer(int id){
    for(int i = 0; i < no_to_produce; ++i){
        q.append(i);
        std::cout << "Producer " << id << " produced " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){

    std::thread c1(consumer, 0);
    std::thread c2(consumer, 1);
    std::thread c3(consumer, 2);
    std::thread p1(producer, 0);
    std::thread p2(producer, 1);

    c1.join();
    c2.join();
    c3.join();
    p1.join();
    p2.join();

    return 0;
}