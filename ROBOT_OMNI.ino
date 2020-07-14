//****bố trí bánh xe****//
//bánh 1 -------- bánh 2
//bánh 3 -------- bánh 4
//****bố trí cảm biến****//
//trước: 39-38-37-36-35-34
//sau: 27-26-25-24-23-22
//phải: 33-32-31-30-29-28
//trái: 45-44-43-42-41-40
#include <Servo.h>

#define pwm1_lui    3
#define pwm1_toi    2
#define pwm2_lui    4
#define pwm2_toi    5
#define pwm3_lui    7
#define pwm3_toi    6
#define pwm4_lui    8
#define pwm4_toi    9

#define encoder1    2
#define encoder2    3
#define encoder3    4
#define encoder4    5

// --------------------------
#define cb_truoc      1
#define cb_trai       2
#define cb_phai       3
#define cb_sau        4
#define cb_truoc_sau  5

#define chay_toi    1
#define chay_trai   2
#define chay_phai   3
#define chay_lui    4

#define quay_trai   1
#define quay_phai   2

int sensor[6] = {0, 0, 0, 0, 0, 0};
int sensor1[6] = {0, 0, 0, 0, 0, 0};

Servo khop1; //0-180
Servo khop2; //0-80-150
byte servo1, servo2, servo3, servo4;
volatile int a = 80, b = 30;

int error, previous_error;
float P, I, D, kp = 25, ki = 0.0001, kd = 250;
int PID_value, PID_phai, PID_trai;
float P1, I1, D1;
int error1, previous_error1;
int PID_value_1, PID_phai_1, PID_trai_1;
int gia_tri_dau_phai = 180;
int gia_tri_dau_trai = 180;
volatile int    xung_encoder1, xung_encoder2, xung_encoder3, xung_encoder4;
unsigned long time_now = 0;
unsigned long time_now1 = 0;

void doc_encoder1() //ngắt 0, chân 2
{
  xung_encoder1++;
}
void doc_encoder2() //ngắt 1, chân 3
{
  xung_encoder2++;
}
void doc_encoder3() //ngắt 4, chân 19
{
  xung_encoder3++;
}
void doc_encoder4() //ngắt 5, chân 18
{
  xung_encoder4++;
}
void setup()
{
  Serial.begin(9600);
  pinMode(encoder1,   INPUT);
  pinMode(encoder2,   INPUT);
  pinMode(encoder3,   INPUT);
  pinMode(encoder4,   INPUT);

  khop1.attach(10); //0-180
  khop2.attach(11); //0-80-150

  readyPosition();

  attachInterrupt(2, doc_encoder1,  RISING); //ngắt 0, chân 2
  attachInterrupt(3, doc_encoder2,  RISING); //ngắt 1, chân 3
  attachInterrupt(4, doc_encoder3,  RISING); //ngắt 4, chân 19
  attachInterrupt(5, doc_encoder4,  RISING); //ngắt 5, chân 18

  for (int i = 5; i < 14; i++)
  {
    pinMode(i , OUTPUT);
  }
  for (int i = 22; i < 46; i++)
  {
    pinMode(i , INPUT);
  }

  for (int i = 5; i < 14; i++)
  {
    analogWrite(i, 0);
  }

  analogWrite(pwm1_toi, 0);
  analogWrite(pwm2_toi, 0);
  analogWrite(pwm3_toi, 0);
  analogWrite(pwm4_toi, 0);
  delay(500);
}
/*
  CÁC ĐỊNH NGHĨA:
  chọn cảm biến: (cb_truoc_sau, cb_truoc, cb_trai, cb_phai)
  chọn hướng chạy: (chay_toi, chay_trai, chay_phai)
  chọn hướng quay: (quay_trai, quay_phai)
  tốc độ: 100 đến 180
  CÁC CHƯƠNG TRÌNH CON:
  chay_do_line_do_encoder (chọn cảm biến, chọn hướng chạy, số xung encoder, dừng = 1/không dừng = 0, tốc độ trái, tốc độ phải, kp);
  chay_do_line_doc_cam_bien (chọn cảm biến, chọn hướng chạy, chọn cảm biến đếm line, số line, dừng = 1/không dừng = 0, tốc độ trái, tốc độ phải, kp);
  quay_bat_line(huong_quay, toc_do, cam_bien_bat_line)
  quay_encoder(huong_quay, toc_do, số xung encoder)
*/
void loop()
{
//  chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 1840, 1, 120, 120, 25); //chọn cb trước và sau, chạy tới, 1200 xung, dừng, tốc độ trái 100, phải 105
//  delay(100);
//
//  haxuong(); // grap two red can
//  delay(100);
//  kep();
//  delay(100);
//  nanglen();
//  delay(100);
//
//  chay_do_line_doc_cam_bien(cb_truoc_sau, chay_toi, 33, 1, 1, 140, 140, 25); // vào ngã ba đầu
//  delay(500);
//  quay_encoder(quay_trai, 250, 300, 0);
//  quay_bat_line(quay_trai, 150, 25);
//  delay(500);
//  chay_do_line_do_encoder(cb_truoc_sau, chay_toi, 1500, 0, 120, 120, 25);
//  chay_do_line_doc_cam_bien(cb_truoc_sau, chay_toi, 39, 1, 1, 140, 140, 25);
//  delay(500);
//
//  haxuong(); // drop two red can
//  delay(500);
//  tha();
//  delay(500);
//  nanglen();
//  delay(500);
//
//  chay_do_line_do_encoder(cb_sau, chay_lui, 2000, 0, 140, 140, 25);
//  chay_do_line_doc_cam_bien(cb_sau, chay_lui, 30, 1, 1, 140, 140, 25); //chạy lùi, thả 2 lon đỏ, bắt 30 đỡ trượt
//  delay(500);
//  quay_encoder(quay_phai, 250, 300, 0);
//  quay_bat_line(quay_phai, 150, 25);
//  delay(500);
//  chay_do_line_do_encoder(cb_truoc_sau, chay_toi, 4620, 1, 150, 150, 25);
//
//  delay(500); // grap two green can
//  haxuong();
//  delay(500);
//  kep();
//  delay(500);
//  nanglen();
//  delay(500);
//
//  chay_do_line_doc_cam_bien(cb_sau, chay_lui, 33, 1, 1, 150, 150, 25);
//  delay(500);
//  quay_encoder(quay_trai, 250, 300, 0);
//  quay_bat_line(quay_trai, 150, 24);
//  delay(500);
//  chay_do_line_doc_cam_bien(cb_truoc_sau, chay_toi, 33, 1, 1, 140, 140, 25); // get center left sensor 33 value
//  delay(500);
//  quay_encoder(quay_phai, 250, 300, 0);
//  quay_bat_line(quay_phai, 150, 24); // ss front center
//  delay(500);
//  chay_do_line_do_encoder(cb_truoc_sau, chay_toi, 3000, 0, 140, 140, 25);
//  chay_do_line_doc_cam_bien(cb_truoc_sau, chay_toi, 33, 1, 1, 140, 140, 25); // get center left sensor 33 value
//  delay(500);
//  quay_encoder(quay_trai, 250, 300, 0);
//  quay_bat_line(quay_trai, 150, 24); // ss front center
//  delay(500);
//  chay_do_line_do_encoder(cb_truoc_sau, chay_toi, 450, 1, 150, 150, 25);
//  delay(500);
//
//  haxuong(); // drop two green can
//  delay(500);
//  tha();
//  delay(500);
//  nanglen();
//  delay(500);
//
  chay_do_line_doc_cam_bien(cb_sau, chay_lui, 31, 1, 1, 140, 140, 25);
  delay(500);
  quay_encoder(quay_phai, 250, 300, 0);
  quay_bat_line(quay_phai, 150, 24); // ss front center
  delay(500);
  chay_do_line_do_encoder(cb_truoc_sau, chay_toi, 1500, 0, 140, 140, 25);
  chay_do_line_do_encoder("", chay_toi, 700, 0, 140, 125, 25); //chạy mờ tới lon đỏ xanh
  delay(500);
  chay_do_line_doc_cam_bien(cb_truoc_sau, chay_toi, 40, 1, 1, 150, 150, 25);
  delay(500);
  quay_encoder(quay_trai, 250, 300, 0);
  quay_bat_line(quay_trai, 150, 31); // ss back center
  delay(500);
//
//  haxuong();
//  delay(100);
//  kep();
//  delay(500);
//  nanglen();
//  delay(500);
//
//  delay(500);
//  quay_encoder(quay_trai, 250, 300, 0);
//  quay_bat_line(quay_trai, 150, 25); // ss back center
//  delay(500);
  
  //todo
  delay(1000000);
}
