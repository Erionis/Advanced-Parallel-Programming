#include <iostream>
#include <map>
#include <vector>

#include "common.hpp"

template <typename KEY, typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<KEY,T>& p)
{
  os << "{" << p.first << "," << p.second << "}";

  return os;
}

template <typename T, typename KEY, typename CMP, typename A, 
         template<class, class, class, class> class MAP>
std::ostream& operator<<(std::ostream& os, const MAP<T,KEY,CMP,A>& m)
{
    std::cout << '{';

    bool first{true};
    for (const auto& value: m) { // posso scandire gli oggetti dell'contenitore 
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

template <typename MAP_TYPE>
void test_index(MAP_TYPE& m)
{
  std::cout << "Modifico m[\"first\"]...";
  m["first"].push_back(0);
  std::cout << "fatto" << std::endl;

  std::cout << " m: " << m << std::endl;
}

template <>
void test_index(std::multimap<std::string, std::vector<int>>& m)
{
  std::cout << "multimap non supporta l'indicizzazione" << std::endl;
}

template <typename MAP_TYPE>
void test()
{
  MAP_TYPE m{{"first", {}},
             {"second", {1}},
             {"third", {2}}};

  std::cout << " m: " << m << std::endl;

  test_index(m);

  std::cout << "Inserisco \"second\"...";
  m.insert({ "second", {8,7} });
  std::cout << "fatto" << std::endl;

  std::cout << " m: " << m << std::endl;

  std::cout << "Cancello \"third\"...";
  m.erase("third");
  std::cout << "fatto" << std::endl;

  std::cout << " m: " << m << std::endl;

  std::cout  << " m.size(): " << m.size()       // stampa "m.size(): 2"
            << " m.count(\"second\"): " 
            << m.count("second")   // stampa " m.count("second"): 1" 
            << std::endl;

  MAP_TYPE m2{{"fourth", {-3,2}}, {"second", {5,6}}};

  std::cout << " m2: " << m2 << std::endl;

  std::cout << "Faccio il merge di m2 a m...";
  m.merge(m2);
  std::cout << "fatto" << std::endl;

  std::cout << " m: " << m << std::endl;
  std::cout << " m2: " << m2 << std::endl;

  std::cout << "Creo m3..." ;
  MAP_TYPE m3;
  std::cout << "fatto" << std::endl;

  std::cout << " m3: " << m3 << std::endl;
  std::cout << "Copio m in m3..." ;
  m3 = m;
  std::cout << "fatto" << std::endl;

  std::cout << " m3: " << m3 << std::endl;

  test_index(m);

  std::cout << " m3: " << m3 << std::endl;
}

int main() {
  std::cout << "MAP" << std::endl;
  test<std::map<std::string, std::vector<int>>>();

  std::cout << std::endl 
            << "MULTIMAP" << std::endl;
  test<std::multimap<std::string, std::vector<int>>>();

  return 0;
}