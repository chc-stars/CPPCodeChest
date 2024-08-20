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
        //����߳�
        //ֱ��������β���������Ԫ�أ�ʡȥ�˿������ƶ�Ԫ�صĹ��̡�
    }
}


template<typename T>
inline threadPool<T>::~threadPool()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;

    condition.notify_all();
    for (auto& ww : work_threads)
        ww.join();   // ����������������join
}


// �������
template<typename T>
bool threadPool<T>::append(T* request)
{
    // ������������ʱһ��Ҫ��������Ϊ���������̹߳���
    queue_mutex.lock(); // ͬһ�������
    tasks_queue.push(request);
    queue_mutex.unlock();
    condition.notify_one();   // �̳߳���ӽ�ȥ��������ȻҪ֪ͨ�ȴ����߳�
    return true;
}

// ���߳�
 

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

        /*��unique_lock() ����������Զ�������/
        this->condition.wait(lk, [this]
        {
          return !this->tasks_queue.empty();
        });//�������Ϊ�գ���wait����ͣ�����ȴ�����//��Ҫ�����񣬲��������̣߳���Ȼ������
        if (this->tasks_queue.empty())//����Ϊ�գ�˫�ر���
        {
            assert(0&&"����");//ʵ���ϲ������е���һ������Ϊ����Ϊ�գ�wait�������ˡ�
            continue;
        }else{
            T *request = tasks_queue.front();
            tasks_queue.pop();
            if (request)//�������ˣ���ʼִ��
                request->process();
              }
        }
         */

    }
}

int runThreadPool() {
    threadPool<Task> pool(6);//6���̣߳�vector
    std::string str;
    while (1)
    {
        Task* tt = new Task();//ʹ������ָ��
        pool.append(tt);//��ͣ��������������Ƕ���queue����Ϊֻ�й̶����߳���
        cout << "��ӵ�����������" << pool.tasks_queue.size() << endl;
        delete tt;
    }
}