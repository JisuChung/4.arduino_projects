void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}//성공코드
#include <cubeplex_plus.h>
#include <mappings.h>
#include <niceTimer.h>

void planarSpin();
void trifade();
int Discrimination(void);
boolean Start = true;
int Tcount = 0;
int Rcolor = 0;
int color;
int h = 0;
int Rx = 0;
int Ry = 0;
int Rz = 0;
int PresentLed[3][3][3];


void setup() {

  initCube();
  animationMax = 100;

  planarSpin();
  Serial.begin(9600);

}

void loop() {
  if (Serial.available() > 0) {
    int st = 0;
    byte r = Serial.read();
    Serial.write(r);
    Serial.println("anything");
    delay(50);
    if (r == '5') {
      st = 1;
    }
    while (st == 1)
    {
      if (r == '5') {
        st = 1;
        Serial.write('s');
        flushBuffer();
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            for (int a = 0; a < 4; a++) {
              PresentLed[i][j][a] = -7;
            }
          }
        }

        //1층에 그려줄 색을 정의
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            int Rcolor = random(0, 3); //랜덤하게 Rcolor를 정해줌
            PresentLed[i][j][0] = Rcolor;// PresentLed [][][]에 Rcolor를 넣어줌
            drawLed((PresentLed[i][j][0]), i, j, 0); //1층에 그리기위해 저장한 색들을 이제 그려준다.
            flushBuffer();
            delay(100);
          }
        }
        delay(1000);
        Rx = random(0, 4);
        Ry = random(0, 4);
        Rz = 1;
        Rcolor = random(0, 3);
        drawLed(Rcolor, Rx, Ry, 1);
        flushBuffer();
        Serial.write('0');
        delay(300);

      }

      r = Serial.read();
      Serial.write(r);
      delay(500);


      //종료
      if (r == '6') {
        Serial.write('e');
        h = 0;
        Rcolor = -7;
        clearBuffer();
        flushBuffer();
        st = 0;

      }
      r = Serial.read();
      Serial.write(r);
      delay(500);

      //x축에서 이동
      if (r == '1' || r == '2') {
        if (r == '1') {
          Serial.write('1');
          if (Rx != 0) {
            drawLed(-7, Rx, Ry, Rz);
            flushBuffer();
            Rx--;
            drawLed(Rcolor, Rx, Ry, Rz);
            flushBuffer();
            delay(200);
          }
        }
        if (r == '2') {
          if (Rx != 3) {
            Serial.write('2');
            drawLed(-7, Rx, Ry, Rz);
            flushBuffer();
            Rx++;
            drawLed(Rcolor, Rx, Ry, Rz);
            flushBuffer();
            delay(200);
          }
        }
      }

      r = Serial.read();
      Serial.write(r);
      delay(500);

      //y축에서 이동
      if (r == '0' || r == '3') {
        if (r == '0') {
          Serial.write('3');
          if (Ry != 3) {
            drawLed(-7, Rx, Ry, Rz);
            flushBuffer();
            Ry++;
            drawLed(Rcolor, Rx, Ry, Rz);
            flushBuffer();
          }
        }
        else if (r == '3') {
          if (Ry != 0) {
            Serial.write('4');
            drawLed(-7, Rx, Ry, Rz);
            flushBuffer();
            Ry--;
            drawLed(Rcolor, Rx, Ry, Rz);
            flushBuffer();

          }
        }
      }

      r = Serial.read();
      Serial.write(r);
      delay(500);

      //다운
      if (r == '4') {
        Serial.write('d');
        int ta = 0; //합쳐야 될 z축 값
        int hap = 1; //합침 유무 확인
        for (int i = 2; i >= 0; i--) {
          drawLed(Rcolor, Rx, Ry, i + 1);
          flushBuffer();
          delay(100);
          drawLed(-7, Rx, Ry, i + 1);
          flushBuffer();
          if (PresentLed[Rx][Ry][i] != -7) { //바로 아래색이 있을때
            int Pcolor = PresentLed[Rx][Ry][i];
            switch (Pcolor) {
              case '0':
                if (Rcolor == '1') {
                  Pcolor = 3;
                  hap = 1;
                }
                else if (Rcolor == '2') {
                  Pcolor = 5;
                  hap = 1;
                }
                break;

              case '1':
                if (Rcolor == '0') {
                  Pcolor = 3;
                  hap = 1;
                }
                else if (Rcolor == '2') {
                  Pcolor = 4;
                  hap = 1;
                }
                break;

              case '2':
                if (Rcolor == '1') {
                  Pcolor = 4;
                  hap = 1;
                }
                else if (Rcolor == '0') {
                  Pcolor = 5;
                  hap = 1;
                }
                break;

              case '3':
                if (Rcolor == '2')
                {
                  Pcolor = 6;
                  hap = 0;
                }
                break;

              case '4':
                if (Rcolor == '0')
                {
                  Pcolor = 6;
                  hap = 0;
                }
                break;

              case '5':
                if (Rcolor == '1')
                {
                  Pcolor = 6;
                  hap = 0;
                }
                break;
            }
            ta = i;
            PresentLed[Rx][Ry][ta] = Pcolor;
            /*변수 hap이 0이면 색이 합쳐졌다는 의미
              현재층의 LEDcolor 값이 6(흰색)이 되면
              0.3초동안 반짝이다가 -7(색X)이 된다.
            */
            if (hap == '0') {
              if (PresentLed[Rx][Ry][ta] == '6') {
                drawLed(6, Rx, Ry, ta);
                flushBuffer();
                delay(300);
                PresentLed[Rx][Ry][ta] = -7;
                drawLed(-7, Rx, Ry, ta);
                flushBuffer();
                delay(300);
                Tcount++;
                //1점 얻은 효과

                if (Tcount == '3')
                {
                  //이겼다는 효과
                  planarSpin();
                  //st 값 0 으로 바꿔서 while 문 탈출
                  st = 0;
                  //h 값을 0으로 바꿔서 start 버튼 눌렀을 때 새 게임으로 넘어감
                  h = 0;
                  Tcount = 0;

                }
                else if ( Tcount != 3)
                {
                  Rx = random(0, 4);
                  Ry = random(0, 4);
                  Rz = 3;
                  Rcolor = random(0, 3);
                  drawLed(Rcolor, Rx, Ry, 1);
                  flushBuffer();
                  Serial.write('1');
                }
              }
              else {
                drawLed(PresentLed[Rx][Ry][ta], Rx, Ry, ta);
                flushBuffer();
                int p, q;
                for (p = 0; p <= 3; p++) {
                  for (q = 0; q <= 3; q++) {
                    if (PresentLed[p][q][3] != '0') {
                      //졌다는 효과
                      trifade();
                      //st값 0으로 바꿔 while 문 탈출
                      st = 0;
                      //h값 0으로 바꿔 새로운 게임
                      h = 0;
                    }
                  }
                }
              }
            }
            /*변수 hap이 0아니면 색이 섞이면 안되므로
              현재층보다 한칸 위에 색이 쌓인다.
            */
            //hap==1안합쳐졌을때
            else {
              drawLed(PresentLed[Rx][Ry][ta + 1], Rx, Ry, ta + 1);
              flushBuffer();
            }
            Rx = random(0, 4);
            Ry = random(0, 4);
            Rz = 3;
            Rcolor = random(0, 3);
            drawLed(Rcolor, Rx, Ry, 1);
            flushBuffer();
            Serial.write('1');

            flushBuffer();
          }
        }
      }
      r = Serial.read();
      Serial.write(r);
      delay(500);
    }
  }
}



//이겼을 때 효과
void planarSpin() {

  int animationSpeed = 50;
  int spinsPerColor = 5; // a spin is actually half a revolution
  int x = 0;
  int y = 0;
  for (int i = 0; i < spinsPerColor; i++) {
    for (int x = 0; x < 3; x++) {
      drawLine(color, x, 0, 0, 3 - x, 3, 0);
      drawLine(color, x, 0, 1, 3 - x, 3, 1);
      drawLine(color, x, 0, 2, 3 - x, 3, 2);
      drawLine(color, x, 0, 3, 3 - x, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int y = 0; y < 3; y++) {
      drawLine(color, 3, y, 0, 0, 3 - y, 0);
      drawLine(color, 3, y, 1, 0, 3 - y, 1);
      drawLine(color, 3, y, 2, 0, 3 - y, 2);
      drawLine(color, 3, y, 3, 0, 3 - y, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
  }
  flushBuffer();
  clearBuffer();
}



//졌을 때 효과
void trifade() {
  continuePattern = true;
  int animationSpeed = 100;
  while (continuePattern) {
    // blue fade out, red fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(blue, 9 - i, 0, 0, 0, 3, 3, 3);
      drawBox(red, i, 0, 0, 0, 3, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // red fade out, green fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(red, 9 - i, 0, 0, 0, 3, 3, 3);
      drawBox(green, i, 0, 0, 0, 3, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // green fade out, blue fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(green, 9 - i, 0, 0, 0, 3, 3, 3);
      drawBox(blue, i, 0, 0, 0, 3, 3, 3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
  }
}
