#include <iostream>
#include <chrono>
#include <string>

#include <vector>
#include <forward_list>
#include <list>
#include <deque>

#include <cstdlib>

template<typename CONTAINER>
struct executer {
    virtual void operator()(CONTAINER& c) const = 0;
};

template<typename CONTAINER>
struct push_front: public executer<CONTAINER> {
    void operator()(CONTAINER& c) const {
        typename CONTAINER::value_type value;
        c.push_front(value);
    }
};

template<typename CONTAINER>
struct push_back: public executer<CONTAINER> {
    void operator()(CONTAINER& c) const {
        typename CONTAINER::value_type value;
        c.push_back(value);
    }
};


template<typename CONTAINER>
struct pop_back: public executer<CONTAINER> {
    void operator()(CONTAINER& c) const {
        c.pop_back();
    }
};

template<typename CONTAINER>
struct pop_front: public executer<CONTAINER> {
    void operator()(CONTAINER& c) const {
        c.pop_front();
    }
};

template<typename CONTAINER>
struct random_access: public executer<CONTAINER> {
    void operator()(CONTAINER& c) const {
        auto value = c[rand()%c.size()];
    }
};

template<typename CONTAINER, template<typename T> class EXEC>
auto n_repeater(const size_t& n, const size_t init_size=1e5)
{
    CONTAINER c(init_size);
    EXEC<CONTAINER> e;

    using namespace std::chrono;

    auto t0 = high_resolution_clock::now();
    for (size_t i=0; i<n; ++i) {
        e(c);
    }

    auto t1 = high_resolution_clock::now();
    auto elapsed = duration_cast<std::chrono::milliseconds>(t1 - t0);

    return elapsed.count();
}

template<typename T>
void measure_random_access(const size_t& max_size, const unsigned int& steps, 
                           const size_t init_size)
{
    std::cout << "random_access" << std::endl;
    double delta_step = static_cast<double>(max_size)/(steps+1);
    std::cout << "n\tVector\tDeque";
    for (size_t i = 0; i<steps; ++i) {
        const auto n = static_cast<size_t>(delta_step*(i+1));
        std::list<long long> times;

        std::cout << std::endl << n;

        times.push_back(n_repeater<std::vector<T>, random_access>(n,init_size));
        times.push_back(n_repeater<std::deque<T>, random_access>(n,init_size));

        for (const auto& time: times) {
            std::cout << "\t" << time;
        }
    }
    std::cout << std::endl << std::endl;   
}

template<typename T>
void measure_push_back(const size_t& max_size, const unsigned int& steps, 
                       const size_t init_size)
{
    std::cout << "push_back" << std::endl;
    double delta_step = static_cast<double>(max_size)/(steps+1);
    std::cout << "n\tVector\tList\tDeque";
    for (size_t i = 0; i<steps; ++i) {
        const auto n = static_cast<size_t>(delta_step*(i+1));
        std::list<long long> times;

        std::cout << std::endl << n;

        times.push_back(n_repeater<std::vector<T>, push_back>(n,init_size));
        times.push_back(n_repeater<std::list<T>, push_back>(n,init_size));
        times.push_back(n_repeater<std::deque<T>, push_back>(n,init_size));

        for (const auto& time: times) {
            std::cout << "\t" << time;
        }
    }
    std::cout << std::endl << std::endl;   
}


template<typename T>
void measure_pop_back(const size_t& max_size, const unsigned int& steps, 
                       const size_t init_size)
{
    std::cout << "pop_back" << std::endl;
    double delta_step = static_cast<double>(max_size)/(steps+1);
    std::cout << "n\tVector\tList\tDeque";
    for (size_t i = 0; i<steps; ++i) {
        const auto n = static_cast<size_t>(delta_step*(i+1));
        std::list<long long> times;

        std::cout << std::endl << n;

        times.push_back(n_repeater<std::vector<T>, pop_back>(n,init_size));
        times.push_back(n_repeater<std::list<T>, pop_back>(n,init_size));
        times.push_back(n_repeater<std::deque<T>, pop_back>(n,init_size));

        for (const auto& time: times) {
            std::cout << "\t" << time;
        }
    }
    std::cout << std::endl << std::endl;   
}

template<typename T>
void measure_push_front(const size_t& max_size, const unsigned int& steps, 
                       const size_t init_size)
{
    std::cout << "push_front" << std::endl;
    double delta_step = static_cast<double>(max_size)/(steps+1);
    std::cout << "n\tForward List\tList\tDeque";
    for (size_t i = 0; i<steps; ++i) {
        const auto n = static_cast<size_t>(delta_step*(i+1));
        std::list<long long> times;

        std::cout << std::endl << n;

        times.push_back(n_repeater<std::list<T>, push_front>(n,init_size));
        times.push_back(n_repeater<std::forward_list<T>, push_front>(n,init_size));
        times.push_back(n_repeater<std::deque<T>, push_front>(n,init_size));

        for (const auto& time: times) {
            std::cout << "\t" << time;
        }
    }
    std::cout << std::endl << std::endl;   
}


template<typename T>
void measure_pop_front(const size_t& max_size, const unsigned int& steps, 
                       const size_t init_size)
{
    std::cout << "pop_front" << std::endl;
    double delta_step = static_cast<double>(max_size)/(steps+1);
    std::cout << "n\tForward List\tList\tDeque";
    for (size_t i = 0; i<steps; ++i) {
        const auto n = static_cast<size_t>(delta_step*(i+1));
        std::list<long long> times;

        std::cout << std::endl << n;

        times.push_back(n_repeater<std::forward_list<T>, pop_front>(n,init_size));
        times.push_back(n_repeater<std::list<T>, pop_front>(n,init_size));
        times.push_back(n_repeater<std::deque<T>, pop_front>(n,init_size));

        for (const auto& time: times) {
            std::cout << "\t" << time;
        }
    }
    std::cout << std::endl << std::endl;   
}

int main()
{
    const size_t max_size = 7e6;
    const unsigned int steps = 6;
    const size_t init_size=1e5;

    measure_random_access<int>(max_size, steps, init_size);
    measure_push_front<int>(max_size, steps, init_size);
    measure_pop_front<int>(max_size, steps, init_size+max_size);
    measure_push_back<int>(max_size, steps, init_size);
    measure_pop_back<int>(max_size, steps, init_size+max_size);

    return 0;
}