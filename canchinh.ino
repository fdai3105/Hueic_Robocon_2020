void canchinhTruoc() {
  int cc_truoc[6] = {0, 0, 0, 0, 0, 0};
  int temp = 0;
  do {
    doc_cam_bien_do_line(cb_truoc);
    temp = error;

    cc_truoc[0] = digitalRead(22);
    cc_truoc[1] = digitalRead(23);
    cc_truoc[2] = digitalRead(24);
    cc_truoc[3] = digitalRead(25);
    cc_truoc[4] = digitalRead(26);
    cc_truoc[5] = digitalRead(27);

    if (error < 0) {
      //lech phai
      analogWrite(pwm1_toi, 0);
      analogWrite(pwm2_lui, 0);
      analogWrite(pwm1_lui, 60);
      analogWrite(pwm2_toi, 60);
    }

    if (error > 0) {
      //lech trai
      analogWrite(pwm1_lui, 0);
      analogWrite(pwm2_toi, 0);
      analogWrite(pwm1_toi, 60);
      analogWrite(pwm2_lui, 60);
    }
  }
  while (temp != 0);

  analogWrite(pwm1_lui, 0);
  analogWrite(pwm2_lui, 0);
  analogWrite(pwm3_lui, 0);
  analogWrite(pwm4_lui, 0);
  analogWrite(pwm1_toi, 0);
  analogWrite(pwm3_toi, 0);
  analogWrite(pwm2_toi, 0);
  analogWrite(pwm4_toi, 0);
}

void canchinhSau() {
  int cb_sau_1 = 0;
  int cb_sau_2 = 0;
  int temp = 0;
  
  do {
    doc_cam_bien_do_line(cb_sau);
    temp = error;
    
    cb_sau_1 = digitalRead(37);
    cb_sau_2 = digitalRead(36);

    if (error < 0) {
      //lech phai
      analogWrite(pwm3_toi, 0);
      analogWrite(pwm4_lui, 0);
      analogWrite(pwm3_lui, 60);
      analogWrite(pwm4_toi, 60);
    }

    if (error > 0) {
      //lech trai
      analogWrite(pwm3_lui, 0);
      analogWrite(pwm4_toi, 0);
      analogWrite(pwm3_toi, 60);
      analogWrite(pwm4_lui, 60);
    }
  }
  while (temp != 0);

  analogWrite(pwm1_lui, 0);
  analogWrite(pwm2_lui, 0);
  analogWrite(pwm3_lui, 0);
  analogWrite(pwm4_lui, 0);
  analogWrite(pwm1_toi, 0);
  analogWrite(pwm3_toi, 0);
  analogWrite(pwm2_toi, 0);
  analogWrite(pwm4_toi, 0);
}
