//============================================================================
// Name        : memoize.cpp
// Author      : Source - http://stackoverflow.com/questions/5353141/what-does-this-c11-code-memoize-do?rq=1
//		 and Dr. Enoch Lee - Auburn University Montgomery 
//  		 and Chris Diggs
//		 
// Compile     : g++ --std=c++11 memoize.cpp -o memoize
// Description : This ultimatly dynamically solves recurrence relations.
// 		 It does this by declaring functions as variables,
//		 which allows a given computation of that fuction to be cache. 
//		 Allowing that computation to be retrieved at any time. 
//
// How-To-RUn  : ./memoize
//======================

//compile: 
#include <functional>
#include <iostream>
#include <tuple>
#include <map>

using namespace std;

template <typename ReturnType, typename... Args>
std::function<ReturnType (Args...)> memoize(std::function<ReturnType (Args...)> func) {
  std::map<std::tuple<Args...>, ReturnType> cache;
  return ([=](Args... args) mutable {
          std::tuple<Args...> t(args...);
          if (cache.find(t) == cache.end())
             cache[t] = func(args...);
          return cache[t];
  });
}

//fibonacci
std::function<int (int)> f;
int fib(int n) {
  if  (n < 2) return n;
  return f(n-1) + f(n-2);
}

//binomial
std::function<int (int, int)> b;
int binomial(int n, int k) {
  if (k == 0 || n == k) return 1;
  return b(n-1, k) + b(n-1, k-1);
}


//recursively produce a given number n
std::function<int (int)> number;
int numb(int n) {
  if (n < 2) return n;
  return number(n-1) + 1;
}

//factorial
std::function<int (int)> ft;
int factorial(int n) {
  if (n < 2) return 1;
  return ft(n-1) * n;
}


//  n*(n-1)/2    is the explicit formula for this x(geometric) arithmetic series..
std::function<int (int)> gs;
int geometric_series(int n) {
  if (n < 2) return 1;
  return gs(n-1) + n;
}



function<int (int)>bn;  //bell number
int bell_num(int n){
  if (n<2) return 1;
  int sum=0;
  for(int k=0;k<=n;k++){
    cout<<k<<" : "<<sum<<endl;
    sum=sum+bn(k-1);//b(n-1,k)*bn(k);
  }
  return sum;
}

function<int (int)>cn;  //catalan number
int catalan_num(int n){
  return (b(2*n,n)/(n+1));
}




int main(void) {

  b = memoize(function<int (int, int)>(binomial));
  bn = memoize(function<int (int)>(bell_num));
  cn= memoize(function<int (int)>(catalan_num));

  int temp;
  cin>>temp;
  cout<<"\nThe "<<temp<<"th bell number is "<<bn(temp)<<endl;
  cout<<"\nThe "<<temp<<"th catalan number is "<<cn(temp)<<endl;
 return 0;
}
