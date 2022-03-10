int trig1 = 13;
int trig2 = 12;
int trig3 = 8;
int trig4 = 7;
int echo1 = 11;
int echo2 = 10;
int echo3 = 9;

#define enA 3
#define in1 A0
#define in2 2
#define enB 6
#define in3 4
#define in4 5

int explored = 0;
struct cell{
  byte steps;     
  byte W;
  byte E;
  byte N;
  byte S;
  byte visited;
  //byte target;
};
struct cell cells[8][8];
struct cell sequence[4];
struct cell target_sequence[4];


byte seq_count = 0;


long duration; 
int distance1,distance2,distance3,distance4;
int x_target, y_target;

void setup() {
  Serial.begin(9600);
  
  //GOAL SEQUENCE
target_sequence[0].N = 0; 
target_sequence[0].E = 1;
target_sequence[0].W = 1;
target_sequence[0].S = 0;

target_sequence[1].N = 1; 
target_sequence[1].E = 1;
target_sequence[1].W = 0;
target_sequence[1].S = 0;

target_sequence[2].N = 1; 
target_sequence[2].E = 1;
target_sequence[2].W = 0;
target_sequence[2].S = 0;

target_sequence[3].N = 1; 
target_sequence[3].E = 1;
target_sequence[3].W = 0;
target_sequence[3].S = 0;

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(trig4, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
//  pinMode(echo4, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //digitalWrite(enA, HIGH);
  //digitalWrite(enB, HIGH);
 // analogWrite(enA, 130);
  //analogWrite(enB, 90);

}

void loop() {
 //delay()

   
  analogWrite(enA, 30);
  analogWrite(enB, 30 );
 digitalWrite(trig1, LOW);
 delay(10);
 digitalWrite(trig1, HIGH);
  delayMicroseconds(2);
 digitalWrite(trig1, LOW);
 duration = pulseIn(echo1, HIGH);
 distance1 = duration * 0.034 / 2;
 Serial.print("sensor 1 reading: ");
 Serial.println(distance1);



 digitalWrite(trig2, LOW);
 delayMicroseconds(2);
 digitalWrite(trig2, HIGH);
  delayMicroseconds(2);
 digitalWrite(trig2, LOW);
 duration = pulseIn(echo2, HIGH);
 distance2 = duration * 0.034 / 2;
 Serial.print("sensor 2 reading: ");
 Serial.println(distance2); 




 digitalWrite(trig3, LOW);
 delayMicroseconds(2);
 digitalWrite(trig3, HIGH);
  delayMicroseconds(2);
 digitalWrite(trig3, LOW);
 duration = pulseIn(echo3, HIGH);
 distance3 = duration * 0.034 / 2;
 Serial.print("sensor 3 reading: ");
 Serial.println(distance3);




 digitalWrite(trig4, LOW);
 delayMicroseconds(2);
 digitalWrite(trig4, HIGH);
  delayMicroseconds(2);
 digitalWrite(trig4, LOW);
// duration = pulseIn(echo4, HIGH);
 distance4 = duration * 0.034 / 2;
 Serial.print("sensor 4 reading: ");
 Serial.println(distance4);

 //if(distance1 < 10)
   // Stop();
 //else
  //BACKWARD();   
  //delay (1000)
  //Stop();
  //delay(10);
  //backward();
  //delay(100);
  Step();
  Stop();
  
}



void Step(){
  
  digitalWrite(in1,0);
  digitalWrite(in3,0);
  digitalWrite(in2,1);
  digitalWrite(in4,1);
  
  delay(1000);
  
  }
void Stop(){
  digitalWrite(in1,0);
  digitalWrite(in3,0);
  digitalWrite(in2,0);
  digitalWrite(in4,0);
  delay(3000);
}


void left(){
  digitalWrite(in1,1);
  digitalWrite(in3,0);
  digitalWrite(in2,0);
  digitalWrite(in4,1);
  delay(10);
}

void right(){
  digitalWrite(in1,0);
  digitalWrite(in3,1);
  digitalWrite(in2,1);
  digitalWrite(in4,0);
 delay(10);
}

void forward()
{
  digitalWrite(in1,0);
  digitalWrite(in3,0);
  digitalWrite(in2,1);
  digitalWrite(in4,1);
  delay(100);
}

void backward(){
 
  digitalWrite(in1,1);
  digitalWrite(in3,1);
  digitalWrite(in2,0);
  digitalWrite(in4,0);
  delay(100);

}

void firstRun(){
  int x=0, y=0;
  while(explored < 63){
    setWalls(x,y);
    nextCell(x,y);
    cells[x][y].visited = 99;
    check_sequence(x,y);
    
  }
  calculateSteps();
  
}

void calculateSteps(){
  if(cells[x_target][y_target].steps == 0){
    for(int i= 0; i <= 9; i ++){
      cells[x_target][y_target + 1];
      
      }
    
    }
  

}

void setWalls(int posX, int posY){
  if(distance1 < 10)
    cells[posX][posY].N = 1;
  else
    cells[posX][posY].N = 0;

  if(distance2 < 10)
    cells[posX][posY].W = 1;
  else
    cells[posX][posY].W = 0;

  if(distance3 < 10)
    cells[posX][posY].E = 1;
  else
    cells[posX][posY].E = 0;

 cells[posX][posY].S = 1;
 sequence[seq_count] =  cells[posX][posY];
 seq_count ++;
 if(seq_count == 4)
    seq_count = 0;
 
 Serial.print("POSITION  ");
 Serial.print(posX); Serial.print(posY);
}

void check_sequence (int posX, int posY){
  //if(sequence[0] == target_sequence[0] && sequence[1] == target_sequence[1] && sequence[2] == target_sequence[2] && sequence[3] == target_sequence[3])
 //{     
      cells[posX][posY].steps = 0;  
      x_target = posX;
      y_target = posY;
 //}
}

void traverse(){
  
}

void nextCell(int posX, int posY){
  //moves robot to next appropriate position and sets x,y
  if(cells[posX][posY].visited!=99){
    cells[posX][posY].visited = 99; //set the visited variable to true(99)
    ++explored;                     //increase the explored count
  }
}
