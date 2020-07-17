
void readyPosition()
{
  a = 0;
  b = 80;
  khop1.write(a);
  khop2.write(b);

  kep();
  delay(10);
  tha();
  delay(10);
  kep();
  delay(10);
  tha();
}

void nanglen()
{
  for (a; a >= 0; a--) // 0 to 90
  {
    khop1.write(a);
    delay(10);
  }
}
void haxuong() // 90 to 0
{
  for (a; a <= 90; a++)
  {
    khop1.write(a);
    delay (10);
  }
}
void kep()
{
  for (b; b >= 5; b--)
  {
    khop2.write(b);
    delay (5);
  }
}
void tha()
{
  for (b; b <= 80; b++)
  {
    khop2.write(b);
    delay (5);
  }
}
