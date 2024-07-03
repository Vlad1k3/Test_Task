#include <iostream>
#include <string>
#include <vector>

using namespace std;

// функция для поиска всех комбинаций операций + и - между цифрами строки numbers, чтобы результат равнялся 200.
// необходимо передавать используемые числа, начальный индекс, текущую операцию, текущее значение итерации и вектор для записи элементов 
void findCombinations(const string& numbers, int index, string current_expr, int current_value, vector<string>& results) {
    // если достигнут конец строки numbers, проверяем текущее значение.
    if (index == numbers.size()) {
        if (current_value == 200) {
            // если текущее значение равно 200, добавляем результат в вектор results.
            results.push_back(current_expr + "=" + to_string(current_value));
        }
        return; // завершаем рекурсию.
    }
    
    // проходимся по строке numbers, начиная с текущего индекса index
    for (int i = index; i < numbers.size(); ++i) {
        // выделяем подстроку от индекса index до i.
        string part = numbers.substr(index, i - index + 1);
        
        // проверяем, чтобы подстрока не была пустой и не превышала 10 символов
        if (!part.empty() && part.size() <= 10) {
            try {
                // преобразуем подстроку в целое число.
                int num = stoi(part);
                
                // если это первое число в выражении, начинаем новую ветвь рекурсии с ним
                if (index == 0) {
                    findCombinations(numbers, i + 1, part, num, results);
                } else {
                    // для последующих чисел добавляем в выражение операцию + и - и вызываем рекурсивно.
                    findCombinations(numbers, i + 1, current_expr + "+" + part, current_value + num, results);
                    findCombinations(numbers, i + 1, current_expr + "-" + part, current_value - num, results);
                }
            } catch (const std::out_of_range&) {
                // если подстрока выходит за пределы диапазона целых чисел, пропускаем её.
                continue;
            }
        }
    }
}

int main() {
   
    string numbers = "9876543210";
    vector<string> results;
    findCombinations(numbers, 0, "", 0, results);
    for (const string& result : results) {
        cout << result << endl;
    }

    return 0;
}
