#include <iostream>
#include <chrono>
#include<string>
#include<fstream>
//���� ����� �� ������ ���� 
class Time {
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time, end_time;
    std::chrono::duration<double> value;
    std::ofstream results;
    //� ������� ����� ��������������� ���������� ����� � ���
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
        start_time = std::chrono::steady_clock::now();//����� ���������� ����� �� ������� ����� ������� 
    }

    void end() {
        end_time = std::chrono::steady_clock::now();//��� ���������� ����� ������ ���������� �� �������
    }

    void log(const std::string& container, const std::string& data_type, const std::string& operation, const int& elements) {//������� ��� ������� ������� �� ������� ��������� ����� � ���
        results << container << ";" << data_type << ";" << operation <<
            ";" << elements << ";" << value.count() << "\n";
    }
    /*������� ����� �� ����� ������� ������ ������ ��� ��� ������ ������� ����� ����� ������������ ������������� */
    void reset() {
        start_time = std::chrono::steady_clock::now();
        end_time = std::chrono::steady_clock::now();

    }
    //currunt mesure��������� ����� ����� ��� �������� ������� ��� �������� ���������� ��������, ������� �� ��� ����
    double current_mesure() {

        return std::chrono::duration<double>(end_time - start_time).count();
    }
};

