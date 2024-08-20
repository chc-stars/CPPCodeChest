#include "threadPool.h"



template <typename T>
threadPool<T>::threadPool(int number) : stop(false)
{
    if (number <= 0 || number > MAX_THREADS)
        throw std::exception();
    for (int i = 0; i < number; i++)
    {
        std::cout << "created Thread num is : " << i << std::endl;
        work_threads.emplace_back(worker, this);
        //添加线程
        //直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
    }
}


template<typename T>
inline threadPool<T>::~threadPool()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;

    condition.notify_all();
    for (auto& ww : work_threads)
        ww.join();   // 可以在析构函数中join
}


// 添加任务
template<typename T>
bool threadPool<T>::append(T* request)
{
    // 操作工作队列时一定要加锁，因为他被所以线程共享
    queue_mutex.lock(); // 同一个类的锁
    tasks_queue.push(request);
    queue_mutex.unlock();
    condition.notify_one();   // 线程池添加进去了任务，自然要通知等待的线程
    return true;
}

// 单线程
 

template <typename T>
void threadPool<T>::worker(void* arg)
{
    threadPool<T>* pool_ = static_cast<threadPool<T>*>(arg);
    pool_->run();
}

template <typename T>
void threadPool<T>::run()
{
    while (!stop)
    {
        std::unique_lock<std::mutex> lk(this->queue_mutex);

        /*　unique_lock() 出作用域会自动解锁　/
        this->condition.wait(lk, [this]
        {
          return !this->tasks_queue.empty();
        });//如果任务为空，则wait，就停下来等待唤醒//需要有任务，才启动该线程，不然就休眠
        if (this->tasks_queue.empty())//任务为空，双重保障
        {
            assert(0&&"断了");//实际上不会运行到这一步，因为任务为空，wait就休眠了。
            continue;
        }else{
            T *request = tasks_queue.front();
            tasks_queue.pop();
            if (request)//来任务了，开始执行
                request->process();
              }
        }
         */

    }
}

int runThreadPool() {
    threadPool<Task> pool(6);//6个线程，vector
    std::string str;
    while (1)
    {
        Task* tt = new Task();//使用智能指针
        pool.append(tt);//不停的添加任务，任务是队列queue，因为只有固定的线程数
        cout << "添加的任务数量：" << pool.tasks_queue.size() << endl;
        delete tt;
    }
}