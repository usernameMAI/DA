#include <iostream>
#include <sstream>

class TelephoneNumber {
public:
    friend std::istream &operator>>(std::istream &in, TelephoneNumber &telephone_number){
        //    пропускаем '+'
        in.ignore(1);
        std::string line;
        std::getline(in, line, '-');
        for (int i = 0; i < line.size(); ++i) {
            telephone_number.country_code[i] = line[i];
        }
        telephone_number.country_code[line.size()] = '\0';
        std::getline(in, line, '-');
        for (int i = 0; i < line.size(); ++i) {
            telephone_number.city_code[i] = line[i];
        }
        telephone_number.city_code[line.size()] = '\0';
        std::getline(in, line, '\t');
        for (int i = 0; i < line.size(); ++i) {
            telephone_number.phone[i] = line[i];
        }
        telephone_number.phone[line.size()] = '\0';
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const TelephoneNumber &telephone_number){
        out << '+' << telephone_number.country_code << '-' << telephone_number.city_code << '-' << telephone_number.phone;
        return out;
    }

    std::string GetCountryCode() const{
        return country_code;
    }

    std::string GetCityCode() const{
        return city_code;
    }

    std::string GetPhone() const{
        return phone;
    }

private:
// +<country code>-<city code>-phone
    char country_code[4];
    char city_code[4];
    char phone[8];
};

class Object {
public:

    Object(){
        for (char &i: value) {
            i = '\0';
        }
    }

    Object(const std::string& initial_string){
        std::stringstream telephone_and_data_stream(initial_string);
        std::string telephone;
        std::string data;
        telephone_and_data_stream >> key;
        std::getline(telephone_and_data_stream, data);
        if (not data.empty()) {
            for (int i = 0; i < data.size() - 1; ++i) {
                value[i] = data[i];
            }
            if (data[data.size() - 1] == '\r') {
                value[data.size() - 1] = '\0';
            } else {
                value[data.size() - 1] = data[data.size() - 1];
            }
        }
        for (size_t i = data.size(); i < 65; ++i) {
            value[i] = '\0';
        }
    }

    TelephoneNumber GetKey() const{
        return key;
    }

    friend std::ostream &operator<<(std::ostream &out, const Object &object){
        out << object.key << "\t" << object.value;
        return out;
    }

    ~Object(){}

private:
    char value[65];
    TelephoneNumber key;
};

template<class T>
class MyVector {
public:
    MyVector();

    MyVector(int initial_size);

    ~MyVector();

    void PushBack(T element);

    void Print();

    T &operator[](const size_t idx);

    const T &operator[](const size_t idx) const;

    int size();

private:
    int capacity;
    int current_size;
    T *data;
};

template<class T>
MyVector<T>::MyVector() {
    current_size = 0;
    capacity = 2;
    data = new T[capacity];
}

template<class T>
MyVector<T>::MyVector(int initial_size) {
    current_size = initial_size;
    capacity = initial_size;
    data = new T[capacity];
}

template<class T>
void MyVector<T>::Print() {
    for (int i = 0; i < current_size; ++i) {
        std::cout << data[i] << '\n';
    }
}

template<class T>
void MyVector<T>::PushBack(T element) {
    if (capacity == current_size) {
        capacity *= 2;
        T *new_vector = new T[capacity];
        for (size_t i = 0; i < current_size; ++i) {
            new_vector[i] = data[i];
        }
        delete[] data;
        data = new_vector;
    }
    data[current_size++] = element;
}

template<class T>
MyVector<T>::~MyVector() {
    delete[] data;
}

template<class T>
int MyVector<T>::size() {
    return current_size;
}

template<class T>
T& MyVector<T>::operator[](const size_t idx) {
    return data[idx];
}

template<class T>
const T& MyVector<T>::operator[](const size_t idx) const {
    return data[idx];
}

class RadixSort {
public:
    void Sort(MyVector<Object> &vector) {
        size_t max_phone_size = 7;
        size_t max_city_code_size = 3;
        size_t max_country_code_size = 3;
        MyVector<Object> sorted_array(vector.size());
//        Сортируем по phone, city_code, country_code
        for (int i = max_phone_size - 1; i >= 0; --i) {
            CountSort(vector, max_phone_size, i, SORT_PHONE, sorted_array);
        }
        for (int i = max_city_code_size - 1; i >= 0; --i) {
            CountSort(vector, max_city_code_size, i, SORT_CITY_NUMBER, sorted_array);
        }
        for (int i = max_country_code_size - 1; i >= 0; --i) {
            CountSort(vector, max_country_code_size, i, SORT_COUNTRY_NUMBER, sorted_array);
        }
    }

private:
    const int SORT_PHONE = 1;
    const int SORT_CITY_NUMBER = 2;
    const int SORT_COUNTRY_NUMBER = 3;

    int FindIdx(MyVector<Object> &vector, int max_size, int i, int r, int flag) {
        int idx = 0;
        int pos = 0;
        int distance = int(max_size) - r - 1;
        int current_phone_size = 7;
        int current_city_code_size = 3;
        int current_country_size = vector[i].GetKey().GetCountryCode().size();
        if (flag == SORT_PHONE) {
            if (distance < current_phone_size) {
                pos = current_phone_size - distance - 1;
                idx = vector[i].GetKey().GetPhone()[pos] - '0';
            }
        } else if (flag == SORT_CITY_NUMBER) {
            if (distance < current_city_code_size) {
                pos = current_city_code_size - distance - 1;
                idx = vector[i].GetKey().GetCityCode()[pos] - '0';
            }
        } else if (flag == SORT_COUNTRY_NUMBER) {
            if (distance < current_country_size) {
                pos = current_country_size - distance - 1;
                idx = vector[i].GetKey().GetCountryCode()[pos] - '0';
            }
        }
        return idx;
    }


    void CountSort(MyVector<Object> &vector, size_t max_size, int r, int flag, MyVector<Object> &sorted_array) {
        //        Так как числа от 0 до 9, то создаём массив из 10 элементов
        int numbers[10] = {0};
        int idx;
        for (int i = 0; i < vector.size(); ++i) {
            idx = FindIdx(vector, max_size, i, r, flag);
            numbers[idx] += 1;
        }
        for (int i = 1; i < 10; ++i) {
            numbers[i] = numbers[i - 1] + numbers[i];
        }
        for (int i = vector.size() - 1; i >= 0; --i) {
            idx = FindIdx(vector, max_size, i, r, flag);
            sorted_array[--numbers[idx]] = vector[i];
        }
        for (int i = 0; i < vector.size(); ++i)
            vector[i] = sorted_array[i];
    }

};

int main() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    MyVector<Object> vector;
    std::string input_string;
    while (std::getline(std::cin, input_string)) {
        if (input_string != "\r" and input_string != "\n" and input_string != "\0") {
            vector.PushBack(input_string);
        }
    }
    RadixSort sort;
    sort.Sort(vector);
    vector.Print();
}