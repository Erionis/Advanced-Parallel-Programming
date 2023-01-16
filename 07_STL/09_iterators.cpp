#include <iostream>   
#include <iterator>     
#include <vector>     
#include <list>  
#include <algorithm>    // per std::copy

#include "common.hpp"

void move_iterator_test() 
{
  std::cout << "Testing move_iterator..."  << std::endl;
  std::vector<double> v1(2);   // creo un array di 2 elementi
  std::vector<double> v2{-5.9, 8.2};

  std::cout << " v1: " << v1 << std::endl;
  std::cout << " v2: " << v2 << std::endl;
  // reisco a spostare le cose da v2 a v1 usando l'iteratore
  typedef std::vector<double>::iterator VIter;
  std::copy ( std::move_iterator<VIter>(v2.begin()),
              std::move_iterator<VIter>(v2.end()),
              v1.begin() );

  std::cout << " v1: " << v1 << std::endl;
  std::cout << " v2: " << v2 << std::endl;

  std::cout << "done" << std::endl;
}


void back_inserter_test () 
{  
  std::cout << "Testing back_inserter..."  << std::endl;
  std::vector<double> v1{2.1, 3.0, -2.1};
  std::vector<double> v2{-5.9, 8.2};

  std::cout << " v1: " << v1 << std::endl;
  std::cout << " v2: " << v2 << std::endl;

  std::copy(v2.begin(), v2.end(), std::back_inserter(v1));

  std::cout << " v1: " << v1 << std::endl;
  std::cout << " v2: " << v2 << std::endl;
  std::cout << "done" << std::endl;
}

void ostream_iterator_test () 
{  

  std::cout << "Testing ostream_iterator..."  << std::endl;
  std::vector<double> v1{2.1, 3.0, -2.1};

  std::cout << " v1: " << v1 << std::endl << " ";

  std::ostream_iterator<int> out_it (std::cout,", ");
  std::copy ( v1.begin(), v1.end(), out_it );
  std::cout << std::endl;

  std::cout << "done" << std::endl;
}

void istream_iterator_test() 
{
  std::vector<int> v;
  std::cout << "Inserisci quanti valori vuoi (0 per finire): ";

  std::istream_iterator<int> eos;                // fine dell'iteratore di input
  std::istream_iterator<int> in_it (std::cin);   // iteratore di input su std::cin

  while (in_it!=eos && *in_it != 0) {
    v.push_back(*(in_it++));
  }

  std::cout << " v: " << v << std::endl;

  std::cout << "done" << std::endl;
}

void insert_iterator_test() 
{

  std::cout << "Testing insert_iterator_test..."  << std::endl;
  std::list<int> l{2, 3, -5, 7, 8};
  std::vector<int> v{4,5};

  std::cout << " l: " << l << std::endl;
  std::cout << " v: " << v << std::endl;
  std::list<int>::iterator l_it = l.begin();
  ++l_it;++l_it;

  std::insert_iterator< std::list<int> > insert_it (l,l_it);

  std::copy (v.begin(),v.end(),insert_it);

  std::cout << " l: " << l << std::endl;
  std::cout << "done" << std::endl;
}

int main()
{
  move_iterator_test();
  back_inserter_test();
  insert_iterator_test();
  ostream_iterator_test();
  istream_iterator_test();

  return 0;
}