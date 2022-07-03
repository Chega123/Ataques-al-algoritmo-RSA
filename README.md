# Ataques-al-algoritmo-RSA
Integrantes

Leonardo Alonso Ramirez Quiroz

Diego Enrique Zegarra Zenteno

Rodrigo del Piero Melendez Flores




funciones que usamos para los ejercicio 1 ya que es el unico hecho en c++ por limitaciones


```c++
#include <iostream>
#include <cstdlib>

using namespace std;

unsigned long long EXPMOD(unsigned long long a, unsigned long long x, unsigned long long n) {
    if (x == 0) { return 1; }
    else if (x % 2 == 0) {
        unsigned long long t = EXPMOD(a, x / 2, n);
        return (t * t) % n;
    }
    else {
        unsigned long long t = EXPMOD(a, x - 1, n);
        a = a % n;
        return (t * a) % n;
    }
}
```
```c++
unsigned long long EXP(unsigned long long a, unsigned long long x) {
    if (x == 0) { return 1; }
    else if (x % 2 == 0) {
        unsigned long long t = EXP(a, x / 2);
        return (t * t);
    }
    else {
        unsigned long long t = EXP(a, x - 1);
        return (t * a);
    }
}
```
```c++
bool ES_COMPUESTO(unsigned long long a, unsigned long long n, unsigned long long t, unsigned long long u) {
    unsigned long long x = EXPMOD(a, u, n);
    if (x == 1 || x == n - 1) { return false; }
    for (int i = 1; i <= t; i++) {
        x = EXPMOD(x, 2, n);
        if (x == n - 1) { return false; }
    }
    return true;
}
```
```c++
bool MILLER_RABIN(unsigned long long n, int s) {
    unsigned long long t = 0;
    unsigned long long u = n - 1;
    while (u % 2 == 0) {
        u = u / 2;
        t = t + 1;
    }
    for (int j = 1; j <= s; j++) {
        unsigned long long a = rand() % (n - 1) + 2;
        if (ES_COMPUESTO(a, n, t, u)) { return false; }
    }
    return true;
}
```
```c++
unsigned long long RANDOMBITS(int b) {
    unsigned long long n = rand() % EXP(2, b - 1);
    unsigned long long m = EXP(2, b - 1) + 1;
    n = n | m;
    return n;
}
```
```c++
unsigned long long RANDOMGEN_PRIMOS(int b) {
    int s = 50;
    unsigned long long n = RANDOMBITS(b);
    while (MILLER_RABIN(n, s) == false) {
        n = n + 2;
    }
    return n;
}
```
```c++
int EuclidesExtendido(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int euclides = EuclidesExtendido(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return euclides;
}
```
```c++
unsigned long long inverso(unsigned long long a, unsigned long long n)
{
    int x, y;
    int eucli = EuclidesExtendido(a, n, x, y);
    if (eucli == 1) {
        if (0 <= x <= n - 1) {
            unsigned long long resultado = (x % n + n) % n;
            return resultado;
        }
        else cout << "no esta en el rango de Zn";
    }
    else cout << "no existe";

}
```


Funciones que usamos para el ejercicio 2 y 3 los cuales estan hechos en python

```py
import random
def Fermat(a, x, n):
  if x == 0:
    return 1
  elif x%2 == 0:
    t = Fermat(a, x/2, n)
    return (t*t)%n
  else:
    t = Fermat(a, x-1, n)
    c = a%n
    return (t*c)%n
```py  
def EXPMOD(a, x, n):
  c = a % n
  r = 1
  while (x > 0):
    if x % 2 != 0:
      r = (r * c) % n
    c = (c * c) % n
    x = int(x/2)
  return r
```py  
def Es_Compuesto(a, n, t, x):
  x0 = Fermat(a, x, n)
  if x0 == 1 or x0 == n-1:
    return False
  for i in range(t):
    x0 = Fermat(x0, 2, n)
    if x0==n-1:
      return False
  return True
```py
def Miller(n,s):
  t = 0
  u = n-1
  while u%2==0:
    u = u/2
    t = t+1
  for j in range(s):
    a = random.randint(2,n-1)
    if Es_Compuesto(a,n,t,u):
      return False
  return True
```py
def Randombits(b):
  po = 2**b
  pos = 2**(b-1)
  n = random.randint(0,po-1)
  m = pos + 1
  n = n | m
  return n
```py
def Randomgen(b):
  n = Randombits(b)
  while Miller(n,23) == False:
    n = n+2
  return n
```py
def Euclides(a, b):
  if b == 0:
    return a
  else:
    return Euclides(b, a%b)
```py
def Ext_Euclides(a, b):
  if b == 0:
    return (a, 1, 0)
  else:
    d, x_, y_ = Ext_Euclides(b, a%b)
    x, y = y_, x_ - int(a/b)*y_
    return (d, x, y)
```py    
def inversa(a, n):
  if Euclides(a, n) == 1:
    mgd, x, y = Ext_Euclides(a, n)
    return x % n
  else:
    print("No existe inversa")
```   
```py      
def RSA_KEY_GENERATOR(k):
  p = Randomgen(k//2)
  q = Randomgen(k//2)
  while(p == q):
    q = Randomgen(k//2)
  n = p*q
  _n = (p-1)*(q-1)
  for e in range(2,n):
    if Euclides(e,_n) == 1:
      break
  d = inversa(e,_n)
  return (n,e,d)
```  
```py
def Cifrado(m,e,n):
  cifra = Fermat(m,e,n)
  return cifra
```
```py
def Descifrado(c,d,n):
  descifra = Fermat(c,d,n)
  return descifra
```
-Ejercicio1

```c++
int main() {
    int k;
    unsigned long long e=65537;
    unsigned long long d=0;    
    unsigned long long c=747120213790;
    unsigned long long n=999630013489;
    unsigned long long r=0;
    unsigned long long p=999671;
    unsigned long long q=999959;
    unsigned long long φn = (p - 1) * (q - 1);
    d = inverso(e, φn);
    cout << EXPMOD(c,d,n) << endl;
   
}
```

```bash
    875125425841
```


