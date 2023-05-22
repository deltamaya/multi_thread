//#include <iostream>
//#include<thread>
//#include <synchapi.h>
//#include <cassert>
//#include <atomic>
//#include <mutex>
//
//using namespace std;
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
//int sum = 0;
//std::mutex mtx;
//
//void fn1() {
//	for (int i = 0; i < 100000000; ++i) {
//		std::lock_guard<std::mutex> lock(mtx); // 获取互斥锁
//		// 进入临界区
//		sum++;
//		// 离开临界区，互斥锁会在lock_guard析构时自动释放
//	}
//}
//
//void fn2() {
//	for (int i = 0; i < 100000000; ++i) {
//		std::lock_guard<std::mutex> lock(mtx); // 获取互斥锁
//		// 进入临界区
//		sum++;
//		// 离开临界区，互斥锁会在lock_guard析构时自动释放
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



//atomic_int count=0;
//atomic_flag flag=ATOMIC_FLAG_INIT;
//void pright(int n){
//	while(1){
//		while(count<=0||flag.test_and_set(std::memory_order_acquire))
//			;
//		count--;
//		printf(")");
//		flag.clear(std::memory_order_release);
//	}
//}
//
//void pleft(int arg) {
//	while(1){
//		while(count>=arg||flag.test_and_set(std::memory_order_acquire))
//			;
//		count++;
//		printf("(");
//		flag.clear(std::memory_order_release);
//	}
//}
//
//int main() {
//	int value = 0;
//	cin>>value;
//	std::thread t(pleft, value); // 创建线程并传递参数
//	std::thread t2(pright,value);
//	t.join(); // 等待线程结束
//	t2.join();
//
//	return 0;
//}

//#include <pthread.h>
//#include <stdio.h>
//#include <unistd.h>
//
//
//struct Test{
//	int num;
//	int age;
//};
//void fn1(Test ret){
//	for(int i=0;i<5;++i){
//		printf("i: %d\n",i);
//	}
//	printf("id: %llu\n",pthread_self());
//
//	ret.num=100;
//	ret.age=18;
//	pthread_exit(&ret);
//}
//
//int main(){
//	pthread_t t1;
//	void*ptr;
//	struct Test ret;
//	pthread_create(&t1, NULL, (void *(*)(void *))(fn1), (void *)(&ret));
//	for(int i=0;i<5;++i){
//		printf("main i: %d\n",i);
//	}
//	printf("main id: %llu\n",pthread_self());
//
//	pthread_join(t1,&ptr);
//	struct Test* p=(struct Test*)ptr;
//	printf("num: %d  age: %d\n",p->num,p->age);
//	return 0;
//}

#include <thread>
#include <iostream>
#include <atomic>
#include <vector>
#include <condition_variable>
#include <mutex>
using namespace std;
//atomic_int count=0;
//atomic_flag flag=ATOMIC_FLAG_INIT;
//void pright(int n){
//	while(1){
//		while(count<=0||flag.test_and_set(std::memory_order_acquire))
//			;
//		count--;
//		printf(")");
//		flag.clear(std::memory_order_release);
//	}
//}
//
//void pleft(int arg) {
//	while(1){
//		while(count>=arg||flag.test_and_set(std::memory_order_acquire))
//			;
//		count++;
//		printf("(");
//		flag.clear(std::memory_order_release);
//	}
//}
//int main(){
//
//	return 0;
//}





//dining philosopher

//+ - - - - - - - - - +
//|                   |
//f p f p f p f p f p |
//int fork[5]{};
//void eat(int i){
//	cout<<"philosopher "<<i<<" eating\n";
//}
//std::mutex mtx;
//void philosopher(int n){
//	while(1){
//		lock_guard<mutex>lock(mtx);
//		if(!fork[n]&&!fork[(n==4?0:n+1)]){
//			fork[n]=1;fork[(n==4?0:n+1)]=1;
//			eat(n);
//			fork[n]=0;fork[(n==4?0:n+1)]=0;
//		}
//	}
//}
//
//int main(){
//	thread t[5];
//	for(int i=0;i<5;++i){
//		t[i]=thread(philosopher,i);
//	}
//	t[0].join();
//	return 0;
//}


//std::vector<int> forks(5);
//std::vector<std::mutex> forkMutexes(5);
//std::vector<std::condition_variable> forkCVs(5);
//
//void eat(int i) {
//	printf("philosopher %d eating\n",i);
//}
//
//void philosopher(int n) {
//	while (true) {
//		std::unique_lock<std::mutex> lock(forkMutexes[n]);
//		if (!forks[n] && !forks[(n == 4 ? 0 : n + 1)]) {
//			forks[n] = 1;
//			forks[(n == 4 ? 0 : n + 1)] = 1;
//			lock.unlock();
//
//			eat(n);
//
//			lock.lock();
//			forks[n] = 0;
//			forks[(n == 4 ? 0 : n + 1)] = 0;
//			forkCVs[n].notify_one();
//			forkCVs[(n == 4 ? 0 : n + 1)].notify_one();
//
//		} else {
//			forkCVs[n].wait(lock);
//		}
//	}
//}
//
//int main() {
//	std::vector<std::thread> threads;
//	for (int i = 0; i < 5; ++i) {
//		threads.emplace_back(philosopher, i);
//	}
//
//	for (auto& thread : threads) {
//		thread.join();
//	}
//
//	return 0;
//}
//#include <pthread.h>
//pthread_mutex_t mtx;
//pthread_rwlock_t rwlock;
//#define MAX 50
//int sum=0;
//void* fn1(void*){
//	for(int i=0;i<MAX;++i){
//		pthread_rwlock_wrlock(&rwlock);
//		++sum;
//		pthread_rwlock_unlock(&rwlock);
//	}
//}
//void* fn2(void*){
//	for(int i=0;i<MAX;++i){
//		pthread_rwlock_wrlock(&rwlock);
//		++sum;
//		pthread_rwlock_unlock(&rwlock);
//	}
//}
//int main(){
//	pthread_rwlock_init(&rwlock,NULL);
//	pthread_t t1,t2;
//	pthread_create(&t1,NULL,fn1,NULL);
//	pthread_create(&t2,NULL,fn2,NULL);
//	pthread_join(t1,NULL);
//	pthread_join(t2,NULL);
//	pthread_rwlock_destroy(&rwlock);
//	cout<<sum<<endl;
//}


//pthread_cond_t cv;
//pthread_mutex_t mtx;
//int n;
//int cnt=0;
//void* pleft(void*){
//	while(1){
//		pthread_mutex_lock(&mtx);
//		while(cnt>=n){
//			pthread_cond_wait(&cv,&mtx);
////			释放互斥锁：线程在调用pthread_cond_wait时会将互斥锁的所有权释放，这样其他线程可以获取该互斥锁并访问受保护的共享资源。
////
////			进入等待状态：线程进入等待状态，并等待条件变量的信号。在等待期间，线程不会继续执行后续的代码。
////
////			接收信号并重新获取互斥锁：当另一个线程调用pthread_cond_signal或pthread_cond_broadcast来唤醒等待的线程时，该线程会被唤醒，并重新尝试获取互斥锁。
////
////			获取互斥锁并继续执行：当等待的线程成功获取互斥锁后，它会从pthread_cond_wait函数返回，并继续执行后续的代码。
//		}
//		++cnt;
//		printf("(",pthread_self());
//		pthread_mutex_unlock(&mtx);
//		pthread_cond_signal(&cv);
//
//	}
//}
//void* pright(void*){
//	while(1){
//		pthread_mutex_lock(&mtx);
//		while(cnt<=0){
//			pthread_cond_wait(&cv,&mtx);
//		}
//		--cnt;
//		printf(")",pthread_self());
//		pthread_mutex_unlock(&mtx);
//		pthread_cond_signal(&cv);
//
//
//	}
//}
//int main(){
//	scanf("%d",&n);
//	pthread_cond_init(&cv,NULL);
//	pthread_mutex_init(&mtx,NULL);
//	pthread_t t[4];
//	for(int i=0;i<8;++i){
//		if(i%2){
//			pthread_create(&t[i],NULL,pleft,NULL);
//		}else{
//			pthread_create(&t[i],NULL,pright,NULL);
//		}
//	}
//	for(int i=0;i<4;++i){
//		pthread_join(t[i],NULL);
//	}
//	pthread_mutex_destroy(&mtx);
//	pthread_cond_destroy(&cv);
//}


//#include <semaphore>
//using namespace std;
//vector<int> forks(5);
//vector<mutex> forkMutexes(5);
//counting_semaphore sem(4);
//void eat(int i) {
//	printf("philosopher %d eating\n",i);
//}
//
//void philosopher(int n) {
//	while (true) {
//		sem.acquire();
//		while(forks[n])
//			;
//		forkMutexes[n].lock();
//		forks[n]=1;
//		while(forks[(n+1==5?0:n+1)])
//			;
//		forkMutexes[(n+1==5?0:n+1)].lock();
//		forks[(n+1==5?0:n+1)]=1;
//		eat(n);
//		forks[n]=0;
//		forks[(n+1==5?0:n+1)]=0;
//		forkMutexes[n].unlock();
//		forkMutexes[(n+1==5?0:n+1)].unlock();
//		sem.release();
//	}
//}
//
//int main() {
//	vector<thread> threads;
//	for (int i = 0; i < 5; ++i) {
//		threads.emplace_back(philosopher, i);
//	}
//
//	for (auto& thread : threads) {
//		thread.join();
//	}
//
//	return 0;
//}






//using namespace std;
//vector<int> forks(5);
//vector<mutex> forkMutexes(5);
//vector<condition_variable>forkCVs(5);
//void eat(int i) {
//	printf("philosopher %d eating\n",i);
//}
//
//void philosopher(int n) {
//	while (true) {
//		unique_lock<mutex>lock(forkMutexes[n]);
//		while(forks[n]){
//			forkCVs[n].wait(lock);
//		}
//		forks[n]=1;
//		unique_lock<mutex>right(forkMutexes[(n+1==5?0:n+1)]);
//		while(forks[(n+1==5?0:n+1)]){
//			forkCVs[(n+1==5?0:n+1)].wait(right);
//		}
//		forks[(n+1==5?0:n+1)]=1;
//		eat(n);
//		forks[n]=0;
//		forkCVs[n].notify_one();
//		forks[(n+1==5?0:n+1)]=0;
//		forkCVs[(n+1==5?0:n+1)].notify_one();
//		lock.unlock();
//		right.unlock();
//	}
//}
//
//int main() {
//	vector<thread> threads;
//	for (int i = 0; i < 5; ++i) {
//		threads.emplace_back(philosopher, i);
//	}
//
//	for (auto& thread : threads) {
//		thread.join();
//	}
//
//	return 0;
//}

vector<int> forks(5);
mutex mtx;
condition_variable cv;

void eat(int i) {
	printf("philosopher %d eating\n", i);
}
//
void philosopher(int n) {
	while (true) {
		unique_lock<mutex> lock(mtx);
		if(!forks[n]&&!forks[(n+1)%5]){
			forks[n]=1;forks[(n+1)%5]=1;
			eat(n);
			forks[n]=0;forks[(n+1)%5]=0;
			lock.unlock();
			cv.notify_all();
		}else{
			cv.wait(lock);
		}
	}
}

int main() {
	vector<thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.emplace_back(philosopher, i);
	}
	
	for (auto& thread : threads) {
		thread.join();
	}
	
	return 0;
}
