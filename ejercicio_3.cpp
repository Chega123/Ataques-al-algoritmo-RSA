import hashlib
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

def Es_Compuesto(a, n, t, x):
  x0 = Fermat(a, x, n)
  if x0 == 1 or x0 == n-1:
    return False
  for i in range(t):
    x0 = Fermat(x0, 2, n)
    if x0==n-1:
      return False
  return True

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

def Randombits(b):
  po = 2**b
  pos = 2**(b-1)
  n = random.randint(0,po-1)
  m = pos + 1
  n = n | m
  return n

def Randomgen(b):
  n = Randombits(b)
  while Miller(n,23) == False:
    n = n+2
  return n

def Euclides(a, b):
  if b == 0:
    return a
  else:
    return Euclides(b, a%b)

def Ext_Euclides(a, b):
  if b == 0:
    return (a, 1, 0)
  else:
    d, x_, y_ = Ext_Euclides(b, a%b)
    x, y = y_, x_ - int(a/b)*y_
    return (d, x, y)
    
def inversa(a, n):
  if Euclides(a, n) == 1:
    mgd, x, y = Ext_Euclides(a, n)
    return x % n
  else:
    print("No existe inversa")
      
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

def Cifrado(m,e,n):
  P = Fermat(m,e,n)
  return P

def Descifrado(c,d,n):
  S = Fermat(c,d,n)
  return S


 
def validación_firmas (M) :
  rsa,_,__ = RSA_KEY_GENERATOR(32)
  result = hashlib.sha1(M.encode())
  m = int(result.hexdigest(), 16)%rsa
  result = hashlib.sha1(M.encode())
  m_ = int(result.hexdigest(), 16)%rsa
  print (m,"|", m_)

print ("P(S(m))", "|", "HASH(M)" )
print ("---------------------------------")
messaje_1 = validación_firmas("Hola mundo")
messaje_2 = validación_firmas("Estoy muy cansado")
messaje_2 = validación_firmas("Un punto extra en el final por favor")
