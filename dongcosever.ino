void readyPosition()
{
  a = 0;
  b = 80;
  khop1.write(a);
  khop2.write(b);
}

void nanglen()
{
  for (a; a >= 0; a--) // h? xu?ng
  {
    khop1.write(a);
    delay(10);
  }
}
void haxuong()
{
  for (a; a <= 90; a++) // nâng lên
  {
    khop1.write(a);
    //delay (50);
  }
}
void kep()
{
  for (b; b >= 15; b--) // k?p
  {
    khop2.write(b);
    //delay (50);
  }
}
void tha()
{
  for (b; b <= 80; b++) // th?
  {
    khop2.write(b);
    //delay (50);
  }
}
