#include <iostream>
#include<thread>
#include <synchapi.h>
#include <cassert>
#include <atomic>
#include <mutex>

using namespace std;
//int sum=0;
//std::atomic_flag lock = ATOMIC_FLAG_INIT;
//
//void fn1() {
//	for (int i = 0; i < 50000000; ++i) {
//		while (lock.test_and_set(std::memory_order_acquire))
//			;  // 自旋等待锁释放
//		// 进入临界区
//		sum++;
//		// 离开临界区
//		lock.clear(std::memory_order_release);
//	}
//}
//
//void fn2() {
//	for (int i = 0; i < 50000000; ++i) {
//		while (lock.test_and_set(std::memory_order_acquire))
//			;  // 自旋等待锁释放
//		// 进入临界区
//		sum++;
//		// 离开临界区
//		lock.clear(std::memory_order_release);
//	}
//}
//int main(){
//	auto begin=clock();
//	thread t1(fn1);
//	thread t2(fn2);
//	//Sleep(1);
//	cout<<sum<<endl;
//	t1.join();
//	cout<<sum<<endl;
//	t2.join();
//	cout<<sum<<endl;
//	cout<<clock()-begin<<endl;
//	return 0;
//}
int sum = 0;
std::mutex mtx;

void fn1() {
	for (int i = 0; i < 100000000; ++i) {
		std::lock_guard<std::mutex> lock(mtx); // 获取互斥锁
		// 进入临界区
		sum++;
		// 离开临界区，互斥锁会在lock_guard析构时自动释放
	}
}

void fn2() {
	for (int i = 0; i < 100000000; ++i) {
		std::lock_guard<std::mutex> lock(mtx); // 获取互斥锁
		// 进入临界区
		sum++;
		// 离开临界区，互斥锁会在lock_guard析构时自动释放
	}
}

//int main(){
//	auto begin=clock();
//	thread t1(fn1);
//	thread t2(fn2);
//	//Sleep(1);
//	cout<<sum<<endl;
//	t1.join();
//	cout<<sum<<endl;
//	t2.join();
//	cout<<sum<<endl;
//	cout<<clock()-begin<<endl;
//	return 0;
//}



atomic_int count=0;
atomic_flag flag=ATOMIC_FLAG_INIT;
void pright(int n){
	while(1){
		while(count<=0||flag.test_and_set(std::memory_order_acquire))
			;
		count--;
		printf(")");
		flag.clear(std::memory_order_release);
	}
}

void pleft(int arg) {
	while(1){
		while(count>=arg||flag.test_and_set(std::memory_order_acquire))
			;
		count++;
		printf("(");
		flag.clear(std::memory_order_release);
	}
}

int main() {
	int value = 0;
	cin>>value;
	std::thread t(pleft, value); // 创建线程并传递参数
	std::thread t2(pright,value);
	t.join(); // 等待线程结束
	t2.join();
	
	return 0;
}
