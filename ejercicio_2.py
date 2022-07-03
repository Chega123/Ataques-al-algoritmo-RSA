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
    
def EXPMOD(a, x, n):
  c = a % n
  r = 1
  while (x > 0):
    if x % 2 != 0:
      r = (r * c) % n
    c = (c * c) % n
    x = int(x/2)
  return r
  
def Cifrado(m,e,n):
  P = Fermat(m,e,n)
  return P
def Descifrado(c,d,n):
  S = Fermat(c,d,n)
  return S

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

    
e1 = 7
e2 = 11
n = 35794234179725868774991807832568455403003778024228226193532908190484670252364677411513516111204504060317568667
c1 = 35794234179725868774991807832568455403003778024228226193532908190484670252364677411513516052471686245831933544
c2 = 35794234179725868774991807832568455403003778024228226193532908190484670252364665786748759822531352444533388184

d1,x1,y1 = Ext_Euclides(e1,e2)

d2,_,__ = Ext_Euclides(c2,n)
m = 0

if d1==1 and d2==1:
  c2_inv = inversa(c2, n)
  m = (EXPMOD(c1,x1,n) * EXPMOD(c2_inv, -1*y1,n)) % n
  print("m= ",m)
  print("c= ",EXPMOD(m, e2, n))

if d1==1 and d2==1:
  c2_inv = inversa(c1, n)
  m = (EXPMOD(c2,y1,n) * EXPMOD(c2_inv, -1*x1,n)) % n
  print("m= " ,m)
  print("c= ",EXPMOD(m, e1, n))
  
c_prima = Cifrado(m,e1,n)
print(c_prima)
c2_prima= Cifrado(m,e2,n)
print(c_prima)
