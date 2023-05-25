#include <iostream>
#include <queue>
#include <thread>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>

std::queue<std::packaged_task<int()>> taskQueue;
std::mutex mtx;
std::condition_variable cv;

void producer()
{
    for (int i = 1; i <= 5; ++i) {
        // Создаем packaged_task с функцией расчета факториала
        std::packaged_task<int()> task([i]() {
            int result = 1;
            for (int j = 1; j <= i; ++j) {
                result *= j;
            }
            return result;
        });

        // Получаем future из packaged_task
        std::future<int> future = task.get_future();

        // Блокируем мьютекс перед добавлением задачи в очередь
        std::unique_lock<std::mutex> lock(mtx);

        // Добавляем задачу в очередь
        taskQueue.push(std::move(task));

        // Уведомляем поток-потребитель о наличии задачи
        cv.notify_one();

        // Разблокируем мьютекс
        lock.unlock();

        // Ожидаем завершения выполнения задачи
        int result = future.get();

        // Выводим результат в консоль
        std::cout << "Факториал " << i << " = " << result << std::endl;
    }
}

void consumer()
{
    while (true) {
        // Блокируем мьютекс перед доступом к очереди задач
        std::unique_lock<std::mutex> lock(mtx);

        // Ожидаем, пока в очереди появится задача
        cv.wait(lock, []() { return !taskQueue.empty(); });

        // Извлекаем задачу из очереди
        std::packaged_task<int()> task = std::move(taskQueue.front());
        taskQueue.pop();

        // Разблокируем мьютекс
        lock.unlock();

        // Выполняем задачу
        task();

        // Уведомляем поток-производитель о завершении выполнения задачи
        cv.notify_one();
    }
}

int main()
{
    // Создаем потоки-производитель и потребитель
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    // Ждем завершения работы потоков
    producerThread.join();
    consumerThread.join();

    return 0;
}
