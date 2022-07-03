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

bool ES_COMPUESTO(unsigned long long a, unsigned long long n, unsigned long long t, unsigned long long u) {
    unsigned long long x = EXPMOD(a, u, n);
    if (x == 1 || x == n - 1) { return false; }
    for (int i = 1; i <= t; i++) {
        x = EXPMOD(x, 2, n);
        if (x == n - 1) { return false; }
    }
    return true;
}

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

unsigned long long RANDOMBITS(int b) {
    unsigned long long n = rand() % EXP(2, b - 1);
    unsigned long long m = EXP(2, b - 1) + 1;
    n = n | m;
    return n;
}

unsigned long long RANDOMGEN_PRIMOS(int b) {
    int s = 50;
    unsigned long long n = RANDOMBITS(b);
    while (MILLER_RABIN(n, s) == false) {
        n = n + 2;
    }
    return n;
}
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


unsigned long long RSA_KEY_GENERATOR(int k, unsigned long long& e, unsigned long long& d) {
    //genera primos aleatorios
    unsigned long long p = RANDOMGEN_PRIMOS(k / 2);
    unsigned long long q = RANDOMGEN_PRIMOS(k / 2);
    //por si son iguales se vuelve a generar q
    while (p == q) {
        q = RANDOMGEN_PRIMOS(k / 2);
    }
    //se calcula n 
    unsigned long long n = p * q;
    //calculamos  φ(n)= φ(p)*φ(q)=(p-1)*(q-1)
    unsigned long long φn = (p - 1) * (q - 1);
    int x, y;
    //hallamos Generar aleatoriamente e ∈ [2, n − 1], tal que gcd(e, φ(n)) = 1 (con euclides de (e,φn)
    e = 2 + rand() % φn - 1;
    while (EuclidesExtendido(e, φn, x, y) != 1) {
        e = 2 + rand() % φn - 1;
    }
    //hallamos d q es el inverso de (e, φn)
    d = inverso(e, φn);
    return n;

}

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
