# Ataques-al-algoritmo-RSA
Integrantes

Leonardo Alonso Ramirez Quiroz

Diego Enrique Zegarra Zenteno

Rodrigo del Piero Melendez Flores


1:
Implementar RSA_KEY_GENERATOR.

Utilizamos algoritmos implementados en anteriores sesiones como: Inversa de un número, Euclides extendido, exponenciación modular y miller rabin.

El algoritmo del RSA recibe un int k, long long e y long long d.

Empieza generando dos números primos (p y q) al azar y asegurándose que sean distintos.

Calcula n como el producto de p y q, y phi de n.

Hallamos Generar aleatoriamente e ∈ [2, n − 1], tal que gcd(e, φ(n)) = 1 (con euclides de (e,φ(n)).

Hallamos d, que es el inverso de (e, φ(n)).

unsigned long long RSA_KEY_GENERATOR(int k, unsigned long long& e, unsigned long long& d) {
    unsigned long long p = RANDOMGEN_PRIMOS(k / 2);
    unsigned long long q = RANDOMGEN_PRIMOS(k / 2);
    while (p == q) q = RANDOMGEN_PRIMOS(k / 2);

    unsigned long long n = p * q;
    unsigned long long φn = (p - 1) * (q - 1);
    int x, y;
    
    e = 2 + rand() % φn - 1;
    while (EuclidesExtendido(e, φn, x, y) != 1) e = 2 + rand() % φn - 1;
    d = inverso(e, φn);
    return n;
}

unsigned long long cifrar(unsigned long long m, unsigned long long e, unsigned long long n) {
    unsigned long long c = EXPMOD(m, e, n);
    return c;
}

unsigned long long descifrar(unsigned long long c, unsigned long long d, unsigned long long n) {
    unsigned long long m = EXPMOD(c, d, n);
    return m;
}
2:
*Crear un sistema RSA-64 y mostrar los valores para e, d y n.

Generar una tabla con tres columnas m, c = P(m) y m' = S(c). Para las filas usar 10 valores números aleatorios distintos para m.*

int main() {
  int k;
  cout << "Inserte valor de k: " << endl;
  cin >> k;
  unsigned long long e;
  unsigned long long d;
  unsigned long long n = RSA_KEY_GENERATOR(k, e, d);
  cout << "n:  " << n << "  e:  " << e << "  d  " << d << endl<< endl;
  cout << "M       " << "\t" << "C       " << "\t" << "M´" << endl;
  for(int i=0;i<10;i++){
      unsigned long long k=rand() % (n - 1);
      unsigned long long cifrado = cifrar(k, e, n);
      unsigned long long descifrado = descifrar(cifrado, d, n);
      cout << k << "\t"<< cifrado << "\t" << descifrado << endl;
  }
}
Inserte valor de k: 
5
n:  4644779  e:  4479961  d  4538041

M           C           M´
804447  1016251 804447
109872  3112222 109872
148210  1804089 148210
240501  75602   240501
2059343 3813913 2059343
1543952 4610851 1543952
1160379 2664214 1160379
3180034 2177321 3180034
689670  994227  689670
3978786 3276525 3978786
