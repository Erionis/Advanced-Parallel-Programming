#include <iostream>
#include <set>

template <typename T, typename CMP, typename A, 
         template<class, class, class> class SET>
std::ostream& operator<<(std::ostream& os, const SET<T,CMP,A>& s)
{
    std::cout << '{';

    bool first{true};
    for (const auto& value: s) { // posso scandire gli oggetti dell'contenitore 
                                 // usando questa sintassi
        if (first) {
            first = false;
        } else {
            std::cout << ',';
        }
        std::cout << value;
    }

    std::cout << '}';

    return os;
}

template <typename SET_TYPE>
void test()
{
  SET_TYPE s{ 0, 5, 3};
  std::cout << " s: " << s << std::endl;

  std::cout << "Inserisco -3 e 5...";
  s.insert(-3);
  s.insert(5);
  std::cout << "fatto" << std::endl;

  std::cout << " s: " << s << std::endl;

  std::cout << "Rimuovo 0...";
  s.erase(0);
  std::cout << "fatto" << std::endl;

  std::cout << " s: " << s << std::endl;

  std::cout  << " s.size(): " << s.size()       // stampa "s.size(): 3"
            << " s.count(5): " << s.count(5)   // stampa " s.count(5): 1" 
            << std::endl;

  SET_TYPE s2{ 0, 5, 6, 4};

  std::cout << " s2: " << s2 << std::endl;

  std::cout << "Faccio il merge di s2 a s...";
  s.merge(s2);
  std::cout << "fatto" << std::endl;

  std::cout << " s: " << s << std::endl;
  std::cout << " s2: " << s2 << std::endl;

  std::cout << "Creo s3..." ;
  SET_TYPE s3;
  std::cout << "fatto" << std::endl;

  std::cout << " s3: " << s3 << std::endl;
  std::cout << "Copio s in s3..." ;
  s3 = s;
  std::cout << "fatto" << std::endl;

  std::cout << " s3: " << s3 << std::endl;
}

int main() {
  std::cout << "SET" << std::endl;
  test<std::set<int>>();

  std::cout << std::endl 
            << "MULTISET" << std::endl;
  test<std::multiset<int>>();

  return 0;
}