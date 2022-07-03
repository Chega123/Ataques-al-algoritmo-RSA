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

def Cifrado(m,e,n):
  P = Fermat(m,e,n)
  return P
def Descifrado(c,d,n):
  S = Fermat(c,d,n)
  return S
  
def EUCLIDES(a, b):
  if b == 0:
    return a
  else:
    return EUCLIDES(b, a%b)

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

    
e = 65537
n = 999630013489
phi_n = 999628013860
c = 747120213790

d = inversa(e,phi_n)
for x in range(1,n):
  if EUCLIDES(x,n)==1:
    break
c_ = (c * Fermat(x,e,n)) %n
m_ = Descifrado(c_,d,n)
x_ =inversa(x,n)
m = (m_*x_)%n
p = Cifrado(m,e,n)
print(m)
