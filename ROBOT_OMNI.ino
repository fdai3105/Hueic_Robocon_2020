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


  //  digitalWrite(encoder1,   HIGH);
  //  digitalWrite(encoder2,   HIGH);
  //  digitalWrite(encoder3,   HIGH);
  //  digitalWrite(encoder4,   HIGH);

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

  //  analogWrite(pwm1_toi, 0);
  //  analogWrite(pwm2_toi, 0);
  //  analogWrite(pwm3_toi, 0);
  //  analogWrite(pwm4_toi, 0);
  delay(2000);
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
  chay_do_line_do_encoder (cb_truoc, chay_toi, 1820, 1, 120, 120, 25); //chọn cb trước và sau, chạy tới, 1200 xung, dừng, tốc độ trái 100, phải 105
  delay(1000);
  haxuong();
  delay(1000);
  kep();
  delay(1000);
  nanglen();
  delay(1000);
  chay_do_line_do_encoder(cb_truoc, chay_toi, 3000, 1, 120, 120, 25); // vào chặng ba đầu
  delay(1000);
  quay_encoder(quay_trai, 68, 15, 0);
  delay(2000);
  chay_do_line_do_encoder(cb_truoc, chay_toi, 2300, 1, 120, 120, 25);
  delay(1000);
  haxuong();
  delay(1000);
  tha();
  delay(1000);
  nanglen();
  delay(1000);
  chay_do_line_do_encoder(cb_sau, chay_lui, 2500, 1, 120, 120, 25);
  delay(1000);
  quay_encoder(quay_phai, 80, 15, 0);
  delay(2000);
  chay_do_line_do_encoder(cb_truoc, chay_toi, 4650, 1, 120, 120, 25); // todo (test delay = 10 on dongcosever)
  delay(1000);
  haxuong();
  delay(1000);
  kep();
  delay(1000);
  nanglen();
  delay(1000);
  //  quay_encoder(quay_trai, 68, 15, 0); //quay phải, tốc độ 120, 400 xung để cảm biến số 36 thoát khỏi line ban đầu
  //  delay(2000);
  //  chay_do_line_do_encoder("", chay_toi, 1800, 1, 120, 120, 25); //chạy không dò line
  //  delay(2000);
  //  quay_encoder(quay_phai, 80, 13, 0);
  //  delay(2000);
  //  chay_do_line_do_encoder(cb_truoc, chay_toi, 2000, 1, 120, 120, 25);
  delay(1000000);
  //THỰC HIỆN 2 QUÀ ĐỎ
  //    quay_bat_line(quay_trai, 120, 42);  //quay phải, tốc độ 120, bắt cảm biến số 42
  //    delay(500);
  //    chay_do_line_doc_cam_bien (cb_trai, chay_trai, 38, 1 , 1, 140, 145, 30); //chọn cb trái, chạy trái, bắt cảm biến số 38, bắt 1 line, dừng, tốc độ trái 140, phải 145
  //    delay(100);
  //    chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 1370, 1, 120, 125, 30);
  //    delay(2000);
  //
  //  //THỰC HIỆN 2 QUÀ XANH - ĐỎ
  //  chay_do_line_doc_cam_bien (cb_sau, chay_lui, 43, 1 , 1, 100, 105, 25);
  //  delay(500);
  //  quay_encoder(quay_trai, 120, 400, 0); //quay trái, tốc độ 120, 400 xung để cảm biến số 37 thoát khỏi line ban đầu
  //  quay_bat_line(quay_trai, 120, 37);    //quay trái, tốc độ 100, bắt cảm biến số 37
  //  delay(500);
  //  chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 3500, 0, 170, 165, 30);    //chọn cb trước và sau, chạy tới, 3500 xung, ko dừng, tốc độ trái 170, phải 165
  //  chay_do_line_doc_cam_bien(cb_truoc_sau, chay_toi, 42, 1 , 1, 100, 105, 25); //chọn cb trước và sau, chạy tới, bắt cảm biến số 42, bắt 1 line, dừng, tốc độ trái 140, phải 145
  //  delay(1000);
  //  quay_bat_line(quay_phai, 100, 30);
  //  delay(2000);
  //  chay_do_line_do_encoder (cb_phai, chay_phai, 3000, 0, 180, 185, 30);
  //  chay_do_line_doc_cam_bien(cb_phai, chay_phai, 36, 1 , 1, 100, 105, 25);
  //  delay(500);
  //  chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 460, 1, 100, 105, 25);
  //  delay(2000);
  //  chay_do_line_doc_cam_bien (cb_sau, chay_lui, 43, 1 , 1, 100, 105, 25);
  //  delay(500);
  //
  //  //  //THỰC HIỆN 2 QUÀ XANH
  //  chay_do_line_do_encoder (cb_trai, chay_trai, 2700, 0, 170, 165, 30);
  //  chay_do_line_doc_cam_bien(cb_trai, chay_trai, 25, 1 , 1, 100, 105, 25);
  //  delay(500);
  //  chay_do_line_do_encoder (cb_sau, chay_lui, 150, 0, 100, 105, 25);
  //  chay_do_line_doc_cam_bien (cb_sau, chay_lui, 30, 1 , 1, 100, 105, 25);
  //  delay(500);
  //  quay_encoder(quay_phai, 120, 400, 0); //quay phải, tốc độ 120, 400 xung để cảm biến số 36 thoát khỏi line ban đầu
  //  quay_bat_line(quay_phai, 100, 36);    //quay phải, tốc độ 100, bắt cảm biến số 36
  //  delay(1000);
  //  chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 1100, 1, 120, 120, 25);
  //  delay(1000);
  //  chay_do_line_do_encoder (cb_sau, chay_lui, 100, 1, 120, 120, 25);
  //  delay(500);
  //  quay_bat_line(quay_trai, 100, 42);
  //  delay(500);
  //  chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 650, 0, 105, 100, 25);
  //  delay(500);
  //  chay_do_line_doc_cam_bien (cb_phai, chay_phai, 36, 2 , 1, 100, 105, 25);
  //  delay(500);
  //  chay_do_line_do_encoder (cb_truoc_sau, chay_toi, 460, 1, 100, 105, 25);
  //  delay(20000);
}
