#include <iostream>
#include "print_array.hpp"
/// @brief   Media degli elementi in un vettore
/// @tparam T 
/// @tparam OUTPUT 
/// @param A 
/// @param length 
/// @return 
template<typename T, typename OUTPUT= T> // imposto che come default il tipo di output è lo stesso di quello in input
OUTPUT compute_average(const T A[], const size_t& length)
{
    OUTPUT sum{0};

    for (size_t i = 0; i < length; i++)
    {
        sum += A[i];
    }
    return sum/length;
}
// metodo per trovare la varianza nel caso disponga della media!
template<typename T, typename AVG_T> 
AVG_T compute_variance(const T A[], const size_t& length, const AVG_T avarage)
{
    AVG_T sum{0};

    for (size_t i = 0; i < length; i++)
    {
        // calcoliamo lo scarto quadratico
        const AVG_T delta = A[i]-avarage;

        sum = delta*delta;
    }
    
    return sum/ length;
}
// metodo per trovare la varianza nel caso in cui non conosco la media
template<typename T, typename OUTPUT=T> // default di output è T
OUTPUT compute_variance(const T A[], const size_t& length)
{
    const auto avg = compute_average<T,OUTPUT>(A, length);
    return compute_variance(A, length, avg);
}

int main()
{
    int A[] = {3,2,10,8,6}; // avro com output un int
    //double A[] = {3,2,10,8,6}; // avro com output un double
    println(A, 5);

    std::cout<< "avg(A)= "
             << compute_average<int,double>(A, 5) // qui ho specificato i tipi che dovro esamniare
             << std::endl;
    // vediamo la varianza in entrambi i casi
    std::cout<< "var(A)= "
             << compute_variance(A, 5) 
             << std::endl;
    std::cout<< "var(A)= "
             << compute_variance(A, 5, compute_average<int,double>(A, 5)) 
             << std::endl;

    return 0;
}

// rivedere un pochino il codice perchè c'è un problema