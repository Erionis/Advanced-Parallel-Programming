#include <iostream>


// definisco comparatore less
template<typename T> 
struct less
{
    bool operator()(const T& a, const T& b) const
    {
        return a<b;
    }
};

// definisco classe Studente
class Student
{
    unsigned int _id;

    public:
    // costruttori
    Student(): _id{0} {}
    Student(unsigned int id): _id{id} {}
    //metodo
    inline const unsigned int id() const
    {
        return _id;
    }

};

// specializzazione per trattare la classe STUDENTE
template<>
bool less<Student>::operator()(const Student& a, const Student& b) const
{
    return a.id()< b.id();
}

#include "sorting.hpp"

int main()
{
    int A[] = {10, 2, -5, 3, -1, 0};
    size_t length{6};

    quicksort<int, less<int>>(A, length);

    for (size_t i = 0; i < length; i++)
    {
        if (i!=0) std::cout << ",";

        std::cout << A[i];
        
    }
    std::cout << std::endl;

    Student B[4]; // array di Studenti
    B[0] = Student(30);  // popolo l'array
    B[1] = Student(1);
    B[2] = Student(5);
    B[3] = Student(3);

    // lanciamo quicksort nel caso di array di tipo Studente con comparatore less<Student>
    quicksort<Student, less<Student>>(B,4);

    // stampo gli id dei studenti ordinati
    for (size_t i = 0; i < 4; i++)
    {
        if (i!=0)
        {
            std::cout<< ",";
            std::cout<< B[i].id();
        }
        std::cout << std::endl;
    }
    


    return 0;
    
}