#include <iostream>
#include <string>
#include <optional>
#include <memory>
#include <unordered_map>

struct Student {
    uint64_t id;
    std::string name;
    uint16_t age;
};

class StudentDataBase {
public:
    using StudentPtr = std::shared_ptr<Student>;
private:
    std::unordered_map<uint64_t, StudentPtr> storage_;
public:
    void Add(const Student& student)
    {
        storage_.insert(
                std::pair<uint64_t, StudentPtr>(
                        student.id,
                        std::make_shared<Student>(student)
                        )
                );
    }

    std::optional<StudentPtr> Get(uint64_t id)
    {
        auto it = storage_.find(id);

        if (it == storage_.end()) return std::nullopt;

        return { it->second };
    }

    void Remove(uint64_t id)
    {
        auto it = storage_.find(id);

        if (it != storage_.end()) storage_.erase(it);
    }
};

void PrintStudent(const std::shared_ptr<Student>& student)
{
    std::cout << "ID: " << student->id << std::endl;
    std::cout << "Name: " << student->name << std::endl;
    std::cout << "Age: " << student->age << std::endl;

    std::cout << std::endl;
}

int main()
{
    StudentDataBase db;

    db.Add(Student {
       1,
       "Vasya",
       23
    });

    db.Add(Student {
        123,
        "Oleg",
        25
    });

    PrintStudent(db.Get(123).value());

    db.Remove(123);

    PrintStudent(db.Get(1).value());
}