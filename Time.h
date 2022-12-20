#include <iostream>
#include <chrono>
#include<string>
#include<fstream>
//файл взять из певрой лабы 
class Time {
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time, end_time;
    std::chrono::duration<double> value;
    std::ofstream results;
    //с помощью хроно иннициализиурем переменные старт и энд
public:
    Time() {};
    explicit Time(const std::string& file_name) {
        value = std::chrono::seconds(0);
        results.open(file_name);
        results << "Container;Data_type;Operation;Number of elements;Time_value\n";
    }
    ~Time() {
        results.close();
    }
    void start() {
        start_time = std::chrono::steady_clock::now();//старт выставляет время на текушее время системы 
    }

    void end() {
        end_time = std::chrono::steady_clock::now();//энд выставляет время второй переменной на текущее
    }

    void log(const std::string& container, const std::string& data_type, const std::string& operation, const int& elements) {//функция лог считает разницу во времени перемнных старт и энд
        results << container << ";" << data_type << ";" << operation <<
            ";" << elements << ";" << value.count() << "\n";
    }
    /*функция ресет не несет особого смысла потому что при вызове функции старт время выставляется автоматически */
    void reset() {
        start_time = std::chrono::steady_clock::now();
        end_time = std::chrono::steady_clock::now();

    }
    //currunt mesureпозваляет взять число для подсчета разницы над временем выполнений операций, поэтому ее тип дабл
    double current_mesure() {

        return std::chrono::duration<double>(end_time - start_time).count();
    }
};

