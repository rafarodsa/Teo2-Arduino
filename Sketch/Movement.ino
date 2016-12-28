MC33887 m1(9, 50, 52);//(pwm (d2), in1, in2)
MC33887 m2(10, 40, 42);//(pwd, en1, en2)
MC33887 m3(11, 30, 32);//(pwd, en1, en2)
Triskar triskar(m1, m2, m3);

int enableMotorsPin = 46;
int enableMotorsPin2 = 36;
int enableMotorsPin3 = 26;

void movementInit() {
  pinMode(9, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(enableMotorsPin, OUTPUT);
  pinMode(enableMotorsPin2, OUTPUT);
  pinMode(enableMotorsPin3, OUTPUT);
}

void Stop() {
  triskar.run(0, 0, 0);
  triskar.stop();
  digitalWrite(enableMotorsPin, LOW);// disattiva motori
  digitalWrite(enableMotorsPin2, LOW);
  digitalWrite(enableMotorsPin3, LOW);

  isTeoMoving = false;
}

//G strafe forward angularSpeed
void Go(int x, int y, int z) {

  triskar.run(x, y, z);//velocità di Spostamento laterale, velocità di avanzamento, velocità angolare
  digitalWrite(enableMotorsPin, HIGH);// disattiva motori
  digitalWrite(enableMotorsPin2, HIGH);
  digitalWrite(enableMotorsPin3, HIGH);

  if (x == 0 && y == 0 && z == 0)
    isTeoMoving = false;
  else
    isTeoMoving = true;
}
