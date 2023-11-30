/* We are going to test the following:
x = 5    # Ref 1
z = 50
q = 4

fun f() # Ref 2
  x = 1
  y = 2

  fun g() # Ref 3
     z = 3
     y = 7
     q = 9
     h = 10
  end
  g()
end

f()

    Ref 1     Ref 2    Ref 3
x   1         1        1
y   Undef     7        7
z   3         3        3   
q   9         9        9
h   Undef     Undef    10
*/